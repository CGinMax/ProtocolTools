#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <QString>
#include <QSignalSpy>
#include <QtConcurrent>
#include <QTimer>
#include <QQueue>
#include "../CdtTools/network/networkbase.h"
#include "../CdtTools/network/tcpserver.h"
#include "../CdtTools/common/threadpool.h"
#include "../CdtTools/protocol/cdtprotocol.h"
#include "../CdtTools/protocol/checkhelper.h"
#include "../CdtTools/common/util.h"

class networkTest : public QObject
{
    Q_OBJECT

public:
    networkTest();
    ~networkTest() override;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_util();
    void test_tcpserver();
    void test_worker();
    void test_threadpool();
    void test_cdt();

public:
    TcpServer* m_tcpServer;
    QTcpSocket* m_testClient;
};

networkTest::networkTest()
{
    m_tcpServer = new TcpServer("127.0.0.1", 8011);
    m_testClient = new QTcpSocket;

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

void networkTest::test_util()
{
    uint8_t unum8 = 1;
    int8_t num8 = 0xee;
    int num = 1000;
    uint unum = 2000;
    QCOMPARE(Util::num2Hex(unum8, 2), "01");
    QCOMPARE(Util::num2Hex(static_cast<uint8_t>(num8)), "EE");
    QCOMPARE(Util::num2Hex(num), "3E8");
    QCOMPARE(Util::num2Hex(unum), "7D0");
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

void networkTest::test_worker()
{
    WorkerThread worker;
    int sum = 0;
    QEventLoop eventloop;
    QtConcurrent::run([&worker, &sum](QEventLoop* event){

        worker.run([&sum](){
            sum += 10;
        });
        event->quit();
    }, &eventloop);
    eventloop.exec();
    while(eventloop.isRunning()) {
        QThread::msleep(100);
    }
    QCOMPARE(sum, 10);
}

void networkTest::test_threadpool()
{
    int sum = 0;
    {
        ThreadPool pool(10);
        for (int i = 0; i < pool.maxCount(); i++) {
            pool.run([i, &sum](){
                sum += i;
            });
        }
    }
    QCOMPARE(sum, 45);

}

void networkTest::test_cdt()
{
    CDTProtocol cdt;
    char rawData[] ={(char)0xEB, (char)0x90, (char)0xEB, (char)0x90, (char)0xEB, (char)0x90, 0x71, (char)0xF4, 0x01, 0x00, 0x00, 0x33, (char)0xF0, 0x38, 0x00, 0x00, 0x00, (char)0xEF};
    QByteArray yxBytes(rawData, sizeof(rawData) / sizeof(char));

//    cdt.m_recvBuffer = yxBytes;
//    cdt.parseRecvData();
//    QCOMPARE(cdt.m_frameQueue.size(), 1);

    // processFrame
//    cdt.m_testYxList.clear();
//    cdt.processFrame();
//    QCOMPARE(cdt.m_testYxList.at(2), 0);
//    QCOMPARE(cdt.m_testYxList.at(3), 1);
}

QTEST_MAIN(networkTest)

#include "tst_networktest.moc"
