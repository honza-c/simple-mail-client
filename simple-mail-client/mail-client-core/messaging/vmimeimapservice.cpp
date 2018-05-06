#include "vmimeimapservice.h"

vmime::utility::url VmimeImapService::getStoreUrl()
{
    QString userName = QString(this->emailAddress.c_str());
    userName = userName.split("@")[0];

    QString imapAddress;

    imapAddress += "imaps://";
    imapAddress += userName;
    imapAddress += ":";
    imapAddress += QString(this->password.c_str());
    imapAddress += "@";
    imapAddress += QString(this->serverUrl.c_str());
    imapAddress += ":";
    imapAddress += QString::number(this->port);

    return vmime::utility::url(imapAddress.toStdString());
}

vmime::shared_ptr<vmime::net::store> VmimeImapService::initializeStore()
{
    vmime::utility::url url = getStoreUrl();
    vmime::shared_ptr<vmime::net::store> store = this->session->getStore(url);
    store->setCertificateVerifier(this->certVerifier);

    return store;
}

int VmimeImapService::getPort()
{
   return this->port;
}

void VmimeImapService::setPort(int port)
{
    this->port = port;
}
