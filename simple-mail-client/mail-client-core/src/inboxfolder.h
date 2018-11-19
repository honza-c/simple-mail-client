#ifndef INBOXFOLDER_H
#define INBOXFOLDER_H

#include <QObject>
#include <QDebug>
#include <QIcon>

class InboxFolder : public QObject
{
    Q_OBJECT
public:
    explicit InboxFolder(QObject *parent = nullptr)
        : QObject(parent) {}
    InboxFolder(const InboxFolder &other);
    InboxFolder &operator=(const InboxFolder &other);

    QString path() const;
    void setPath(const QString path);

    QString emailAddress() const;
    void setEmailAddress(const QString emailAddress);

    bool isAllMessages() const;
    void setIsAllMessages(const bool isAllMessages);

    bool isArchive() const;
    void setIsArchive(const bool isArchive);

    bool isDrafts() const;
    void setIsDrafts(const bool isDrafts);

    bool isFlagged() const;
    void setIsFlagged(const bool isFlagged);

    bool isImportant() const;
    void setIsImportant(const bool isImportant);

    bool isJunk() const;
    void setIsJunk(const bool isJunk);

    bool isSent() const;
    void setIsSent(const bool isSent);

    bool isTrash() const;
    void setIsTrash(const bool isTrash);

    bool hasChildren() const;
    void setHasChildren(const bool hasChildren);

    QIcon getIcon() const;

signals:

public slots:

private:
    QString m_path;
    QString m_emailAddress;
    bool m_isAllMessages;
    bool m_isArchive;
    bool m_isDrafts;
    bool m_isFlagged;
    bool m_isImportant;
    bool m_isJunk;
    bool m_isSent;
    bool m_isTrash;
    bool m_hasChildren;
};

QDebug operator<<(QDebug debug, const InboxFolder &inboxFolder);

#endif // INBOXFOLDER_H
