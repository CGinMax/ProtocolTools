#include "protocolbase.h"
#include "../common/util.h"
#include <QTime>
#include <QDateTime>
#include <QThread>
#include <QTimer>
ProtocolBase::ProtocolBase()
{

}

ProtocolBase::ProtocolBase(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : m_network(network)
    , m_settingData(settingData)
    , m_strategy(nullptr)
{
    connect(this, &ProtocolBase::write, network.data(), &NetworkBase::writeData);
    connect(m_network.data(), &NetworkBase::readyRead, this, &ProtocolBase::onReadyRead);
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
//        if (PortOpenFailedCount == 0) return true;
//        PortOpenFailedCount = 0;
//        ProcessPortOpenSucceed();
        return true;
    }

    // 打开端口
    QTime tmOrg;
    tmOrg.start();
    //isFirstConnect = false;

    m_network->open();
    /*
    if (portObj->porttype == ePortType::TcpServer)
    {// 等待对方连接，特殊处理
        PortTcpServer* portTcpServer = (PortTcpServer*)portObj;
        if (portTcpServer->IsActiveListen())
        {// 监听正常，等待对方连接
            for (int i = 0; i < 5; i++)
            {
                QThread::msleep(100);
                if (portObj->IsActive()) break;
            }
        }
    }
    */

    if (!m_network->isActived())
    {// 休眠不足500ms，则补足
        int milliseconds = tmOrg.elapsed();
        if (milliseconds < 500) QThread::msleep(500 - milliseconds);
    }

    if (m_network->isActived())
    {// 打开端口成功
//        PortOpenFailedCount = 0;
//        ProcessPortOpenSucceed();
        return true;
    }

    /*
    bool isActiveListen = false;// 是否监听正常
    if (portObj->porttype == ePortType::TcpServer)
    {// TCP服务端特殊处理
        isActiveListen = ((PortTcpServer*)portObj)->IsActiveListen();
        if (isActiveListen)
        {
            QString str = " 监听正常，等待对方连接...";
            ShowMsg(eMsgType::eMsgLink, portObj->ToString() + str);
        }
        else
        {
            QString str = "  监听失败！";
            ShowMsg(eMsgType::eMsgLink, portObj->ToString() + str);
        }
    }
    else
    {
        ShowMsg(eMsgType::eMsgLink, QString("%1 %2").arg(portObj->ToString()).arg("连接失败！"));
    }

    if (portObj->porttype == ePortType::TcpClient &&
        !this->tcpClient_ForceChangeIP)
    {// TCP客户端连接，切换备用网口
        switchPort = ((PortTcpClient*)portObj)->SwitchPort();
    }

    PortOpenFailedCount++;
    if (!switchPort)
    {// 没有切换端口，则两次打开失败就认为是故障
        if (isActiveListen)
        {// 监听正常，则给超过2秒的时间
            ProcessPortOpenfailed(PortOpenFailedCount >= 4);
        }
        else
        {// 监听失败，或是打开串口失败，或者连接对方单一IP失败
            ProcessPortOpenfailed(PortOpenFailedCount >= 2);
        }
    }
    else
    {// 切换了端口，说明有两个IP地址，给3次连接机会
        ProcessPortOpenfailed(PortOpenFailedCount >= 3);
    }
    */

    return false;
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
    disconnect(m_network.data(), &NetworkBase::readyRead, this, &ProtocolBase::onReadyRead);
}

void ProtocolBase::onTimeout()
{
    this->run();
}
