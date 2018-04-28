#ifndef VMIMESMTPMESSAGESENDER_H
#define VMIMESMTPMESSAGESENDER_H

#include <QObject>
#include <QDebug>
#include "abstractmessagesender.h"
#include "mailmessage.h"
#include "vmimerootcertificateshelper.h"
#include "tools/constants.h"
#include <vmime/vmime.hpp>

class VmimeSmtpMessageSender : public AbstractMessageSender
{
    Q_OBJECT
public:
    VmimeSmtpMessageSender() {}
    VmimeSmtpMessageSender(QString smtpServerUrl, QString senderAddress, QString senderPassword);
    void sendMessage(MailMessage message) override;

    void setSmtpServerUrl(QString smtpServerUrl);
    void setSenderAddress(QString senderAddress);
    void setSenderPassword(QString senderPassword);

    QString getSmtpServerUrl();
    QString getSenderAddress();
    QString getSenderPassword();

private:
    std::string smtpServerUrl;
    std::string senderAddress;
    std::string senderPassword;

    vmime::shared_ptr<vmime::net::session> session;
    vmime::shared_ptr<vmime::net::transport> transport;
    vmime::shared_ptr<vmime::security::cert::defaultCertificateVerifier> certVerifier;

    void initializeSession();
    void initializeTransport();
    void initializeCertificateHelper();
    vmime::shared_ptr<vmime::message> buildMessage(MailMessage message);
};

#endif // VMIMESMTPMESSAGESENDER_H
