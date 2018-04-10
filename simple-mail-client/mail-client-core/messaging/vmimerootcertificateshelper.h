#ifndef VMIMEROOTCERTIFICATESHELPER_H
#define VMIMEROOTCERTIFICATESHELPER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QDebug>

#include <vmime/vmime.hpp>

#include <vector>
#include <iostream>
#include <fstream>

class VMimeRootCertificatesHelper : public QObject
{
    Q_OBJECT
public:
    explicit VMimeRootCertificatesHelper(QString certLocationPath, QObject *parent = nullptr);
    std::vector <vmime::shared_ptr<vmime::security::cert::X509Certificate>> getSystemRootCertificates();

private:
    QDir *certificatesDir;

    vmime::shared_ptr<vmime::security::cert::X509Certificate> getCertificate(const char *absolutePath);

signals:

public slots:
};

#endif // VMIMEROOTCERTIFICATESHELPER_H
