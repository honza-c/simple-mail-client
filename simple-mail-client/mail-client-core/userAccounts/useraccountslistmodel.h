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
    QList<UserAccount> getUserAccountList();

public slots:
    void addNewUserAccount(UserAccount *account);
    void editSelectedUserAccount(QModelIndex index, UserAccount *account);
    void removeSelectedUserAccount(QModelIndex index);

private:
    QList<UserAccount> users;

    bool insertRows(int row, int count, const QModelIndex &parent, QList<UserAccount*> newUsers);
    bool removeRows(int row, int count, const QModelIndex &parent);

};

#endif // USERACCOUNTSLISTMODEL_H
