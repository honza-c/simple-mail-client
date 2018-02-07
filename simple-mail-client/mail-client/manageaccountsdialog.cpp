#include "manageaccountsdialog.h"
#include "ui_manageaccountsdialog.h"


ManageAccountsDialog::ManageAccountsDialog(UserAccountsListModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAccountsDialog)
{
    ui->setupUi(this);
    this->model = model;
    ui->accountsListView->setModel(this->model);
}

ManageAccountsDialog::~ManageAccountsDialog()
{
    delete ui;
}

void ManageAccountsDialog::on_btnClose_clicked()
{
    this->close();
}
