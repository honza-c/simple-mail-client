#ifndef MESSAGEMETADATATABLEMODEL_H
#define MESSAGEMETADATATABLEMODEL_H

#include <QObject>
#include <QtWidgets>
#include "messagemetadata.h"

class MessageMetadataTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MessageMetadataTableModel(QList<MessageMetadata> messagesMetadata);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

signals:

public slots:

private:
    QList<MessageMetadata> messagesMetadata;
};

#endif // MESSAGEMETADATATABLEMODEL_H
