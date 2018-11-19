#include "attachmentslistmodel.h"

QVariant AttachmentsListModel::data(const QModelIndex &index, int role) const
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
        return m_data->at(index.row()).name();
    }
    else if (role == Qt::DecorationRole)
    {
        return QIcon::fromTheme("mail-attachment");
    }
    else
    {
        return QVariant();
    }
}

int AttachmentsListModel::rowCount(const QModelIndex &index) const
{
    return m_data->size();
}

bool AttachmentsListModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        m_data->removeAt(position);
    }

    endRemoveRows();
    return true;
}
