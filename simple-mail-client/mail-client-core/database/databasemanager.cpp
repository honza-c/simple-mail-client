#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    this->tableNames << "MailFolders" << "MessageData";

    this->mailFolderTableFields << "id" << "email" << "path" << "flag_all" << "flag_archive"
                                << "flag_drafts" << "flag_important"  << "flag_junk"
                                << "flag_sent" << "flag_trash";

    this->messageDataTableFields << "id" << "folderId" << "positionInFolder" << "flag_seen" << "flag_deleted"
                                 << "flag_recent" << "flag_replied" << "flag_draft"
                                 << "date" << "from" << "size" << "subject"
                                 << "to" << "inCopy" << "plainTextContent" << "htmlContent" << "hasAttachments";

    if (!checkDatabaseStructure())
    {
        if (QFile::exists(Constants::DATABASE_FILE_NAME))
        {
            database.close();
            QFile::remove(Constants::DATABASE_FILE_NAME);
        }

        initializeDatabaseStructure();
    }
}

bool DatabaseManager::checkDatabaseStructure()
{
    if (!QFile::exists(Constants::DATABASE_FILE_NAME))
    {
        return false;
    }

    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->database.setDatabaseName(Constants::DATABASE_FILE_NAME);

    this->database.open();

    QStringList tablesFromDatabase = database.tables();

    for (QString table : this->tableNames)
    {
        if (!tablesFromDatabase.contains(table))
        {
            database.close();
            return false;
        }
    }

    for (QString table : tablesFromDatabase)
    {
        if (!checkTableStructure(table))
        {
            database.close();
            return false;
        }
    }

    return true;
}

bool DatabaseManager::checkTableStructure(QSqlRecord tableRecord, QStringList tableFields)
{
    int columnCount = tableRecord.count();

    if (columnCount != tableFields.size())
    {
        return false;
    }

    for (QString fieldName : tableFields)
    {
        if (!tableFields.contains(fieldName))
        {
            return false;
        }
    }

    return true;
}

bool DatabaseManager::checkTableStructure(QString tableName)
{
    QSqlRecord tableRecord = database.record(tableName);

    if (tableName == "MailFolders")
    {
        return checkTableStructure(tableRecord, this->mailFolderTableFields);
    }
    else if (tableName == "MessageData")
    {
        return checkTableStructure(tableRecord, this->messageDataTableFields);
    }

    return false;
}

void DatabaseManager::initializeDatabaseStructure()
{
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->database.setDatabaseName(Constants::DATABASE_FILE_NAME);
    this->database.open();

    QSqlQuery foldersQuery;
    foldersQuery.exec("create table Folders "
               "(id integer primary key, "
               "email text,"
               "path text,"
               "flag_all integer,"
               "flag_archive integer,"
               "flag_drafts integer,"
               "flag_important integer,"
               "flag_junk integer,"
               "flag_sent integer,"
               "flag_trash integer)");

    QSqlQuery messageDataQuery;

    messageDataQuery.exec("create table MessageData "
               "(id integer primary key, "
               "folderId integer, "
               "positionInFolder integer, "
               "flag_seen integer, "
               "flag_deleted integer, "
               "flag_recent integer, "
               "flag_replied integer, "
               "flag_draft integer, "
               "date text, "
               "sender text, "
               "size integer, "
               "subject text, "
               "recipient text, "
               "inCopy text, "
               "plainTextContent text, "
               "htmlContent text, "
               "hasAttachments integer)");
}

void DatabaseManager::addMessageDataToDatabase(MessageMetadata data)
{
    QSqlQuery query;

    query.prepare("INSERT INTO MessageData "
                  "(folderId, positionInFolder, flag_seen, flag_deleted, flag_recent, flag_replied, flag_draft, date, sender, size, subject, recipient, inCopy, plainTextContent, htmlContent, hasAttachments)"
                  " VALUES "
                  "(:folderId, :positionInFolder, :flag_seen, :flag_deleted, :flag_recent, :flag_replied, :flag_draft, :date, :sender, :size, :subject, :recipient, :inCopy, :plainTextContent, :htmlContent, :hasAttachments)");

    query.bindValue(":folderId", 666);
    query.bindValue(":positionInFolder", static_cast<int>(data.getId()));
    query.bindValue(":flag_seen", data.getIsSeen());
    query.bindValue(":flag_deleted", data.getIsDeleted());
    query.bindValue(":flag_recent", data.getIsRecent());
    query.bindValue(":flag_replied", data.getIsReplied());
    query.bindValue(":flag_draft", data.getIsDraft());
    query.bindValue(":date", data.getDate().toMSecsSinceEpoch());
    query.bindValue(":sender", data.getFromAddress());
    query.bindValue(":size", static_cast<int>(data.getSize()));
    query.bindValue(":subject", data.getSubject());
    query.bindValue(":recipient", "Foo");
    query.bindValue(":inCopy", "Foo");
    query.bindValue(":plainTextContent", "foo");
    query.bindValue(":htmlContent", "foo");
    query.bindValue(":hasAttachments", 0);

    query.exec();
}

void DatabaseManager::addFolderToDatabase(InboxFolder folder)
{
    QSqlQuery query;


    query.prepare("INSERT INTO Folders "
                  "(email, path, flag_all, flag_archive, flag_drafts, flag_important, flag_junk, flag_sent, flag_trash)"
                  " VALUES "
                  "(:email, :path, :flag_all, :flag_archive, :flag_drafts, :flag_important, :flag_junk, :flag_sent, :flag_trash)");

    query.bindValue(":email", folder.getEmailAddress());
    query.bindValue(":path", folder.getPath());
    query.bindValue(":flag_all", folder.isAllMessages());
    query.bindValue(":flag_archive", folder.isArchive());
    query.bindValue(":flag_drafts", folder.isDrafts());
    query.bindValue(":flag_important", folder.isImportant());
    query.bindValue(":flag_junk", folder.isJunk());
    query.bindValue(":flag_sent", folder.isSent());
    query.bindValue(":flag_trash", folder.isTrash());


    query.exec();
}
