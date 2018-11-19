#include "aesencryptordecryptor.h"

void AesEncryptorDecryptor::setHexKey(const QString hexKey)
{
    m_key = importHexString(hexKey.toStdString());
}

void AesEncryptorDecryptor::setHexIV(const QString hexIV)
{
    m_iv = importHexString(hexIV.toStdString());
}

QString AesEncryptorDecryptor::getHexKey() const
{
    return QString(exportStringToHex(m_key).c_str());
}

QString AesEncryptorDecryptor::getHexIV() const
{
    return QString(exportStringToHex(m_iv).c_str());
}

QString AesEncryptorDecryptor::encryptString(const QString decryptedString)
{
    initializeEncryptionCyphers();
    std::string encryptedText;

    m_stfEncryptor = new CryptoPP::StreamTransformationFilter(*m_cbcEncryption,
                                                              new CryptoPP::StringSink(encryptedText));

    m_stfEncryptor->Put(reinterpret_cast<const unsigned char*>(decryptedString.toStdString().c_str()),
                        decryptedString.toStdString().length() + 1);
    m_stfEncryptor->MessageEnd();

    return QString(exportStringToHex(encryptedText).c_str());
}

QString AesEncryptorDecryptor::decryptString(const QString encryptedHexString)
{
    initializeDecryptionCyphers();
    std::string encryptedString = importHexString(encryptedHexString.toStdString());

    std::string decryptedString;

    m_stfDecryptor = new CryptoPP::StreamTransformationFilter(*m_cbcDecryption,
                                                              new CryptoPP::StringSink(decryptedString));
    m_stfDecryptor->Put(reinterpret_cast<const unsigned char*>(encryptedString.c_str()),
                        encryptedString.length());
    m_stfDecryptor->MessageEnd();

    return QString(decryptedString.c_str());
}

void AesEncryptorDecryptor::initializeEncryptionCyphers()
{
    m_aesEncryption = new CryptoPP::AESEncryption();
    m_aesEncryption->SetKey(reinterpret_cast<const unsigned char*>(m_key.c_str()),
                            CryptoPP::AESEncryption::DEFAULT_KEYLENGTH);

    m_cbcEncryption = new CryptoPP::CBC_Mode_ExternalCipher::Encryption();
    m_cbcEncryption->SetCipherWithIV(*m_aesEncryption,
                                     reinterpret_cast<const unsigned char*>(m_iv.c_str()));
}

void AesEncryptorDecryptor::initializeDecryptionCyphers()
{
    m_aesDecryption = new CryptoPP::AES::Decryption();
    m_aesDecryption->SetKey(reinterpret_cast<const unsigned char*>(m_key.c_str()),
                            CryptoPP::AES::DEFAULT_KEYLENGTH);

    m_cbcDecryption = new CryptoPP::CBC_Mode_ExternalCipher::Decryption();
    m_cbcDecryption->SetCipherWithIV(*m_aesDecryption,
                                     reinterpret_cast<const unsigned char*>(m_iv.c_str()));
}

std::string AesEncryptorDecryptor::importHexString(const std::string input) const
{
    std::string output;

    CryptoPP::StringSource stringSource(input,
                                        true,
                                        new CryptoPP::HexDecoder(new CryptoPP::StringSink(output)));

    return output;
}

std::string AesEncryptorDecryptor::exportStringToHex(const std::string input) const
{
    std::string output;

    CryptoPP::StringSource stringSource(input,
                                        true,
                                        new CryptoPP::HexEncoder(new CryptoPP::StringSink(output)));

    return output;
}
