#include "cdtframe.h"
#include "checkhelper.h"

uint8_t CDTFrame::header[7] = {0xEB, 0x90, 0xEB, 0x90, 0xEB, 0x90, 0x00};

CDTFrame::CDTFrame()
{

}


QByteArray CDTFrame::toByteArray()
{
    QByteArray rawArray;
    for (int i = 0; i < 6; i++) {
        rawArray.append(CDTFrame::header[i]);
    }
    rawArray.append(this->frameControl.control);
    rawArray.append(this->frameControl.type);
    rawArray.append(this->frameControl.dataNum);
    rawArray.append(this->frameControl.sourceAddr);
    rawArray.append(this->frameControl.destAddr);
    rawArray.append(this->frameControl.crcCode);

    return rawArray;
}

QByteArray CDTFrame::toAllByteArray() const
{
    QByteArray rawArray;
    for (int i = 0; i < 6; i++) {
        rawArray.append(CDTFrame::header[i]);
    }
    rawArray.append(this->frameControl.control);
    rawArray.append(this->frameControl.type);
    rawArray.append(this->frameControl.dataNum);
    rawArray.append(this->frameControl.sourceAddr);
    rawArray.append(this->frameControl.destAddr);
    rawArray.append(this->frameControl.crcCode);
    for (const InfoFieldEntity &entity : this->infoFields) {
        rawArray.append(entity.funCode);
        rawArray.append(entity.dataArray[0]);
        rawArray.append(entity.dataArray[1]);
        rawArray.append(entity.dataArray[2]);
        rawArray.append(entity.dataArray[3]);
        rawArray.append(entity.crcCode);
    }

    return rawArray;
}

eCDTParseResult CDTFrame::parseBytesToFrame(QByteArray &data, int &index, QString &errorMsg)
{
    // 1、解析头
    // 查找是否有帧头
    index = data.indexOf(reinterpret_cast<char *>(CDTFrame::header));
    if (index == -1)
    {
        // 未找到帧头
        if (data.size() >= FIELD_LENGTH)
        {
            errorMsg = QString("接受数据帧头部错误,为找到帧头, 接收到的数据帧长度为%1").arg(data.size());
            data.clear();
        }
        return eCDTParseResult::HeaderError;
    }

    index += FIELD_LENGTH;

    // 2、控制字
    // 控制字断帧
    if (data.size() - index < FIELD_LENGTH)
    {
        return eCDTParseResult::PartOfFrame;
    }

    // 控制字完整则校验、接收
    frameControl.fillData(data.at(index), data.at(index + 1), data.at(index + 2),
                                data.at(index + 3), data.at(index + 4));
    index += FIELD_LENGTH;
    if (frameControl.crcCode != static_cast<uint8_t>(data.at(index - 1)))
    {
        index += frameControl.dataNum * FIELD_LENGTH;
        data.remove(0, index);
        errorMsg = QString("控制字校验错误, 接收到的校验码为%1，实际校验码为%2").arg(data.at(index - 1)).arg(frameControl.crcCode);
        return eCDTParseResult::ControlCrcError;
    }

    // 3、解析信息字
    if (data.size() - index < frameControl.dataNum * FIELD_LENGTH)
    {
        return eCDTParseResult::PartOfFrame;
    }

    for (uint8_t i = 0; i < frameControl.dataNum; ++i)
    {
        InfoFieldEntity entity(static_cast<uint8_t>(data.at(index)), reinterpret_cast<uint8_t*>(data.data() + index + 1));

        index += FIELD_LENGTH;
        if (entity.crcCode != static_cast<uint8_t>(data.at(index - 1)))
        {
            index += (frameControl.dataNum - i - 1) * FIELD_LENGTH;
            errorMsg = QString("信息字校验错误, 接收到的校验码为%1，实际校验码为%2").arg(data.at(index - 1)).arg(entity.crcCode);
            data.remove(0, index);
            return eCDTParseResult::InfoCrcError;
        }
        infoFields.append(entity);
    }

    return eCDTParseResult::CompleteFrame;
}

CDTFrame CDTFrame::createYKFrame(uint8_t ctrlCode, uint8_t type, uint8_t funCode, uint8_t operCode, uint8_t ptId)
{
    CDTFrame frame;
    // 循环填三个信息字
    for (int i = 0; i < 3; ++i)
    {
        InfoFieldEntity entity;
        entity.fillData(funCode, operCode, ptId, operCode, ptId);
        frame.infoFields.append(entity);
    }
    frame.frameControl.fillData(ctrlCode, type, frame.infoFields.count(), 0, 0);
    return frame;
}

ControlEntity::ControlEntity()
{}


void ControlEntity::fillData(uint8_t control, uint8_t type, uint8_t dataNum, uint8_t sourceAddr, uint8_t destAddr)
{
    this->control = control;
    this->type = type;
    this->dataNum = dataNum;
    this->sourceAddr = sourceAddr;
    this->destAddr = destAddr;
    this->crcCode = CheckHelper::CheckCRC8(reinterpret_cast<uchar*>(this->toBytes().data()), 0, 5);
}

void ControlEntity::calcCrc()
{
    uchar buf[5] = {0};
    buf[0] = control;
    buf[1] = type;
    buf[2] = dataNum;
    buf[3] = sourceAddr;
    buf[4] = destAddr;
    crcCode = CheckHelper::CheckCRC8(buf, 0, sizeof(buf) / sizeof(uchar));
}

QByteArray ControlEntity::toBytes()
{
    QByteArray bytes(5, '\0');
    bytes[0] = control;
    bytes[1] = type;
    bytes[2] = dataNum;
    bytes[3] = sourceAddr;
    bytes[4] = destAddr;

    return bytes;
}

InfoFieldEntity::InfoFieldEntity()
{

}

InfoFieldEntity::InfoFieldEntity(uint8_t code, uint8_t data[])
{
    funCode = code;
    memcpy(dataArray, data, sizeof(dataArray) / sizeof(uint8_t));
    crcCode = CheckHelper::CheckCRC8(reinterpret_cast<uchar*>(this->toBytes().data()), 0, 5);

}

void InfoFieldEntity::fillData(uint8_t funCode, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
    this->funCode = funCode;
    this->dataArray[0] = d0;
    this->dataArray[1] = d1;
    this->dataArray[2] = d2;
    this->dataArray[3] = d3;
    this->crcCode = CheckHelper::CheckCRC8(reinterpret_cast<uchar*>(this->toBytes().data()), 0, 5);
}

void InfoFieldEntity::calcCrc()
{
    crcCode = CheckHelper::CheckCRC8(reinterpret_cast<uchar*>(this->toBytes().data()), 0, 5);
}

QByteArray InfoFieldEntity::toBytes()
{
    QByteArray bytes(5, '\0');

    bytes[0] = funCode;
    for (int i = 0; i < 4; ++i) {
        bytes[i + 1] = dataArray[i];
    }

    return bytes;
}

