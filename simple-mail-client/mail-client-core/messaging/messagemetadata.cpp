#include "messagemetadata.h"

MessageMetadata::MessageMetadata()
{

}

MessageMetadata::MessageMetadata(const MessageMetadata &other)
{
    this->id = other.id;
    this->size = other.size;
    this->folderPath = other.folderPath;
    this->emailAddress = other.emailAddress;
    this->plainTextContent = other.plainTextContent;
    this->htmlContent = other.htmlContent;
    this->recipients = other.recipients;
    this->inCopy = other.inCopy;
    this->date = other.date;
    this->fromAddress = other.fromAddress;
    this->fromName = other.fromName;
    this->subject = other.subject;
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
    this->folderPath = other.folderPath;
    this->emailAddress = other.emailAddress;
    this->plainTextContent = other.plainTextContent;
    this->htmlContent = other.htmlContent;
    this->recipients = other.recipients;
    this->inCopy = other.inCopy;
    this->date = other.date;
    this->fromAddress = other.fromAddress;
    this->fromName = other.fromName;
    this->subject = other.subject;
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

    result += "Folder path: ";
    result += this->folderPath;

    result += "Email address: ";
    result += this->emailAddress;

    result += "Recipients: ";
    result += this->recipients;

    result += "In copy: ";
    result += this->inCopy;

    result += " Date: ";
    result += this->date.toString("dd.MM.yyyy HH:mm");

    result += " From name: ";
    result += this->fromName;

    result += " From address: ";
    result += this->fromAddress;

    result += " Subject: ";
    result += this->subject;

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

    result += "Plain text content: ";
    result += this->plainTextContent;

    result += "HTML content: ";
    result += this->htmlContent;

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

void MessageMetadata::setFolderPath(QString folderPath)
{
    this->folderPath = folderPath;
}

void MessageMetadata::setEmailAddress(QString emailAddress)
{
    this->emailAddress = emailAddress;
}

void MessageMetadata::setRecipients(QString recipients)
{
    this->recipients = recipients;
}

void MessageMetadata::setDate(QDateTime date)
{
    this->date = date;
}

void MessageMetadata::setInCopy(QString inCopy)
{
    this->inCopy = inCopy;
}

void MessageMetadata::setFromAddress(QString fromAddress)
{
    this->fromAddress = fromAddress;
}

void MessageMetadata::setFromName(QString fromName)
{
    this->fromName = fromName;
}

void MessageMetadata::setSubject(QString subject)
{
    this->subject = subject;
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

void MessageMetadata::setPlainTextContent(QString plainTextContent)
{
    this->plainTextContent = plainTextContent;
}

void MessageMetadata::setHtmlContent(QString htmlContent)
{
    this->htmlContent = htmlContent;
}

unsigned long MessageMetadata::getId()
{
    return this->id;
}

unsigned long MessageMetadata::getSize()
{
    return this->size;
}

QString MessageMetadata::getFolderPath()
{
    return this->folderPath;
}

QString MessageMetadata::getEmailAddress()
{
    return this->emailAddress;
}

QString MessageMetadata::getRecipients()
{
    return this->recipients;
}

QString MessageMetadata::getInCopy()
{
    return this->inCopy;
}

QDateTime MessageMetadata::getDate()
{
    return this->date;
}

QString MessageMetadata::getFromAddress()
{
    return this->fromAddress;
}

QString MessageMetadata::getFromName()
{
    return this->fromName;
}

QString MessageMetadata::getSubject()
{
    return this->subject;
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

QString MessageMetadata::getPlainTextContent()
{
    return this->plainTextContent;
}

QString MessageMetadata::getHtmlContent()
{
    return this->htmlContent;
}
