#ifndef XMLUSERACCOUNTSREADERWRITER_H
#define XMLUSERACCOUNTSREADERWRITER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

#include "iuseraccountsreaderwriter.h"
#include "tools/constants.h"
#include "useraccount.h"
#include "tools/aespasswordencryptordecryptor.h"
#include "tools/ipasswordencryptordecryptor.h"

class XmlUserAccountsReaderWriter : public IUserAccountsReaderWriter
{
    Q_OBJECT
public:
    XmlUserAccountsReaderWriter(QList<UserAccount> *userAccounts);
    bool loadUserAccounts(QIODevice *device) override;
    bool storeUserAccounts(QIODevice *device) override;

private:
    QXmlStreamReader reader;
    QXmlStreamWriter writer;
    QList<UserAccount> *accountList;
    IPasswordEncryptorDecryptor *pwdEncryptorDecryptor;

    bool loadAccount();
    bool storeAccount(int index);

signals:

public slots:
};

#endif // XMLUSERACCOUNTSREADERWRITER_H
