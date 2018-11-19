#include "vmimesmtpservice.h"

void VmimeSmtpService::sendMessage(Message message) const
{
    vmime::shared_ptr<vmime::message> constructedMessage = constructMessage(message);
    vmime::shared_ptr<vmime::net::transport> transport = getTransport();

    try
    {
        transport->connect();
        transport->send(constructedMessage);
        transport->disconnect();
    }
    catch (vmime::exception e)
    {
        qWarning() << "vmime error " << e.what();
    }
    catch (std::exception e)
    {
        qWarning() << "std error " << e.what();
    }
}

vmime::shared_ptr<vmime::net::transport> VmimeSmtpService::getTransport() const
{
    vmime::shared_ptr<vmime::net::transport> transport;
    vmime::utility::url url(m_serverUrl);

    transport = m_session->getTransport(url);

    transport->setProperty("connection.tls", true);
    transport->setProperty("auth.username", m_emailAddress);
    transport->setProperty("auth.password", m_password);
    transport->setProperty("options.need-authentication", true);
    transport->setCertificateVerifier(m_certificateVerifier);

    return transport;
}

vmime::shared_ptr<vmime::message> VmimeSmtpService::constructMessage(const Message message) const
{
    vmime::messageBuilder messageBuilder;

    messageBuilder.setSubject(vmime::text(message.subject().toStdString()));
    messageBuilder.setExpeditor(vmime::mailbox(m_emailAddress));

    if (message.htmlContent() != QString())
    {
        messageBuilder.constructTextPart(vmime::mediaType(vmime::mediaTypes::TEXT, vmime::mediaTypes::TEXT_HTML));

        vmime::shared_ptr<vmime::htmlTextPart> htmlTextPart = vmime::dynamicCast<vmime::htmlTextPart>(messageBuilder.getTextPart());
        htmlTextPart->setCharset(vmime::charsets::UTF_8);
        htmlTextPart->setText(vmime::make_shared<vmime::stringContentHandler>(message.htmlContent().toStdString()));
        htmlTextPart->setPlainText(vmime::make_shared<vmime::stringContentHandler>(message.plainTextContent().toStdString()));
        // TODO: embedded objects
    }
    else
    {
        messageBuilder.getTextPart()->setCharset(vmime::charsets::UTF_8);
        messageBuilder.getTextPart()->setText(
                    vmime::make_shared<vmime::stringContentHandler>(message
                                                                    .plainTextContent()
                                                                    .toStdString()));
    }

    vmime::addressList addressListTo;

    for (Contact contact : message.addressListTo())
    {
        addressListTo.appendAddress(vmime::make_shared<vmime::mailbox>(contact.emailAddress().toStdString()));
    }

    messageBuilder.setRecipients(addressListTo);

    if (!message.addressListInCopy().isEmpty())
    {
        vmime::addressList copyRecipients;

        for (Contact contact : message.addressListInCopy())
        {
            copyRecipients.appendAddress(vmime::make_shared<vmime::mailbox>(contact.emailAddress().toStdString()));
        }

        messageBuilder.setCopyRecipients(copyRecipients);
    }

    if (!message.addressListInBlindCopy().isEmpty())
    {
        vmime::addressList blindCopyRecipients;

        for (Contact contact : message.addressListInBlindCopy())
        {
            blindCopyRecipients.appendAddress(vmime::make_shared<vmime::mailbox>(contact.emailAddress().toStdString()));
        }

        messageBuilder.setBlindCopyRecipients(blindCopyRecipients);
    }

    if (!message.attachments().isEmpty())
    {
        for (Attachment attachment : message.attachments())
        {
            QString attachmentData;

            for (int i = 0; i < attachment.data().size(); i++)
            {
               attachmentData.append(attachment.data().at(i));
            }

            vmime::encoding encoding;
            encoding.setUsage(vmime::encoding::USAGE_BINARY_DATA);

            vmime::shared_ptr<vmime::contentHandler> contentHandler
                    = vmime::make_shared<vmime::stringContentHandler>(attachmentData.toStdString(), encoding);

            vmime::word fileName(attachment.name().toStdString().c_str());
            vmime::mediaType mediaType(attachment.mimeType().toStdString());

            vmime::shared_ptr<vmime::fileAttachment> vmimeAttachment = vmime::make_shared<vmime::fileAttachment>(contentHandler, fileName, mediaType);

            messageBuilder.appendAttachment(vmimeAttachment);
        }
    }

    return messageBuilder.construct();
}
