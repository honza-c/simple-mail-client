#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QObject>
#include <iostream>

class UserAccount : public QObject
{
    Q_OBJECT
public:
    explicit UserAccount(QString emailAddress, QString password, QString smtpUrl, QObject *parent = nullptr);

    void setEmailAddress(QString emailAddress);
    void setPassword(QString password);
    void setSmtpUrl(QString smtpUrl);

    QString getEmailAddress();
    QString getPassword();
    QString getSmtpUrl();

    void printToConsole();

private:
    QString emailAddress;
    QString password;
    QString smtpUrl;

signals:

public slots:
};

#endif // USERACCOUNT_H
