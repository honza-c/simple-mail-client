#ifndef XMLUSERACCOUNTSREADERWRITER_H
#define XMLUSERACCOUNTSREADERWRITER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include "src/useraccount.h"
#include "src/aesencryptordecryptor.h"

class XmlUserAccountsReaderWriter : public QObject
{
    Q_OBJECT
public:
    explicit XmlUserAccountsReaderWriter(QObject *parent = nullptr);

    void setUserAccounts(QList<UserAccount> *userAccounts);
    QList<UserAccount> *userAccounts() const;
    void setEncryptionKey(const QString key);
    void setEncryptionIV(const QString iv);

    bool loadUserAccounts(QIODevice *device);
    bool storeUserAccounts(QIODevice *device);
signals:

public slots:

private:
    bool loadAccount();
    bool storeAccount(const int index);

    const QString USERS_ROOT_TAGNAME = "Users";
    const QString USERACCOUNT_TAGNAME = "User";
    const QString ACCOUNT_NAME_TAGNAME = "AccountName";
    const QString CONTACT_NAME_TAGNAME = "ContactName";
    const QString EMAIL_ADDRESS_TAGNAME = "EmailAddress";
    const QString USER_NAME_TAGNAME = "UserName";
    const QString PASSWORD_TAGNAME = "Password";
    const QString SMTP_SERVER_URL_TAGNAME = "SMTPServerURL";
    const QString INCOMING_SERVER_TYPE_TAGNAME = "IncomingServerType";
    const QString INCOMING_SERVER_URL_TAGNAME = "IncomingServerURL";
    const QString SMTP_SERVER_PORT_TAGNAME = "SMTPServerPort";
    const QString INCOMING_SERVER_PORT_TAGNAME = "IncomingServerPort";

    QList<UserAccount> *m_userAccounts;
    QXmlStreamReader m_reader;
    QXmlStreamWriter m_writer;
    AesEncryptorDecryptor *m_passwordEncryptorDecryptor;
};

#endif // XMLUSERACCOUNTSREADERWRITER_H
