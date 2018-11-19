#include "messagecontent.h"

MessageContent::MessageContent(const MessageContent &other)
{
    m_htmlContent = other.m_htmlContent;
    m_plainTextContent = other.m_plainTextContent;
    m_attachments = other.m_attachments;
    m_embeddedObjects = other.m_embeddedObjects;
    m_recipients = other.m_recipients;
    m_copyRecipients = other.m_copyRecipients;
    m_blindCopyRecipients = other.m_blindCopyRecipients;
}

MessageContent& MessageContent::operator=(const MessageContent &other)
{
    m_htmlContent = other.m_htmlContent;
    m_plainTextContent = other.m_plainTextContent;
    m_attachments = other.m_attachments;
    m_embeddedObjects = other.m_embeddedObjects;
    m_recipients = other.m_recipients;
    m_copyRecipients = other.m_copyRecipients;
    m_blindCopyRecipients = other.m_blindCopyRecipients;

    return *this;
}

bool MessageContent::operator==(const MessageContent &other)
{
    return  m_htmlContent == other.m_htmlContent &&
            m_plainTextContent == other.m_plainTextContent &&
            m_attachments == other.m_attachments &&
            m_embeddedObjects == other.m_embeddedObjects &&
            m_recipients == other.m_recipients &&
            m_copyRecipients == other.m_copyRecipients &&
            m_blindCopyRecipients == other.m_blindCopyRecipients;
}

bool MessageContent::operator!=(const MessageContent &other)
{
    return  m_htmlContent != other.m_htmlContent ||
            m_plainTextContent != other.m_plainTextContent ||
            m_attachments != other.m_attachments ||
            m_embeddedObjects != other.m_embeddedObjects ||
            m_recipients != other.m_recipients ||
            m_copyRecipients != other.m_copyRecipients ||
            m_blindCopyRecipients != other.m_blindCopyRecipients;
}

QString MessageContent::htmlContent() const
{
    return m_htmlContent;
}

void MessageContent::setHtmlContent(const QString htmlContent)
{
    m_htmlContent = htmlContent;
}

QString MessageContent::plainTextContent() const
{
    return m_plainTextContent;
}

void MessageContent::setPlainTextContent(const QString plainTextContent)
{
    m_plainTextContent = plainTextContent;
}

QList<Attachment> MessageContent::attachments() const
{
    return m_attachments;
}

void MessageContent::setAttachments(const QList<Attachment> attachments)
{
    m_attachments = attachments;
}

QList<EmbeddedObject> MessageContent::embeddedObjects() const
{
    return m_embeddedObjects;
}

void MessageContent::setEmbeddedObjects(const QList<EmbeddedObject> embeddedObjects)
{
    m_embeddedObjects = embeddedObjects;
}

QList<Contact> MessageContent::recipients() const
{
    return m_recipients;
}

void MessageContent::setRecipients(const QList<Contact> recipients)
{
    m_recipients = recipients;
}

QList<Contact> MessageContent::copyRecipients() const
{
    return m_copyRecipients;
}

void MessageContent::setCopyRecipients(const QList<Contact> copyRecipients)
{
    m_copyRecipients = copyRecipients;
}

QList<Contact> MessageContent::blindCopyRecipients() const
{
    return m_blindCopyRecipients;
}

void MessageContent::setBlindCopyRecipients(const QList<Contact> blindCopyRecipients)
{
    m_blindCopyRecipients = blindCopyRecipients;
}

QDebug operator<<(QDebug debug, const MessageContent &messageContent)
{
    QDebugStateSaver saver(debug);

    debug.noquote() << "HTML content: "
                    << messageContent.htmlContent()
                    << "\nPlainText content: "
                    << messageContent.plainTextContent()
                    << "\nAttachments: ";

    for (Attachment attachment : messageContent.attachments())
    {
        debug.noquote() << attachment.name() << ", ";
    }

    debug.noquote() << "\nEmbedded objects: ";

    for (Attachment embeddedObject : messageContent.embeddedObjects())
    {
        debug.noquote() << embeddedObject.name() << ", ";
    }

    debug.noquote() << "\nRecipients: ";

    for (Contact contact : messageContent.recipients())
    {
        debug.noquote() << contact;
    }

    debug.noquote() << "\nCopy recipients: ";

    for (Contact contact : messageContent.copyRecipients())
    {
        debug.noquote() << contact;
    }

    debug.noquote() << "\nBlind copy recipients: ";

    for (Contact contact : messageContent.blindCopyRecipients())
    {
        debug.noquote() << contact;
    }

    return debug;
}
