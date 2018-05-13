#include "messagemetadatatablemodel.h"

MessageMetadataTableModel::MessageMetadataTableModel(QList<MessageMetadata> messagesMetadata)
{
    this->messagesMetadata = messagesMetadata;
}

int MessageMetadataTableModel::rowCount(const QModelIndex &parent) const
{
    return this->messagesMetadata.count();
}

int MessageMetadataTableModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant MessageMetadataTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (!(index.row() >= messagesMetadata.count()) && !(index.column() > columnCount()))
    {
        if (role == Qt::DisplayRole)
        {
            MessageMetadata metadata = messagesMetadata.at(index.row());

            switch (index.column())
            {
            case 0:
                return QString::number(metadata.getId());
            case 1:
                return metadata.getSubject();
            case 2:
                return metadata.getSender();
            case 3:
                return metadata.getFrom();
            case 4:
                return metadata.getTo();
            case 5:
                return metadata.getDate();
            default:
                return QVariant();
            }
        }
        else
        {
            return QVariant();
        }
    }
    else
    {
        return QVariant();
    }
}

QVariant MessageMetadataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return "ID";
            case 1:
                return "Subject";
            case 2:
                return "Sender";
            case 3:
                return "From";
            case 4:
                return "To";
            case 5:
                return "Date";
            }
        }
    }
    return QVariant();
}