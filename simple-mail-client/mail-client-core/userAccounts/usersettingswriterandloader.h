#ifndef USERSETTINGSWRITERANDLOADER_H
#define USERSETTINGSWRITERANDLOADER_H

#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <qxmlstream.h>

#include "useraccount.h"
#include "tools/constants.h"

class UserSettingsWriterAndLoader
{
public:
    UserSettingsWriterAndLoader() {}
    static QList<UserAccount> loadSettings(const QString &fileName);
    static void writeSettings(const QList<UserAccount*> users, const QString &fileName);

private:
};

#endif // USERSETTINGSWRITERANDLOADER_H
