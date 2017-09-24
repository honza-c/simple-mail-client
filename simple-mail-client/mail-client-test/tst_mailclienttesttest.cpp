#include <QString>
#include <QtTest>

class MailClientTestTest : public QObject
{
    Q_OBJECT

public:
    MailClientTestTest();

private Q_SLOTS:
    void testCase1();
};

MailClientTestTest::MailClientTestTest()
{
}

void MailClientTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(MailClientTestTest)

#include "tst_mailclienttesttest.moc"
