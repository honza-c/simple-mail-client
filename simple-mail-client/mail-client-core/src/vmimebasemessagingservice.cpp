#include "vmimebasemessagingservice.h"

VmimeBaseMessagingService::VmimeBaseMessagingService(QObject *parent)
    : QObject(parent)
{
    initializeSession();
}

VmimeBaseMessagingService::VmimeBaseMessagingService(const VmimeBaseMessagingService &other)
{
    m_emailAddress = other.m_emailAddress;
    m_userName = other.m_userName;
    m_password = other.m_password;
    m_serverUrl = other.m_serverUrl;

    initializeSession();
}

QString VmimeBaseMessagingService::serverUrl() const
{
    return QString(m_serverUrl.c_str());
}

void VmimeBaseMessagingService::setServerUrl(const QString serverUrl)
{
    m_serverUrl = serverUrl.toStdString();
}

QString VmimeBaseMessagingService::emailAddress() const
{
    return QString(m_emailAddress.c_str());
}

void VmimeBaseMessagingService::setEmailAddress(const QString emailAddress)
{
    m_emailAddress = emailAddress.toStdString();
}

QString VmimeBaseMessagingService::userName() const
{
    return QString(m_userName.c_str());
}

void VmimeBaseMessagingService::setUserName(const QString userName)
{
    m_userName = userName.toStdString().c_str();
}

QString VmimeBaseMessagingService::password() const
{
    return QString(m_password.c_str());
}

void VmimeBaseMessagingService::setPassword(const QString password)
{
    m_password = password.toStdString();
}

int VmimeBaseMessagingService::port() const
{
    return m_port;
}

void VmimeBaseMessagingService::setPort(const int port)
{
    m_port = port;
}

void VmimeBaseMessagingService::initializeSession()
{
    initializeCertificateVerifier();
    m_session = vmime::net::session::create();
}

void VmimeBaseMessagingService::initializeCertificateVerifier()
{
    m_certificateVerifier = vmime::make_shared<vmime::security::cert::defaultCertificateVerifier>();
    m_certificateVerifier->setX509RootCAs(getSystemCertificates());
}

std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> VmimeBaseMessagingService::getSystemCertificates()
{
    std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> vmimeCertificates;

    QSslConfiguration sslConfiguration;
    QList<QSslCertificate> certificates = sslConfiguration.systemCaCertificates();

    for (QSslCertificate certificate : certificates)
    {
        vmime::utility::inputStreamStringAdapter isAdapter(certificate.toDer().toStdString());
        vmime::shared_ptr<vmime::security::cert::X509Certificate> vmimeCertificate = vmime::security::cert::X509Certificate::import(isAdapter);

        if (vmimeCertificate != nullptr)
        {
            vmimeCertificates.push_back(vmimeCertificate);
        }
    }

    return vmimeCertificates;
}
