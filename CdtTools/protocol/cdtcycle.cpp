#include "cdtcycle.h"
#include <QtMath>
CDTCycle::CDTCycle()
{

}

void CDTCycle::parseRecvData()
{
    // buffer中有数据开始解析
    while (m_recvBuffer.size() > 0)
    {
        if (parseToFrame() != eCDTParseResult::CompleteFrame) {
            break;
        }
        // 处理帧
        processFrame();
    }
}

eCDTParseResult CDTCycle::parseToFrame()
{
    CDTFrame frame;
    int index = 0;

    // 1、解析头
    // 查找是否有帧头
    index = m_recvBuffer.indexOf(reinterpret_cast<char *>(CDTFrame::header));
    if (index == -1)
    {
        // 未找到帧头
        if (m_recvBuffer.size() >= FIELD_LENGTH)
        {
            //LogInfo(QString("接受数据帧头部错误,为找到帧头"), QString("接收到的数据帧长度为%1").arg(m_recvBuffer.size()));
            m_recvBuffer.clear();
        }
        return eCDTParseResult::HeaderError;
    }

    index += FIELD_LENGTH;

    // 2、控制字
    // 控制字断帧
    if (m_recvBuffer.size() - index < FIELD_LENGTH)
    {
        return eCDTParseResult::PartOfFrame;
    }

    // 控制字完整则校验、接收
    frame.frameControl.setValue(m_recvBuffer.at(index), m_recvBuffer.at(index + 1), m_recvBuffer.at(index + 2),
                                m_recvBuffer.at(index + 3), m_recvBuffer.at(index + 4));
    index += FIELD_LENGTH;
    if (frame.frameControl.crcCode != static_cast<uint8_t>(m_recvBuffer.at(index - 1)))
    {
        index += frame.frameControl.dataNum * FIELD_LENGTH;
        m_recvBuffer.remove(0, index);
        //LogInfo(QString("控制字校验错误"));
        return eCDTParseResult::ControlCrcError;
    }


    // 3、解析信息字
    if (m_recvBuffer.size() - index < frame.frameControl.dataNum * FIELD_LENGTH)
    {
        return eCDTParseResult::PartOfFrame;
    }

    InfoFieldEntity entity;
    for (int i = 0; i < (int)frame.frameControl.dataNum; ++i)
    {
        entity.setValue(m_recvBuffer.at(index), m_recvBuffer.at(index + 1), m_recvBuffer.at(index + 2),
                        m_recvBuffer.at(index + 3), m_recvBuffer.at(index + 4));

        index += FIELD_LENGTH;
        if (entity.crcCode != static_cast<uint8_t>(m_recvBuffer.at(index - 1)))
        {
            index += (frame.frameControl.dataNum - i - 1) * FIELD_LENGTH;
           // LogInfo(QString("信息字校验错误"), QString("接收到的校验码为%1，实际校验码为%2").arg(m_recvBuffer.at(index - 1)).arg(entity.crcCode));
            m_recvBuffer.remove(0, index);
            return eCDTParseResult::InfoCrcError;
        }
        frame.infoFields.append(entity);
    }

    m_recvBuffer.remove(0, index);
    m_frameQueue.enqueue(frame);

    return eCDTParseResult::CompleteFrame;
}

void CDTCycle::processFrame()
{
    CDTFrame frame = m_frameQueue.dequeue();

    QByteArray ba = frame.toAllByteArray();

    //CallbackResponse(frame);

    switch (frame.frameControl.type)
    {
    // 0x61，遥测
    case eCDTFrameType::RmtMeasurement:
        //ShowMsgArray(eMsgType::eMsgRecv, "接收到遥测帧，正在处理...", ba, ba.size());
        yxResponse(frame.infoFields);
        break;

    // 0x85,遥信
    case eCDTFrameType::RmtInformation:
        //ShowMsgArray(eMsgType::eMsgRecv, "接收到遥信帧，正在处理...", ba, ba.size());
        yxResponse(frame.infoFields);
        break;

    case eCDTFrameType::ACCType:
        //ShowMsgArray(eMsgType::eMsgRecv, "接收到电度量，正在处理...", ba, ba.size());
        accResponse(frame.infoFields);
        break;

    default :
        break;
    }

}

void CDTCycle::ykCommand(uint8_t ctrlCode, uint8_t objNo)
{
//    ykAckTimer = GlobalVar::SecondCounter;

    createCmdFrame(eCDTFrameType::RmtControlSelectType, eCDTFunCode::RmtControlSelectCode, ctrlCode, objNo);

}

void CDTCycle::createCmdFrame(uint8_t type, uint8_t funCode, uint8_t ctrlCode, uint8_t objNo)
{
    CDTFrame cmdFrame;
    // 设置控制字值
    cmdFrame.frameControl.setValue(eCDTFrameControlType::StandardType, type, 0x03, 0, 0);

    for (int i = 0; i < cmdFrame.frameControl.dataNum; ++i)
    {
        InfoFieldEntity entity;
        // 设置信息字值
        entity.setValue(funCode, ctrlCode, objNo, ctrlCode, objNo);

        cmdFrame.infoFields.append(entity);
    }

    QByteArray frameBytes = cmdFrame.toAllByteArray();
    //ShowMsgArray(eMsgType::eMsgSend, QString("发送命令"), frameBytes, frameBytes.size());

    //sendFrameQueue.push_back(cmdFrame);
}

void CDTCycle::yxResponse(QList<InfoFieldEntity> &infoFieldList)
{

    for (InfoFieldEntity &entity : infoFieldList) {
        // 当前信息字的遥信点起始地址,funCode：F0-FF
        int curPointStartAddr = (entity.funCode & 0x0F) * 32;
        int nSeq = 0; // 遥信点号
        uint8_t yxValue = 0;// 遥信值1bit

        // 将四个无符号char放到四个字节的无符号int中
        uint combineNum = 0;
        for (int i = 0; i < 4; ++i)
        {
            combineNum |= entity.dataArray[i] << (i * 8);
        }

        // 从int中读取每一位
        for (int i = 0; i < 32; ++i)
        {
            yxValue = (combineNum >> i) & 0x01; // 从最低位开始获取每一位

            nSeq = curPointStartAddr + i + 1;  // 点号
            // TODO
        }
    }

}

void CDTCycle::ycResponse(QList<InfoFieldEntity> &infoFieldList)
{
    for (InfoFieldEntity &entity : infoFieldList)
    {
        int nSeq = 0;
        int16_t ycAccept = 0;
        bool valid = false;
        bool overflow = false;

        for (int i = 0; i < 4; i += 2)
        {
            // 将两个字节合并到16位的整数中
            uint16_t combineNum = entity.dataArray[i + 1];
            combineNum = (combineNum << 8) | entity.dataArray[i];
            // 点号
            nSeq = entity.funCode + (i / 2) + 1;

            // 0~11为有效数据
            ycAccept = (combineNum & 0x03FF);
            // 解析符号位
            uint8_t sig = (combineNum >> 10) & (uint8_t)0x01;
            if (sig)
            {
                // 负号，减1取反
                ycAccept--;
                ycAccept = int16_t((~ycAccept) & 0x03FF);
                ycAccept = -ycAccept;
            }
            // 该遥测值是否有效
            valid = !(combineNum >> 14 & 0x01);
            // 该遥测值是否溢出
            overflow = combineNum >> 13 & 0x01;

            // TODO

        }
    }
}

void CDTCycle::accResponse(QList<InfoFieldEntity> &infoFieldList)
{
    for (InfoFieldEntity &entity : infoFieldList)
    {
        // 点号
        int nSeq = entity.funCode - eCDTFunCode::ACCStartCode;
        // 有效值
        bool valid = (entity.dataArray[3] >> 7) & 0x01;
        // 是否为bcd
        bool bcd = (entity.dataArray[3] >> 5) & 0x01;

        int combineNum = entity.dataArray[2];
        combineNum = (combineNum << 8) | entity.dataArray[1];
        combineNum = (combineNum << 8) | entity.dataArray[0];

        double value = 0.0;
        if (bcd)
        {
            // 根据规约BCD格式转换
            value = bcdToValue(combineNum);
        }
        else
        {
            value = static_cast<double>(combineNum);
        }

    }
}

double CDTCycle::bcdToValue(int bcdValue)
{
    // 每4位对应一个量级，最低从10^-2开始
    // |10^-1|10^-2|bit7~0|
    // |10^1 |10^0 |bit15~8|
    // |10^3 |10^2 |bit23~16|
    double value = 0.0;
    // 交换第一个和第三个字节
    uint32_t firstByte = bcdValue & 0xFF;
    bcdValue &= 0xFFFF00;
    bcdValue = bcdValue | (uint8_t(bcdValue >> 16) & 0xFF);
    bcdValue &= 0x00FFFF;
    bcdValue |= firstByte << 16;
    // 对每四位进行转换
    for (int i = 0; i < 6; i++) {
        uint8_t v = bcdValue & 0x0F;
        bcdValue = bcdValue >> 4;
        value += double(v) * qPow(10.0, (double)(i - 2));
    }

    return value;
}

uint32_t CDTCycle::valueToBCD(double value)
{
    // 每4位对应一个量级，最低从10^-2开始
    // |10^-1|10^-2|bit7~0|
    // |10^1 |10^0 |bit15~8|
    // |10^3 |10^2 |bit23~16|
    uint32_t combineNum = 0;
    int transformNum = 100 * value;
    for (int i = 0; i < 6; i+=2) {
        // 将每一位数转为十六进制，并按每四位存放一个数
        uint8_t first = transformNum % 10;
        transformNum /= 10;
        uint8_t second = transformNum % 10;
        transformNum /= 10;
        second = second << 4 | first;

        // 低位在前
        combineNum = combineNum << 8;
        combineNum |= second;
    }
    return combineNum;
}
