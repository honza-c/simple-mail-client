#ifndef INBOXFOLDER_H
#define INBOXFOLDER_H

#include <QObject>

class InboxFolder : public QObject
{
    Q_OBJECT
public:
    explicit InboxFolder(QObject *parent = nullptr)
        : QObject(parent) {}

    InboxFolder(const InboxFolder &other);
    InboxFolder &operator=(const InboxFolder &other);
    operator QString() const;

    QString getPath();
    QString getEmailAddress();
    bool isAllMessages();
    bool isArchive();
    bool isDrafts();
    bool isFlagged();
    bool isImportant();
    bool isJunk();
    bool isSent();
    bool isTrash();
    bool hasChildren();

    void setPath(QString path);
    void setEmailAddress(QString emailAddress);
    void setIsAllMessages(bool value);
    void setIsArchive(bool value);
    void setIsDrafts(bool value);
    void setIsFlagged(bool value);
    void setIsImportant(bool value);
    void setIsJunk(bool value);
    void setIsSent(bool value);
    void setIsTrash(bool value);
    void setHasChildren(bool value);

private:
    bool allMessages;
    bool archive;
    bool drafts;
    bool flagged;
    bool important;
    bool junk;
    bool sent;
    bool trash;
    bool children;
    QString path;
    QString emailAddress;

signals:

public slots:
};

#endif // INBOXFOLDER_H
