#include "vmimesmtpmessagesender.h"

VmimeSmtpMessageSender::VmimeSmtpMessageSender(QString smtpServerUrl, QString senderAddress, QString senderPassword)
{
    this->smtpServerUrl = smtpServerUrl.toStdString();
    this->senderAddress = senderAddress.toStdString();
    this->senderPassword = senderPassword.toStdString();

    initializeCertificateHelper();
    initializeSession();
    initializeTransport();
}

void VmimeSmtpMessageSender::setSenderAddress(QString senderAddress)
{
    this->senderAddress = senderAddress.toStdString();
    initializeTransport();
}

void VmimeSmtpMessageSender::setSmtpServerUrl(QString smtpServerUrl)
{
    this->smtpServerUrl = smtpServerUrl.toStdString();
    initializeSession();
    initializeTransport();
}

void VmimeSmtpMessageSender::setSenderPassword(QString senderPassword)
{
    this->senderPassword = senderPassword.toStdString();
    initializeTransport();
}

QString VmimeSmtpMessageSender::getSenderAddress()
{
    return QString(this->senderAddress.c_str());
}

QString VmimeSmtpMessageSender::getSmtpServerUrl()
{
    return QString(this->smtpServerUrl.c_str());
}

QString VmimeSmtpMessageSender::getSenderPassword()
{
    return QString(this->senderPassword.c_str());
}

void VmimeSmtpMessageSender::initializeCertificateHelper()
{
    this->certVerifier = vmime::make_shared<vmime::security::cert::defaultCertificateVerifier>();
    VMimeRootCertificatesHelper certHelper(Constants::ROOT_CERTIFICATES_DIRECTORY_PATH_LINUX);
    this->certVerifier->setX509RootCAs(certHelper.getSystemRootCertificates());
}

void VmimeSmtpMessageSender::initializeSession()
{
    this->session = vmime::net::session::create();
}

void VmimeSmtpMessageSender::initializeTransport()
{
    vmime::utility::url url(this->smtpServerUrl);
    this->transport = this->session->getTransport(url);

    this->transport->setProperty("connection.tls", true);
    this->transport->setProperty("auth.username", this->senderAddress);
    this->transport->setProperty("auth.password", this->senderPassword);
    this->transport->setProperty("options.need-authentication", true);

    this->transport->setCertificateVerifier(this->certVerifier);
}

void VmimeSmtpMessageSender::sendMessage(MailMessage message)
{
    vmime::shared_ptr<vmime::message> constructedMessage = buildMessage(message);

    this->transport->connect();
    this->transport->send(constructedMessage);
    this->transport->disconnect();
}

vmime::shared_ptr<vmime::message> VmimeSmtpMessageSender::buildMessage(MailMessage message)
{
    vmime::messageBuilder messageBuilder;

    messageBuilder.setSubject(vmime::text(message.getSubject().toStdString()));
    messageBuilder.setExpeditor(vmime::mailbox(this->getSenderAddress().toStdString()));

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
