#include "vmimesmtpservice.h"

vmime::shared_ptr<vmime::net::transport> VmimeSmtpService::initializeTransport()
{
    vmime::shared_ptr<vmime::net::transport> transport;
    vmime::utility::url url(this->serverUrl);

    transport = this->session->getTransport(url);

    transport->setProperty("connection.tls", true);
    transport->setProperty("auth.username", this->emailAddress);
    transport->setProperty("auth.password", this->password);
    transport->setProperty("options.need-authentication", true);
    transport->setCertificateVerifier(this->certVerifier);

    return transport;
}

void VmimeSmtpService::sendMessage(MailMessage message)
{
    vmime::shared_ptr<vmime::message> constructedMessage = buildMessage(message);
    vmime::shared_ptr<vmime::net::transport> transport = initializeTransport();

    transport->connect();
    transport->send(constructedMessage);
    transport->disconnect();
}

vmime::shared_ptr<vmime::message> VmimeSmtpService::buildMessage(MailMessage message)
{
    vmime::messageBuilder messageBuilder;

    messageBuilder.setSubject(vmime::text(message.getSubject().toStdString()));
    messageBuilder.setExpeditor(vmime::mailbox(this->getEmailAddress().toStdString()));

    vmime::addressList vmimeAddressListTo;
    vmime::addressList vmimeAddressListBcc;

    for (QString to : message.getAddressListTo())
    {
        vmimeAddressListTo.appendAddress(vmime::make_shared<vmime::mailbox>(to.toStdString()));
    }

    for (QString bcc : message.getAddressListBlindCopy())
    {
        vmimeAddressListBcc.appendAddress(vmime::make_shared<vmime::mailbox>(bcc.toStdString()));
    }

    messageBuilder.setRecipients(vmimeAddressListTo);
    messageBuilder.setBlindCopyRecipients(vmimeAddressListBcc);

    messageBuilder.getTextPart()->setText(vmime::make_shared<vmime::stringContentHandler>(message.getMessageContent().toStdString()));

    return messageBuilder.construct();
}
