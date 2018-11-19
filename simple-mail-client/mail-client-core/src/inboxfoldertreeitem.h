#ifndef INBOXFOLDERTREEITEM_H
#define INBOXFOLDERTREEITEM_H

#include <QObject>
#include <QVariant>

class InboxFolderTreeItem
{
public:
    explicit InboxFolderTreeItem(const QList<QVariant> &data, InboxFolderTreeItem *parent = nullptr);
    ~InboxFolderTreeItem();

    void appendChild(InboxFolderTreeItem *item);
    void setParent(InboxFolderTreeItem *parent);
    InboxFolderTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    InboxFolderTreeItem *parentItem();

signals:

public slots:

private:

    QList<InboxFolderTreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    InboxFolderTreeItem *m_parentItem;
};

#endif // INBOXFOLDERTREEITEM_H
