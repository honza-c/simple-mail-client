#ifndef VMIMESMTPMESSAGESENDER_H
#define VMIMESMTPMESSAGESENDER_H

#include <QObject>
#include "abstractmessagesender.h"
#include "mailmessage.h"
#include "userAccounts/useraccount.h"
#include "tools/constants.h"
#include "vmimerootcertificateshelper.h"
#include <vmime/vmime.hpp>

class VMimeSmtpMessageSender : public AbstractMessageSender
{
public:
    VMimeSmtpMessageSender(QString smtpServerUrl, QString senderAddress, QString senderPassword);

    void sendMessage(MailMessage message) override;

    void setSmtpServerUrl(QString smtpServerUrl);
    void setSenderAddress(QString senderAddress);
    void setSenderPassword(QString senderPassword);

    QString getSmtpSenderUrl();
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
    vmime::shared_ptr<vmime::message> buildVmimeMessage(MailMessage message);

};

#endif // VMIMESMTPMESSAGESENDER_H
