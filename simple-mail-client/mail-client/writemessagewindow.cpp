#include "writemessagewindow.h"
#include "ui_writemessagewindow.h"

WriteMessageWindow::WriteMessageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WriteMessageWindow)
{
    ui->setupUi(this);
}

WriteMessageWindow::~WriteMessageWindow()
{
    delete ui;
}
