#include "manageaccountsdialog.h"
#include "ui_manageaccountsdialog.h"

ManageAccountsDialog::ManageAccountsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAccountsDialog)
{
    ui->setupUi(this);
}

ManageAccountsDialog::~ManageAccountsDialog()
{
    delete ui;
}

void ManageAccountsDialog::on_btnClose_clicked()
{
    this->close();
}
