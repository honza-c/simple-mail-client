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

QList<UserAccount> UserAccountsListModel::getUserAccountList()
{
    return this->users;
}

void UserAccountsListModel::addNewUserAccount(UserAccount *account)
{
    int count = users.length();

    QList<UserAccount*> newUsers;
    newUsers.push_back(account);

    insertRows(count, 1, QModelIndex(), newUsers);
}

void UserAccountsListModel::editSelectedUserAccount(QModelIndex index, UserAccount *account)
{
    beginResetModel();
    users.replace(index.row(), *account);
    endResetModel();
}

void UserAccountsListModel::removeSelectedUserAccount(QModelIndex index)
{
    removeRows(index.row(), 1, QModelIndex());
}

bool UserAccountsListModel::insertRows(int position, int rows, const QModelIndex &parent, QList<UserAccount*> newUsers)
{
    beginInsertRows(parent, position, rows + position - 1);

    for (int row = 0; row < rows; row++)
    {
        users.insert(position, *(newUsers.at(row)));
    }

    endInsertRows();

    return true;
}

bool UserAccountsListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    for (int x = row; x < row + count; x++)
    {
        users.removeAt(x);
    }

    endRemoveRows();

    return true;
}