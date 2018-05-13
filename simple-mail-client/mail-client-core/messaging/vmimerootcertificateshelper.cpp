#include "vmimerootcertificateshelper.h"

VMimeRootCertificatesHelper::VMimeRootCertificatesHelper(QObject *parent) : QObject(parent)
{
    if (QFile::exists(Constants::ROOT_CERTIFICATES_LINUX_PEM_BUNDLE_PATH))
    {
        this->certificatesPath = Constants::ROOT_CERTIFICATES_LINUX_PEM_BUNDLE_PATH;
    }
    else if (QFile::exists(Constants::ROOT_CERTIFICATES_LINUX_MOZILLA_CA_CERTS))
    {
        this->certificatesPath = Constants::ROOT_CERTIFICATES_LINUX_MOZILLA_CA_CERTS;
    }
    else
    {
        this->certificatesPath = "";
    }
}

std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> VMimeRootCertificatesHelper::getSystemRootCertificates()
{
    std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> rootCAs;

    if (this->certificatesPath == Constants::ROOT_CERTIFICATES_LINUX_MOZILLA_CA_CERTS)
    {
        return getCertificatesFromFolder();
    }
    else if (this->certificatesPath == Constants::ROOT_CERTIFICATES_LINUX_PEM_BUNDLE_PATH)
    {
        return getCertificatesFromPemBundlePath();
    }

    return rootCAs;
}

std::vector <vmime::shared_ptr<vmime::security::cert::X509Certificate>> VMimeRootCertificatesHelper::getCertificatesFromPemBundlePath()
{
    std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> rootCAs;
    QDir certDir(this->certificatesPath);
    QStringList certFileNamesList = certDir.entryList();

    QString certAbsolutePath;
    for (QString certFileName : certFileNamesList)
    {
        certAbsolutePath = certDir.absoluteFilePath(certFileName);
        QFile certFile(certAbsolutePath);
        certFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QList<QString*> certificatesContent;
        QString *currentCert = new QString();

        while (!certFile.atEnd())
        {
            QString line = certFile.readLine();

            if (line == '\n')
            {
                certificatesContent.push_back(currentCert);
                currentCert = new QString();
            }
            else
            {
                currentCert->append(line);
            }
        }

        for (QString *certContent : certificatesContent)
        {
            std::istringstream stringStream(certContent->toStdString());
            vmime::utility::inputStreamAdapter isAdapter(stringStream);
            vmime::shared_ptr<vmime::security::cert::X509Certificate> cert;
            cert = vmime::security::cert::X509Certificate::import(isAdapter);

            if (cert != nullptr)
            {
                rootCAs.push_back(cert);
            }
        }
    }

    return rootCAs;
}

std::vector <vmime::shared_ptr<vmime::security::cert::X509Certificate>> VMimeRootCertificatesHelper::getCertificatesFromFolder()
{
    std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>> rootCAs;
    QDir certDir(this->certificatesPath);
    QStringList certFileNamesList = certDir.entryList();

    QString certificateAbsolutePath;

    for (QString certFileName : certFileNamesList)
    {
        // don't open special "." and ".." files
        if (certFileName == "." || certFileName == "..")
        {
            continue;
        }

        certificateAbsolutePath = certDir.absoluteFilePath(certFileName);
        vmime::shared_ptr<vmime::security::cert::X509Certificate> cert;
        cert = getCertificateFromFile(certificateAbsolutePath.toStdString().c_str());

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

vmime::shared_ptr<vmime::security::cert::X509Certificate> VMimeRootCertificatesHelper::getCertificateFromFile(const char *absolutePath)
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
