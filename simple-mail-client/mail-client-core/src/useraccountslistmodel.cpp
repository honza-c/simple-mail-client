#include "useraccountslistmodel.h"

int UserAccountsListModel::rowCount(const QModelIndex &parent) const
{
    return m_data->size();
}

QVariant UserAccountsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= m_data->size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        QString result;

        result.append(m_data->at(index.row()).contactName());
        result.append(" <");
        result.append(m_data->at(index.row()).emailAddress());
        result.append(">");

        return result;
    }
    else
    {
        return QVariant();
    }
}
