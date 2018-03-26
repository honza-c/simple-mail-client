#include "mainwindow.h"
#include <QApplication>
#include "tools/utils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(Tools::Utils::customLogMessageHandler);
    MainWindow w;
    w.show();

    return a.exec();
}
