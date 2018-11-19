#include "useraccount.h"

UserAccount::UserAccount(QObject *parent)
    : QObject (parent)
{
    m_smtpServerPort = 0;
    m_incomingServerPort = 0;
}

UserAccount::UserAccount(const UserAccount &other)
{
    m_accountName = other.m_accountName;
    m_contactName = other.m_contactName;
    m_emailAddress = other.m_emailAddress;
    m_userName = other.m_userName;
    m_password = other.m_password;

    m_smtpServerUrl = other.m_smtpServerUrl;
    m_smtpServerPort = other.m_smtpServerPort;

    m_incomingServerType = other.m_incomingServerType;
    m_incomingServerAddress = other.m_incomingServerAddress;
    m_incomingServerPort = other.m_incomingServerPort;

    m_inboxService = other.m_inboxService;
}

UserAccount& UserAccount::operator=(const UserAccount &other)
{
    m_accountName = other.m_accountName;
    m_contactName = other.m_contactName;
    m_emailAddress = other.m_emailAddress;
    m_userName = other.m_userName;
    m_password = other.m_password;

    m_smtpServerUrl = other.m_smtpServerUrl;
    m_smtpServerPort = other.m_smtpServerPort;

    m_incomingServerType = other.m_incomingServerType;
    m_incomingServerAddress = other.m_incomingServerAddress;
    m_incomingServerPort = other.m_incomingServerPort;

    m_inboxService = other.m_inboxService;

    return *this;
}

QString UserAccount::accountName() const
{
    return m_accountName;
}

void UserAccount::setAccountName(QString accountName)
{
    m_accountName = accountName;
}

QString UserAccount:: contactName() const
{
    return m_contactName;
}

void UserAccount::setContactName(QString userName)
{
    m_contactName = userName;
}

QString UserAccount::emailAddress() const
{
    return m_emailAddress;
}

void UserAccount::setEmailAddress(QString emailAddress)
{
    m_emailAddress = emailAddress;
}

QString UserAccount::userName() const
{
    return m_userName;
}

void UserAccount::setUserName(const QString userName)
{
    m_userName = userName;
}

QString UserAccount::password() const
{
    return m_password;
}

void UserAccount::setPassword(QString password)
{
    m_password = password;
}

QString UserAccount::smtpServerUrl() const
{
    return m_smtpServerUrl;
}

void UserAccount::setSmtpServerUrl(QString smtpServerUrl)
{
    m_smtpServerUrl = smtpServerUrl;
}

int UserAccount::smtpServerPort() const
{
    return m_smtpServerPort;
}

void UserAccount::setSmtpServerPort(int smtpServerPort)
{
    m_smtpServerPort = smtpServerPort;
}

UserAccount::IncomingServerType UserAccount::incomingServerType() const
{
    return m_incomingServerType;
}

void UserAccount::setIncomingServerType(IncomingServerType type)
{
    m_incomingServerType = type;
}

QString UserAccount::incomingServerAddress() const
{
    return m_incomingServerAddress;
}

void UserAccount:: setIncomingServerAddress(QString incomingServerAddress)
{
    m_incomingServerAddress = incomingServerAddress;
}

int UserAccount::incomingServerPort() const
{
    return m_incomingServerPort;
}

void UserAccount::setIncomingServerPort(int incomingServerPort)
{
    m_incomingServerPort = incomingServerPort;
}

void UserAccount::updateFolderStructureInDatabase(QList<InboxFolder> folders)
{
    QStringList folderPathsFromDatabase = DatabaseManager::getFoldersPathForAccount(m_emailAddress);

    for (QString path : folderPathsFromDatabase)
    {
        bool found = false;

        for (InboxFolder folder : folders)
        {
            if (folder.path() == path)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            DatabaseManager::deleteFolderFromDatabase(m_emailAddress, path);
        }
    }

    for (InboxFolder folder : folders)
    {
        bool found = false;

        for (QString path : folderPathsFromDatabase)
        {
            if (folder.path() == path)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            DatabaseManager::addFolderToDatabase(folder);
        }
    }

    emit inboxStructureChanged();
}

void UserAccount::initializeInbox()
{
    fetchStoreContent();
}

QFuture<QList<InboxFolder>> UserAccount::fetchInboxFolders()
{
    auto fetchInboxFoldersWorker = [](
            const connectionSettingsHolder settings)
    {
        VmimeInboxService *inboxService = nullptr;

        if (settings.incomingServerType == UserAccount::IMAP)
        {
            inboxService = new VmimeImapService();
        }
        else if (settings.incomingServerType == UserAccount::POP3)
        {
            inboxService = new VmimePop3Service();
        }

        if (inboxService != nullptr)
        {
            inboxService->setEmailAddress(settings.emailAddress);
            inboxService->setUserName(settings.userName);
            inboxService->setPassword(settings.password);
            inboxService->setServerUrl(settings.incomingServerAddress);
            inboxService->setPort(settings.incomingServerPort);

            return inboxService->fetchInboxFolders();
        }
        else
        {
            return QList<InboxFolder>();
        }
    };

    return QtConcurrent::run(fetchInboxFoldersWorker, getConnectionSettings());
}

QFuture<bool> UserAccount::moveMessageThread(const QString sourceFolderPath, const int messageId, const QString destinationFolderPath)
{
    auto moveMessageWorker = [](
            const connectionSettingsHolder settings,
            const QString sourceFolderPath,
            const int messageId,
            const QString destinationFolderPath)
    {
        VmimeInboxService *inboxService = nullptr;

        if (settings.incomingServerType == UserAccount::IMAP)
        {
            inboxService = new VmimeImapService();
        }
        else if (settings.incomingServerType == UserAccount::POP3)
        {
            inboxService = new VmimePop3Service();
        }

        if (inboxService != nullptr)
        {
            inboxService->setEmailAddress(settings.emailAddress);
            inboxService->setUserName(settings.userName);
            inboxService->setPassword(settings.password);
            inboxService->setServerUrl(settings.incomingServerAddress);
            inboxService->setPort(settings.incomingServerPort);

            inboxService->moveMessage(sourceFolderPath, messageId, destinationFolderPath);

            return true;
        }
        return false;
    };

    return QtConcurrent::run(moveMessageWorker, getConnectionSettings(), sourceFolderPath, messageId, destinationFolderPath);
}

void UserAccount::moveMessage(const QString sourceFolderPath, const int messageId, const QString destinationFolderPath)
{
    QFuture<bool> future = moveMessageThread(sourceFolderPath, messageId, destinationFolderPath);
    QFutureWatcher<bool> *watcher = new QFutureWatcher<bool>();

    connect(watcher, &QFutureWatcher<bool>::finished, [=](){
        qWarning() << "Presun zprav dobehl se stavem: " << future.result();
    });

    watcher->setFuture(future);
}

void UserAccount::fetchStoreContent()
{
    QFuture<QList<InboxFolder>> future = fetchInboxFolders();

    QFutureWatcher<QList<InboxFolder>> *watcher = new QFutureWatcher<QList<InboxFolder>>();

    connect(watcher, &QFutureWatcher<QList<InboxFolder>>::finished, [=](){
        updateFolderStructureInDatabase(future.result());
        fetchMessageMetadata(future.result());
    });

    watcher->setFuture(future);
}

void UserAccount::fetchMessageMetadata(QList<InboxFolder> folders)
{
    QMap<QString, int> folderPathsWithMessagesCountsInDb;

    for (InboxFolder folder : folders)
    {
        folderPathsWithMessagesCountsInDb[folder.path()] = DatabaseManager::getMessagesCountForFolder(m_emailAddress, folder.path());
    }

    QFuture<QList<MessageMetadata>> future = fetchMessagesMetadata(folderPathsWithMessagesCountsInDb);
    QFutureWatcher<QList<MessageMetadata>> *watcher = new QFutureWatcher<QList<MessageMetadata>>();

    connect(watcher, &QFutureWatcher<QList<MessageMetadata>>::finished, [=](){
        DatabaseManager::addMessagesMetadataToDatabase(future.result());

        QList<MessageMetadata> metadataList = future.result();
        int unreadMessages = 0;

        for (MessageMetadata metadata : metadataList)
        {
            if (!metadata.isSeen())
            {
                unreadMessages++;
            }
        }

        if (unreadMessages > 0)
        {
            emit newMessagesReceived(m_emailAddress, unreadMessages);
        }
    });

    watcher->setFuture(future);
}

void UserAccount::sendMessage(Message message) const
{
    auto sendMessageWorker = [](
            const connectionSettingsHolder settings,
            const Message message)
    {
        VmimeSmtpService smtpService;

        smtpService.setEmailAddress(settings.emailAddress);
        smtpService.setUserName(settings.userName);
        smtpService.setPassword(settings.password);
        smtpService.setServerUrl(settings.smtpServerUrl);
        smtpService.setPort(settings.smtpServerPort);

        smtpService.sendMessage(message);
    };

    QtConcurrent::run(sendMessageWorker, getConnectionSettings(),message);
}

void UserAccount::fetchMissingMessageContent(const QString folderPath, const int positionInFolder)
{
    QFuture<MessageContent> future = fetchMessageContent(folderPath, positionInFolder);
    QFutureWatcher<MessageContent> *watcher = new QFutureWatcher<MessageContent>();

    connect(watcher, &QFutureWatcher<MessageContent>::finished, [=](){
        updateMessageContentInDatabase(folderPath, positionInFolder, future.result());
    });

    watcher->setFuture(future);
}

QFuture<MessageContent> UserAccount::fetchMessageContent(QString folderPath, int positionInFolder)
{
    auto fetchMessageContentWorker = [](
            const connectionSettingsHolder settings,
            const QString folderPath,
            const int positionInFolder)
    {
        VmimeInboxService *inboxService = nullptr;

        if (settings.incomingServerType == UserAccount::IMAP)
        {
            inboxService = new VmimeImapService();
        }
        else if (settings.incomingServerType == UserAccount::POP3)
        {
            inboxService = new VmimePop3Service();
        }

        if (inboxService != nullptr)
        {
            inboxService->setEmailAddress(settings.emailAddress);
            inboxService->setUserName(settings.userName);
            inboxService->setPassword(settings.password);
            inboxService->setServerUrl(settings.incomingServerAddress);
            inboxService->setPort(settings.incomingServerPort);

            return inboxService->fetchMessageContent(folderPath, positionInFolder);
        }
        else
        {
            return MessageContent();
        }
    };

    return QtConcurrent::run(fetchMessageContentWorker, getConnectionSettings(), folderPath, positionInFolder);
}

UserAccount::connectionSettingsHolder UserAccount::getConnectionSettings() const
{
    connectionSettingsHolder settings;

    settings.contactName = m_contactName;
    settings.userName = m_userName;
    settings.emailAddress = m_emailAddress;
    settings.password = m_password;
    settings.smtpServerUrl = m_smtpServerUrl;
    settings.smtpServerPort = m_smtpServerPort;
    settings.incomingServerType = m_incomingServerType;
    settings.incomingServerAddress = m_incomingServerAddress;
    settings.incomingServerPort = m_incomingServerPort;

    return settings;
}

QFuture<QList<MessageMetadata>> UserAccount::fetchMessagesMetadata(QMap<QString, int> folderPathsWithMessagesCountsInDb)
{
    auto fetchMessageMetadataWorker = [](
            const connectionSettingsHolder settings,
            const QMap<QString, int> folderPathsWithMessagesCountInDb)
    {
        VmimeInboxService *inboxService = nullptr;

        if (settings.incomingServerType == UserAccount::IMAP)
        {
            inboxService = new VmimeImapService();
        }
        else if (settings.incomingServerType == UserAccount::POP3)
        {
            inboxService = new VmimePop3Service();
        }

        if (inboxService != nullptr)
        {
            inboxService->setEmailAddress(settings.emailAddress);
            inboxService->setUserName(settings.userName);
            inboxService->setPassword(settings.password);
            inboxService->setServerUrl(settings.incomingServerAddress);
            inboxService->setPort(settings.incomingServerPort);

            return inboxService->fetchMessagesMetadata(folderPathsWithMessagesCountInDb);
        }
        else
        {
            return QList<MessageMetadata>();
        }
    };

    return QtConcurrent::run(fetchMessageMetadataWorker, getConnectionSettings(), folderPathsWithMessagesCountsInDb);
}

void UserAccount::updateMessageContentInDatabase(const QString folderPath, const int positionInFolder, MessageContent messageContent)
{
    if (messageContent != MessageContent())
    {
        int folderId = DatabaseManager::getFolderId(m_emailAddress, folderPath);
        int messageId = DatabaseManager::getMessageId(folderId, positionInFolder);

        DatabaseManager::updateHtmlContent(messageId, messageContent.htmlContent());
        DatabaseManager::updatePlainTextContent(messageId, messageContent.plainTextContent());
        DatabaseManager::updateAttachmentsContent(messageId, messageContent.attachments());
        DatabaseManager::updateEmbeddedObjectsContent(messageId, messageContent.embeddedObjects());
        DatabaseManager::updateRecipients(messageId, messageContent.recipients());
        DatabaseManager::updateCopyRecipients(messageId, messageContent.copyRecipients());
        DatabaseManager::updateBlindCopyRecipients(messageId, messageContent.blindCopyRecipients());

        emit messageContentFetched(messageId);
    }
}

QDebug operator<<(QDebug debug, const UserAccount &account)
{
    QString incomingServerType;

    if (account.incomingServerType() == UserAccount::IMAP)
    {
        incomingServerType = "IMAP";
    }
    else
    {
        incomingServerType = "POP3";
    }

    QDebugStateSaver saver(debug);

    debug.noquote() << "Account name: "
                    << account.accountName()
                    << "\nContact name: "
                    << account.contactName()
                    << "\nEmail address: "
                    << account.emailAddress()
                    << "\nUser name: "
                    << account.userName()
                    << "\nPassword: "
                    << account.password()
                    << "\nSMTP server URL: "
                    << account.smtpServerUrl()
                    << "\nSMTP server port: "
                    << account.smtpServerPort()
                    << "\nIncoming server type: "
                    << incomingServerType
                    << "\nIncoming server address: "
                    << account.incomingServerAddress()
                    << "\nIncoming server port: "
                    << account.incomingServerPort();

    return debug;
}
