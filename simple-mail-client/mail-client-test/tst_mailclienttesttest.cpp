#include <QString>
#include <QtTest>
#include <userAccounts/useraccount.h>

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
    /*
    UserAccount account("foo@foo", "pass", "smtp://foo");
    QString emailAddress = account.getEmailAddress();

    QVERIFY2(emailAddress == QString("foo@foo"), "Error in getter UserAccount.getEmailAddress()");
    */
}

QTEST_APPLESS_MAIN(MailClientTestTest)

#include "tst_mailclienttesttest.moc"
