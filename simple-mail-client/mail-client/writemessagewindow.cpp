#include "writemessagewindow.h"
#include "ui_writemessagewindow.h"

WriteMessageWindow::WriteMessageWindow(UserAccountsListModel *model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WriteMessageWindow)
{
    ui->setupUi(this);
    this->model = model;
    ui->comboBoxFrom->setModel(this->model);
}

WriteMessageWindow::~WriteMessageWindow()
{
    delete ui;
}
