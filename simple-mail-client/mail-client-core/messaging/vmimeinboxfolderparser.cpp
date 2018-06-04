#include "vmimeinboxfolderparser.h"

VmimeInboxFolderParser::VmimeInboxFolderParser(QObject *parent) : QObject(parent)
{

}

InboxFolder VmimeInboxFolderParser::parse(vmime::shared_ptr<vmime::net::folder> folder, QString emailAddress)
{
    InboxFolder inboxFolder;

    QString path = getFolderPath(folder);

    if (path != "/")
    {
        path = path.left(path.size() - 1);
    }

    inboxFolder.setPath(path);

    vmime::net::folderAttributes attributes = folder->getAttributes();

    inboxFolder.setIsAllMessages(attributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_ALL);
    inboxFolder.setIsArchive(attributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_ARCHIVE);
    inboxFolder.setIsDrafts(attributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_DRAFTS);
    inboxFolder.setIsFlagged(attributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_FLAGGED);
    inboxFolder.setIsImportant(attributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_IMPORTANT);
    inboxFolder.setIsJunk(attributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_JUNK);
    inboxFolder.setIsSent(attributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_SENT);
    inboxFolder.setIsTrash(attributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_TRASH);
    inboxFolder.setHasChildren(folder->getFolders(false).size() > 0);
    inboxFolder.setEmailAddress(emailAddress);

    return inboxFolder;
}

QString VmimeInboxFolderParser::getFolderPath(vmime::shared_ptr<vmime::net::folder> folder)
{
    vmime::string path = folder->getName().getBuffer();

    if (path.empty())
    {
        return QString("/");
    }
    else
    {
        vmime::shared_ptr<vmime::net::folder> parent = folder->getParent();
        return QString(getFolderPath(parent) + path.c_str() + "/");
    }
}
