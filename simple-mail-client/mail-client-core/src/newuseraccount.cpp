#include "newuseraccount.h"

NewUserAccount::NewUserAccount(const NewUserAccount &other)
{
    m_accountName = other.m_accountName;
    m_userName = other.m_userName;
    m_emailAddress = other.m_emailAddress;
    m_password = other.m_password;

    m_smtpServerUrl = other.m_smtpServerUrl;
    m_smtpServerPort = other.m_smtpServerPort;

    m_incomingServerType = other.m_incomingServerType;
    m_incomingServerAddress = other.m_incomingServerAddress;
    m_incomingServerPort = other.m_incomingServerPort;

    // TODO:
    m_inboxService = other.m_inboxService;
    m_inboxFolders = other.m_inboxFolders;
}

NewUserAccount& NewUserAccount::operator=(const NewUserAccount &other)
{
    m_accountName = other.m_accountName;
    m_userName = other.m_userName;
    m_emailAddress = other.m_emailAddress;
    m_password = other.m_password;

    m_smtpServerUrl = other.m_smtpServerUrl;
    m_smtpServerPort = other.m_smtpServerPort;

    m_incomingServerType = other.m_incomingServerType;
    m_incomingServerAddress = other.m_incomingServerAddress;
    m_incomingServerPort = other.m_incomingServerPort;

    // TODO:
    m_inboxService = other.m_inboxService;
    m_inboxFolders = other.m_inboxFolders;

    return *this;
}

QString NewUserAccount::accountName() const
{
    return m_accountName;
}

void NewUserAccount::setAccountName(QString accountName)
{
    m_accountName = accountName;
}

QString NewUserAccount:: userName() const
{
    return m_userName;
}

void NewUserAccount::setUserName(QString userName)
{
    m_userName = userName;
}

QString NewUserAccount::emailAddress() const
{
    return m_emailAddress;
}

void NewUserAccount::setEmailAddress(QString emailAddress)
{
    m_emailAddress = emailAddress;
}

QString NewUserAccount::password() const
{
    return m_password;
}

void NewUserAccount::setPassword(QString password)
{
    m_password = password;
}

QString NewUserAccount::smtpServerUrl() const
{
    return m_smtpServerUrl;
}

void NewUserAccount::setSmtpServerUrl(QString smtpServerUrl)
{
    m_smtpServerUrl = smtpServerUrl;
}

int NewUserAccount::smtpServerPort() const
{
    return m_smtpServerPort;
}

void NewUserAccount::setSmtpServerPort(int smtpServerPort)
{
    m_smtpServerPort = smtpServerPort;
}

NewUserAccount::IncomingServerType NewUserAccount::incomingServerType() const
{
    return m_incomingServerType;
}

void NewUserAccount::setIncomingServerType(IncomingServerType type)
{
    m_incomingServerType = type;
}

QString NewUserAccount::incomingServerAddress() const
{
    return m_incomingServerAddress;
}

void NewUserAccount:: setIncomingServerAddress(QString incomingServerAddress)
{
    m_incomingServerAddress = incomingServerAddress;
}

int NewUserAccount::incomingServerPort() const
{
    return m_incomingServerPort;
}

void NewUserAccount::setIncomingServerPort(int incomingServerPort)
{
    m_incomingServerPort = incomingServerPort;
}

bool NewUserAccount::isConnectionSettingsCorrect()
{
    // TODO: stub
    return true;
}

void NewUserAccount::initializeInbox()
{
    if (!isConnectionSettingsCorrect())
    {
        return;
    }
    // TODO: stub
}

void NewUserAccount::sendMessage()
{
    // TODO: stub
}

void NewUserAccount::getFolderTreeItemStructure() // InboxFolderTreeItem*
{
    // TODO: stub
}

QList<QString> NewUserAccount::fetchMessagesMetadata() // QList<MessageData>
{
    // TODO: stub

    return QList<QString>();
}

void NewUserAccount::addFoldersToDatabase()
{
    // TODO: stub
}

void NewUserAccount::addMessageMetadataToDatabase()
{
    // TODO: stub
}

void NewUserAccount::removeFoldersFromDatabase()
{
    // TODO: stub
}

void NewUserAccount::removeMessageMetadataFromDatabase()
{
    // TODO: stub
}

void NewUserAccount::updateMessageContentInDatabase(int messageId)
{
    // TODO: stub
}

QDebug operator<<(QDebug debug, const NewUserAccount &account)
{
    QString incomingServerType;

    if (account.incomingServerType() == NewUserAccount::IMAP)
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
                    << "\nUser name: "
                    << account.userName()
                    << "\nEmail address: "
                    << account.emailAddress()
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
