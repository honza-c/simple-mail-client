#include "vmimeinboxservice.h"

QList<MessageMetadata> VmimeInboxService::getMessageMetadata()
{
    vmime::shared_ptr<vmime::net::store> store = this->initializeStore();

    store->connect();

    vmime::shared_ptr<vmime::net::folder> rootFolder = store->getDefaultFolder();
    rootFolder->open(vmime::net::folder::MODE_READ_ONLY);

    size_t messageCount = rootFolder->getMessageCount();

    std::vector<vmime::shared_ptr<vmime::net::message>> messages =
            rootFolder->getMessages(vmime::net::messageSet::byNumber(1, messageCount));

    rootFolder->fetchMessages(messages,
                              vmime::net::fetchAttributes::ENVELOPE |
                              vmime::net::fetchAttributes::FLAGS |
                              vmime::net::fetchAttributes::SIZE |
                              vmime::net::fetchAttributes::UID);

    QString folderPath = getFolderPath(rootFolder);

    store->disconnect();

    QList<MessageMetadata> metadataList;

    VmimeMessageMetadataParser metadataParser(this->emailAddress.c_str(), folderPath);

    for (unsigned int i = 0; i < messages.size(); i++)
    {
        vmime::shared_ptr<vmime::net::message> message = messages[i];
        metadataList.push_back(metadataParser.parse(message));
    }

    return metadataList;
}

QString VmimeInboxService::getFolderPath(vmime::shared_ptr<vmime::net::folder> folder)
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

QList<InboxFolder> VmimeInboxService::getInboxFolders()
{
    QList<InboxFolder> folders;

    vmime::shared_ptr<vmime::net::store> store = initializeStore();
    store->connect();
    vmime::shared_ptr<vmime::net::folder> rootFolder = store->getRootFolder();
    std::vector<vmime::shared_ptr<vmime::net::folder>> subFolders = rootFolder->getFolders(true);

    VmimeInboxFolderParser parser;

    folders << parser.parse(rootFolder, QString(this->emailAddress.c_str()));

    for (unsigned int i = 0; i < subFolders.size(); i++)
    {
        folders << parser.parse(subFolders[i], QString(this->emailAddress.c_str()));
    }

    store->disconnect();

    return folders;
}

QString VmimeInboxService::getHtmlMessageContent(QString folderPath, int folderPosition)
{
    vmime::shared_ptr<vmime::net::store> store = initializeStore();
    store->connect();
    vmime::shared_ptr<vmime::net::folder> rootFolder = store->getDefaultFolder();
    rootFolder->open(vmime::net::folder::MODE_READ_ONLY);

    size_t messagesCount = rootFolder->getMessageCount();
    vmime::shared_ptr<vmime::net::message> message = rootFolder->getMessage(messagesCount);

    rootFolder->fetchMessage(message, vmime::net::fetchAttributes::STRUCTURE);

    VmimeMessageContentParser contentParser;
    vmime::shared_ptr<vmime::message> parsedMessage = message->getParsedMessage();

    store->disconnect();

    return contentParser.parseHtmlContent(parsedMessage);
}

QString VmimeInboxService::getTextMessageContent(QString folderPath, int folderPosition)
{
    vmime::shared_ptr<vmime::net::store> store = initializeStore();
    store->connect();
    vmime::shared_ptr<vmime::net::folder> rootFolder = store->getDefaultFolder();
    rootFolder->open(vmime::net::folder::MODE_READ_ONLY);

    size_t messagesCount = rootFolder->getMessageCount();
    vmime::shared_ptr<vmime::net::message> message = rootFolder->getMessage(messagesCount);

    rootFolder->fetchMessage(message, vmime::net::fetchAttributes::STRUCTURE);

    VmimeMessageContentParser contentParser;

    vmime::shared_ptr<vmime::message> parsedMessage = message->getParsedMessage();

    store->disconnect();
    return contentParser.parsePlainTextContent(parsedMessage);
}
