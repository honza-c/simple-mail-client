#include "useraccountslistmodel.h"

int UserAccountsListModel::rowCount(const QModelIndex &parent) const
{
    return users.count();
}

QVariant UserAccountsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= users.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        UserAccount u = users.at(index.row());
        return u.getAccountName();
    }
    else
    {
        return QVariant();
    }
}
