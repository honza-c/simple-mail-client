#ifndef VMIMEIMAPSTORE_H
#define VMIMEIMAPSTORE_H

#include <QObject>
#include <vmime/vmime.hpp>
#include "vmimerootcertificateshelper.h"
#include "vmimemessagemetadataparser.h"
#include "messagemetadata.h"

class VmimeImapStore : public QObject
{
    Q_OBJECT
public:
    explicit VmimeImapStore(QObject *parent = nullptr);
    VmimeImapStore(QString serverUrl, QString emailAddress, QString password, int port);
    VmimeImapStore(const VmimeImapStore &other);
    VmimeImapStore &operator= (const VmimeImapStore &other);

    QString getServerUrl();
    QString getEmailAddress();
    QString getPassword();
    int getPort();

    void setServerUrl(QString url);
    void setEmailAddress(QString emailAddress);
    void setPassword(QString password);
    void setPort(int port);

    QList<MessageMetadata> getMessagesMetadata();

signals:

public slots:

private:
    std::string serverUrl;
    std::string emailAddress;
    std::string password;
    int port;

    vmime::shared_ptr<vmime::net::session> session;
    vmime::shared_ptr<vmime::security::cert::defaultCertificateVerifier> certVerifier;
    std::vector <vmime::shared_ptr <vmime::security::cert::X509Certificate>> rootCAs;

    void initializeSession();
    void initializeCertificateVerifier();

    vmime::utility::url generateVmimeImapUrl();
};

#endif // VMIMEIMAPSTORE_H
