#include "newuseraccountslistmodel.h"

int NewUserAccountsListModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant NewUserAccountsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= m_data.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return m_data.at(index.row()).accountName();
    }
    else
    {
        return QVariant();
    }
}
