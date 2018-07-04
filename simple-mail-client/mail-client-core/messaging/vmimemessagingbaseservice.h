#ifndef VMIMEMESSAGINGBASESERVICE_H
#define VMIMEMESSAGINGBASESERVICE_H

#include <QObject>
#include <vmime/vmime.hpp>
#include "tools/constants.h"
#include <QSslCertificate>
#include <QSslConfiguration>

class VmimeMessagingBaseService : public QObject
{
    Q_OBJECT
public:
    VmimeMessagingBaseService(QString serverUrl,
                              QString emailAddress,
                              QString password);

    void setServerUrl(QString serverUrl);
    void setEmailAddress(QString emailAddress);
    void setPassword(QString password);

    QString getServerUrl();
    QString getEmailAddress();
    QString getPassword();

signals:

public slots:

protected:
    std::string serverUrl;
    std::string emailAddress;
    std::string password;

    vmime::shared_ptr<vmime::net::session> session;
    vmime::shared_ptr<vmime::net::transport> transport;
    vmime::shared_ptr<vmime::security::cert::defaultCertificateVerifier> certVerifier;

    void initializeSession();
    void initializeCertificateVerifier();
    std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> getSystemCertificates();
};

#endif // VMIMEMESSAGINGBASESERVICE_H
