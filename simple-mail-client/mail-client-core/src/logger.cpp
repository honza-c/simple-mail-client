#include "logger.h"
void Logger::customLogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile logFile("error.log");
    QTextStream errorLogStream(&logFile);
    QString logLine;
    QString currentDate = QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:s");
    QByteArray localMsg = msg.toLocal8Bit();

    switch (type)
    {
    case QtDebugMsg:
        logLine = QString("%1 Debug: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        break;
    case QtInfoMsg:
        logLine = QString("%1 Info: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        break;
    case QtWarningMsg:
        logLine = QString("%1 Warning: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        break;
    case QtCriticalMsg:
        logLine = QString("%1 Critical: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
        errorLogStream << logLine;
        logFile.close();
        break;
    case QtFatalMsg:
        logLine = QString("%1 Fatal: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
        errorLogStream << logLine;
        logFile.close();
        abort();
    }
}
