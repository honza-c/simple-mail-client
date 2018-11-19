#ifndef MESSAGEMETADATASQLTABLEMODEL_H
#define MESSAGEMETADATASQLTABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QDateTime>
#include <QFont>
#include <QDataStream>
#include "src/contact.h"

class MessageMetadataSqlTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
public slots:
    void onTableHeaderClicked(int);
    void currentRowChanged(const QModelIndex &, const QModelIndex &);
};

#endif // MESSAGEMETADATASQLTABLEMODEL_H
