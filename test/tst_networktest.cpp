#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <QString>
#include <QSignalSpy>
#include "../CdtTools/network/networkbase.h"
#include "../CdtTools/network/tcpserver.h"

class networkTest : public QObject
{
    Q_OBJECT

public:
    networkTest();
    ~networkTest() override;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_tcpserver();

public:
    TcpServer* m_tcpServer;
    QTcpSocket* m_testClient;
};

networkTest::networkTest()
{
    m_tcpServer = new TcpServer("127.0.0.1", 8011);
    m_testClient = new QTcpSocket;
//    connect(m_testClient, &QTcpSocket::connected, [=](){

//    });
}

networkTest::~networkTest()
{
    delete m_tcpServer;
    delete m_testClient;
}

void networkTest::initTestCase()
{
    m_tcpServer->open();
    if (m_tcpServer->isActived()) {
        m_testClient->connectToHost(m_tcpServer->ip(), m_tcpServer->port());
    }
}

void networkTest::cleanupTestCase()
{

}

void networkTest::test_tcpserver()
{
    QSignalSpy connectSpy(m_tcpServer, &TcpServer::connected);
    QVERIFY(connectSpy.wait(1000));

    QTest::qWait(1000);
    QVERIFY(m_testClient->state() == QTcpSocket::ConnectedState);
    m_testClient->write("aaaa");
    QSignalSpy writeSpy(m_tcpServer, &TcpServer::recvData);
    QVERIFY(writeSpy.wait(1000));

    QVERIFY(m_tcpServer->write("aaaa"));

}

QTEST_MAIN(networkTest)

#include "tst_networktest.moc"
