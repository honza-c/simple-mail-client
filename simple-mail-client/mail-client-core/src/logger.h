#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QDateTime>
#include <QDebug>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr)
        : QObject(parent) {}

    static void customLogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:

public slots:
};

#endif // LOGGER_H
