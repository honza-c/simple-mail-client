#include "vmimeinboxfolderparser.h"
VmimeInboxFolderParser::VmimeInboxFolderParser(vmime::shared_ptr<vmime::net::folder> folder, QObject *parent)
    : QObject(parent)
{
    m_folder = folder;
    m_folderAttributes = m_folder->getAttributes();
}

InboxFolder VmimeInboxFolderParser::parse() const
{
    InboxFolder inboxFolder;

    inboxFolder.setPath(getFolderPath());
    inboxFolder.setIsAllMessages(m_folderAttributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_ALL);
    inboxFolder.setIsArchive(m_folderAttributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_ARCHIVE);
    inboxFolder.setIsDrafts(m_folderAttributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_DRAFTS);
    inboxFolder.setIsFlagged(m_folderAttributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_FLAGGED);
    inboxFolder.setIsImportant(m_folderAttributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_IMPORTANT);
    inboxFolder.setIsJunk(m_folderAttributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_JUNK);
    inboxFolder.setIsSent(m_folderAttributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_SENT);
    inboxFolder.setIsTrash(m_folderAttributes.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_TRASH);
    inboxFolder.setHasChildren(m_folder->getFolders(false).size() > 0);

    return inboxFolder;
}

QString VmimeInboxFolderParser::getFolderPath() const
{
    QString path = getFolderPath(m_folder);

    if (path != "/")
    {
        return path.left(path.size() - 1);
    }

    return path;
}

QString VmimeInboxFolderParser::getFolderPath(const vmime::shared_ptr<vmime::net::folder> folder) const
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
