#include "protocolchannelbase.h"
#include "../../Protocols/convert.h"

#include <QDateTime>

ProtocolChannelBase::ProtocolChannelBase(const QSharedPointer<CommunicationBase> &communication, QObject *parent)
    : QObject(parent)
    , m_communication(communication)
    , m_loopTimer(new QTimer())
{
    connect(this, &ProtocolChannelBase::write, m_communication.data(), &CommunicationBase::writeData);
    connect(m_loopTimer.data(), &QTimer::timeout, this, &ProtocolChannelBase::onTimeout);
    connect(m_communication.data(), &CommunicationBase::readyRead, this, &ProtocolChannelBase::onReadyRead);
}

ProtocolChannelBase::~ProtocolChannelBase()
{

}

void ProtocolChannelBase::showMessage(ProtocolChannelBase::eMsgType type, const std::string &msg, const std::vector<uint8_t> &buffer)
{
    QString str = transferMsgHumanize(type, msg, buffer);
    emit showProtocolMsg(str);
}

QString ProtocolChannelBase::transferMsgHumanize(ProtocolChannelBase::eMsgType type, const std::string &msg, const std::vector<uint8_t> &buffer)
{
    auto hexString = Convert::bytes2String(buffer);
    return decorateMsg(type, msg, hexString, static_cast<int>(buffer.size()));
}

QString ProtocolChannelBase::decorateMsg(ProtocolChannelBase::eMsgType type, const std::string &desc, const std::string &bufString, int buflen)
{
    // 报文时间
    QString strBuilder;
    strBuilder.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"));

    if (buflen > 0) {// 报文长度
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
    if (!bufString.empty()) {
        strBuilder.append(QString::fromStdString(bufString));
        strBuilder.append("<br \\>");
    }
    if (!desc.empty()) {
        strBuilder.append(QString::fromStdString(desc));
    }

    return fontColor.arg(strBuilder);
}

void ProtocolChannelBase::start()
{
    if (!m_loopTimer->isActive()) {
        m_loopTimer->start(100);
    }
}

void ProtocolChannelBase::stop()
{
    m_loopTimer->stop();
    disconnect(m_communication.data(), &CommunicationBase::readyRead, this, &ProtocolChannelBase::onReadyRead);
}

void ProtocolChannelBase::onTimeout()
{
    this->run();
}
