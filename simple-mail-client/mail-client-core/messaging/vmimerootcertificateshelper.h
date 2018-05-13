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

#include "tools/constants.h"

class VMimeRootCertificatesHelper : public QObject
{
    Q_OBJECT
public:
    explicit VMimeRootCertificatesHelper(QObject *parent = nullptr);
    std::vector <vmime::shared_ptr<vmime::security::cert::X509Certificate>> getSystemRootCertificates();

private:
    QString certificatesPath;

    vmime::shared_ptr<vmime::security::cert::X509Certificate> getCertificateFromFile(const char *absolutePath);
    std::vector <vmime::shared_ptr<vmime::security::cert::X509Certificate>> getCertificatesFromPemBundlePath();
    std::vector <vmime::shared_ptr<vmime::security::cert::X509Certificate>> getCertificatesFromFolder();

signals:

public slots:
};

#endif // VMIMEROOTCERTIFICATESHELPER_H
