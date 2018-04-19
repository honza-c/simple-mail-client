#include "vmimesmtpmessagesender.h"

VMimeSmtpMessageSender::VMimeSmtpMessageSender(QString smtpServerUrl, QString senderAddress, QString senderPassword)
{
    this->smtpServerUrl = smtpServerUrl.toStdString();
    this->senderAddress = senderAddress.toStdString();
    this->senderPassword = senderPassword.toStdString();

    initializeCertificateHelper();
    initializeSession();
    initializeTransport();
}

void VMimeSmtpMessageSender::sendMessage(MailMessage message)
{
    vmime::shared_ptr<vmime::message> vmimeMessage = buildVmimeMessage(message);

    transport->connect();
    transport->send(vmimeMessage);
    transport->disconnect();
}

void VMimeSmtpMessageSender::setSmtpServerUrl(QString smtpServerUrl)
{
    this->smtpServerUrl = smtpServerUrl.toStdString();

    initializeSession();
    initializeTransport();
}

void VMimeSmtpMessageSender::setSenderAddress(QString senderAddress)
{
    this->senderAddress = senderAddress.toStdString();
    initializeTransport();
}

void VMimeSmtpMessageSender::setSenderPassword(QString senderPassword)
{
    this->senderPassword = senderPassword.toStdString();
    initializeTransport();
}

QString VMimeSmtpMessageSender::getSmtpSenderUrl()
{
    return QString(this->smtpServerUrl.c_str());
}

QString VMimeSmtpMessageSender::getSenderAddress()
{
    return QString(this->senderAddress.c_str());
}

QString VMimeSmtpMessageSender::getSenderPassword()
{
    return QString(this->senderPassword.c_str());
}

void VMimeSmtpMessageSender::initializeSession()
{
    this->session = vmime::net::session::create();
}

void VMimeSmtpMessageSender::initializeTransport()
{
    vmime::utility::url url(this->smtpServerUrl);
    this->transport = this->session->getTransport(url);

    this->transport->setProperty("connection.tls", true);
    this->transport->setProperty("auth.username", this->senderAddress);
    this->transport->setProperty("auth.password", this->senderPassword);
    this->transport->setProperty("options.need-authentication", true);

    this->transport->setCertificateVerifier(this->certVerifier);
}

void VMimeSmtpMessageSender::initializeCertificateHelper()
{
    this->certVerifier = vmime::make_shared<vmime::security::cert::defaultCertificateVerifier>();
    VMimeRootCertificatesHelper certHelper(Constants::ROOT_CERTIFICATES_DIRECTORY_PATH_LINUX);
    this->certVerifier->setX509RootCAs(certHelper.getSystemRootCertificates());

}

vmime::shared_ptr<vmime::message> VMimeSmtpMessageSender::buildVmimeMessage(MailMessage message)
{
    std::string subject = message.getSubject().toStdString();
    std::string messageContent = message.getMessageContent().toStdString();

    vmime::addressList addressListTo;
    vmime::addressList addressListBcc;

    for (QString address : message.getAddressListTo())
    {
        vmime::shared_ptr<vmime::mailbox> mailbox = vmime::make_shared<vmime::mailbox>(address.toStdString());
        addressListTo.appendAddress(mailbox);
    }

    for (QString address : message.getAddressListBlindCopyTo())
    {
        vmime::shared_ptr<vmime::mailbox> mailbox = vmime::make_shared<vmime::mailbox>(address.toStdString());
        addressListTo.appendAddress(mailbox);
    }

    vmime::messageBuilder messageBuilder;

    messageBuilder.setRecipients(addressListTo);
    messageBuilder.setBlindCopyRecipients(addressListBcc);

    messageBuilder.getTextPart()->setText(vmime::make_shared<vmime::stringContentHandler>(messageContent));

    return messageBuilder.construct();
}
