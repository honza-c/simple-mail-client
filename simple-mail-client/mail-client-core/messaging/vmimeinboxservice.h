#ifndef VMIMEINBOXSERVICE_H
#define VMIMEINBOXSERVICE_H

#include <QObject>
#include <vmime/vmime.hpp>

#include "vmimemessagingbaseservice.h"
#include "vmimemessagemetadataparser.h"
#include "abstractinboxservice.h"
#include "messagemetadata.h"
#include "inboxfolder.h"
#include "vmimeinboxfolderparser.h"
#include "vmimemessagecontentparser.h"

class VmimeInboxService: public VmimeMessagingBaseService, public AbstractInboxService
{
public:
    VmimeInboxService(QString serverUrl, QString emailAddress, QString password)
        : VmimeMessagingBaseService(serverUrl, emailAddress, password) {}

    QList<MessageMetadata> getMessageMetadata() override;
    QList<InboxFolder> getInboxFolders() override;
    QString getHtmlMessageContent(QString folderPath, int folderPosition) override;
    QString getTextMessageContent(QString folderPath, int folderPosition) override;

protected:
    virtual vmime::utility::url getStoreUrl() = 0;
    virtual vmime::shared_ptr<vmime::net::store> initializeStore() = 0;   
};

#endif // VMIMEINBOXSERVICE_H
