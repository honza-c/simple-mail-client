#include "usersettingswriterandloader.h"

static QList<UserAccount*> UserSettingsWriterAndLoader::loadSettings(const QString &filePath)
{
    QList<UserAccount*> users = new QList<UserAccount*>();
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "Error while opening the file for read: " << file.errorString();
        return users;
    }

    QXmlStreamReader reader(file);

    while (reader.readNextStartElement())
    {
        if (reader.name() == "Users")
        {
            while (reader.readNextStartElement())
            {
                if (reader.name() == "User")
                {
                    while (reader.readNextStartElement())
                    {
                        UserAccount *account = new UserAccount();

                        switch (reader.name())
                        {
                        case Constants::USERACCOUNT_ACCOUNT_NAME_TAGNAME:
                            account->setAccountName(reader.readElementText());
                            break;
                        case Constants::USERACCOUNT_YOUR_NAME_TAGNAME:
                            account->setYourName(reader.readElementText());
                            break;
                        case Constants::USERACCOUNT_EMAIL_ADDRESS_TAGNAME:
                            account->setEmailAddress(reader.readElementText());
                            break;
                        case Constants::USERACCOUNT_PASSWORD_TAGNAME:
                            account->setPassword(reader.readElementText());
                            break;
                        case Constants::USERACCOUNT_SMTP_SERVER_URL_TAGNAME:
                            account->setSmtpServerUrl(reader.readElementText());
                            break;
                        case Constants::USERACCOUNT_POP3_SERVER_URL_TAGNAME:
                            account->setPopServerUrl(reader.readElementText());
                            break;
                        case Constants::USERACCOUNT_SMTP_SERVER_PORT_TAGNAME:
                            account->setSmtpServerPort(reader.readElementText().toInt());
                            break;
                        case Constants::USERACCOUNT_POP3_SERVER_PORT_TAGNAME:
                            account->setPopServerPort(reader.readElementText().toInt());
                            break;
                        default:
                            qWarning() << Constants::USER_ACCOUNT_SETTINGS_FILE << " is inconsistent";
                            reader.skipCurrentElement();
                            break;
                        }

                        users.push_back(account);
                    }
                }
                else
                {
                    qWarning() << Constants::USER_ACCOUNT_SETTINGS_FILE << " is inconsistent";
                    reader.skipCurrentElement();
                }
            }
        }
        else
        {
            qWarning() << Constants::USER_ACCOUNT_SETTINGS_FILE << " is inconsistent";
            reader.skipCurrentElement();
        }
    }

    file.close();

    return users;
}

static void UserSettingsWriterAndLoader::writeSettings(const QList<UserAccount*> users, const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qWarning() << "Error while opening the file for write: " << file.errorString();
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Users");

    for (UserAccount *account : users)
    {
        xmlWriter.writeStartElement("User");

        xmlWriter.writeTextElement(Constants::USERACCOUNT_ACCOUNT_NAME_TAGNAME, account->getAccountName());
        xmlWriter.writeTextElement(Constants::USERACCOUNT_YOUR_NAME_TAGNAME, account->getYourName());
        xmlWriter.writeTextElement(Constants::USERACCOUNT_EMAIL_ADDRESS_TAGNAME, account->getEmailAddress());
        xmlWriter.writeTextElement(Constants::USERACCOUNT_PASSWORD_TAGNAME, account->getPassword());
        xmlWriter.writeTextElement(Constants::USERACCOUNT_SMTP_SERVER_URL_TAGNAME, account->getSmtpServerUrl());
        xmlWriter.writeTextElement(Constants::USERACCOUNT_POP3_SERVER_URL_TAGNAME, account->getPopServerUrl());
        xmlWriter.writeTextElement(Constants::USERACCOUNT_SMTP_SERVER_PORT_TAGNAME, account->getSmtpServerPort());
        xmlWriter.writeTextElement(Constants::USERACCOUNT_POP3_SERVER_PORT_TAGNAME, account->getPopServerPort());

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}
