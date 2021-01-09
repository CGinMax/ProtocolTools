#include "cdtprotocol.h"
#include <QtMath>
#include <QThread>
#include <QMutexLocker>
#include "../network/tcpserver.h"

CDTProtocol::CDTProtocol(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : ProtocolBase(network, settingData)
{

}

CDTProtocol::~CDTProtocol()
{
    delete m_timer;
    m_timer = nullptr;
}

void CDTProtocol::run()
{

    /**
     * 检查是否链接
     * 处理命令
     * 读取bytes里面的数据
     * 解析
     * 循环发送
     */
    if (!m_network->isActived()) {
        QThread::msleep(2000);// 2s
    }

    if (!initConnection()) {
        return;
    }
    // 处理命令
    processCommand();

    auto bytes = m_network->readAll();

    if (!bytes.isEmpty()) {
        m_recvBuffer.append(bytes);
        //处理数据
        parseRecvData();
    }
    // 处理帧
    processFrame();

    if (m_settingData->m_stationType == eStationType::Minitor) {
        sendAllAi();
        sendAllDi();
    }

}

void CDTProtocol::start()
{
    if (!m_timer) {
        m_timer = new QTimer;
        QObject::connect(m_timer, &QTimer::timeout, [this](){
            this->run();
        });
    }
    m_timer->start(100);
}

void CDTProtocol::stop()
{
    if (m_timer->isActive()) {
        QMetaObject::invokeMethod(m_timer, &QTimer::stop);

    }
}

void CDTProtocol::processCommand()
{

}

void CDTProtocol::parseRecvData()
{
    QMutexLocker locker(&m_mtx);
    // buffer中有数据开始解析
    while (m_recvBuffer.size() > 0)
    {
        if (parseToFrame() != eCDTParseResult::CompleteFrame) {
            break;
        }
    }
}

eCDTParseResult CDTProtocol::parseToFrame()
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
    frame.frameControl.fillData(m_recvBuffer.at(index), m_recvBuffer.at(index + 1), m_recvBuffer.at(index + 2),
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
        entity.fillData(m_recvBuffer.at(index), m_recvBuffer.at(index + 1), m_recvBuffer.at(index + 2),
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

void CDTProtocol::processFrame()
{
    while (!m_frameQueue.isEmpty()) {
        CDTFrame frame = m_frameQueue.dequeue();

        switch (frame.frameControl.type)
        {
        // 0x61，遥测
        case eCDTFrameType::RmtMeasurement:
            showMessageBuffer(eMsgType::eMsgRecv, "接收到遥测帧，正在处理...", frame.toAllByteArray());
            yxResponse(frame.infoFields);
            break;

        // 0xF4,遥信
        case eCDTFrameType::RmtInformation:
            if (m_settingData->m_stationType == eStationType::WF) {
                showMessageBuffer(eMsgType::eMsgRecv, "接收到遥信帧，正在处理...", frame.toAllByteArray());
                yxResponse(frame.infoFields);
            } else if (m_settingData->m_stationType == eStationType::Minitor) {
                // 监控接收虚遥信

            }
            break;

        case eCDTFrameType::RmtControlType:
            ykResponse(frame);
            break;

        default :
            break;
        }
    }

}


void CDTProtocol::send(CDTFrame &frame)
{
    QByteArray bytes = frame.toAllByteArray();

    if (bytes.size() > 0) {
        if (m_network->write(bytes)) {
            return ;
        }
    }
}

void CDTProtocol::sendAllDi()
{
    if (m_settingData->m_ptCfg->m_globalDiList->isEmpty()) {
        return ;
    }
    auto frame = buildYXFrame(m_settingData->m_ptCfg->m_yxFuncode);
    // 标准虚遥信
    frame.frameControl.fillData(m_settingData->m_ptCfg->m_controlType, m_settingData->m_ptCfg->m_yxFrameType, frame.infoFields.size(), 0, 0);
    showMessageBuffer(eMsgType::eMsgSend, "发送全遥信", frame.toAllByteArray());
    send(frame);
}

void CDTProtocol::sendAllAi()
{

    CDTFrame frame;

    uint8_t curCode = m_settingData->m_ptCfg->m_ycFuncode;

    int aiNum = m_settingData->m_ptCfg->m_globalAiList->size();
    int n = 0;
    while (n < aiNum && curCode < 0x80)
    {
        uint8_t ptBinaryArr[4] = {0, 0, 0, 0};
        for (int j = 0; j < 2 && n < aiNum; j++)
        {
            int ycValue = (*m_settingData->m_ptCfg->m_globalAiList)[n].value();
            uint8_t valueBytes[2]{0};
            ptBinaryArr[j * 2] = ycValue >> 8;
            ptBinaryArr[j * 2 + 1] = ycValue;

//            bool sign = ptValue < 0 ? true : false;

//            bool overflow = false;
//            uint16_t transValue = ptValue;
//            // 溢出
//            if (ptValue > 0x03FF || ptValue < -0x03FF) {
//                overflow = true;
//            }
//            // 负数
//            if (sign)
//            {
//                // 取反加1
//                transValue = -ptValue;
//                transValue = ~transValue;
//                transValue++;
//            }

//            // 拼接发送数据的字节
//            uint16_t byteValue = valid ? 0 : 1;
//            // 溢出位
//            byteValue = (byteValue << 1) | overflow;
//            // 符号位
//            byteValue = (byteValue << 4) | sign;
//            // 拼接数据位
//            byteValue = (byteValue << 10) | (transValue & 0x03FF);
//            // 低位字节在后，高位字节在前
//            ptBinaryArr[j * 2 + 1] = (uint8_t)byteValue;
//            ptBinaryArr[j * 2] = (uint8_t)(byteValue >> 8);
            n++;
        }

        InfoFieldEntity entity(curCode, ptBinaryArr);
        frame.infoFields.append(entity);
        curCode++;
    }

    frame.frameControl.fillData(eCDTFrameControlType::StandardType, eCDTFrameType::RmtMeasurement, frame.infoFields.size(), 0, 0);
    showMessageBuffer(eMsgType::eMsgSend, "发送全遥测", frame.toAllByteArray());
    send(frame);

}

void CDTProtocol::sendVirtualYX()
{
    if (m_settingData->m_ptCfg->m_globalDiList->isEmpty()) {
        return ;
    }
    auto frame = buildYXFrame(m_settingData->m_ptCfg->m_vyxFuncode);
    // 标准虚遥信
    frame.frameControl.fillData(m_settingData->m_ptCfg->m_controlType, m_settingData->m_ptCfg->m_vyxFrameType, frame.infoFields.size(), 0, 0);
    showMessageBuffer(eMsgType::eMsgSend, "发送虚遥信", frame.toAllByteArray());
    send(frame);
}

void CDTProtocol::yxResponse(QList<InfoFieldEntity> &infoFieldList)
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
            // 0号开始
            if(nSeq <  m_settingData->m_ptCfg->m_globalDiList->size()) {
                (*m_settingData->m_ptCfg->m_globalDiList)[nSeq].setValue(yxValue>0);
            }
        }
    }

}

void CDTProtocol::ycResponse(QList<InfoFieldEntity> &infoFieldList)
{
    for (InfoFieldEntity &entity : infoFieldList)
    {
        int nSeq = 0;
        double ycAccept = 0;

        for (int i = 0; i < 4; i += 2)
        {
            uint8_t valueBytes[2]{0};
            valueBytes[0] = entity.dataArray[i + 1];
            valueBytes[1] = entity.dataArray[i];
            memcpy(&ycAccept, valueBytes, 2);
            // 点号
            nSeq = entity.funCode + (i / 2) + 1;
            if (nSeq < m_settingData->m_ptCfg->m_globalAiList->size()) {
                (*m_settingData->m_ptCfg->m_globalAiList)[nSeq].setValue(nSeq);
            }

        }
    }
}

void CDTProtocol::ykResponse(CDTFrame &frame)
{
//    InfoFieldEntity firstInfoData = frame.infoFields.front();
//    uint8_t funCode = firstInfoData.funCode;
//    uint8_t ctrlCode = firstInfoData.dataArray[0];
//    // true开,false关
//    bool status = ctrlCode == eControlLockCode::CloseValidLock;
//    int ptId = firstInfoData.dataArray[2];
//    ptId |= firstInfoData.dataArray[3] << 8;

//    // 遥控执行
//    auto frameBytes = frame.toAllByteArray();
//    //ShowMsgArray(eMsgType::eMsgRecv, "接收到遥控帧，正在处理...", frameBytes, frameBytes.count());
//    switch (funCode) {
//    case eCDTFunCode::RmtControlSelectCode:
//        ykSelectBack(ctrlCode, static_cast<uint8_t>(ptId));
//        break;
//    case eCDTFunCode::RmtControlBackCode:
//        yKExecute(ctrlCode, static_cast<uint8_t>(ptId));
//        break;

//    case eCDTFunCode::RmtControlExecuteCode:
//    {
//        // TODO: 执行遥控变位
//    }
//        break;
//    case eCDTFunCode::RmtControlCancelCode:
//    {
//    }
//        break;
//    }
}

void CDTProtocol::ykSelect(uint8_t operCode, uint8_t ptNo)
{
    auto frame = interactYKFrame(eCDTFrameControlType::StandardType,eCDTFrameType::RmtControlType, eCDTFunCode::RmtControlSelectCode, operCode, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控选择"), frame.toAllByteArray());
    send(frame);
}

void CDTProtocol::ykSelectBack(uint8_t operCode, uint8_t ptNo)
{
    auto frame = interactYKFrame(eCDTFrameControlType::StandardType,eCDTFrameType::RmtControlType, eCDTFunCode::RmtControlBackCode, operCode, ptNo);
    //    Send(frame, QStringLiteral("遥控选择应答"));
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控选择应答"), frame.toAllByteArray());
    send(frame);
}

void CDTProtocol::yKExecute(uint8_t operCode, uint8_t ptNo)
{
    auto frame = interactYKFrame(eCDTFrameControlType::StandardType,eCDTFrameType::RmtControlType, eCDTFunCode::RmtControlExecuteCode, operCode, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控执行"), frame.toAllByteArray());
    send(frame);
}

void CDTProtocol::yKCancel(uint8_t operCode, uint8_t ptNo)
{
    auto frame = interactYKFrame(eCDTFrameControlType::StandardType,eCDTFrameType::RmtControlType, eCDTFunCode::RmtControlCancelCode, operCode, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控取消"), frame.toAllByteArray());
    send(frame);
}


CDTFrame CDTProtocol::interactYKFrame(uint8_t ctrlCode, uint8_t type, uint8_t funCode, uint8_t operCode, uint8_t ptId)
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

void CDTProtocol::yKNotAllow(int ptId)
{
    CDTFrame frame = createCycleYKFrame(false, ptId);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控闭锁命令"), frame.toAllByteArray());
    send(frame);
}

void CDTProtocol::yKAllNotAllow()
{
    CDTFrame frame = createCycleYKFrame(true);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控全闭锁命令"), frame.toAllByteArray());
    send(frame);
}

CDTFrame CDTProtocol::buildYXFrame(uint8_t startFuncode)
{
    QList<uchar> combineByteList;
    uchar val = 0;
    int index = 0;
    for (const auto& di: *m_settingData->m_ptCfg->m_globalDiList) {
        if (index % 8 == 0) {
            combineByteList.append(val);
            val = 0;
            index = 0;
        }
        bool diVal = di.value();
        if (diVal) {
            val |= (1 << index % 8);
        }
        index++;
    }
    if ((index - 1) % 8 != 0) {
        combineByteList.append(val);
    }
    int offset = combineByteList.count() % 4;
    if (offset != 0) {
        for (int i = 0; i < 4 - offset; i++) {
            combineByteList.append(0);
        }
    }

    uint8_t funCode = startFuncode;
    CDTFrame frame;
    for (int j = 0; j < combineByteList.count() / 4; j++)
    {
        InfoFieldEntity entity;
        entity.fillData(funCode, combineByteList.at(j * 4), combineByteList.at(j * 4 + 1), combineByteList.at(j * 4 + 2), combineByteList.at(j * 4 + 2));
        frame.infoFields.append(entity);
        funCode++;
    }
    return frame;
}

CDTFrame CDTProtocol::createCycleYKFrame(bool isAllPoint, int ptId)
{
    CDTFrame cmdFrame;

    uint8_t infoFieldCount = 0;
    if (isAllPoint) {
        int doCount = 0;
        // TODO:获取Di数量
        //    for (const auto& dev : RtuObj->ListDev) {
        //        doCount += dev->ListDo.size();
        //    }
        infoFieldCount = qRound(static_cast<double>(doCount) / 32.0);
    }
    else {
        infoFieldCount = qRound(static_cast<double>(ptId) / 32.0);
    }

    // 0xF0-0xFF, 16
    uint8_t funCode = infoFieldCount < 16 ? 0xF0 : 0x80;
    // 设置控制字值
    cmdFrame.frameControl.fillData(eCDTFrameControlType::StandardType, 0xF1, infoFieldCount, 0, 0);
    // 填充空数据
    for (uint8_t i = 0; i < infoFieldCount; i++) {
        uint8_t datas[4] = {0, 0, 0, 0};

        InfoFieldEntity entity(funCode, datas);
        funCode++;
        cmdFrame.infoFields.append(entity);
    }
    return  cmdFrame;
}

double CDTProtocol::bcdToValue(int bcdValue)
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

uint32_t CDTProtocol::valueToBCD(double value)
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
