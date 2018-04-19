#ifndef ABSTRACTMESSAGESENDER_H
#define ABSTRACTMESSAGESENDER_H

#include <QObject>
#include "mailmessage.h"

class AbstractMessageSender : public QObject
{
    Q_OBJECT
public:
    explicit AbstractMessageSender(QObject *parent = nullptr) {}
    virtual void sendMessage(MailMessage message);

signals:

public slots:
};

#endif // ABSTRACTMESSAGESENDER_H
