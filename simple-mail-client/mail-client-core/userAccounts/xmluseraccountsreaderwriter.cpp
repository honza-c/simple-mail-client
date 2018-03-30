#include "xmluseraccountsreaderwriter.h"


XmlUserAccountsReaderWriter::XmlUserAccountsReaderWriter(QList<UserAccount> *userAccounts)
{
    this->accountList = userAccounts;
}


bool XmlUserAccountsReaderWriter::loadUserAccounts(QIODevice *device)
{
    reader.setDevice(device);

    while (reader.readNextStartElement())
    {
        if (reader.name() == Constants::USERSETTINGS_ROOT_TAGNAME)
        {
            while (reader.readNextStartElement())
            {
                if (reader.name() == Constants::USERSETTINGS_USERACCOUNT_TAGNAME)
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

    return (reader.hasError() && reader.error() == QXmlStreamReader::PrematureEndOfDocumentError)
            || !reader.hasError();
}

bool XmlUserAccountsReaderWriter::storeUserAccounts(QIODevice *device)
{
    writer.setDevice(device);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();

    writer.writeStartElement(Constants::USERSETTINGS_ROOT_TAGNAME);

    for (int i = 0; i < accountList->size(); i++)
    {
        if (!storeAccount(i))
        {
            qWarning() << "Error while writing user account settings to settings file";
            return false;
        }
    }

    writer.writeEndElement();
    writer.writeEndDocument();

    if (writer.hasError())
    {
        qWarning() << "Error while writing user account settings to settings file";
    }

    return !writer.hasError();
}

bool XmlUserAccountsReaderWriter::loadAccount()
{
    UserAccount account;

    qWarning() << reader.errorString();
    while (reader.readNextStartElement())
    {
        QString currentTagName = reader.name().toString();

        if (currentTagName == Constants::USERACCOUNT_ACCOUNT_NAME_TAGNAME)
        {
            account.setAccountName(reader.readElementText());
        }
        else if (currentTagName == Constants::USERACCOUNT_YOUR_NAME_TAGNAME)
        {
            account.setYourName(reader.readElementText());
        }
        else if (currentTagName == Constants::USERACCOUNT_EMAIL_ADDRESS_TAGNAME)
        {
            account.setEmailAddress(reader.readElementText());
        }
        else if (currentTagName == Constants::USERACCOUNT_PASSWORD_TAGNAME)
        {
            account.setPassword(reader.readElementText());
        }
        else if (currentTagName == Constants::USERACCOUNT_SMTP_SERVER_URL_TAGNAME)
        {
            account.setSmtpServerUrl(reader.readElementText());
        }
        else if (currentTagName == Constants::USERACCOUNT_POP3_SERVER_URL_TAGNAME)
        {
            account.setPopServerUrl(reader.readElementText());
        }
        else if (currentTagName == Constants::USERACCOUNT_SMTP_SERVER_PORT_TAGNAME)
        {
            account.setSmtpServerPort(reader.readElementText().toInt());
        }
        else if (currentTagName == Constants::USERACCOUNT_POP3_SERVER_PORT_TAGNAME)
        {
            account.setPopServerPort(reader.readElementText().toInt());
        }
        else
        {
            return false;
        }
    }

    accountList->push_back(account);
    return !reader.hasError();
}

bool XmlUserAccountsReaderWriter::storeAccount(int index)
{
    UserAccount account = accountList->at(index);

    writer.writeStartElement(Constants::USERSETTINGS_USERACCOUNT_TAGNAME);

    writer.writeTextElement(Constants::USERACCOUNT_ACCOUNT_NAME_TAGNAME, account.getAccountName());
    writer.writeTextElement(Constants::USERACCOUNT_YOUR_NAME_TAGNAME, account.getYourName());
    writer.writeTextElement(Constants::USERACCOUNT_EMAIL_ADDRESS_TAGNAME, account.getEmailAddress());
    writer.writeTextElement(Constants::USERACCOUNT_PASSWORD_TAGNAME, account.getPassword());
    writer.writeTextElement(Constants::USERACCOUNT_SMTP_SERVER_URL_TAGNAME, account.getSmtpServerUrl());
    writer.writeTextElement(Constants::USERACCOUNT_POP3_SERVER_URL_TAGNAME, account.getPopServerUrl());
    writer.writeTextElement(Constants::USERACCOUNT_SMTP_SERVER_PORT_TAGNAME, QString::number(account.getSmtpServerPort()));
    writer.writeTextElement(Constants::USERACCOUNT_POP3_SERVER_PORT_TAGNAME, QString::number(account.getPopServerPort()));

    writer.writeEndElement();

    return !writer.hasError();
}
