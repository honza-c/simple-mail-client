#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants
{
    // filename constants for files used in application
    const QString ERROR_LOG_FILE_NAME = "error.log";
    const QString USER_ACCOUNT_SETTINGS_FILE = "users.xml";

    // element names used in XML configuration file for store user accounts
    const QString USERSETTINGS_ROOT_TAGNAME = "Users";
    const QString USERSETTINGS_USERACCOUNT_TAGNAME = "User";
    const QString USERACCOUNT_ACCOUNT_NAME_TAGNAME = "AccountName";
    const QString USERACCOUNT_YOUR_NAME_TAGNAME = "YourName";
    const QString USERACCOUNT_EMAIL_ADDRESS_TAGNAME = "EmailAddress";
    const QString USERACCOUNT_PASSWORD_TAGNAME = "Password";
    const QString USERACCOUNT_SMTP_SERVER_URL_TAGNAME = "SMTPServerURL";
    const QString USERACCOUNT_POP3_SERVER_URL_TAGNAME = "POP3ServerURL";
    const QString USERACCOUNT_SMTP_SERVER_PORT_TAGNAME = "SMTPServerPort";
    const QString USERACCOUNT_POP3_SERVER_PORT_TAGNAME = "POP3ServerPort";

    // password encryption keys
    const QString PASSWORD_AES_CBC_ENCRYPTION_KEY = "1234567890123456789012345678901234567890123456789012345678901234";
    const QString PASSWORD_AES_CBC_ENCRYPTION_IV = "1111111111222222222233333333334444444444555555555566666666667777";
}

#endif // CONSTANTS_H
