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

    store->disconnect();

    QList<MessageMetadata> metadataList;
    VmimeMessageMetadataParser metadataParser;

    for (unsigned int i = 0; i < messages.size(); i++)
    {
        vmime::shared_ptr<vmime::net::message> message = messages[i];
        metadataList.push_back(metadataParser.parse(message));
    }

    return metadataList;
}
