#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <QString>
#include <QSignalSpy>
#include <QtConcurrent>
#include <QTimer>
#include <QTabBar>
#include <QQueue>
#include "../ProtocolTools/common/util.h"
#include "../PressPlateTool/protocol/ybframe.h"

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

    std::list<uint8_t> completeMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x02, 0x00, 0x01, 0x01, 0x0a,0x0b};
    auto completeRes = YBFrame::parseBytesToFrame(completeMsg);
    QCOMPARE(YBFrame::calcCrc(completeRes.first), 0x4643);
}

void networkTest::test_ybframe_parse()
{
    // header fine
    std::list<uint8_t> headerMsg = {0x90, 0x20, 0xEB, 0x90, 0xEB, 0x90, 2, 0, 2, 0x02, 0x00, 0x01, 0x01, 0x0a,0x0b};
    auto headerRes = YBFrame::parseBytesToFrame(headerMsg);
    QVERIFY(headerRes.second != eYBParseResult::HeaderError);

    // header fine in tail
    headerMsg = {0x90, 0x20, 2, 0, 2, 0x02, 0xEB, 0x90, 0x01, 0x0a,0x0b, 0xEB, 0x90, 0xEB, 0x90};
    headerRes = YBFrame::parseBytesToFrame(headerMsg);
    QVERIFY(headerRes.second != eYBParseResult::HeaderError);

    // header error
    headerMsg = {0x90, 0x20, 2, 0, 2, 0x02, 0xEB, 0x90, 0x90, 0xEB, 0x90, 0xEB, 0x00, 0x90, 0x01, 0x0a,0x0b};
    headerRes = YBFrame::parseBytesToFrame(headerMsg);
    QVERIFY(headerRes.second == eYBParseResult::HeaderError);
    headerMsg = {0x90, 0x20, 2, 0, 2, 0x02, 0xEB, 0x90, 0xEB, 0x10, 0x20, 0x01, 0x0a,0x0b};
    headerRes = YBFrame::parseBytesToFrame(headerMsg);
    QVERIFY(headerRes.second == eYBParseResult::HeaderError);

    // not complete
    std::list<uint8_t> bodyMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, /*0x02, 0x00, 0x01, 0x01, 0x0a, */0x0b};
    auto bodyMsgRes = YBFrame::parseBytesToFrame(bodyMsg);
    QVERIFY(bodyMsgRes.second == eYBParseResult::NotComplete);
    // no complete no crc
    bodyMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x02, 0x00, 0x01, 0x01/*, 0x0a,0x0b*/};
    bodyMsgRes = YBFrame::parseBytesToFrame(bodyMsg);
    QVERIFY(bodyMsgRes.second == eYBParseResult::NotComplete);
    // data length error
    bodyMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0xaa, 0x00, 0x01, 0x01, 0x0a,0x0b};
    bodyMsgRes = YBFrame::parseBytesToFrame(bodyMsg);
    QVERIFY(bodyMsgRes.second == eYBParseResult::DataLengthError);

    // crc error
    std::list<uint8_t> crcMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x02, 0x00, 0x01, 0x01, 0x10,0x20};
    auto crcRes = YBFrame::parseBytesToFrame(crcMsg);
    QVERIFY(crcRes.second == eYBParseResult::CrcError);

    // complete
    std::list<uint8_t> completeMsg = {0xEB, 0x90, 0xEB, 0x90, 0x20, 0x20, 1, 0, 2, 0, 2, 0x02, 0x00, 0x01, 0x01, 0x43,0x46};
    auto completeRes = YBFrame::parseBytesToFrame(completeMsg);
    QVERIFY(completeRes.second == eYBParseResult::NoError);

}


QTEST_MAIN(networkTest)

#include "tst_networktest.moc"
