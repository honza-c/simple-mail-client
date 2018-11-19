#ifndef ATTACHMENTSLISTMODEL_H
#define ATTACHMENTSLISTMODEL_H

#include <QObject>
#include <QtWidgets>
#include "src/attachment.h"

class AttachmentsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    AttachmentsListModel(QList<Attachment> &data, QObject *parent = nullptr)
        : QAbstractListModel(parent), m_data(&data) {}

    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

private:
    QList<Attachment> *m_data;
};

#endif // ATTACHMENTSLISTMODEL_H
