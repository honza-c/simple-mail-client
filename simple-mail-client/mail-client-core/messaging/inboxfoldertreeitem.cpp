#include "inboxfoldertreeitem.h"

InboxFolderTreeItem::InboxFolderTreeItem(const QList<QVariant> &data, InboxFolderTreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

InboxFolderTreeItem::~InboxFolderTreeItem()
{
    qDeleteAll(m_childItems);
}

void InboxFolderTreeItem::appendChild(InboxFolderTreeItem *item)
{
    m_childItems.append(item);
}

InboxFolderTreeItem *InboxFolderTreeItem::child(int row)
{
    return m_childItems.value(row);
}

int InboxFolderTreeItem::childCount() const
{
    return m_childItems.count();
}

int InboxFolderTreeItem::row() const
{
    if (m_parentItem)
    {
        return m_parentItem->m_childItems.indexOf(const_cast<InboxFolderTreeItem*>(this));
    }

    return 0;
}

int InboxFolderTreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant InboxFolderTreeItem::data(int column) const
{
    return m_itemData.value(column);
}

InboxFolderTreeItem *InboxFolderTreeItem::parentItem()
{
    return m_parentItem;
}
