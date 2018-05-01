#include "messagemetadata.h"

MessageMetadata::MessageMetadata()
{

}

MessageMetadata::MessageMetadata(const MessageMetadata &other)
{
    this->id = other.id;
    this->size = other.size;
    this->date = other.date;
    this->from = other.from;
    this->sender = other.sender;
    this->subject = other.subject;
    this->to = other.to;
    this->isDeleted = other.isDeleted;
    this->isDraft = other.isDraft;
    this->isRecent = other.isRecent;
    this->isReplied = other.isReplied;
    this->isSeen = other.isSeen;
}

MessageMetadata& MessageMetadata::operator=(const MessageMetadata &other)
{
    this->id = other.id;
    this->size = other.size;
    this->date = other.date;
    this->from = other.from;
    this->sender = other.sender;
    this->subject = other.subject;
    this->to = other.to;
    this->isDeleted = other.isDeleted;
    this->isDraft = other.isDraft;
    this->isRecent = other.isRecent;
    this->isReplied = other.isReplied;
    this->isSeen = other.isSeen;
}

MessageMetadata::operator QString() const
{
    QString result;

    result += "Id: ";
    result += QString::number(this->id);

    result += " Size: ";
    result += QString::number(this->size);

    result += " Date: ";
    result += this->date;

    result += " From: ";
    result += this->from;

    result += " Sender: ";
    result += this->sender;

    result += " Subject: ";
    result += this->subject;

    result += " To: ";
    result += this->to;

    result += " Is Deleted: ";
    result += this->isDeleted;

    result += " Is Draft: ";
    result += this->isDraft;

    result += " Is Recent: ";
    result += this->isRecent;

    result += " Is Replied: ";
    result += this->isReplied;

    result += " Is Seen: ";
    result += this->isSeen;

    return result;
}


void MessageMetadata::setId(unsigned long id)
{
    this->id = id;
}

void MessageMetadata::setSize(unsigned long size)
{
    this->size = size;
}

void MessageMetadata::setDate(QString date)
{
    this->date = date;
}

void MessageMetadata::setFrom(QString from)
{
    this->from = from;
}

void MessageMetadata::setSender(QString sender)
{
    this->sender = sender;
}

void MessageMetadata::setSubject(QString subject)
{
    this->subject = subject;
}

void MessageMetadata::setTo(QString to)
{
    this->to = to;
}

void MessageMetadata::setIsDeleted(bool isDeleted)
{
    this->isDeleted = isDeleted;
}

void MessageMetadata::setIsDraft(bool isDraft)
{
    this->isDraft = isDraft;
}

void MessageMetadata::setIsRecent(bool isRecent)
{
    this->isRecent = isRecent;
}

void MessageMetadata::setIsReplied(bool isReplied)
{
    this->isReplied = isReplied;
}

void MessageMetadata::setIsSeen(bool isSeen)
{
    this->isSeen = isSeen;
}

unsigned long MessageMetadata::getId()
{
    return this->id;
}

unsigned long MessageMetadata::getSize()
{
    return this->size;
}

QString MessageMetadata::getDate()
{
    return this->date;
}

QString MessageMetadata::getFrom()
{
    return this->from;
}

QString MessageMetadata::getSender()
{
    return this->sender;
}

QString MessageMetadata::getSubject()
{
    return this->subject;
}

QString MessageMetadata::getTo()
{
    return this->to;
}

bool MessageMetadata::getIsDeleted()
{
    return this->isDeleted;
}

bool MessageMetadata::getIsDraft()
{
    return this->isDraft;
}

bool MessageMetadata::getIsRecent()
{
    return this->isRecent;
}

bool MessageMetadata::getIsReplied()
{
    return this->isReplied;
}

bool MessageMetadata::getIsSeen()
{
    return this->isSeen;
}

