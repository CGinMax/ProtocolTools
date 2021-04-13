#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <QString>
#include <QSignalSpy>
#include <QtConcurrent>
#include <QTimer>
#include <QTabBar>
#include <QQueue>
//#include "../CdtTools/common/util.h"
//#include "../CdtTools/ui/tabs/maintabwidget.h"

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
    void test_maintabwidget();
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
//    uint8_t unum8 = 1;
//    int8_t num8 = 0xee;
//    int num = 1000;
//    uint unum = 2000;
//    QCOMPARE(Util::num2Hex(unum8, 2), "01");
//    QCOMPARE(Util::num2Hex(static_cast<uint8_t>(num8)), "EE");
//    QCOMPARE(Util::num2Hex(num), "3E8");
//    QCOMPARE(Util::num2Hex(unum), "7D0");
}

void networkTest::test_maintabwidget()
{
//    MainTabWidget widget;
//    widget.show();
}

QTEST_MAIN(networkTest)

#include "tst_networktest.moc"
