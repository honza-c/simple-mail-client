#include "inboxfoldertreemodel.h"

InboxFolderTreeModel::InboxFolderTreeModel(const QList<QList<InboxFolder>> &data, QObject *parent)
    : QAbstractItemModel (parent)
{
    QList<QVariant> captionData;
    captionData << "Folders";
    rootItem = new InboxFolderTreeItem(captionData);

    for (int i = 0; i < data.length(); i++)
    {
        parseFolderTree(data.at(i), rootItem);
    }
}

void InboxFolderTreeModel::parseFolderTree(QList<InboxFolder> folderList, InboxFolderTreeItem *parentItem)
{
    QList<QVariant> rootItemData;
    InboxFolder rootFolder = folderList.at(0);
    QIcon rootFolderIcon = getIcon(rootFolder);
    rootItemData << rootFolder.getEmailAddress() << rootFolderIcon;

    InboxFolderTreeItem *rootTreeItem = new InboxFolderTreeItem(rootItemData, parentItem);
    parentItem->appendChild(rootTreeItem);

    int level = 0;
    InboxFolderTreeItem *previousItem = rootTreeItem;

    for (int i = 0; i < folderList.length(); i++)
    {
        InboxFolder folder = folderList.at(i);

        if (folder.getPath() == "/")
        {
            continue;
        }

        int currentLevel = getLevel(folder.getPath());
        QString name = getNameFromPath(folder.getPath());
        QIcon icon = getIcon(folder);
        QList<QVariant> folderData;
        folderData << name << icon;

        if (currentLevel == level + 1)
        {
            level++;
            InboxFolderTreeItem *item = new InboxFolderTreeItem(folderData, previousItem);
            previousItem->appendChild(item);
            previousItem = item;
        }
        else
        {
            while (currentLevel != level + 1)
            {
                level--;
                previousItem = previousItem->parentItem();
            }

            level++;
            InboxFolderTreeItem *item = new InboxFolderTreeItem(folderData, previousItem);
            previousItem->appendChild(item);
            previousItem = item;
        }
    }
}

InboxFolderTreeModel::~InboxFolderTreeModel()
{
    delete rootItem;
}

QModelIndex InboxFolderTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    InboxFolderTreeItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<InboxFolderTreeItem*>(parent.internalPointer());
    }

    InboxFolderTreeItem *childItem = parentItem->child(row);

    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex InboxFolderTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    InboxFolderTreeItem *childItem = static_cast<InboxFolderTreeItem*>(index.internalPointer());
    InboxFolderTreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int InboxFolderTreeModel::rowCount(const QModelIndex &parent) const
{
    InboxFolderTreeItem *parentItem;

    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<InboxFolderTreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int InboxFolderTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant InboxFolderTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    InboxFolderTreeItem *item = static_cast<InboxFolderTreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        return item->data(0);
    }
    else if (role == Qt::DecorationRole)
    {
        return item->data(1);
    }
    else
    {
        return QVariant();
    }
}

Qt::ItemFlags InboxFolderTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return nullptr;
    }

    return QAbstractItemModel::flags(index);
}

int InboxFolderTreeModel::getLevel(QString path)
{
    return path.count('/');
}

QString InboxFolderTreeModel::getNameFromPath(QString path)
{
    return path.split('/').last();
}

QIcon InboxFolderTreeModel::getIcon(InboxFolder folder)
{
    if (folder.isArchive())
    {
        return QIcon::fromTheme("mail-read");
    }
    else if (folder.isDrafts())
    {
        return QIcon::fromTheme("mail-read");
    }
    else if (folder.isFlagged())
    {
        return QIcon::fromTheme("emblem-mail");
    }
    else if (folder.isImportant())
    {
        return QIcon::fromTheme("mail-mark-important");
    }
    else if (folder.isJunk())
    {
        return QIcon::fromTheme("mail-mark-junk");
    }
    else if (folder.isTrash())
    {
        return QIcon::fromTheme("user-trash");
    }
    else if (folder.isSent())
    {
        return QIcon::fromTheme("mail-send");
    }
    else
    {
        return QIcon::fromTheme("folder");
    }
}
