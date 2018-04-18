#include "mailmessage.h"

MailMessage::MailMessage(const MailMessage &other)
{
    this->subject = other.subject;
    this->messageContent = other.messageContent;
    this->addressListTo = other.addressListTo;
    this->addressListBlindCopyTo = other.addressListBlindCopyTo;
}

MailMessage& MailMessage::operator=(const MailMessage &other)
{
    this->subject = other.subject;
    this->messageContent = other.messageContent;
    this->addressListTo = other.addressListTo;
    this->addressListBlindCopyTo = other.addressListBlindCopyTo;
}

MailMessage::operator QString() const
{
    QString result;

    result += "Subject: ";
    result += this->subject;
    result += "\nMessage content: ";
    result += this->messageContent;
    result += "\nAddress List: ";

    for (QString address : this->addressListTo)
    {
        result += address;
        result += ", ";
    }

    result += "\nBlind Copy List: ";

    for (QString address : this->addressListBlindCopyTo)
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

void MailMessage::setAddressListto(QStringList addressListTo)
{
    this->addressListTo = addressListTo;
}

void MailMessage::setAddressListBlindCopyTo(QStringList addressListBlindCopyTo)
{
    this->addressListBlindCopyTo = addressListBlindCopyTo;
}
