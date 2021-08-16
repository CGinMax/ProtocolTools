#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <iterator>
#include <iostream>
#include <QString>
#include <QSignalSpy>
#include <QtConcurrent>
#include <QTimer>
#include <QTabBar>
#include <QQueue>
#include "../ProtocolTool/common/util.h"
#include "../Protocols/convert.h"
#include "../Protocols/YBProtocol/ybframe.h"
#include "../Protocols/YBProtocol/ybprotocol.h"
#include "../Protocols/YBProtocol/ybprotocolexception.h"

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
    void test_crc16();
    void test_ybframe_parse();
    void test_ybframe_packet();
    void test_ybprotocol();
public:
};

networkTest::networkTest()
{
}

networkTest::~networkTest()
{
}

void networkTest::initTestCase()
{
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

void networkTest::test_crc16()
{
    std::vector<uint8_t> bodyMsg = {0x20, 0x20, 1, 0, 2, 0, 2, 0xaa, 0x00, 0x01, 0x01/*, 0x0a,0x0b*/};
    auto res = YBFrame::checkCRC16(bodyMsg, 0);
    QCOMPARE(res, 0x29F6);

    try {
        std::list<uint8_t> completeMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x02, 0x00, 0x01, 0x01, 0x0a,0x0b};
        auto completeRes = YBFrame::parseBytesToFrame(completeMsg);
        QCOMPARE(YBFrame::calcCrc(completeRes), 0x4643);

    } catch (const YBProtocolException& e) {
        QVERIFY(e.result() == eYBParseResult::CrcError);
    }
}

void networkTest::test_ybframe_parse()
{
    // header fine
    try {
        std::list<uint8_t> headerMsg = {0x90, 0x20, 0xEB, 0x90, 0xEB, 0x90, 2, 0, 2, 0x02, 0x00, 0x01, 0x01, 0x0a,0x0b};
        auto headerRes = YBFrame::parseBytesToFrame(headerMsg);
    } catch (const YBProtocolException& e) {
        QVERIFY(e.result() != eYBParseResult::HeaderError);
    }

    // header fine in tail
    try {
        std::list<uint8_t> headerMsg = {0x90, 0x20, 2, 0, 2, 0x02, 0xEB, 0x90, 0x01, 0x0a,0x0b, 0xEB, 0x90, 0xEB, 0x90};
        auto headerRes = YBFrame::parseBytesToFrame(headerMsg);

    } catch (const YBProtocolException& e) {
        QVERIFY(e.result() != eYBParseResult::HeaderError);
    }

    // header error
    try {
        std::list<uint8_t> headerMsg = {0x90, 0x20, 2, 0, 2, 0x02, 0xEB, 0x90, 0x90, 0xEB, 0x90, 0xEB, 0x00, 0x90, 0x01, 0x0a,0x0b};
        auto headerRes = YBFrame::parseBytesToFrame(headerMsg);
    } catch (const YBProtocolException& e) {
        QVERIFY(e.result() == eYBParseResult::HeaderError);
    }

    try {
        std::list<uint8_t> headerMsg = {0x90, 0x20, 2, 0, 2, 0x02, 0xEB, 0x90, 0xEB, 0x10, 0x20, 0x01, 0x0a,0x0b};
        auto headerRes = YBFrame::parseBytesToFrame(headerMsg);

    } catch (const YBProtocolException& e) {
        QVERIFY(e.result() == eYBParseResult::HeaderError);
    }

    // not complete
    try {
        std::list<uint8_t> bodyMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, /*0x02, 0x00, 0x01, 0x01, 0x0a, */0x0b};
        auto bodyMsgRes = YBFrame::parseBytesToFrame(bodyMsg);

    } catch (const YBProtocolException& e) {

        QVERIFY(e.result() == eYBParseResult::NotComplete);
    }
    // no complete no crc
    try {
        std::list<uint8_t> bodyMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x02, 0x00, 0x01, 0x01/*, 0x0a,0x0b*/};
        auto bodyMsgRes = YBFrame::parseBytesToFrame(bodyMsg);

    } catch (const YBProtocolException& e) {

        QVERIFY(e.result() == eYBParseResult::NotComplete);
    }

    // crc error
    try {
        std::list<uint8_t> crcMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x02, 0x00, 0x01, 0x01, 0x10,0x20};
        auto crcRes = YBFrame::parseBytesToFrame(crcMsg);

    } catch (const YBProtocolException& e) {
        QVERIFY(e.result() == eYBParseResult::CrcError);
    }

    // complete
    try {
        std::list<uint8_t> completeMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x02, 0x00, 0x01, 0x01, 0x43,0x46};
        auto completeRes = YBFrame::parseBytesToFrame(completeMsg);

    } catch (const YBProtocolException& e) {

        QVERIFY(e.result() == eYBParseResult::NoError);
    }

}

void networkTest::test_ybframe_packet()
{
    std::list<uint8_t> srcMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x01, 0x00, 0x01, 0x22,0x79};
    std::list<uint8_t> msg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x01, 0x00, 0x01, 0x22,0x79};
    auto frame = YBFrame::parseBytesToFrame(msg);
    std::vector<uint8_t> packetDatas = frame.packetFrameToPureData();

    packetDatas.shrink_to_fit();
    QCOMPARE(srcMsg.size() , packetDatas.size());
    auto srcIter = srcMsg.begin();
    auto dstIter = packetDatas.begin();
    for (;srcIter != srcMsg.begin() && dstIter != packetDatas.end(); srcIter++, dstIter++) {
        QVERIFY(*srcIter == *dstIter);
    }
}

void networkTest::test_ybprotocol()
{
    YBProtocol protocol;
    std::list<uint8_t> crcErrorMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x01, 0x00, 0x01, 0x22/*,0x79*/, 0};
    protocol.appendDatas(crcErrorMsg);
    protocol.parseRecvData();
    auto exceptions = protocol.popAllException();
    QCOMPARE(exceptions.size(), 1);
    QCOMPARE(exceptions.at(0).result(), eYBParseResult::CrcError);

    std::list<uint8_t> successMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x01, 0x00, 0x01, 0x22, 0x79};
    protocol.appendDatas(successMsg);
    protocol.parseRecvData();
    if (!protocol.isRecvFrameEmpty()) {
        auto frame = protocol.popRecvFrame();
        QCOMPARE(frame.m_dataLen, 1);
        QCOMPARE(frame.m_funCode, 0x02);

    }
}


QTEST_MAIN(networkTest)

#include "tst_networktest.moc"
