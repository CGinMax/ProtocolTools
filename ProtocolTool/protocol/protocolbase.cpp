#include "protocolbase.h"
#include "../common/util.h"
#include <QElapsedTimer>
#include <QDateTime>
#include <QThread>
#include <QTimer>

ProtocolBase::ProtocolBase(const QSharedPointer<CommunicationBase> &network, const QSharedPointer<SettingData> &settingData)
    : m_network(network)
    , m_settingData(settingData)
    , m_strategy(nullptr)
    , m_portOpenFailedCount(0)
    , m_yxSendCounter(0)
    , m_ycSendCounter(0)
    , m_vyxSendCounter(0)
{
    connect(this, &ProtocolBase::write, network.data(), &CommunicationBase::writeData);
    connect(m_network.data(), &CommunicationBase::readyRead, this, &ProtocolBase::onReadyRead);
}

ProtocolBase::~ProtocolBase()
{
    if (m_strategy != nullptr) {
        delete m_strategy;
        m_strategy = nullptr;
    }
}

bool ProtocolBase::initConnection()
{
    if (m_network->isActived())
    {// 打开状态
        if (m_portOpenFailedCount == 0) return true;
        m_portOpenFailedCount = 0;
        processPortOpenSucceed();
        return true;
    }

    // 打开端口
    QElapsedTimer tmOrg;
    tmOrg.start();

    m_network->open();

    if (!m_network->isActived())
    {// 休眠不足500ms，则补足
        int milliseconds = tmOrg.elapsed();
        if (milliseconds < 500) QThread::msleep(500 - milliseconds);
    }

    if (m_network->isActived())
    {// 打开端口成功
        m_portOpenFailedCount = 0;
        processPortOpenSucceed();
        return true;
    }

    m_portOpenFailedCount++;

    return false;
}

void ProtocolBase::processPortOpenSucceed()
{

}

bool ProtocolBase::isConnection()
{
    return m_network->isActived();
}

void ProtocolBase::showMessage(ProtocolBase::eMsgType type, const QString &msg)
{
    sendHumanizeMsg(type, msg, QByteArray());
}

void ProtocolBase::showMessageBuffer(ProtocolBase::eMsgType type, const QString &msg, const char *buffer, int len)
{
    sendHumanizeMsg(type, msg, buffer, len);
}

void ProtocolBase::showMessageBuffer(ProtocolBase::eMsgType type, const QString &msg, const QByteArray &buffer)
{
    sendHumanizeMsg(type, msg, buffer);
}

void ProtocolBase::sendHumanizeMsg(ProtocolBase::eMsgType type, const QString &msg, const char *buffer, int len)
{
    auto hexString = Util::bytes2String(buffer, len);
    auto packString = decorateMsg(type, msg, hexString, len);
    emit sendProtocolContent(packString);
}

void ProtocolBase::sendHumanizeMsg(ProtocolBase::eMsgType type, const QString &msg, const QByteArray &buffer)
{
    auto hexString = Util::bytes2String(buffer);
    auto packString = decorateMsg(type, msg, hexString, buffer.length());

    emit sendProtocolContent(packString);
}

QString ProtocolBase::decorateMsg(eMsgType type, const QString &desc, const QString &bufrString, int buflen)
{
    // 报文时间
    QString strBuilder;
    strBuilder.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"));

    if (buflen > 0)
    {// 报文长度
        strBuilder.append(" (");
        strBuilder.append(QString::number(buflen));
        strBuilder.append(" ");
        strBuilder.append("bytes");
        strBuilder.append(")");
    }


    strBuilder.append("<br \\>");

    QString fontColor = QString("<font color=\"%1\">%2</font>");
    // 报文类型
    if (type == eMsgType::eMsgLink) {
        strBuilder.append("连接");
        fontColor = fontColor.arg("#FF0000");// QString("<font color=\"#FF0000\">%1</font>");
    }
    else if ( type == eMsgType::eMsgSend ) {
        strBuilder.append("发送");
        fontColor = fontColor.arg("#0000FF");
    }
    else if ( type == eMsgType::eMsgRecv ) {
        strBuilder.append("接收");
        fontColor = fontColor.arg("#008000");
    }
    else if ( type == eMsgType::eMsgOther ) {
        strBuilder.append("其他");
        fontColor = fontColor.arg("#000000");
    }
    strBuilder.append(": ");

    // 报文及描述
    if (buflen > 0)
    {
        strBuilder.append(bufrString);
        strBuilder.append("<br \\>");
    }
    if (desc != "") strBuilder.append(desc);

    //strBuilder = ;
    return fontColor.arg(strBuilder);
}

void ProtocolBase::start()
{
    if (!m_timer) {
        m_timer = new QTimer;
        QObject::connect(m_timer, &QTimer::timeout, this, &ProtocolBase::onTimeout);
    }
    m_timer->start(100);
}

void ProtocolBase::stop()
{
    if (m_timer && m_timer->isActive()) {
        m_timer->stop();
        delete m_timer;
        m_timer = nullptr;
    }
    disconnect(m_network.data(), &CommunicationBase::readyRead, this, &ProtocolBase::onReadyRead);
}

void ProtocolBase::onTimeout()
{
    this->run();
}
