#ifndef USERACCOUNTSLISTMODEL_H
#define USERACCOUNTSLISTMODEL_H

#include <QtWidgets>
#include "useraccount.h"

class UserAccountsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    UserAccountsListModel(const QList<UserAccount> &users, QObject *parent = 0)
        : QAbstractListModel(parent), users(users) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QList<UserAccount> users;
};

#endif // USERACCOUNTSLISTMODEL_H
