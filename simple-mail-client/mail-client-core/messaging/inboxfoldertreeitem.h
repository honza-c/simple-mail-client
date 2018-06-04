#ifndef INBOXFOLDERTREEITEM_H
#define INBOXFOLDERTREEITEM_H

#include <QtWidgets>

class InboxFolderTreeItem
{
public:
    explicit InboxFolderTreeItem(const QList<QVariant> &data, InboxFolderTreeItem *parent = nullptr);
    ~InboxFolderTreeItem();

    void appendChild(InboxFolderTreeItem *item);
    InboxFolderTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    InboxFolderTreeItem *parentItem();

private:
    QList<InboxFolderTreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    InboxFolderTreeItem *m_parentItem;
};

#endif // INBOXFOLDERTREEITEM_H
