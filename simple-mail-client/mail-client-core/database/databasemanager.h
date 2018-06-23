#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QFile>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include "tools/constants.h"
#include "messaging/inboxfolder.h"
#include "messaging/messagemetadata.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    void addFolderToDatabase(InboxFolder folder);
    void addMessageDataToDatabase(MessageMetadata msgData);

signals:

public slots:

private:
    QSqlDatabase database;

    QStringList tableNames;
    QStringList mailFolderTableFields;
    QStringList messageDataTableFields;

    bool checkDatabaseStructure();
    bool checkTableStructure(QString tableName);
    bool checkTableStructure(QSqlRecord tableRecord, QStringList tableFields);
    void initializeDatabaseStructure();
};

#endif // DATABASEMANAGER_H
