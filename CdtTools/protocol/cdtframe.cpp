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

QByteArray CDTFrame::toAllByteArray()
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

ControlEntity::ControlEntity()
{}


void ControlEntity::setValue(uint8_t control, uint8_t type, uint8_t dataNum, uint8_t sourceAddr, uint8_t destAddr)
{
    this->control = control;
    this->type = type;
    this->dataNum = dataNum;
    this->sourceAddr = sourceAddr;
    this->destAddr = destAddr;
    this->crcCode = CheckHelper::CheckCRC8(reinterpret_cast<uchar*>(this->toBytes().data()), 0, 5);
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

void InfoFieldEntity::setValue(uint8_t funCode, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
    this->funCode = funCode;
    this->dataArray[0] = d0;
    this->dataArray[1] = d1;
    this->dataArray[2] = d2;
    this->dataArray[3] = d3;
    this->crcCode = CheckHelper::CheckCRC8(reinterpret_cast<uchar*>(this->toBytes().data()), 0, 5);
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

