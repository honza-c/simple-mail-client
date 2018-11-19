#ifndef AESENCRYPTORDECRYPTOR_H
#define AESENCRYPTORDECRYPTOR_H

#include <QObject>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <sstream>
#include <iostream>
#include <QDebug>

class AesEncryptorDecryptor : public QObject
{
    Q_OBJECT
public:
    explicit AesEncryptorDecryptor(QObject *parent = nullptr)
        : QObject(parent) {}

    void setHexKey(const QString hexKey);
    void setHexIV(const QString hexIV);

    QString getHexKey() const;
    QString getHexIV() const;

    QString encryptString(const QString decryptedString);
    QString decryptString(const QString encryptedHexString);

signals:

public slots:

private:
    std::string importHexString(const std::string input) const;
    std::string exportStringToHex(const std::string input) const;
    void initializeEncryptionCyphers();
    void initializeDecryptionCyphers();

    std::string m_key;
    std::string m_iv;

    CryptoPP::AES::Encryption *m_aesEncryption;
    CryptoPP::CBC_Mode_ExternalCipher::Encryption *m_cbcEncryption;
    CryptoPP::StreamTransformationFilter *m_stfEncryptor;

    CryptoPP::AES::Decryption *m_aesDecryption;
    CryptoPP::CBC_Mode_ExternalCipher::Decryption *m_cbcDecryption;
    CryptoPP::StreamTransformationFilter *m_stfDecryptor;
};

#endif // AESENCRYPTORDECRYPTOR_H
