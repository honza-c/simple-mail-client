#ifndef VMIMESMTPMESSAGESENDER_H
#define VMIMESMTPMESSAGESENDER_H

#include <QObject>
#include <QDebug>
#include "abstractmessagesender.h"
#include "mailmessage.h"

class VmimeSmtpMessageSender : public AbstractMessageSender
{
    Q_OBJECT
public:
    VmimeSmtpMessageSender() {}
    void sendMessage(MailMessage message) override;
};

#endif // VMIMESMTPMESSAGESENDER_H
