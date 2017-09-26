#include "useraccount.h"

UserAccount::UserAccount(QString emailAddress, QString password, QString smtpUrl, QObject *parent) : QObject(parent)
{
    this->emailAddress = emailAddress;
    this->password = password;
    this->smtpUrl = smtpUrl;
}

void UserAccount::setEmailAddress(QString emailAddress)
{
    this->emailAddress = emailAddress;
}

void UserAccount::setPassword(QString password)
{
    this->password = password;
}

void UserAccount::setSmtpUrl(QString smtpUrl)
{
    this->smtpUrl = smtpUrl;
}

QString UserAccount::getEmailAddress()
{
    return this->emailAddress;
}

QString UserAccount::getPassword()
{
    return this->password;
}

QString UserAccount::getSmtpUrl()
{
    return this->smtpUrl;
}

void UserAccount::printToConsole()
{
    std::cout << "E-mail address: " << emailAddress.toStdString() << std::endl;
    std::cout << "Password: " << password.toStdString() << std::endl;
    std::cout << "SMTP URL: " << smtpUrl.toStdString() << std::endl << std::endl;
}
