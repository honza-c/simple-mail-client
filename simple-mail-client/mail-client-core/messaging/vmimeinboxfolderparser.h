#ifndef VMIMEINBOXFOLDERPARSER_H
#define VMIMEINBOXFOLDERPARSER_H

#include <QObject>
#include <vmime/vmime.hpp>
#include "inboxfolder.h"

class VmimeInboxFolderParser : public QObject
{
    Q_OBJECT
public:
    explicit VmimeInboxFolderParser(QObject *parent = nullptr);
    InboxFolder parse(vmime::shared_ptr<vmime::net::folder> folder, QString emailAddress);

private:
    QString getFolderPath(vmime::shared_ptr<vmime::net::folder> folder);

signals:

public slots:
};

#endif // VMIMEINBOXFOLDERPARSER_H
