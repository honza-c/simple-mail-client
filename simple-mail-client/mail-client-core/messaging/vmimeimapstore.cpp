#include "vmimeimapstore.h"

VmimeImapStore::VmimeImapStore(QObject *parent) : QObject(parent)
{

}

VmimeImapStore::VmimeImapStore(QString serverUrl, QString emailAddress, QString password, int port)
{
    this->serverUrl = serverUrl.toStdString();
    this->emailAddress = emailAddress.toStdString();
    this->password = password.toStdString();
    this->port = port;

    initializeCertificateVerifier();
    initializeSession();
}

VmimeImapStore::VmimeImapStore(const VmimeImapStore &other)
{
    this->serverUrl = other.serverUrl;
    this->emailAddress = other.emailAddress;
    this->password = other.password;
    this->port = other.port;

    initializeCertificateVerifier();
    initializeSession();
}

VmimeImapStore& VmimeImapStore::operator=(const VmimeImapStore &other)
{
    this->serverUrl = other.serverUrl;
    this->emailAddress = other.emailAddress;
    this->password = other.password;
    this->port = other.port;

    initializeCertificateVerifier();
    initializeSession();
}

/*
 *     VmimeImapStore(VmimeImapStore &other);
    VmimeImapStore &operator= (const VmimeImapStore &other);
    */

QString VmimeImapStore::getServerUrl()
{
    return QString(this->serverUrl.c_str());
}

QString VmimeImapStore::getEmailAddress()
{
    return QString(this->emailAddress.c_str());
}

QString VmimeImapStore::getPassword()
{
    return QString(this->password.c_str());
}

int VmimeImapStore::getPort()
{
    return this->port;
}

void VmimeImapStore::setServerUrl(QString serverUrl)
{
    this->serverUrl = serverUrl.toStdString();
}

void VmimeImapStore::setEmailAddress(QString emailAddress)
{
    this->emailAddress = emailAddress.toStdString();
}

void VmimeImapStore::setPassword(QString password)
{
    this->password = password.toStdString();
}

void VmimeImapStore::setPort(int port)
{
    this->port = port;
}

QList<MessageMetadata> VmimeImapStore::getMessagesMetadata()
{
    vmime::utility::url url = generateVmimeImapUrl();
    vmime::shared_ptr<vmime::net::store> store = this->session->getStore(url);
    store->setCertificateVerifier(this->certVerifier);

    store->connect();

    vmime::shared_ptr<vmime::net::folder> rootFolder = store->getDefaultFolder();
    rootFolder->open(vmime::net::folder::MODE_READ_ONLY);

    std::vector<vmime::shared_ptr<vmime::net::message>> messages
            = rootFolder->getMessages(vmime::net::messageSet::byNumber(1, 500));

    rootFolder->fetchMessages(messages,
                              vmime::net::fetchAttributes::ENVELOPE |
                              vmime::net::fetchAttributes::FLAGS |
                              vmime::net::fetchAttributes::SIZE |
                              vmime::net::fetchAttributes::UID);
    store->disconnect();

    QList<MessageMetadata> metadataList;
    VmimeMessageMetadataParser parser;

    for (unsigned int i = 0; i < messages.size(); i++)
    {
        vmime::shared_ptr<vmime::net::message> message = messages[i];
        metadataList.push_back(parser.parse(message));
    }

    return metadataList;
}


void VmimeImapStore::initializeSession()
{
    this->session = vmime::net::session::create();
}

void VmimeImapStore::initializeCertificateVerifier()
{
    this->certVerifier = vmime::make_shared<vmime::security::cert::defaultCertificateVerifier>();
    VMimeRootCertificatesHelper certHelper("/usr/share/ca-certificates/mozilla");
    this->certVerifier->setX509RootCAs(certHelper.getSystemRootCertificates());
}

vmime::utility::url VmimeImapStore::generateVmimeImapUrl()
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
