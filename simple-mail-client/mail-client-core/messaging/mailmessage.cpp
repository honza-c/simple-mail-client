#include "mailmessage.h"

MailMessage::MailMessage(const MailMessage &other)
{
    this->subject = other.subject;
    this->messageContent = other.messageContent;
    this->addressListTo = other.addressListTo;
    this->addressListBlindCopy = other.addressListBlindCopy;
}

MailMessage& MailMessage::operator=(const MailMessage &other)
{
    this->subject = other.subject;
    this->messageContent = other.messageContent;
    this->addressListTo = other.addressListTo;
    this->addressListBlindCopy = other.addressListBlindCopy;
}

MailMessage::operator QString() const
{
    QString result;

    result += "Subject: ";
    result += this->subject;
    result += "\nMessage content: ";
    result += this->messageContent;

    result += "\nTo: ";

    for (QString address : addressListTo)
    {
        result += address;
        result += ", ";
    }

    result += "\nBlind copy: ";

    for (QString address : addressListBlindCopy)
    {
        result += address;
        result += ", ";
    }

    return result;
}

void MailMessage::setSubject(QString subject)
{
    this->subject = subject;
}

void MailMessage::setMessageContent(QString messageContent)
{
    this->messageContent = messageContent;
}

void MailMessage::setAddressListTo(QStringList addressListTo)
{
    this->addressListTo = addressListTo;
}

void MailMessage::setAddressListBlindCopy(QStringList addressListBlindCopy)
{
    this->addressListBlindCopy = addressListBlindCopy;
}

QString MailMessage::getSubject()
{
    return this->subject;
}

QString MailMessage::getMessageContent()
{
    return this->messageContent;
}

QStringList MailMessage::getAddressListTo()
{
    return this->addressListTo;
}

QStringList MailMessage::getAddressListBlindCopy()
{
    return this->addressListBlindCopy;
}
