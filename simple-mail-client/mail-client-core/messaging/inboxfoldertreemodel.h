#ifndef INBOXFOLDERTREEMODEL_H
#define INBOXFOLDERTREEMODEL_H

#include <QtWidgets>
#include "inboxfoldertreeitem.h"
#include "inboxfolder.h"

class InboxFolderTreeModel : public QAbstractItemModel
{
public:
    InboxFolderTreeModel(const QList<QList<InboxFolder>> &data, QObject *parent = nullptr);
    ~InboxFolderTreeModel() override;

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    void parseFolderTree(QList<InboxFolder> folderList, InboxFolderTreeItem *parentItem);
    int getLevel(QString path);
    QIcon getIcon(InboxFolder folder);
    QString getNameFromPath(QString path);

    InboxFolderTreeItem *rootItem;
};

#endif // INBOXFOLDERTREEMODEL_H
