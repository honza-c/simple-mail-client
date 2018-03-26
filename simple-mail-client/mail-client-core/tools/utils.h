#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include "constants.h"

namespace Tools
{
    class Utils : public QObject
    {
        Q_OBJECT
    public:
        explicit Utils(QObject *parent = nullptr);
        static void customLogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    signals:

    public slots:
    };
}

#endif // UTILS_H
