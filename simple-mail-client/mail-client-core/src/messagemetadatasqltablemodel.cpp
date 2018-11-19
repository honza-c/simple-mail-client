#include "messagemetadatasqltablemodel.h"

QVariant MessageMetadataSqlTableModel::data(const QModelIndex &index, int role) const
{
    QModelIndex isSeenIndex = this->index(index.row(), 3, QModelIndex());
    bool isSeen = QSqlTableModel::data(isSeenIndex, Qt::DisplayRole).toInt() == 1;

    if (role == Qt::FontRole && !isSeen)
    {
        QFont font;
        font.setBold(true);
        return font;
    }
    else if (index.column() == 8 && role == Qt::DisplayRole)
    {
        QString timeData = QSqlTableModel::data(index, role).toString();
        return QDateTime::fromSecsSinceEpoch(timeData.toLong()).toString("dd.MM.yyyy HH:mm");
    }
    else if (index.column() == 9 && role == Qt::DisplayRole)
    {
        QString jsonString = QSqlTableModel::data(index, role).toString();
        Contact sender = Contact::contactFromJson(jsonString);

        if (sender.name() != QString())
        {
            return sender.name();
        }
        else
        {
            return sender.emailAddress();
        }
    }
    else
    {
        return QSqlTableModel::data(index, role);
    }
}

void MessageMetadataSqlTableModel::onTableHeaderClicked(int column)
{
    static bool ascending = false;

    if (ascending)
    {
        ascending = false;
        this->sort(column, Qt::DescendingOrder);
    }
    else
    {
        ascending = true;
        this->sort(column, Qt::AscendingOrder);
    }
}

void MessageMetadataSqlTableModel::currentRowChanged(const QModelIndex &index, const QModelIndex &previous)
{
    QModelIndex isSeenIndex = this->index(index.row(), 3, QModelIndex());

    if (QSqlTableModel::data(isSeenIndex, Qt::DisplayRole).toInt() == 0)
    {
        QSqlTableModel::setData(isSeenIndex, 1);
    }
}

QVariant MessageMetadataSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return "ID";
        case 8:
            return "Date";
        case 9:
            return "Sender";
        case 10:
            return "Size";
        case 11:
            return "Subject";
        default:
            return QVariant();
        }
    }

    return QVariant();
}
