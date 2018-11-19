#include "mainwindow.h"
#include <QApplication>
#include "src/logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(Logger::customLogMessageHandler);
    MainWindow w;
    w.show();

    return a.exec();
}
