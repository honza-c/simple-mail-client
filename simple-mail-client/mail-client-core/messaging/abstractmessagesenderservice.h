#ifndef ABSTRACTMESSAGESENDERSERVICE_H
#define ABSTRACTMESSAGESENDERSERVICE_H

#include <QObject>
#include "mailmessage.h"

class AbstractMessageSenderService : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractMessageSenderService() {}
    virtual void sendMessage(MailMessage message) = 0;
};

#endif // ABSTRACTMESSAGESENDERSERVICE_H
