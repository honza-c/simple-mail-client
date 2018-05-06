#ifndef VMIMESMTPSERVICE_H
#define VMIMESMTPSERVICE_H

#include <QObject>
#include <vmime/vmime.hpp>
#include "abstractmessagesenderservice.h"
#include "mailmessage.h"
#include "vmimemessagingbaseservice.h"

class VmimeSmtpService: public VmimeMessagingBaseService, public AbstractMessageSenderService
{
public:
    VmimeSmtpService(QString serverUrl, QString emailAddress, QString password)
        : VmimeMessagingBaseService(serverUrl, emailAddress, password) {}

    void sendMessage(MailMessage message) override;

private:
    vmime::shared_ptr<vmime::message> buildMessage(MailMessage message);
    vmime::shared_ptr<vmime::net::transport> initializeTransport();
};

#endif // VMIMESMTPSERVICE_H
