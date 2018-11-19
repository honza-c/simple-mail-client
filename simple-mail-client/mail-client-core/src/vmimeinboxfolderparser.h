#ifndef VMIMEINBOXFOLDERPARSER_H
#define VMIMEINBOXFOLDERPARSER_H

#include <QObject>
#include <vmime/vmime.hpp>
#include "src/inboxfolder.h"

class VmimeInboxFolderParser : public QObject
{
    Q_OBJECT
public:
    explicit VmimeInboxFolderParser(vmime::shared_ptr<vmime::net::folder> folder, QObject *parent = nullptr);

    InboxFolder parse() const;

signals:

public slots:

private:
    QString getFolderPath() const;
    QString getFolderPath(const vmime::shared_ptr<vmime::net::folder> folder) const;

    vmime::shared_ptr<vmime::net::folder> m_folder;
    vmime::net::folderAttributes m_folderAttributes;
};

#endif // VMIMEINBOXFOLDERPARSER_H
