#include "vmimemessagecontentparser.h"

VmimeMessageContentParser::VmimeMessageContentParser(vmime::shared_ptr<vmime::message> message, QObject *parent)
    : QObject(parent), m_message(message)
{
    m_messageParser = vmime::make_shared<vmime::messageParser>(m_message);
}

QString VmimeMessageContentParser::parseHtmlContent() const
{
    return parseTextParts(vmime::mediaTypes::TEXT_HTML);
}

QString VmimeMessageContentParser::parsePlaintextContent() const
{
    return parseTextParts(vmime::mediaTypes::TEXT_PLAIN);
}

QList<Attachment> VmimeMessageContentParser::parseAttachments() const
{
    QList<Attachment> result;

    for (vmime::size_t i = 0; i < m_messageParser->getAttachmentCount(); i++)
    {
        vmime::shared_ptr<const vmime::attachment> vmimeAttachment = m_messageParser->getAttachmentAt(i);

        QString name = vmimeAttachment->getName().getConvertedText(vmime::charsets::UTF_8).c_str();
        QString mimeType = vmimeAttachment->getType().getType().c_str();
        QString mimeSubType = vmimeAttachment->getType().getSubType().c_str();

        vmime::shared_ptr<const vmime::contentHandler> contentHandler = vmimeAttachment->getData();
        QByteArray data = parseContentHandler(contentHandler);

        Attachment attachment;
        attachment.setData(data);
        attachment.setMimeType(mimeType + "/" + mimeSubType);
        attachment.setName(name);

        result.append(attachment);
    }

    return result;
}

QList<EmbeddedObject> VmimeMessageContentParser::parseEmbeddedObjects() const
{
    QList<EmbeddedObject> result;
    std::vector<vmime::shared_ptr<const vmime::htmlTextPart::embeddedObject>> embeddedObjects = extractEmbeddedObjects();

    for (unsigned int i = 0; i < embeddedObjects.size(); i++)
    {
        vmime::shared_ptr<const vmime::htmlTextPart::embeddedObject> vmimeEmbeddedObject = embeddedObjects.at(i);
        QString mediaType = vmimeEmbeddedObject->getType().getType().c_str();
        QString mediaSubType = vmimeEmbeddedObject->getType().getSubType().c_str();
        QString contentId = vmimeEmbeddedObject->getId().c_str();

        QString name = vmimeEmbeddedObject->getId().c_str();
        vmime::shared_ptr<const vmime::contentHandler> contentHandler = vmimeEmbeddedObject->getData();
        QByteArray data = parseContentHandler(contentHandler);

        EmbeddedObject embeddedObject;

        embeddedObject.setContentId(contentId);
        embeddedObject.setData(data);
        embeddedObject.setMimeType(mediaType + "/" + mediaSubType);
        embeddedObject.setName(name);

        result.append(embeddedObject);
    }

    return result;
}

QByteArray VmimeMessageContentParser::parseContentHandler(vmime::shared_ptr<const vmime::contentHandler> contentHandler) const
{
    vmime::size_t length = 0;

    if (contentHandler->isEncoded())
    {
        length = contentHandler->getEncoding().getEncoder()->getDecodedSize(contentHandler->getLength());
    }
    else
    {
        length = contentHandler->getLength();
    }

    if (length > 0)
    {
        std::ostringstream stringStream;
        vmime::utility::outputStreamAdapter outputStreamAdapter(stringStream);
        contentHandler->extract(outputStreamAdapter);

        std::string content = stringStream.str();

        QByteArray byteArray;

        for (unsigned int i = 0; i < content.length(); i++)
        {
            byteArray.append(content[i]);
        }

        return byteArray;
    }

    return QByteArray();
}

std::vector<vmime::shared_ptr<const vmime::htmlTextPart::embeddedObject>> VmimeMessageContentParser::extractEmbeddedObjects() const
{
    std::vector<vmime::shared_ptr<const vmime::htmlTextPart::embeddedObject>> result;

    for (vmime::size_t i = 0; i < m_messageParser->getTextPartCount(); i++)
    {
        vmime::shared_ptr<const vmime::textPart> textPart = m_messageParser->getTextPartAt(i);

        if (textPart->getType().getSubType() == vmime::mediaTypes::TEXT_HTML)
        {
            vmime::shared_ptr<const vmime::htmlTextPart> htmlTextPart = vmime::dynamicCast<const vmime::htmlTextPart>(textPart);

            for (vmime::size_t j = 0; j < htmlTextPart->getObjectCount(); j++)
            {
                result.push_back(htmlTextPart->getObjectAt(j));
            }
        }
    }

    return result;
}

QList<Contact> VmimeMessageContentParser::parseContacts(const vmime::shared_ptr<vmime::address> address) const
{
    QList<Contact> result;

    if (!address->isEmpty())
    {
        if (!address->isGroup())
        {
            Contact contact;
            vmime::shared_ptr<vmime::mailbox> mailbox = vmime::dynamicCast<vmime::mailbox>(address);

            contact.setName(mailbox->getName().getConvertedText(vmime::charsets::UTF_8).c_str());
            contact.setEmailAddress(mailbox->getEmail().toString().c_str());

            result.append(contact);
        }
        else
        {
            vmime::shared_ptr<vmime::mailboxGroup> mailgroup = vmime::dynamicCast<vmime::mailboxGroup>(address);

            if (!mailgroup->isEmpty())
            {
                for (vmime::size_t i = 0; i < mailgroup->getMailboxCount(); i++)
                {
                    result.append(parseContacts(mailgroup->getMailboxAt(i)));
                }
            }
        }
    }

    return result;
}

QList<Contact> VmimeMessageContentParser::parseRecipients() const
{
    QList<Contact> result;
    vmime::addressList recipients = m_messageParser->getRecipients();

    for (vmime::size_t i = 0; i < recipients.getAddressCount(); i++)
    {
        vmime::shared_ptr<vmime::address> address = recipients.getAddressAt(i);
        result.append(parseContacts(address));
    }

    return result;
}

QList<Contact> VmimeMessageContentParser::parseInCopyRecipients() const
{
    QList<Contact> result;
    vmime::addressList copyRecipients = m_messageParser->getCopyRecipients();

    for (vmime::size_t i = 0; i < copyRecipients.getAddressCount(); i++)
    {
        vmime::shared_ptr<vmime::address> address = copyRecipients.getAddressAt(i);
        result.append(parseContacts(address));
    }

    return result;
}

QList<Contact> VmimeMessageContentParser::parseBlindCopyRecipients() const
{
    QList<Contact> result;
    vmime::addressList blindCopyRecipients = m_messageParser->getBlindCopyRecipients();

    for (vmime::size_t i = 0; i < blindCopyRecipients.getAddressCount(); i++)
    {
        vmime::shared_ptr<vmime::address> address = blindCopyRecipients.getAddressAt(i);
        result.append(parseContacts(address));
    }

    return result;
}

QString VmimeMessageContentParser::parseTextParts(const char *type) const
{
    QString result;

    for (vmime::size_t i = 0; i < m_messageParser->getTextPartCount(); i++)
    {
        vmime::shared_ptr<const vmime::textPart> textPart = m_messageParser->getTextPartAt(i);

        if (textPart->getType().getSubType() == type)
        {
            vmime::string extractedText;
            vmime::string convertedText;

            vmime::utility::outputStreamStringAdapter extractedTextOutputStringAdapter(extractedText);
            textPart->getText()->extract(extractedTextOutputStringAdapter);
            textPart->getCharset().convert(extractedText, convertedText, textPart->getCharset().getName(), vmime::charsets::UTF_8);

            result.append(convertedText.c_str());
        }
    }

    return result;
}
