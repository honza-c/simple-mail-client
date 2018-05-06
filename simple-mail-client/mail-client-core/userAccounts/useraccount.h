#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QObject>
#include <iostream>
#include "messaging/mailmessage.h"
#include "messaging/abstractmessagesenderservice.h"
#include "messaging/vmimesmtpservice.h"

class UserAccount : public QObject
{
    Q_OBJECT
public:
    UserAccount();
    UserAccount(const UserAccount &other);
    UserAccount &operator=(const UserAccount &other);
    operator QString() const;

    void setAccountName(QString accountName);
    void setYourName(QString yourName);
    void setEmailAddress(QString emailAddress);
    void setPassword(QString password);
    void setSmtpServerUrl(QString smtpServerUrl);
    void setPopServerUrl(QString popServerUrl);
    void setSmtpServerPort(int smtpServerPort);
    void setPopServerPort(int popServerPort);

    QString getAccountName();
    QString getYourName();
    QString getEmailAddress();
    QString getPassword();
    QString getSmtpServerUrl();
    QString getPopServerUrl();
    int getSmtpServerPort();
    int getPopServerPort();

    void sendMessage(MailMessage message);

private:
    QString accountName;
    QString yourName;
    QString emailAddress;
    QString password;
    QString smtpServerUrl;
    QString popServerUrl;
    int smtpServerPort = 0;
    int popServerPort = 0;

signals:

public slots:
};

#endif // USERACCOUNT_H
