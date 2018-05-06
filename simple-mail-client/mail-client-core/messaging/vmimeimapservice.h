#ifndef VMIMEIMAPSERVICE_H
#define VMIMEIMAPSERVICE_H

#include <QObject>
#include <vmime/vmime.hpp>
#include "vmimeinboxservice.h"

class VmimeImapService : public VmimeInboxService
{
public:
    VmimeImapService(QString serverUrl, QString emailAddress, QString password, int port)
        : VmimeInboxService(serverUrl, emailAddress, password)
        , port(port) {}

    int getPort();
    void setPort(int port);

private:
    vmime::utility::url getStoreUrl() override;
    vmime::shared_ptr<vmime::net::store> initializeStore() override;

    int port;
};

#endif // VMIMEIMAPSERVICE_H
