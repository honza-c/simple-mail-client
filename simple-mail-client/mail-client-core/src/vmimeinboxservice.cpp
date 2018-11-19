#include "vmimeinboxservice.h"

QList<InboxFolder> VmimeInboxService::fetchInboxFolders()
{
    QList<InboxFolder> folders;

    initializeStore();
    vmime::shared_ptr<vmime::net::folder> rootFolder = m_store->getRootFolder();
    std::vector<vmime::shared_ptr<vmime::net::folder>> subFolders = rootFolder->getFolders(true);
    subFolders.push_back(rootFolder);

    for (vmime::shared_ptr<vmime::net::folder> folder : subFolders)
    {
        VmimeInboxFolderParser parser(folder);
        InboxFolder inboxFolder = parser.parse();
        inboxFolder.setEmailAddress(QString(m_emailAddress.c_str()));

        folders.push_back(inboxFolder);
    }

    m_store->disconnect();

    return folders;
}

QList<MessageMetadata> VmimeInboxService::fetchMessagesMetadata(QMap<QString, int> folderPathsWithMessagesCountsInDb)
{
    QList<MessageMetadata> metadata;
    QList<VmimeInboxFolder> inboxFolders;

    initializeStore();
    vmime::shared_ptr<vmime::net::folder> rootFolder = m_store->getRootFolder();
    std::vector<vmime::shared_ptr<vmime::net::folder>> subFolders = rootFolder->getFolders(true);
    subFolders.push_back(rootFolder);

    for (vmime::shared_ptr<vmime::net::folder> folder : subFolders)
    {
        inboxFolders << VmimeInboxFolder(folder, QString(m_emailAddress.c_str()));
    }

    for (VmimeInboxFolder inboxFolder : inboxFolders)
    {
        if (folderPathsWithMessagesCountsInDb.contains(inboxFolder.data().path()))
        {
            int count = folderPathsWithMessagesCountsInDb[inboxFolder.data().path()];
            metadata.append(inboxFolder.getMessagesMetadataFromPosition(count));
        }
    }

    m_store->disconnect();

    return metadata;
}

MessageContent VmimeInboxService::fetchMessageContent(QString folderPath, int positionInFolder)
{
    initializeStore();
    vmime::shared_ptr<vmime::net::folder> rootFolder = m_store->getRootFolder();
    std::vector<vmime::shared_ptr<vmime::net::folder>> folders = rootFolder->getFolders(true);
    folders.push_back(rootFolder);

    for (vmime::shared_ptr<vmime::net::folder> folder : folders)
    {
        if (QString(folder->getFullPath().toString("/", vmime::charsets::UTF_8).c_str()) == folderPath.right(folderPath.length() - 1))
        {
            try
            {
                folder->open(vmime::net::folder::MODE_READ_ONLY);
            }
            catch (vmime::exceptions::authentication_error e) {

            }
            catch (vmime::exceptions::command_error e)
            {

            }

            vmime::shared_ptr<vmime::net::message> message = folder->getMessage(static_cast<vmime::size_t>(positionInFolder));

            try
            {
                folder->fetchMessage(message, vmime::net::fetchAttributes::STRUCTURE);
            }
            catch (std::exception e)
            {

            }

            vmime::shared_ptr<vmime::message> parsedMessage = message->getParsedMessage();

            VmimeMessageContentParser contentParser(parsedMessage);
            MessageContent messageContent;

            messageContent.setHtmlContent(contentParser.parseHtmlContent());
            messageContent.setPlainTextContent(contentParser.parsePlaintextContent());
            messageContent.setAttachments(contentParser.parseAttachments());
            messageContent.setEmbeddedObjects(contentParser.parseEmbeddedObjects());
            messageContent.setRecipients(contentParser.parseRecipients());
            messageContent.setCopyRecipients(contentParser.parseInCopyRecipients());
            messageContent.setBlindCopyRecipients(contentParser.parseBlindCopyRecipients());

            return messageContent;
        }
    }

    return MessageContent();
}

void VmimeInboxService::initializeStore()
{
    vmime::utility::url url = getStoreUrl();

    m_store = m_session->getStore(url);
    m_store->setCertificateVerifier(m_certificateVerifier);
    m_store->connect();
}

void VmimeInboxService::moveMessage(const QString sourceFolderPath, const int messageId, const QString destinationFolderPath)
{
    initializeStore();

    vmime::shared_ptr<vmime::net::folder> rootFolder = m_store->getRootFolder();
    std::vector<vmime::shared_ptr<vmime::net::folder>> folders = rootFolder->getFolders(true);
    folders.push_back(rootFolder);

    vmime::shared_ptr<vmime::net::folder> sourceFolder = nullptr;
    vmime::shared_ptr<vmime::net::folder> destinationFolder = nullptr;

    for (vmime::shared_ptr<vmime::net::folder> folder : folders)
    {
        if (folder->getFullPath().toString("/", vmime::charsets::UTF_8) == sourceFolderPath.right(sourceFolderPath.size() - 1).toStdString().c_str())
        {
            sourceFolder = folder;
        }

        if (folder->getFullPath().toString("/", vmime::charsets::UTF_8) == destinationFolderPath.right(destinationFolderPath.size() - 1).toStdString().c_str())
        {
            destinationFolder = folder;
        }
    }

    if (sourceFolder != nullptr && destinationFolder != nullptr)
    {
        try
        {
            sourceFolder->open(vmime::net::folder::MODE_READ_WRITE, true);
        }
        catch (std::exception e) {
            return;
        }

        try
        {
            destinationFolder->open(vmime::net::folder::MODE_READ_WRITE, true);
        }
        catch (std::exception e) {
            return;
        }

        vmime::net::messageSet set = sourceFolder->copyMessages(sourceFolder->getFullPath(),
                                                                vmime::net::messageSet::byNumber(static_cast<vmime::size_t>(messageId)));

        /*
        vmime::shared_ptr<vmime::message> message = sourceFolder->getMessage(static_cast<vmime::size_t>(messageId))->getParsedMessage();
        vmime::shared_ptr<vmime::message> newMessage = vmime::make_shared<vmime::message>();
        vmime::net::messageSet set = destinationFolder->addMessage(message);
        */

        if (set.isEmpty())
        {
            qWarning() << "Message has been added, but UID is not known";
        }
        else
        {
            qWarning() << "Message has been added, UID is known";
        }

        sourceFolder->deleteMessages(vmime::net::messageSet::byNumber(static_cast<vmime::size_t>(messageId)));

        sourceFolder->expunge();
        destinationFolder->expunge();


        vmime::shared_ptr<vmime::net::message> message = sourceFolder->getMessage(static_cast<vmime::size_t>(messageId));
        if (message->isExpunged())
        {
            qWarning() << "Message is successfully deleted";
        }
        else
        {
            qWarning() << "Message is not successfully deleted";
        }

        sourceFolder->close(true);
        destinationFolder->close(true);
    }
}
