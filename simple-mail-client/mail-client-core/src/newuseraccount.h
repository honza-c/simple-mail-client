#ifndef NEWUSERACCOUNT_H
#define NEWUSERACCOUNT_H

#include <QObject>
#include <QDebug>

class NewUserAccount : public QObject
{
    Q_OBJECT
public:
    explicit NewUserAccount(QObject *parent = nullptr)
        : QObject (parent){}
    NewUserAccount(const NewUserAccount &other);
    NewUserAccount &operator=(const NewUserAccount &other);

    enum IncomingServerType { POP3, IMAP };

    QString accountName() const;
    void setAccountName(const QString accountName);

    QString userName() const;
    void setUserName(const QString userName);

    QString emailAddress() const;
    void setEmailAddress(const QString emailAddress);

    QString password() const;
    void setPassword(const QString password);

    QString smtpServerUrl() const;
    void setSmtpServerUrl(const QString smtpServerUrl);

    int smtpServerPort() const;
    void setSmtpServerPort(const int smtpServerPort);

    IncomingServerType incomingServerType() const;
    void setIncomingServerType(const IncomingServerType type);

    QString incomingServerAddress() const;
    void setIncomingServerAddress(const QString incomingServerAddress);

    int incomingServerPort() const;
    void setIncomingServerPort(const int incomingServerPort);

    bool isConnectionSettingsCorrect();
    void initializeInbox();
    void sendMessage();
    void getFolderTreeItemStructure(); // InboxFolderTreeItem*

private:
    QList<QString> fetchMessagesMetadata(); // QList<MessageData>
    void addFoldersToDatabase();
    void addMessageMetadataToDatabase();
    void removeFoldersFromDatabase();
    void removeMessageMetadataFromDatabase();
    void updateMessageContentInDatabase(int messageId);

    QString m_accountName;
    QString m_userName;
    QString m_emailAddress;
    QString m_password;

    QString m_smtpServerUrl;
    int m_smtpServerPort;

    IncomingServerType m_incomingServerType;
    QString m_incomingServerAddress;
    int m_incomingServerPort;

    QString m_inboxService; // VmimeInboxService
    QList<QString> m_inboxFolders;

signals:
    void inboxStructureChanged();

public slots:
};

QDebug operator<<(QDebug debug, const NewUserAccount &account);

#endif // NEWUSERACCOUNT_H
