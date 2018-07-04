#include "vmimemessagingbaseservice.h"

VmimeMessagingBaseService::VmimeMessagingBaseService(QString serverUrl, QString emailAddress, QString password)
{
    this->serverUrl = serverUrl.toStdString();
    this->emailAddress = emailAddress.toStdString();
    this->password = password.toStdString();

    initializeCertificateVerifier();
    initializeSession();
}

void VmimeMessagingBaseService::setServerUrl(QString serverUrl)
{
    this->serverUrl = serverUrl.toStdString();
}

void VmimeMessagingBaseService::setEmailAddress(QString emailAddress)
{
    this->emailAddress = emailAddress.toStdString();
}

void VmimeMessagingBaseService::setPassword(QString password)
{
    this->password = password.toStdString();
}

QString VmimeMessagingBaseService::getServerUrl()
{
    return QString(this->serverUrl.c_str());
}

QString VmimeMessagingBaseService::getEmailAddress()
{
    return QString(this->emailAddress.c_str());
}

QString VmimeMessagingBaseService::getPassword()
{
    return QString(this->password.c_str());
}

void VmimeMessagingBaseService::initializeSession()
{
    this->session = vmime::net::session::create();
}

void VmimeMessagingBaseService::initializeCertificateVerifier()
{
    this->certVerifier = vmime::make_shared<vmime::security::cert::defaultCertificateVerifier>();
    this->certVerifier->setX509RootCAs(getSystemCertificates());
}

std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> VmimeMessagingBaseService::getSystemCertificates()
{
    std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> vmimeCerts;

    QSslConfiguration sslConfiguration;
    QList<QSslCertificate> certs = sslConfiguration.systemCaCertificates();

    for (QSslCertificate cert : certs)
    {
        vmime::utility::inputStreamStringAdapter isAdapter(cert.toDer().toStdString());
        vmime::shared_ptr<vmime::security::cert::X509Certificate> vmimeCert = vmime::security::cert::X509Certificate::import(isAdapter);

        if (vmimeCert != nullptr)
        {
            vmimeCerts.push_back(vmimeCert);
        }
    }

    return vmimeCerts;
}
