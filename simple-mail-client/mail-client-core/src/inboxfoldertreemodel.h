#ifndef INBOXFOLDERTREEMODEL_H
#define INBOXFOLDERTREEMODEL_H

#include <QObject>
/*
#include <QAbstractItemModel>
#include <QIcon>
*/
#include <QtWidgets>
#include "src/useraccount.h"
#include "src/vmimeinboxservice.h"
#include "src/vmimeinboxfolder.h"
#include "src/inboxfoldertreeitem.h"

class InboxFolderTreeModel : public QAbstractItemModel
{
public:
    InboxFolderTreeModel(const QList<InboxFolder> &data, QObject *parent = nullptr);
    ~InboxFolderTreeModel() override;

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    void createFolderTreeStructure(QList<InboxFolder> data);
    int getLevel(const QString path) const;
    QIcon getIcon(const InboxFolder folder) const;
    QString getNameFromPath(const QString path) const;

    InboxFolderTreeItem *m_rootItem;
};

#endif // INBOXFOLDERTREEMODEL_H
