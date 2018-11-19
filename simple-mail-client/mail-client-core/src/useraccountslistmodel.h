#ifndef NEWUSERACCOUNTSLISTMODEL_H
#define NEWUSERACCOUNTSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "src/useraccount.h"

class UserAccountsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit UserAccountsListModel(QList<UserAccount> &data, QObject *parent = nullptr)
        : QAbstractListModel(parent), m_data(&data) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:

    QList<UserAccount> *m_data;
};

#endif // NEWUSERACCOUNTSLISTMODEL_H
