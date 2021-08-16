﻿#include "cdtprotocol.h"
#include <QtMath>
#include <QVector>
#include "cdtmintorstrategy.h"
#include "cdtwfstrategy.h"

CDTProtocol::CDTProtocol(const QSharedPointer<CommunicationBase> &network, const QSharedPointer<SettingData> &settingData)
    : ProtocolBase(network, settingData)
    , m_isRunYK(false)
{

    connect(m_network.data(), &CommunicationBase::disconnected, this, &CDTProtocol::onDisconnected, Qt::BlockingQueuedConnection);

}

CDTProtocol::~CDTProtocol()
{

}

void CDTProtocol::initStrategy()
{
    if (m_settingData->m_stationType == eStationType::WF) {
        m_strategy = new CDTWFStrategy(this, this);
    } else {
        m_strategy = new CDTMintorStrategy(this, this);
    }
    connect(this, &ProtocolBase::sendYk, m_strategy, &StrategyBase::sendYK);
}

void CDTProtocol::run()
{
    m_strategy->uploadTiming();
}

void CDTProtocol::parseRecvData()
{
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
    QString error;
    eCDTParseResult result = frame.parseBytesToFrame(m_recvBuffer, index, error);
    if (result == eCDTParseResult::CompleteFrame) {
        m_recvBuffer.remove(0, index);
        m_frameQueue.enqueue(frame);
    }
    else if (!error.isEmpty()) {
        qInfo("%s", qPrintable(error));
    }
    return result;
}

void CDTProtocol::processFrame()
{
    while (!m_frameQueue.isEmpty()) {
        CDTFrame frame = m_frameQueue.dequeue();
        uint8_t ykType = m_settingData->m_stationType == eStationType::WF ? m_settingData->m_ptCfg->m_ykReqType : m_settingData->m_ptCfg->m_ykAckType;

        if (frame.frameControl.type == m_settingData->m_ptCfg->m_ycFrameType) {
            showMessageBuffer(eMsgType::eMsgRecv, QStringLiteral("接收到遥测帧，正在处理..."), frame.toAllByteArray());
            ycResponse(frame.infoFields);
        }
        else if (frame.frameControl.type == m_settingData->m_ptCfg->m_yxFrameType) {
            if (m_settingData->m_stationType == eStationType::WF) {
                showMessageBuffer(eMsgType::eMsgRecv, QStringLiteral("接收到遥信帧，正在处理..."), frame.toAllByteArray());
                yxResponse(frame.infoFields);
            } else if (m_settingData->m_stationType == eStationType::Minitor) {
                showMessageBuffer(eMsgType::eMsgRecv, QStringLiteral("接收到虚遥信，正在处理..."), frame.toAllByteArray());
                // 监控接收虚遥信
                vyxResponse(frame.infoFields);
            }
        }
        else if (frame.frameControl.type == ykType) {
            showMessageBuffer(eMsgType::eMsgRecv, QStringLiteral("接收到遥控帧，正在处理..."), frame.toAllByteArray());
            m_strategy->ykResponse(frame);

        }
        else if (frame.frameControl.type == m_settingData->m_ptCfg->m_vyxFrameType) {
            showMessageBuffer(eMsgType::eMsgRecv, QStringLiteral("接收到虚遥信，正在处理..."), frame.toAllByteArray());
            // 监控接收虚遥信
            vyxResponse(frame.infoFields);
        }
    }

}


void CDTProtocol::send(const CDTFrame &frame)
{
    QByteArray bytes = frame.toAllByteArray();

    if (bytes.size() > 0) {
        emit write(bytes);
    }
}

void CDTProtocol::send(const QByteArray &sendBytes)
{
    if (sendBytes.size() > 0) {
        emit write(sendBytes);
    }
}

void CDTProtocol::sendAllDi()
{
    auto frameBytes = CDTProtocol::buildYXProtocol(m_settingData);
    if (frameBytes.isEmpty()) {
        return ;
    }
    showMessageBuffer(eMsgType::eMsgSend, "发送全遥信", frameBytes);
    send(frameBytes);
}

void CDTProtocol::sendAllAi()
{
    auto frameBytes = CDTProtocol::buildYCProtocol(m_settingData);
    if (frameBytes.isEmpty()) {
        return ;
    }
    showMessageBuffer(eMsgType::eMsgSend, "发送全遥测", frameBytes);
    send(frameBytes);

}

void CDTProtocol::sendVirtualYX()
{
    auto frameBytes = CDTProtocol::buildVYXProtocol(m_settingData);
    if (frameBytes.isEmpty()) {
        return ;
    }
    showMessageBuffer(eMsgType::eMsgSend, "发送虚遥信", frameBytes);
    send(frameBytes);
}

void CDTProtocol::yxResponse(QList<InfoFieldEntity> &infoFieldList)
{
    int startOffset = m_settingData->m_ptCfg->m_globalDiList->first()->io();
//    int diSize = m_settingData->m_ptCfg->m_globalDiList->size();
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

            nSeq = curPointStartAddr + i + startOffset;  // 点号

            auto di = m_settingData->m_ptCfg->findDiById(nSeq);
            if (di) {
                di->setValue(yxValue > 0);
            }
//            else {
//                qInfo("未找到遥信点，点号=%d", nSeq);
//            }
        }
    }

}

void CDTProtocol::ycResponse(QList<InfoFieldEntity> &infoFieldList)
{
    int offset = m_settingData->m_ptCfg->m_globalAiList->first()->io();
    for (InfoFieldEntity &entity : infoFieldList)
    {
        int nSeq = 0;
        double ycAccept = 0;

        for (int i = 0; i < 4; i += 2)
        {
            // 将两个字节合并到16位的整数中
            uint16_t combineNum = entity.dataArray[i];
            combineNum = (combineNum << 8) | entity.dataArray[i + 1];
            ycAccept = combineNum;
            // 0~10为有效数据
            if (combineNum > 0x07FF) {
                ycAccept = 0x4000;//溢出
            }
            // 点号
            nSeq = entity.funCode + (i / 2) + offset;
//            if (nSeq < offset + m_settingData->m_ptCfg->m_globalAiList->size()) {

//            }
            auto ai = m_settingData->m_ptCfg->findAiById(nSeq);
            if (ai) {
                ai->setValue(ycAccept);
            }
//            else {
//                qInfo("未找到遥测点，点号=%d", nSeq);
//            }

        }
        offset++;
    }
}

void CDTProtocol::vyxResponse(QList<InfoFieldEntity> &infoFieldList)
{
    int startOffset = m_settingData->m_ptCfg->m_globalVDiList->first()->io();
    int diSize = m_settingData->m_ptCfg->m_globalVDiList->size();
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

            nSeq = curPointStartAddr + i + startOffset;  // 点号

            if(nSeq < (startOffset + diSize)) {
                auto vdi = m_settingData->m_ptCfg->findVDiById(nSeq);
                if (vdi) {
                    vdi->setValue(yxValue > 0);
                }
                else {
                    qInfo("未找到虚遥信点，点号=%d", nSeq);
                }
            }
        }
    }
}

void CDTProtocol::ykSelect(uint8_t operCode, uint8_t ptNo)
{
    auto frame = CDTFrame::createYKFrame(m_settingData->m_ptCfg->m_controlType, m_settingData->m_ptCfg->m_ykReqType, m_settingData->m_ptCfg->m_ykReqCode, operCode, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控选择"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的%2操作遥控选择指令").arg(ptNo).arg(operCode == eControlLockCode::CloseValidLock ? QStringLiteral("合"):QStringLiteral("分")));
    send(frame);
}

void CDTProtocol::ykSelectBack(uint8_t operCode, uint8_t ptNo)
{
    auto frame = CDTFrame::createYKFrame(m_settingData->m_ptCfg->m_controlType, m_settingData->m_ptCfg->m_ykAckType, m_settingData->m_ptCfg->m_ykAckCode, operCode, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控选择应答"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的%2操作遥控选择回传指令").arg(ptNo).arg(operCode == eControlLockCode::CloseValidLock ? QStringLiteral("合"):QStringLiteral("分")));
    send(frame);
}

void CDTProtocol::yKExecute(uint8_t operCode, uint8_t ptNo)
{
    // TODO fix 0xC2
    auto frame = CDTFrame::createYKFrame(m_settingData->m_ptCfg->m_controlType, 0xC2, m_settingData->m_ptCfg->m_ykExeCode, operCode, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控执行"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的%2操作遥控执行指令").arg(ptNo).arg(operCode == eControlLockCode::CloseValidLock ? QStringLiteral("合"):QStringLiteral("分")));
    send(frame);
}

void CDTProtocol::yKCancel(uint8_t operCode, uint8_t ptNo)
{
    auto frame = CDTFrame::createYKFrame(m_settingData->m_ptCfg->m_controlType, 0xB3, eCDTFunCode::RmtControlCancelCode, operCode, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控取消"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的%2操作遥控取消指令").arg(ptNo).arg(operCode == eControlLockCode::CloseValidLock ? QStringLiteral("合"):QStringLiteral("分")));
    send(frame);
}

CDTFrame CDTProtocol::buildYXFrame(uint8_t startFuncode, const QMap<int, DiData *> &ptMap)
{
    QList<uint8_t> combineByteList;
    uchar val = 0;
    int index = 0;
    int lastIndex = ptMap.last()->io();
    for (int i = 0; i <= lastIndex; i++) {

        bool diVal = false;
        if (ptMap.contains(i)) {
            diVal = ptMap.value(i)->value();
        }
        if (diVal) {
            val |= (1 << index % 8);
        }
        index++;
        if (index % 8 == 0 && index != 0) {
            combineByteList.append(val);
            val = 0;
            index = 0;
        }
    }
    if (index % 8 != 0) {
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
        entity.fillData(funCode, combineByteList.at(j * 4), combineByteList.at(j * 4 + 1), combineByteList.at(j * 4 + 2), combineByteList.at(j * 4 + 3));
        frame.infoFields.append(entity);
        funCode++;
    }
    return frame;
}

CDTFrame CDTProtocol::buildYCFrame(uint8_t startFuncode, const QMap<int, AiData *> &ptMap)
{

    CDTFrame frame;

    uint8_t curCode = startFuncode;
    QVector<uint8_t> combineList;
    int aiNum = ptMap.last()->io();
    for (int i = 0; i <= aiNum; i++) {
//        YcData aiValue;
        int aiValue = 0;
        if (ptMap.contains(i)) {
            aiValue = static_cast<int>(ptMap.value(i)->value());
        }
        if (aiValue > 0x07FF) {
            aiValue = 0x4000;// 溢出
        }
//        combineList.append(static_cast<uint8_t>(aiValue.idata >> 8));
//        combineList.append(static_cast<uint8_t>(aiValue.idata));
        combineList.append(static_cast<uint8_t>(aiValue >> 8));
        combineList.append(static_cast<uint8_t>(aiValue));
    }
    int offset = combineList.size() % 4;
    if (offset != 0) {
        for (int i = 0; i < offset; i++) {
            combineList.append(0);
        }
    }
    for (int i = 0; i < combineList.size() / 4; i++) {
        InfoFieldEntity entity;
        entity.fillData(curCode, combineList[i * 4], combineList[i * 4 + 1], combineList[i * 4 + 2], combineList[i * 4 + 3]);
        frame.infoFields.append(entity);
        curCode++;
    }

    return frame;
}

QByteArray CDTProtocol::buildYXProtocol(const QSharedPointer<SettingData> &settingData)
{
    if (settingData->m_ptCfg->m_globalDiList->isEmpty()) {
        return QByteArray();
    }
    auto frame = CDTProtocol::buildYXFrame(settingData->m_ptCfg->m_yxFuncode, settingData->m_ptCfg->getDiMap()/**settingData->m_ptCfg->m_globalDiList*/);

    frame.frameControl.fillData(settingData->m_ptCfg->m_controlType, settingData->m_ptCfg->m_yxFrameType, frame.infoFields.size(), 0, 0);

    return frame.toAllByteArray();
}

QByteArray CDTProtocol::buildYCProtocol(const QSharedPointer<SettingData> &settingData)
{
    if (settingData->m_ptCfg->m_globalAiList->isEmpty()) {
        return QByteArray();
    }
    CDTFrame frame = CDTProtocol::buildYCFrame(settingData->m_ptCfg->m_ycFuncode, settingData->m_ptCfg->getAiMap());
    frame.frameControl.fillData(settingData->m_ptCfg->m_controlType, settingData->m_ptCfg->m_ycFrameType, frame.infoFields.size(), 0, 0);
    return frame.toAllByteArray();
}

QByteArray CDTProtocol::buildVYXProtocol(const QSharedPointer<SettingData> &settingData)
{
    if (settingData->m_ptCfg->m_globalVDiList->isEmpty()) {
        return QByteArray();
    }
    auto frame = CDTProtocol::buildYXFrame(settingData->m_ptCfg->m_yxFuncode, settingData->m_ptCfg->getVDiMap()/**settingData->m_ptCfg->m_globalVDiList*/);
    frame.frameControl.fillData(settingData->m_ptCfg->m_controlType, settingData->m_ptCfg->m_vyxFrameType, frame.infoFields.size(), 0, 0);
    return frame.toAllByteArray();
}

void CDTProtocol::uploadDi()
{
    if (m_yxSendCounter > static_cast<uint>(m_settingData->m_ptCfg->m_yxTime)) {
        sendAllDi();
        m_yxSendCounter = 0;
    }
}

void CDTProtocol::uploadAi()
{
    if (m_ycSendCounter > static_cast<uint>(m_settingData->m_ptCfg->m_ycTime)) {
        sendAllAi();
        m_ycSendCounter = 0;
    }
}

void CDTProtocol::uploadVDi()
{
    if (m_vyxSendCounter > static_cast<uint>(m_settingData->m_ptCfg->m_ycTime)) {
        sendVirtualYX();
        m_vyxSendCounter = 0;
    }
}

void CDTProtocol::onReverseYx(int ptId, bool allow)
{
    if (allow) {
        auto di = m_settingData->m_ptCfg->findDiById(ptId);
        auto changeMsg = di->value() ? QStringLiteral("合->分") : QStringLiteral("分->合");
        di->setValue(!di->value());
        sendAllDi();

        qInfo("点%d遥控变位完成", ptId);
        emit sendYKMsg(QStringLiteral("允许点%1发生遥控变位，%2").arg(ptId).arg(changeMsg));
    }
    else {
        emit sendYKMsg(QStringLiteral("禁止点%1发生遥控变位").arg(ptId));
    }
    m_isRunYK = false;

}

void CDTProtocol::onReadyRead()
{
    auto bytes = m_network->readAll();

    if (!bytes.isEmpty()) {
        m_recvBuffer.append(bytes);
        //处理数据
        parseRecvData();
    }
    // 处理帧
    processFrame();
}

void CDTProtocol::onDisconnected()
{
    stop();
}

void CDTProtocol::onTimeout()
{
    this->m_yxSendCounter += 100;
    this->m_ycSendCounter += 100;
    ProtocolBase::onTimeout();
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
