#include "vmimerootcertificateshelper.h"

VMimeRootCertificatesHelper::VMimeRootCertificatesHelper(QString certLocationPath, QObject *parent) : QObject(parent)
{
    this->certificatesDir = new QDir(certLocationPath);
}

std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> VMimeRootCertificatesHelper::getSystemRootCertificates()
{
    QStringList certFileNamesList = this->certificatesDir->entryList();
    std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> rootCAs;
    QString certificateAbsolutePath;

    for (QString certFileName : certFileNamesList)
    {
        // don't open special "." and ".." files
        if (certFileName == "." || certFileName == "..")
        {
            continue;
        }

        certificateAbsolutePath = this->certificatesDir->absoluteFilePath(certFileName);
        vmime::shared_ptr<vmime::security::cert::X509Certificate> cert;
        cert = getCertificate(certificateAbsolutePath.toStdString().c_str());

        if (cert == nullptr)
        {
            continue;
        }
        else
        {
            rootCAs.push_back(cert);
        }
    }

    return rootCAs;
}

vmime::shared_ptr<vmime::security::cert::X509Certificate> VMimeRootCertificatesHelper::getCertificate(const char *absolutePath)
{
    std::ifstream fileStream;
    fileStream.open(absolutePath, std::ios_base::in | std::ios_base::binary);

    if (!fileStream.is_open())
    {
        qWarning() << "Error while opening the file: " << absolutePath;
        fileStream.close();

        return nullptr;
    }

    vmime::utility::inputStreamAdapter is(fileStream);
    vmime::shared_ptr<vmime::security::cert::X509Certificate> cert;
    cert = vmime::security::cert::X509Certificate::import(is);

    fileStream.close();

    return cert;
}
