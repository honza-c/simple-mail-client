#include "aespasswordencryptordecryptor.h"

AESPasswordEncryptorDecryptor::AESPasswordEncryptorDecryptor(QString hexKey, QString hexIV)
{
    this->key = importHexString(hexKey.toStdString());
    this->iv = importHexString(hexIV.toStdString());
}

QString AESPasswordEncryptorDecryptor::encryptPassword(QString plaintextPassword)
{
    std::string encryptedText;

    initializeEncryptionCyphers();

    this->stfEncryptor = new CryptoPP::StreamTransformationFilter(*(this->cbcEncryption),
                                                                  new CryptoPP::StringSink(encryptedText));
    this->stfEncryptor->Put(reinterpret_cast<const unsigned char*>(plaintextPassword.toStdString().c_str()),
                            plaintextPassword.toStdString().length() + 1);
    this->stfEncryptor->MessageEnd();

    return QString(exportStringToHex(encryptedText).c_str());
}

QString AESPasswordEncryptorDecryptor::decryptPassword(QString encryptedHexPassword)
{
    std::string encryptedPassword = importHexString(encryptedHexPassword.toStdString());
    std::string plaintextPassword;

    initializeDecryptionCyphers();

    this->stfDecryptor = new CryptoPP::StreamTransformationFilter(*(this->cbcDecryption),
                                                                  new CryptoPP::StringSink(plaintextPassword));
    this->stfDecryptor->Put(reinterpret_cast<const unsigned char*>(encryptedPassword.c_str()),
                            encryptedPassword.length());
    this->stfDecryptor->MessageEnd();

    return QString(plaintextPassword.c_str());
}

void AESPasswordEncryptorDecryptor::initializeEncryptionCyphers()
{
    this->aesEncryption = new CryptoPP::AESEncryption();
    this->aesEncryption->SetKey(reinterpret_cast<const unsigned char *>(this->key.c_str()),
                                CryptoPP::AESEncryption::DEFAULT_KEYLENGTH);

    this->cbcEncryption = new CryptoPP::CBC_Mode_ExternalCipher::Encryption();
    this->cbcEncryption->SetCipherWithIV(*(this->aesEncryption),
                                         reinterpret_cast<const unsigned char *>(this->iv.c_str()));
}

void AESPasswordEncryptorDecryptor::initializeDecryptionCyphers()
{
    this->aesDecryption = new CryptoPP::AES::Decryption();
    this->aesDecryption->SetKey(reinterpret_cast<const unsigned char *>(this->key.c_str()),
                                CryptoPP::AES::DEFAULT_KEYLENGTH);

    this->cbcDecryption = new CryptoPP::CBC_Mode_ExternalCipher::Decryption();
    this->cbcDecryption->SetCipherWithIV(*(this->aesDecryption),
                                         reinterpret_cast<const unsigned char *>(this->iv.c_str()));
}

std::string AESPasswordEncryptorDecryptor::importHexString(std::string input)
{
    std::string output;

    CryptoPP::StringSource stringSource(input,
                                        true,
                                        new CryptoPP::HexDecoder(
                                            new CryptoPP::StringSink(output)));

    return output;
}

std::string AESPasswordEncryptorDecryptor::exportStringToHex(std::string input)
{
    std::string output;

    CryptoPP::StringSource stringSource(input,
                                        true,
                                        new CryptoPP::HexEncoder(
                                            new CryptoPP::StringSink(output)));

    return output;
}
