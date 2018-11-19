#ifndef MESSAGEMETADATA_H
#define MESSAGEMETADATA_H

#include <QObject>
#include <QDateTime>
#include "src/contact.h"

class MessageMetadata : public QObject
{
    Q_OBJECT
public:
    explicit MessageMetadata(QObject *parent = nullptr)
        : QObject(parent) {}
    MessageMetadata(const MessageMetadata &other);
    MessageMetadata &operator=(const MessageMetadata &other);

    QString emailAddress() const;
    void setEmailAddress(const QString emailAddress);

    QString folderPath() const;
    void setFolderPath(const QString folderPath);

    unsigned long messageId() const;
    void setMessageId(const unsigned long messageId);

    unsigned long size() const;
    void setSize(const unsigned long size);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime dateTime);

    Contact from() const;
    void setFrom(const Contact from);

    QList<Contact> replyTo() const;
    void setReplyTo(const QList<Contact> replyTo);

    QString subject() const;
    void setSubject(const QString subject);

    bool isDeleted() const;
    void setIsDeleted(const bool isDeleted);

    bool isDraft() const;
    void setIsDraft(const bool isDraft);

    bool isRecent() const;
    void setIsRecent(const bool isRecent);

    bool isReplied() const;
    void setIsReplied(const bool isReplied);

    bool isSeen() const;
    void setIsSeen(const bool isSeen);

signals:

public slots:

private:
    QString m_emailAddress;
    QString m_folderPath;
    unsigned long m_messageId;
    unsigned long m_size;
    QDateTime m_dateTime;
    Contact m_from;
    QList<Contact> m_replyTo;
    QString m_subject;
    bool m_isDeleted;
    bool m_isDraft;
    bool m_isRecent;
    bool m_isReplied;
    bool m_isSeen;
};

QDebug operator<<(QDebug debug, const MessageMetadata &metadata);

#endif // MESSAGEMETADATA_H
