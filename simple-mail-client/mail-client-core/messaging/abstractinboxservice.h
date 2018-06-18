#ifndef ABSTRACTINBOXSERVICE_H
#define ABSTRACTINBOXSERVICE_H

#include "messagemetadata.h"
#include "inboxfolder.h"

class AbstractInboxService : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractInboxService() {}
    virtual QList<MessageMetadata> getMessageMetadata() = 0;
    virtual QList<InboxFolder> getInboxFolders() = 0;
    virtual QString getHtmlMessageContent(QString folderPath, int folderPosition) = 0;
    virtual QString getTextMessageContent(QString folderPath, int folderPosition) = 0;

signals:

public slots:
};

#endif // ABSTRACTINBOXSERVICE_H
