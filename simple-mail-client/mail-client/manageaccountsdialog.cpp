#include "manageaccountsdialog.h"
#include "ui_manageaccountsdialog.h"


ManageAccountsDialog::ManageAccountsDialog(UserAccountsListModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAccountsDialog)
{
    ui->setupUi(this);
    this->model = model;
    ui->accountsListView->setModel(this->model);
    editDialog = new EditUserAccountDialog();

    connect(this, SIGNAL(addUserAccount(UserAccount*)), model, SLOT(addNewUserAccount(UserAccount*)));
    connect(this, SIGNAL(editUserAccount(QModelIndex, UserAccount*)), model, SLOT(editSelectedUserAccount(QModelIndex, UserAccount*)));
    connect(this, SIGNAL(removeUserAccount(QModelIndex)), model, SLOT(removeSelectedUserAccount(QModelIndex)));
    connect(this, SIGNAL(initializeEditDialog(UserAccount*,EditUserAccountDialog::Mode)), editDialog, SLOT(initializeDialog(UserAccount*,EditUserAccountDialog::Mode)));
    connect(editDialog, SIGNAL(returnNewUser(UserAccount*,EditUserAccountDialog::Mode)), this, SLOT(receiveNewUserAccount(UserAccount*,EditUserAccountDialog::Mode)));
}

ManageAccountsDialog::~ManageAccountsDialog()
{
    delete ui;
}

void ManageAccountsDialog::on_btnClose_clicked()
{
    this->close();
}

void ManageAccountsDialog::on_btnEdit_clicked()
{
    QModelIndex index = ui->accountsListView->currentIndex();

    if (!index.isValid() || index.row() < 0)
    {
        return;
    }

    int rowIndex = index.row();
    UserAccount account = model->getUserAccountList().at(rowIndex);

    emit initializeEditDialog(&account, EditUserAccountDialog::Mode::EDIT);
    editDialog->show();
}

void ManageAccountsDialog::on_btnAdd_clicked()
{
    emit initializeEditDialog(new UserAccount, EditUserAccountDialog::Mode::ADD);
    editDialog->show();
}

void ManageAccountsDialog::on_btnDelete_clicked()
{
    QModelIndex index = ui->accountsListView->currentIndex();

    if (!index.isValid() || index.row() < 0)
    {
        return;
    }

    emit removeUserAccount(index);
}

void ManageAccountsDialog::receiveNewUserAccount(UserAccount *account, EditUserAccountDialog::Mode mode)
{
    if (mode == EditUserAccountDialog::Mode::ADD)
    {
        emit addUserAccount(account);
    }
    else
    {
        QModelIndex index = ui->accountsListView->currentIndex();
        emit editUserAccount(index, account);
    }
}
