#ifndef AESPASSWORDENCRYPTORDECRYPTOR_H
#define AESPASSWORDENCRYPTORDECRYPTOR_H

#include "ipasswordencryptordecryptor.h"

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <sstream>
#include <iostream>
#include <QDebug>

class AESPasswordEncryptorDecryptor : public IPasswordEncryptorDecryptor
{
    Q_OBJECT
public:
    AESPasswordEncryptorDecryptor(QString hexKey, QString hexIV);
    QString encryptPassword(QString plaintextPassword) override;
    QString decryptPassword(QString encryptedHexPassword) override;

private:
    std::string importHexString(std::string input);
    std::string exportStringToHex(std::string input);

    void initializeEncryptionCyphers();
    void initializeDecryptionCyphers();

    std::string key;
    std::string iv;

    CryptoPP::AES::Encryption *aesEncryption;
    CryptoPP::CBC_Mode_ExternalCipher::Encryption *cbcEncryption;
    CryptoPP::StreamTransformationFilter *stfEncryptor;

    CryptoPP::AES::Decryption *aesDecryption;
    CryptoPP::CBC_Mode_ExternalCipher::Decryption *cbcDecryption;
    CryptoPP::StreamTransformationFilter *stfDecryptor;
};

#endif // AESPASSWORDENCRYPTORDECRYPTOR_H
