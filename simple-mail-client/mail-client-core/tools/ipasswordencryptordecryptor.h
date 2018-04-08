#ifndef IPASSWORDENCRYPTORDECRYPTOR_H
#define IPASSWORDENCRYPTORDECRYPTOR_H

#include <QObject>

class IPasswordEncryptorDecryptor : public QObject
{
    Q_OBJECT
public:
    explicit IPasswordEncryptorDecryptor(QObject *parent = nullptr) {}
    virtual QString encryptPassword(QString decryptedPassword) = 0;
    virtual QString decryptPassword(QString encryptedPassword) = 0;

signals:

public slots:
};

#endif // IPASSWORDENCRYPTORDECRYPTOR_H
