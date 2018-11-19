#include "xmluseraccountsreaderwriter.h"

XmlUserAccountsReaderWriter::XmlUserAccountsReaderWriter(QObject *parent) : QObject(parent)
{
    m_passwordEncryptorDecryptor = new AesEncryptorDecryptor();
}

void XmlUserAccountsReaderWriter::setUserAccounts(QList<UserAccount> *userAccounts)
{
    m_userAccounts = userAccounts;
}

QList<UserAccount> *XmlUserAccountsReaderWriter::userAccounts() const
{
    return m_userAccounts;
}

void XmlUserAccountsReaderWriter::setEncryptionKey(const QString encryptionKey)
{
    m_passwordEncryptorDecryptor->setHexKey(encryptionKey);
}

void XmlUserAccountsReaderWriter::setEncryptionIV(const QString encryptionIV)
{
    m_passwordEncryptorDecryptor->setHexIV(encryptionIV);
}

bool XmlUserAccountsReaderWriter::loadUserAccounts(QIODevice *device)
{
    m_reader.setDevice(device);

    while (m_reader.readNextStartElement())
    {
        if (m_reader.name() == USERS_ROOT_TAGNAME)
        {
            while (m_reader.readNextStartElement())
            {
                if (m_reader.name() == USERACCOUNT_TAGNAME)
                {
                    if (!loadAccount())
                    {
                        qWarning() << "Error while loading user account from settings file.";
                        return false;
                    }
                }
                else
                {
                    qWarning() << "Error while loading user accounts from settings file: file is not valid";
                    return false;
                }
            }
        }
        else
        {
            qWarning() << "Error while loading user accounts from settings file: file is not valid";
            return false;
        }
    }

    return (m_reader.hasError() && m_reader.error() == QXmlStreamReader::PrematureEndOfDocumentError)
            || !m_reader.hasError();
}

bool XmlUserAccountsReaderWriter::storeUserAccounts(QIODevice *device)
{
    m_writer.setDevice(device);
    m_writer.setAutoFormatting(true);

    m_writer.writeStartDocument();
    m_writer.writeStartElement(USERS_ROOT_TAGNAME);

    for (int i = 0; i < m_userAccounts->size(); i++)
    {
        if (!storeAccount(i))
        {
            qWarning() << "Error while writing user account settings to settings file";
            return false;
        }
    }

    m_writer.writeEndElement();
    m_writer.writeEndDocument();

    if (m_writer.hasError())
    {
        qWarning() << "Error while writing user account settings to settings file";
    }

    return !m_writer.hasError();
}

bool XmlUserAccountsReaderWriter::loadAccount()
{
    UserAccount userAccount;

    while (m_reader.readNextStartElement())
    {
        QString currentTagName = m_reader.name().toString();

        if (currentTagName == ACCOUNT_NAME_TAGNAME)
        {
            userAccount.setAccountName(m_reader.readElementText());
        }
        else if (currentTagName == CONTACT_NAME_TAGNAME)
        {
            userAccount.setContactName(m_reader.readElementText());
        }
        else if (currentTagName == EMAIL_ADDRESS_TAGNAME)
        {
            userAccount.setEmailAddress(m_reader.readElementText());
        }
        else if (currentTagName == USER_NAME_TAGNAME)
        {
            userAccount.setUserName(m_reader.readElementText());
        }
        else if (currentTagName == PASSWORD_TAGNAME)
        {
            QString encryptedPassword = m_reader.readElementText();
            QString decryptedPassword = m_passwordEncryptorDecryptor->decryptString(encryptedPassword);
            userAccount.setPassword(decryptedPassword);
        }
        else if (currentTagName == INCOMING_SERVER_TYPE_TAGNAME)
        {
            QString serverTypeValue = m_reader.readElementText();

            if (serverTypeValue == "IMAP")
            {
                userAccount.setIncomingServerType(UserAccount::IncomingServerType::IMAP);
            }
            else if (serverTypeValue == "POP3")
            {
                userAccount.setIncomingServerType(UserAccount::IncomingServerType::POP3);
            }
            else
            {
                return false;
            }
        }
        else if (currentTagName == SMTP_SERVER_URL_TAGNAME)
        {
            userAccount.setSmtpServerUrl(m_reader.readElementText());
        }
        else if (currentTagName == INCOMING_SERVER_URL_TAGNAME)
        {
            userAccount.setIncomingServerAddress(m_reader.readElementText());
        }
        else if (currentTagName == SMTP_SERVER_PORT_TAGNAME)
        {
            userAccount.setSmtpServerPort(m_reader.readElementText().toInt());
        }
        else if (currentTagName == INCOMING_SERVER_PORT_TAGNAME)
        {
            userAccount.setIncomingServerPort(m_reader.readElementText().toInt());
        }
        else
        {
            return false;
        }
    }

    if (m_reader.hasError())
    {
        return false;
    }
    else
    {
        m_userAccounts->push_back(userAccount);
        return true;
    }
}

bool XmlUserAccountsReaderWriter::storeAccount(const int index)
{
    UserAccount userAccount = m_userAccounts->at(index);
    QString encryptedPassword = m_passwordEncryptorDecryptor->encryptString(userAccount.password());

    m_writer.writeStartElement(USERACCOUNT_TAGNAME);

    m_writer.writeTextElement(ACCOUNT_NAME_TAGNAME, userAccount.accountName());
    m_writer.writeTextElement(CONTACT_NAME_TAGNAME, userAccount.contactName());
    m_writer.writeTextElement(EMAIL_ADDRESS_TAGNAME, userAccount.emailAddress());
    m_writer.writeTextElement(USER_NAME_TAGNAME, userAccount.userName());
    m_writer.writeTextElement(PASSWORD_TAGNAME, encryptedPassword);
    m_writer.writeTextElement(SMTP_SERVER_URL_TAGNAME, userAccount.smtpServerUrl());

    UserAccount::IncomingServerType type = userAccount.incomingServerType();

    if (type == UserAccount::IncomingServerType::IMAP)
    {
        m_writer.writeTextElement(INCOMING_SERVER_TYPE_TAGNAME, "IMAP");
    }
    else if (type == UserAccount::IncomingServerType::POP3)
    {
        m_writer.writeTextElement(INCOMING_SERVER_TYPE_TAGNAME, "POP3");
    }
    else
    {
        return false;
    }

    m_writer.writeTextElement(INCOMING_SERVER_URL_TAGNAME, userAccount.incomingServerAddress());
    m_writer.writeTextElement(SMTP_SERVER_PORT_TAGNAME, QString::number(userAccount.smtpServerPort()));
    m_writer.writeTextElement(INCOMING_SERVER_PORT_TAGNAME, QString::number(userAccount.incomingServerPort()));

    m_writer.writeEndElement();

    return !m_writer.hasError();
}
