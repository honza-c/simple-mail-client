#ifndef VMIMEBASEMESSAGINGSERVICE_H
#define VMIMEBASEMESSAGINGSERVICE_H

#include <QObject>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <vmime/vmime.hpp>

class VmimeBaseMessagingService : public QObject
{
    Q_OBJECT
public:
    explicit VmimeBaseMessagingService(QObject *parent = nullptr);
    VmimeBaseMessagingService(const VmimeBaseMessagingService &other);

    QString serverUrl() const;
    void setServerUrl(const QString serverUrl);

    QString emailAddress() const;
    void setEmailAddress(const QString emailAddress);

    QString userName() const;
    void setUserName(const QString userName);

    QString password() const;
    void setPassword(const QString password);

    int port() const;
    void setPort(const int port);

    void initializeSession();

signals:

public slots:

    protected:
    void initializeCertificateVerifier();
    std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> getSystemCertificates();

    std::string m_serverUrl;
    std::string m_emailAddress;
    std::string m_userName;
    std::string m_password;
    int m_port;

    vmime::shared_ptr<vmime::net::session> m_session;
    vmime::shared_ptr<vmime::security::cert::defaultCertificateVerifier> m_certificateVerifier;
};

#endif // VMIMEBASEMESSAGINGSERVICE_H
