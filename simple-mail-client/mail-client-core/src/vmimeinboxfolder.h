#ifndef VMIMEINBOXFOLDER_H
#define VMIMEINBOXFOLDER_H

#include <QObject>
#include <QDebug>
#include <vmime/vmime.hpp>
#include "src/vmimeinboxfolderparser.h"
#include "src/vmimemessagecontentparser.h"
#include "src/vmimemessagemetadataparser.h"
#include "src/messagemetadata.h"
#include "src/attachment.h"
#include "src/databasemanager.h"
#include "src/inboxfolder.h"
#include "src/contact.h"

class VmimeInboxFolder : public QObject
{
    Q_OBJECT
public:
    explicit VmimeInboxFolder(vmime::shared_ptr<vmime::net::folder> remoteFolder, QString emailAddress, QObject *parent = nullptr);
    VmimeInboxFolder(const VmimeInboxFolder &other);
    VmimeInboxFolder &operator=(const VmimeInboxFolder &other);

    InboxFolder data() const;
    void setData(const InboxFolder data);

    QList<MessageMetadata> getMessagesMetadataFromPosition(int position) const;
signals:

public slots:

private:
    void openFolder();
    vmime::shared_ptr<vmime::net::folder> m_remoteFolder;
    InboxFolder m_inboxFolder;

    bool m_successfullyOpened;
};

#endif // VMIMEINBOXFOLDER_H
