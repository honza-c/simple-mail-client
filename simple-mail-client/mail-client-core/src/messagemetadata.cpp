#include "messagemetadata.h"

MessageMetadata::MessageMetadata(const MessageMetadata &other)
{
    m_emailAddress = other.m_emailAddress;
    m_folderPath = other.m_folderPath;
    m_messageId = other.m_messageId;
    m_size = other.m_size;
    m_dateTime = other.m_dateTime;
    m_from = other.m_from;
    m_replyTo = other.m_replyTo;
    m_subject = other.m_subject;
    m_isDeleted = other.m_isDeleted;
    m_isDraft = other.m_isDraft;
    m_isRecent = other.m_isRecent;
    m_isReplied = other.m_isReplied;
    m_isSeen = other.m_isSeen;
}

MessageMetadata& MessageMetadata::operator=(const MessageMetadata &other)
{
    m_emailAddress = other.m_emailAddress;
    m_folderPath = other.m_folderPath;
    m_messageId = other.m_messageId;
    m_size = other.m_size;
    m_dateTime = other.m_dateTime;
    m_from = other.m_from;
    m_replyTo = other.m_replyTo;
    m_subject = other.m_subject;
    m_isDeleted = other.m_isDeleted;
    m_isDraft = other.m_isDraft;
    m_isRecent = other.m_isRecent;
    m_isReplied = other.m_isReplied;
    m_isSeen = other.m_isSeen;

    return *this;
}

QString MessageMetadata::emailAddress() const
{
    return m_emailAddress;
}

void MessageMetadata::setEmailAddress(const QString emailAddress)
{
    m_emailAddress = emailAddress;
}

QString MessageMetadata::folderPath() const
{
    return m_folderPath;
}

void MessageMetadata::setFolderPath(const QString folderPath)
{
    m_folderPath = folderPath;
}

unsigned long MessageMetadata::messageId() const
{
    return m_messageId;
}

void MessageMetadata::setMessageId(const unsigned long messageId)
{
    m_messageId = messageId;
}

unsigned long MessageMetadata::size() const
{
    return m_size;
}

void MessageMetadata::setSize(const unsigned long size)
{
    m_size = size;
}

QDateTime MessageMetadata::dateTime() const
{
    return m_dateTime;
}

void MessageMetadata::setDateTime(const QDateTime dateTime)
{
    m_dateTime = dateTime;
}

Contact MessageMetadata::from() const
{
    return m_from;
}

void MessageMetadata::setFrom(const Contact from)
{
    m_from = from;
}

QList<Contact> MessageMetadata::replyTo() const
{
    return m_replyTo;
}

void MessageMetadata::setReplyTo(const QList<Contact> replyTo)
{
    m_replyTo = replyTo;
}

QString MessageMetadata::subject() const
{
    return m_subject;
}

void MessageMetadata::setSubject(const QString subject)
{
    m_subject = subject;
}

bool MessageMetadata::isDeleted() const
{
    return m_isDeleted;
}

void MessageMetadata::setIsDeleted(const bool isDeleted)
{
    m_isDeleted = isDeleted;
}

bool MessageMetadata::isDraft() const
{
    return m_isDraft;
}

void MessageMetadata::setIsDraft(const bool isDraft)
{
    m_isDraft = isDraft;
}

bool MessageMetadata::isRecent() const
{
    return m_isRecent;
}

void MessageMetadata::setIsRecent(const bool isRecent)
{
    m_isRecent = isRecent;
}

bool MessageMetadata::isReplied() const
{
    return m_isReplied;
}

void MessageMetadata::setIsReplied(const bool isReplied)
{
    m_isReplied = isReplied;
}

bool MessageMetadata::isSeen() const
{
    return m_isSeen;
}

void MessageMetadata::setIsSeen(const bool isSeen)
{
    m_isSeen = isSeen;
}

QDebug operator<<(QDebug debug, const MessageMetadata &metadata)
{
    QDebugStateSaver saver(debug);

    debug.noquote() << "Email address: "
                    << metadata.emailAddress()
                    << "\nFolder path: "
                    << metadata.folderPath()
                    << "Message ID: "
                    << metadata.messageId()
                    << "\nSize: "
                    << metadata.size()
                    << "\nDate and time: "
                    << metadata.dateTime().toString("")
                    << "\nFrom: "
                    << metadata.from()
                    << "\nReply-To: "
                    << metadata.replyTo()
                    << "\nSubject: "
                    << metadata.subject()
                    << "\nIs deleted: "
                    << metadata.isDeleted()
                    << "\nIs draft: "
                    << metadata.isDraft()
                    << "\nIs recent: "
                    << metadata.isRecent()
                    << "\nIs replied: "
                    << metadata.isReplied()
                    << "\nIs seen: "
                    << metadata.isSeen();

    return debug;
}
