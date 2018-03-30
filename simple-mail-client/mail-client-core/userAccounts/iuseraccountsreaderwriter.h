#ifndef IUSERACCOUNTSREADERWRITER_H
#define IUSERACCOUNTSREADERWRITER_H

#include <QObject>
#include <QIODevice>

#include "useraccount.h"

class IUserAccountsReaderWriter : public QObject
{
    Q_OBJECT
public:
    // explicit IUserAccountsReaderWriter(QList<UserAccount> *accountList);
    virtual bool loadUserAccounts(QIODevice *device) = 0;
    virtual bool storeUserAccounts(QIODevice *device) = 0;

private:
    QList<UserAccount> *userAccounts;
signals:

public slots:
};

#endif // IUSERACCOUNTSREADERWRITER_H
