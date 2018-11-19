#include "message.h"

Message::Message(const Message &other)
{
    m_sender = other.m_sender;
    m_subject = other.m_subject;

    m_addressListTo = other.m_addressListTo;
    m_addressListInCopy = other.m_addressListInCopy;
    m_addressListInBlindCopy = other.m_addressListInBlindCopy;
    m_addressListReplyTo = other.m_addressListReplyTo;

    m_plainTextContent = other.m_plainTextContent;
    m_htmlContent = other.m_htmlContent;

    m_attachments = other.m_attachments;
    m_embeddedObjects = other.m_embeddedObjects;

    m_dateTime = other.m_dateTime;
}

Message& Message::operator=(const Message &other)
{
    m_sender = other.m_sender;
    m_subject = other.m_subject;

    m_addressListTo = other.m_addressListTo;
    m_addressListInCopy = other.m_addressListInCopy;
    m_addressListInBlindCopy = other.m_addressListInBlindCopy;
    m_addressListReplyTo = other.m_addressListReplyTo;

    m_plainTextContent = other.m_plainTextContent;
    m_htmlContent = other.m_htmlContent;

    m_attachments = other.m_attachments;
    m_embeddedObjects = other.m_embeddedObjects;

    m_dateTime = other.m_dateTime;

    return *this;
}

Contact Message::sender() const
{
    return m_sender;
}

void Message::setSender(const Contact sender)
{
    m_sender = sender;
}

QString Message::subject() const
{
    return m_subject;
}

void Message::setSubject(const QString subject)
{
    m_subject = subject;
}

QList<Contact> Message::addressListTo() const
{
    return m_addressListTo;
}

void Message::setAddressListTo(const QList<Contact> addressListTo)
{
    m_addressListTo = addressListTo;
}

QList<Contact> Message::addressListInCopy() const
{
    return m_addressListInCopy;
}

void Message::setAddressListInCopy(const QList<Contact> addressListInCopy)
{
    m_addressListInCopy = addressListInCopy;
}

QList<Contact> Message::addressListInBlindCopy() const
{
    return m_addressListInBlindCopy;
}

void Message::setAddressListInBlindCopy(const QList<Contact> addressListInBlindCopy)
{
    m_addressListInBlindCopy = addressListInBlindCopy;
}

QList<Contact> Message::replyTo() const
{
    return m_addressListReplyTo;
}

void Message::setReplyTo(const QList<Contact> replyTo)
{
    m_addressListReplyTo = replyTo;
}

QString Message::plainTextContent() const
{
    return m_plainTextContent;
}

void Message::setPlainTextContent(const QString plainTextContent)
{
    m_plainTextContent = plainTextContent;
}

QString Message::htmlContent() const
{
    return m_htmlContent;
}

void Message::setHtmlContent(const QString htmlContent)
{
    m_htmlContent = htmlContent;
}

QList<Attachment> Message::attachments() const
{
    return m_attachments;
}

void Message::setAttachments(const QList<Attachment> attachments)
{
    m_attachments = attachments;
}

QList<EmbeddedObject> Message::embeddedObjects() const
{
    return m_embeddedObjects;
}

void Message::setEmbeddedObjects(QList<EmbeddedObject> embeddedObjects)
{
    m_embeddedObjects = embeddedObjects;
}

QDateTime Message::dateTime() const
{
    return m_dateTime;
}

void Message::setDateTime(const QDateTime dateTime)
{
    m_dateTime = dateTime;
}

QDebug operator<<(QDebug debug, const Message &message)
{
    QDebugStateSaver saver(debug);

    debug.noquote() << "Sender: "
                    << message.sender()
                    << "\nSubject: "
                    << message.subject()
                    << "\nAddressListTo: ";

    for (Contact address : message.addressListTo())
    {
        debug.noquote() << address << ", ";
    }

    debug.noquote() << "\nAddressListInCopy: ";

    for (Contact address : message.addressListInCopy())
    {
        debug.noquote() << address << ", ";
    }

    debug.noquote() << "\nAddressListInBlindCopy: ";

    for (Contact address : message.addressListInBlindCopy())
    {
        debug.noquote() << address << ", ";
    }

    debug.noquote() << "\nAddressListReplyTo: ";

    for (Contact address : message.replyTo())
    {
        debug.noquote() << address << ", ";
    }

    debug.noquote() << "\nAttachments: ";

    for (Attachment attachment : message.attachments())
    {
        debug.noquote() << attachment.name() << ", ";
    }

    debug.noquote() << "\nEmbedded objects: ";

    for (Attachment embeddedObject : message.embeddedObjects())
    {
        debug.noquote() << embeddedObject.name() << ", ";
    }

    debug.noquote() << "\nDate and time: " << message.dateTime().toString("dd.MM.yyyy HH:mm");

    return debug;
}
