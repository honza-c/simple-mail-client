#ifndef VMIMESMTPSERVICE_H
#define VMIMESMTPSERVICE_H

#include <vmime/vmime.hpp>
#include <QObject>
#include "src/vmimebasemessagingservice.h"
#include "src/message.h"

class VmimeSmtpService : public VmimeBaseMessagingService
{
public:
    explicit VmimeSmtpService(QObject *parent = nullptr)
        : VmimeBaseMessagingService(parent) {}

    void sendMessage(Message message) const;

private:
    vmime::shared_ptr<vmime::net::transport> getTransport() const;
    vmime::shared_ptr<vmime::message> constructMessage(const Message message) const;
};

#endif // VMIMESMTPSERVICE_H
