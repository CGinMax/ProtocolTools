#include "protocolbase.h"
#include <QTime>
#include <QThread>

ProtocolBase::ProtocolBase()
{

}

ProtocolBase::ProtocolBase(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : m_network(network)
    , m_settingData(settingData)
{

}

ProtocolBase::~ProtocolBase()
{

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
