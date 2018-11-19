#ifndef CONSTANTS_H
#define CONSTANTS_H

#endif // CONSTANTS_H

#include <QString>

namespace Constants
{
    // filename constants for files used in application
    const QString ERROR_LOG_FILE_NAME = "error.log";
    const QString USER_ACCOUNT_SETTINGS_FILE = "users.xml";
    const QString DATABASE_FILE_NAME = "db.sqlite";

    // password encryption keys
    const QString PASSWORD_AES_CBC_ENCRYPTION_KEY = "1234567890123456789012345678901234567890123456789012345678901234";
    const QString PASSWORD_AES_CBC_ENCRYPTION_IV = "1111111111222222222233333333334444444444555555555566666666667777";

    const int ATTACHMENT_MAXIMUM_SIZE_IN_MB = 20;
    const QString DATETIME_FORMAT = "dd.MM.yyyy HH:mm";
}
