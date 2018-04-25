#include "useraccount.h"

UserAccount::UserAccount()
{
    this->messageSender = new VmimeSmtpMessageSender();
}

UserAccount::UserAccount(const UserAccount &other)
{
    this->accountName = other.accountName;
    this->yourName = other.yourName;
    this->emailAddress = other.emailAddress;
    this->password = other.password;
    this->smtpServerUrl = other.smtpServerUrl;
    this->popServerUrl = other.popServerUrl;
    this->smtpServerPort = other.smtpServerPort;
    this->popServerPort = other.popServerPort;

    this->messageSender = new VmimeSmtpMessageSender();
}

UserAccount& UserAccount::operator =(const UserAccount &other)
{
    this->accountName = other.accountName;
    this->yourName = other.yourName;
    this->emailAddress = other.emailAddress;
    this->password = other.password;
    this->smtpServerUrl = other.smtpServerUrl;
    this->popServerUrl = other.popServerUrl;
    this->smtpServerPort = other.smtpServerPort;
    this->popServerPort = other.popServerPort;

    this->messageSender = new VmimeSmtpMessageSender();
}

UserAccount::operator QString() const
{
    QString result;
    result += "Account name: ";
    result += accountName;
    result += "\nYour name: ";
    result += yourName;
    result += "\nEmail address: ";
    result += emailAddress;
    result += "\nPassword: ";
    result += password;
    result += "\nSMTP server URL: ";
    result += smtpServerUrl;
    result += "\nPOP3 server URL: ";
    result += popServerUrl;
    result += "\nSMTP server port: ";
    result += QString("%1").arg(smtpServerPort);
    result += "\nPOP3 server port: ";
    result += QString("%1").arg(popServerPort);

    return result;
}

void UserAccount::setAccountName(QString accountName)
{
    this->accountName = accountName;
}

void UserAccount::setYourName(QString yourName)
{
    this->yourName = yourName;
}

void UserAccount::setEmailAddress(QString emailAddress)
{
    this->emailAddress = emailAddress;
}

void UserAccount::setPassword(QString password)
{
    this->password = password;
}

void UserAccount::setSmtpServerUrl(QString smtpServerUrl)
{
    this->smtpServerUrl = smtpServerUrl;
}

void UserAccount::setPopServerUrl(QString popServerUrl)
{
    this->popServerUrl = popServerUrl;
}

void UserAccount::setSmtpServerPort(int smtpServerPort)
{
    this->smtpServerPort = smtpServerPort;
}

void UserAccount::setPopServerPort(int popServerPort)
{
    this->popServerPort = popServerPort;
}

void UserAccount::setMessageSender(AbstractMessageSender *messageSender)
{
    this->messageSender = messageSender;
}

QString UserAccount::getAccountName()
{
    return this->accountName;
}

QString UserAccount::getYourName()
{
    return this->yourName;
}

QString UserAccount::getEmailAddress()
{
    return this->emailAddress;
}

QString UserAccount::getPassword()
{
    return this->password;
}

QString UserAccount::getSmtpServerUrl()
{
    return this->smtpServerUrl;
}

QString UserAccount::getPopServerUrl()
{
    return this->popServerUrl;
}

int UserAccount::getSmtpServerPort()
{
    return this->smtpServerPort;
}

int UserAccount::getPopServerPort()
{
    return this->popServerPort;
}

AbstractMessageSender* UserAccount::getMessageSender()
{
    return this->messageSender;
}

void UserAccount::sendMessage(MailMessage message)
{
    this->messageSender->sendMessage(message);
}
