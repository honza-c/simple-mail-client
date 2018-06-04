#include "inboxfolder.h"

InboxFolder::InboxFolder(const InboxFolder &other)
{
    this->path = other.path;
    this->emailAddress = other.emailAddress;
    this->archive = other.archive;
    this->drafts = other.drafts;
    this->flagged = other.flagged;
    this->important = other.important;
    this->junk = other.junk;
    this->sent = other.sent;
    this->trash = other.trash;
    this->children = other.children;
}

InboxFolder& InboxFolder::operator=(const InboxFolder &other)
{
    this->path = other.path;
    this->emailAddress = other.emailAddress;
    this->archive = other.archive;
    this->drafts = other.drafts;
    this->flagged = other.flagged;
    this->important = other.important;
    this->junk = other.junk;
    this->sent = other.sent;
    this->trash = other.trash;
    this->children = other.children;
}

InboxFolder::operator QString() const
{
    QString result;

    result += "Email Address: ";
    result += this->emailAddress;
    result += "Path: ";
    result += path;
    result += ", isAllMessages: ";
    result += allMessages;
    result += ", isArchive: ";
    result += archive;
    result += ", isDrafts: ";
    result += drafts;
    result += ", isFlagged: ";
    result += ", isImportant: ";
    result += important;
    result += ", isJunk: ";
    result += junk;
    result += ", isSent: ";
    result += sent;
    result += ", isTrash: ";
    result += trash;
    result += ", hasChildren: ";
    result += children;

    return result;
}

QString InboxFolder::getPath()
{
    return this->path;
}

QString InboxFolder::getEmailAddress()
{
    return this->emailAddress;
}

bool InboxFolder::isAllMessages()
{
    return this->allMessages;
}

bool InboxFolder::isArchive()
{
    return this->archive;
}

bool InboxFolder::isDrafts()
{
    return this->drafts;
}

bool InboxFolder::isFlagged()
{
    return this->flagged;
}

bool InboxFolder::isImportant()
{
    return this->important;
}

bool InboxFolder::isJunk()
{
    return this->junk;
}

bool InboxFolder::isSent()
{
    return this->sent;
}

bool InboxFolder::isTrash()
{
    return this->trash;
}

bool InboxFolder::hasChildren()
{
    return this->children;
}

void InboxFolder::setPath(QString path)
{
    this->path = path;
}

void InboxFolder::setEmailAddress(QString emailAddress)
{
    this->emailAddress = emailAddress;
}

void InboxFolder::setIsAllMessages(bool value)
{
    this->allMessages = value;
}

void InboxFolder::setIsArchive(bool value)
{
    this->archive = value;
}

void InboxFolder::setIsDrafts(bool value)
{
    this->drafts = value;
}

void InboxFolder::setIsFlagged(bool value)
{
    this->flagged = value;
}

void InboxFolder::setIsImportant(bool value)
{
    this->important = value;
}

void InboxFolder::setIsJunk(bool value)
{
    this->junk = value;
}

void InboxFolder::setIsSent(bool value)
{
    this->sent = value;
}

void InboxFolder::setIsTrash(bool value)
{
    this->trash = value;
}

void InboxFolder::setHasChildren(bool value)
{
    this->children = value;
}
