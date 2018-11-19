#include "databasemanager.h"

DatabaseManager::DatabaseManager(QString databaseFileName, QObject *parent)
    : QObject(parent)
{
    m_databaseFileName = databaseFileName;

    m_tableNames << "Folders" << "MessageData";

    m_mailFolderTableFields << "id" << "email" << "path" << "flag_all" << "flag_archive"
                            << "flag_drafts" << "flag_important"  << "flag_junk"
                            << "flag_sent" << "flag_trash";

    m_messageDataTableFields << "id" << "folderId" << "positionInFolder" << "flag_seen" << "flag_deleted"
                              << "flag_recent" << "flag_replied" << "flag_draft"
                              << "date" << "sender" << "size" << "subject"
                              << "recipients" << "copyRecipients" << "plainTextContent" << "htmlContent"
                              << "attachments" << "embeddedObjects" << "blindCopyRecipients" << "replyTo";

    if (!checkDatabaseStructure())
    {
        initializeDatabaseStructure();
    }
}


void DatabaseManager::initializeDatabaseStructure()
{
    if (m_database.isOpen())
    {
        m_database.close();
    }

    if (QFile::exists(m_databaseFileName))
    {
        QFile::remove(m_databaseFileName);
    }

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(m_databaseFileName);
    m_database.open();

    QSqlQuery msgFoldersQuery;
    msgFoldersQuery.exec("create table Folders "
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

    QSqlQuery msgDataQuery;
    msgDataQuery.exec("create table MessageData "
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
                      "recipients text, "
                      "copyRecipients text, "
                      "plainTextContent text, "
                      "htmlContent text, "
                      "attachments blob, "
                      "embeddedObjects blob, "
                      "blindCopyRecipients text, "
                      "replyTo text)");

}

bool DatabaseManager::checkDatabaseStructure()
{
    if (!QFile::exists(m_databaseFileName))
    {
        return false;
    }

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(m_databaseFileName);
    m_database.open();

    QStringList tablesFromDatabase = m_database.tables();

    for (QString table : m_tableNames)
    {
        if (!tablesFromDatabase.contains(table))
        {
            qWarning() << "Table " << table << " is not in the database";
            m_database.close();
            return false;
        }
    }

    for (QString table : tablesFromDatabase)
    {
        if (!checkTableStructure(table))
        {
            qWarning() << " Table " << table << " has not valid structure";
            m_database.close();
            return false;
        }
    }

    return true;
}

bool DatabaseManager::checkTableStructure(QString tableName)
{
    QSqlRecord tableRecord = m_database.record(tableName);

    if (tableName == "Folders")
    {
        return  checkTableStructure(tableRecord, m_mailFolderTableFields);
    }
    else if (tableName == "MessageData")
    {
        return checkTableStructure(tableRecord, m_messageDataTableFields);
    }

    qWarning() << tableName << " is not a name of table according to DB structure";

    return false;
}

bool DatabaseManager::checkTableStructure(QSqlRecord tableRecord, QStringList tableFields)
{
    int columnCount = tableRecord.count();

    if (columnCount != tableFields.size())
    {
        qWarning() << "column count doesnt match";
        return false;
    }

    for (QString fieldName : tableFields)
    {
        if (!tableFields.contains(fieldName))
        {
            qWarning() << "column names doesnt match";
            return false;
        }
    }

    return true;
}

int DatabaseManager::getFolderId(const QString emailAddress, const QString folderPath)
{
    int folderId = -1;

    QSqlQuery query;

    query.prepare("SELECT id FROM Folders "
                  "WHERE email = :email AND path = :path");

    query.bindValue(":email", emailAddress);
    query.bindValue(":path", folderPath);
    query.exec();

    while (query.next())
    {
        folderId = query.value(0).toInt();
    }


    return folderId;
}

QString DatabaseManager::getHtmlContent(const int messageId)
{
    QString content;

    QSqlQuery query;

    query.prepare("SELECT htmlContent FROM MessageData "
                  "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);
    query.exec();

    while (query.next())
    {
        content = query.value(0).toString();
    }

    return content;
}

QString DatabaseManager::getTextContent(const int messageId)
{
    QString content;

    QSqlQuery query;

    query.prepare("SELECT plainTextContent FROM MessageData "
                  "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);
    query.exec();

    while (query.next())
    {
        content = query.value(0).toString();
    }

    return content;
}

QList<Contact> DatabaseManager::getRecipients(const int messageId)
{
    QList<Contact> recipients;

    QSqlQuery recipientsQuery;

    recipientsQuery.prepare("SELECT recipients FROM MessageData "
                            "WHERE id = :messageId");

    recipientsQuery.bindValue(":messageId", messageId);
    recipientsQuery.exec();

    while (recipientsQuery.next())
    {
        recipients = Contact::contactsFromJson(recipientsQuery.value(0).toString());
    }

    return recipients;
}

QList<Contact> DatabaseManager::getCopyRecipients(const int messageId)
{
    QList<Contact> copyRecipients;

    QSqlQuery recipientsQuery;

    recipientsQuery.prepare("SELECT copyRecipients FROM MessageData "
                            "WHERE id = :messageId");

    recipientsQuery.bindValue(":messageId", messageId);
    recipientsQuery.exec();

    while (recipientsQuery.next())
    {
        copyRecipients = Contact::contactsFromJson(recipientsQuery.value(0).toString());
    }

    return copyRecipients;
}

QList<Contact> DatabaseManager::getReplyTo(const int messageId)
{
    QList<Contact> replyTo;

    QSqlQuery query;

    query.prepare("SELECT replyTo FROM MessageData "
                            "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);
    query.exec();

    while (query.next())
    {
        replyTo = Contact::contactsFromJson(query.value(0).toString());
    }

    return replyTo;
}

int DatabaseManager::getPositionInFolder(const int messageId)
{
    int positionInFolder = 0;

    QSqlQuery query;

    query.prepare("SELECT positionInFolder FROM MessageData "
                  "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);
    query.exec();

    while (query.next())
    {
        positionInFolder = query.value(0).toInt();
    }

    return positionInFolder;
}

int DatabaseManager::getMessageId(const int folderId, const int positionInFolder)
{
    int messageId = 0;

    QSqlQuery query;

    query.prepare("SELECT id FROM MessageData "
                  "WHERE folderId = :folderId AND positionInFolder = :positionInFolder");

    query.bindValue(":folderId", folderId);
    query.bindValue(":positionInFolder", positionInFolder);
    query.exec();

    while (query.next())
    {
        messageId = query.value(0).toInt();
    }

    return messageId;
}

void DatabaseManager::updateHtmlContent(const int messageId, const QString htmlContent)
{
    QSqlQuery query;

    query.prepare("UPDATE MessageData "
                  "SET htmlContent = :htmlContent "
                  "WHERE id = :messageId");

    query.bindValue(":htmlContent", htmlContent);
    query.bindValue(":messageId", messageId);

    query.exec();
}

void DatabaseManager::updatePlainTextContent(const int messageId, const QString plainTextContent)
{
    QSqlQuery query;

    query.prepare("UPDATE MessageData "
                  "SET plainTextContent = :plainTextContent "
                  "WHERE id = :messageId");

    query.bindValue(":plainTextContent", plainTextContent);
    query.bindValue(":messageId", messageId);

    query.exec();
}

void DatabaseManager::updateRecipients(const int messageId, const QList<Contact> recipients)
{   
    QString jsonString = Contact::toJson(recipients);
    QSqlQuery query;

    query.prepare("UPDATE MessageData "
                  "SET recipients = :json "
                  "WHERE id = :messageId");

    query.bindValue(":json", jsonString);
    query.bindValue(":messageId", messageId);

    query.exec();
}

void DatabaseManager::updateCopyRecipients(const int messageId, const QList<Contact> copyRecipients)
{   
    QString jsonString = Contact::toJson(copyRecipients);
    QSqlQuery query;

    query.prepare("UPDATE MessageData "
                  "SET copyRecipients = :json "
                  "WHERE id = :messageId");

    query.bindValue(":json", jsonString);
    query.bindValue(":messageId", messageId);

    query.exec();
}

void DatabaseManager::updateBlindCopyRecipients(const int messageId, const QList<Contact> blindCopyRecipients)
{    
    QString jsonString = Contact::toJson(blindCopyRecipients);
    QSqlQuery query;

    query.prepare("UPDATE MessageData "
                  "SET blindCopyRecipients = :json "
                  "WHERE id = :messageId");

    query.bindValue(":json", jsonString);
    query.bindValue(":messageId", messageId);

    query.exec();
}

QString DatabaseManager::getSubject(const int messageId)
{
    QString subject;

    QSqlQuery query;

    query.prepare("SELECT subject FROM MessageData "
                  "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);
    query.exec();

    while (query.next())
    {
        subject = query.value(0).toString();
    }

    return subject;
}

Contact DatabaseManager::getSender(const int messageId)
{
    Contact sender;
    QSqlQuery query;

    query.prepare("SELECT sender FROM MessageData "
                  "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);
    query.exec();

    while (query.next())
    {
        sender = Contact::contactFromJson(query.value(0).toString());
    }

    return sender;
}

QDateTime DatabaseManager::getDate(const int messageId)
{
    long dateTime = 0;

    QSqlQuery query;

    query.prepare("SELECT date FROM MessageData "
                  "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);
    query.exec();

    while (query.next())
    {
        dateTime = query.value(0).toLongLong();
    }

    return QDateTime::fromSecsSinceEpoch(dateTime);
}

void DatabaseManager::updateAttachmentsContent(const int messageId, const QList<Attachment> attachments)
{
    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);

    for (Attachment attachment : attachments)
    {
        dataStream << attachment;
    }

    QSqlQuery query;

    query.prepare("UPDATE MessageData "
                  "SET attachments = :byteArray "
                  "WHERE id = :messageId");

    query.bindValue(":byteArray", byteArray);
    query.bindValue(":messageId", messageId);

    query.exec();
}

void DatabaseManager::updateEmbeddedObjectsContent(const int messageId, const QList<EmbeddedObject> embeddedObjects)
{
    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);

    for (EmbeddedObject embeddedObject : embeddedObjects)
    {
        dataStream << embeddedObject;
    }

    QSqlQuery query;

    query.prepare("UPDATE MessageData "
                  "SET embeddedObjects = :byteArray "
                  "WHERE id = :messageId");

    query.bindValue(":byteArray", byteArray);
    query.bindValue(":messageId", messageId);

    query.exec();
}

QList<Attachment> DatabaseManager::getAttachments(const int messageId)
{
    QList<Attachment> attachments;

    QSqlQuery query;

    query.prepare("SELECT attachments FROM MessageData "
                  "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);

    query.exec();

    while (query.next())
    {
        QByteArray byteArray = query.value(0).toByteArray();
        QDataStream dataStream(byteArray);

        while (!dataStream.atEnd())
        {
            Attachment attachment;
            dataStream >> attachment;
            attachments.append(attachment);
        }
    }

    return attachments;
}

QList<EmbeddedObject> DatabaseManager::getEmbeddedObjects(const int messageId)
{
    QList<EmbeddedObject> embeddedObjects;

    QSqlQuery query;

    query.prepare("SELECT embeddedObjects FROM MessageData "
                  "WHERE id = :messageId");

    query.bindValue(":messageId", messageId);

    query.exec();

    while (query.next())
    {
        QByteArray byteArray = query.value(0).toByteArray();
        QDataStream dataStream(byteArray);

        while (!dataStream.atEnd())
        {
            EmbeddedObject embeddedObject;
            dataStream >> embeddedObject;
            embeddedObjects.append(embeddedObject);
        }
    }

    return embeddedObjects;
}

void DatabaseManager::clearDatabase()
{
    initializeDatabaseStructure();
}

QStringList DatabaseManager::getFoldersPathForAccount(const QString emailAddress)
{
    QStringList result;
    QSqlQuery query;

    query.prepare("SELECT path FROM Folders"
                  " WHERE "
                  "email = :email");

    query.bindValue(":email", emailAddress);
    query.exec();

    while (query.next())
    {
        result << query.value(0).toString();
    }

    return result;
}

void DatabaseManager::deleteFolderFromDatabase(const QString emailAddress, const QString path)
{
    int folderId = DatabaseManager::getFolderId(emailAddress, path);

    QSqlQuery deleteMessagesQuery;

    deleteMessagesQuery.prepare("DELETE FROM MessageData"
                                " WHERE "
                                "folderId = :folderId");

    deleteMessagesQuery.bindValue(":folderId", folderId);

    deleteMessagesQuery.exec();

    QSqlQuery deleteFolderQuery;

    deleteFolderQuery.prepare("DELETE FROM Folders"
                              " WHERE "
                              "email = :email AND path = :path");

    deleteFolderQuery.bindValue(":email", emailAddress);
    deleteFolderQuery.bindValue(":path", path);

    deleteFolderQuery.exec();
}

void DatabaseManager::addFolderToDatabase(const InboxFolder folder)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Folders "
                  "(email, path, flag_all, flag_archive, flag_drafts, flag_important, flag_junk, flag_sent, flag_trash)"
                  " VALUES "
                  "(:email, :path, :flag_all, :flag_archive, :flag_drafts, :flag_important, :flag_junk, :flag_sent, :flag_trash)");

    query.bindValue(":email", folder.emailAddress());
    query.bindValue(":path", folder.path());
    query.bindValue(":flag_all", folder.isAllMessages());
    query.bindValue(":flag_archive", folder.isArchive());
    query.bindValue(":flag_drafts", folder.isDrafts());
    query.bindValue(":flag_important", folder.isImportant());
    query.bindValue(":flag_junk", folder.isJunk());
    query.bindValue(":flag_sent", folder.isSent());
    query.bindValue(":flag_trash", folder.isTrash());

    query.exec();
}

int DatabaseManager::getMessagesCountForFolder(const QString emailAddress, const QString path)
{
    int folderId = getFolderId(emailAddress, path);

    QSqlQuery query;

    query.prepare("SELECT"
                  " COUNT( * ) "
                  "FROM MessageData"
                  " WHERE "
                  "folderId = :folderId");

    query.bindValue(":folderId", folderId);

    query.exec();

    if (query.next())
    {
        return query.value(0).toInt();
    }
    else
    {
        return -1;
    }
}

int DatabaseManager::getTotalCountOfUnreadMessages()
{
    QSqlQuery query;

    query.prepare("SELECT"
                  " COUNT( * ) "
                  "FROM MessageData"
                  " WHERE "
                  "flag_seen = :flag_seen");

    query.bindValue(":flag_seen", 0);
    query.exec();

    if (query.next())
    {
        return query.value(0).toInt();
    }
    else
    {
        return -1;
    }
}

int DatabaseManager::getCountOfUnreadMessagesForFolder(QString emailAddress, QString path)
{
    int folderId = getFolderId(emailAddress, path);

    QSqlQuery query;

    query.prepare("SELECT"
                  " COUNT( * ) "
                  "FROM MessageData"
                  " WHERE "
                  "flag_seen = :flag_seen"
                  " AND "
                  "folderId = :folderId");

    query.bindValue(":flag_seen", 0);
    query.bindValue(":folderId", folderId);
    query.exec();

    if (query.next())
    {
        return query.value(0).toInt();
    }
    else
    {
        return -1;
    }
}

void DatabaseManager::addMessagesMetadataToDatabase(const QList<MessageMetadata> metadata)
{
        QSqlQuery query;

        query.prepare("INSERT INTO MessageData "
                      "(folderId, positionInFolder, flag_seen, flag_deleted, flag_recent, flag_replied, flag_draft, date, sender, size, subject, replyTo)"
                      " VALUES "
                      "(:folderId, :positionInFolder, :flag_seen, :flag_deleted, :flag_recent, :flag_replied, :flag_draft, :date, :sender, :size, :subject, :replyTo)");

        QVariantList folderIdInDb, positionInFolder, flag_seen, flag_deleted, flag_recent, flag_replied, flag_draft, date, sender, size, subject, replyTo;

        for (MessageMetadata data : metadata)
        {
            int folderId = getFolderId(data.emailAddress(), data.folderPath());

            if (folderId > 0)
            {
                folderIdInDb << folderId;
                positionInFolder << static_cast<int>(data.messageId());
                flag_seen << data.isSeen();
                flag_deleted << data.isDeleted();
                flag_recent << data.isRecent();
                flag_replied << data.isReplied();
                flag_draft << data.isDraft();
                date << data.dateTime().toSecsSinceEpoch();
                sender << Contact::toJson(data.from());
                size << static_cast<int>(data.size());
                subject << data.subject();
                replyTo << Contact::toJson(data.replyTo());
            }
        }

        query.bindValue(":folderId", folderIdInDb);
        query.bindValue(":positionInFolder", positionInFolder);
        query.bindValue(":flag_seen", flag_seen);
        query.bindValue(":flag_deleted", flag_deleted);
        query.bindValue(":flag_recent", flag_recent);
        query.bindValue(":flag_replied", flag_replied);
        query.bindValue(":flag_draft", flag_draft);
        query.bindValue(":date", date);
        query.bindValue(":sender", sender);
        query.bindValue(":size", size);
        query.bindValue(":subject", subject);
        query.bindValue(":replyTo", replyTo);

        query.execBatch();
}

void DatabaseManager::cleanUnusedDataFromDatabase(const QStringList emailAddresses)
{
    // 1) getting FolderIDs from database, which do not belong to any user account in application
    QList<int> unusedFolderIds;

    QSqlQuery query;

    query.prepare("SELECT * FROM Folders");
    query.exec();

    while (query.next())
    {
        bool found = false;

        for (int i = 0; i < emailAddresses.size(); i++)
        {
            if (query.value(1).toString() == emailAddresses.at(i))
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            unusedFolderIds << query.value(0).toInt();
        }
    }

    // 2) removing messages data which belong to folder ids that are not associated with any user account in application

    for (int folderId : unusedFolderIds)
    {
        QSqlQuery messagesDataQuery;
        messagesDataQuery.prepare("DELETE FROM MessageData"
                                  " WHERE "
                                  "folderId = :folderId");
        messagesDataQuery.bindValue(":folderId", folderId);
        messagesDataQuery.exec();

        QSqlQuery foldersQuery;
        foldersQuery.prepare("DELETE FROM Folders"
                             " WHERE "
                             "id = :folderId");
        foldersQuery.bindValue(":folderId", folderId);
        foldersQuery.exec();
    }
}

QList<InboxFolder> DatabaseManager::getInboxFolders()
{
    QList<InboxFolder> result;

    QSqlQuery query;

    query.exec("SELECT"
                  " * "
                  "FROM Folders"
                  " ORDER BY"
                  " email ASC,"
                  " path ASC");

    while (query.next())
    {
        InboxFolder folder;

        folder.setEmailAddress(query.value(1).toString());
        folder.setPath(query.value(2).toString());
        folder.setIsAllMessages(query.value(3).toBool());
        folder.setIsArchive(query.value(4).toBool());
        folder.setIsDrafts(query.value(5).toBool());
        folder.setIsImportant(query.value(6).toBool());
        folder.setIsJunk(query.value(7).toBool());
        folder.setIsSent(query.value(8).toBool());
        folder.setIsTrash(query.value(9).toBool());

        result << folder;
    }

    return result;
}

QList<InboxFolder> DatabaseManager::getInboxFolders(QString emailAddress)
{
    QList<InboxFolder> result;

    QSqlQuery query;

    query.prepare("SELECT"
                  " * "
                  "FROM Folders"
                  " WHERE "
                  " email = :email "
                  " ORDER BY"
                  " path ASC");

    query.bindValue(":email", emailAddress);
    query.exec();

    while (query.next())
    {
        InboxFolder folder;

        folder.setEmailAddress(query.value(1).toString());
        folder.setPath(query.value(2).toString());
        folder.setIsAllMessages(query.value(3).toBool());
        folder.setIsArchive(query.value(4).toBool());
        folder.setIsDrafts(query.value(5).toBool());
        folder.setIsImportant(query.value(6).toBool());
        folder.setIsJunk(query.value(7).toBool());
        folder.setIsSent(query.value(8).toBool());
        folder.setIsTrash(query.value(9).toBool());

        result << folder;
    }

    return result;
}

QStringList DatabaseManager::getDataForContactsCompleter()
{
    QSet<QString> contacts;

    QSqlQuery senderQuery;
    senderQuery.prepare("SELECT sender FROM MessageData");
    senderQuery.exec();

    while (senderQuery.next())
    {
        Contact sender = Contact::contactFromJson(senderQuery.value(0).toString());
        contacts << Contact::toString(sender);
    }

    QSqlQuery recipientsQuery;
    recipientsQuery.prepare("SELECT recipients FROM MessageData");
    recipientsQuery.exec();

    while (recipientsQuery.next())
    {
        Contact contact = Contact::contactFromJson(recipientsQuery.value(0).toString());
        contacts << Contact::toString(contact);
    }

    QSqlQuery copyRecipientsQuery;
    copyRecipientsQuery.prepare("SELECT copyRecipients FROM MessageData");
    copyRecipientsQuery.exec();

    while (copyRecipientsQuery.next())
    {
        Contact contact = Contact::contactFromJson(copyRecipientsQuery.value(0).toString());
        contacts << Contact::toString(contact);
    }

    QSqlQuery replyToQuery;
    replyToQuery.prepare("SELECT replyTo FROM MessageData");
    replyToQuery.exec();

    while (replyToQuery.next())
    {
        Contact contact = Contact::contactFromJson(replyToQuery.value(0).toString());
        contacts << Contact::toString(contact);
    }

    return contacts.toList();
}

QString DatabaseManager::getFolderPath(int folderId)
{
    QString folderPath;

    QSqlQuery query;

    query.prepare("SELECT path FROM Folders "
                  "WHERE id = :id");

    query.bindValue(":id", folderId);
    query.exec();

    while (query.next())
    {
        folderPath = query.value(0).toString();
    }

    return folderPath;
}

QString DatabaseManager::getEmailAddress(int folderId)
{
    QString emailAddress;

    QSqlQuery query;

    query.prepare("SELECT email FROM Folders "
                  "WHERE id = :id");

    query.bindValue(":id", folderId);
    query.exec();

    while (query.next())
    {
        emailAddress = query.value(0).toString();
    }

    return emailAddress;
}

bool DatabaseManager::isFolderJunk(int folderId)
{
    bool isJunk = false;

    QSqlQuery query;

    query.prepare("SELECT flag_junk FROM Folders "
                  "WHERE id = :id");

    query.bindValue(":id", folderId);
    query.exec();

    while (query.next())
    {
        isJunk = query.value(0).toBool();
    }

    return isJunk;
}

bool DatabaseManager::isFolderTrash(int folderId)
{
    bool isTrash = false;

    QSqlQuery query;

    query.prepare("SELECT flag_trash FROM Folders "
                  "WHERE id = :id");

    query.bindValue(":id", folderId);
    query.exec();

    while (query.next())
    {
        isTrash = query.value(0).toBool();
    }

    return isTrash;
}

bool DatabaseManager::isFolderArchive(int folderId)
{
    bool isArchive = false;

    QSqlQuery query;

    query.prepare("SELECT flag_archive FROM Folders "
                  "WHERE id = :id");

    query.bindValue(":id", folderId);
    query.exec();

    while (query.next())
    {
        isArchive = query.value(0).toBool();
    }

    return isArchive;
}

QString DatabaseManager::getArchiveFolderPathForAccount(QString emailAddress)
{
    QString path;

    QSqlQuery query;

    query.prepare("SELECT path FROM Folders "
                  "WHERE email = :email AND flag_archive = :flag_archive");

    query.bindValue(":email", emailAddress);
    query.bindValue(":flag_archive", 1);

    query.exec();

    while (query.next())
    {
        path = query.value(0).toString();
    }

    return path;
}
