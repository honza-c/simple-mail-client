#include "edituseraccountdialog.h"
#include "ui_edituseraccountdialog.h"

EditUserAccountDialog::EditUserAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserAccountDialog)
{
    ui->setupUi(this);
}

EditUserAccountDialog::~EditUserAccountDialog()
{
    delete ui;
}

void EditUserAccountDialog::on_btnCancel_clicked()
{
    this->close();
}

void EditUserAccountDialog::on_btnSave_clicked()
{
    UserAccount *account = new UserAccount();

    account->setAccountName(ui->editAccountName->text());
    account->setYourName(ui->editYourName->text());
    account->setEmailAddress(ui->editEmailAddress->text());
    account->setPassword(ui->editPassword->text());
    account->setSmtpServerUrl(ui->editSmtpServerUrl->text());
    account->setPopServerUrl(ui->editPopServerUrl->text());
    account->setSmtpServerPort(ui->editSmtpServerPort->text().toInt());
    account->setPopServerPort(ui->editPopServerPort->text().toInt());

    emit returnNewUser(account, this->mode);

    this->close();
}

void EditUserAccountDialog::initializeDialog(UserAccount *account, EditUserAccountDialog::Mode mode)
{
    this->mode = mode;

    ui->editAccountName->setText(account->getAccountName());
    ui->editYourName->setText(account->getYourName());
    ui->editEmailAddress->setText(account->getEmailAddress());
    ui->editPassword->setText(account->getEmailAddress());
    ui->editSmtpServerUrl->setText(account->getSmtpServerUrl());
    ui->editPopServerUrl->setText(account->getPopServerUrl());
    ui->editSmtpServerPort->setText(QString::number(account->getSmtpServerPort()));
    ui->editPopServerPort->setText(QString::number(account->getPopServerPort()));

    if (mode == Mode::ADD)
    {
        this->setWindowTitle("Add new account");
    }
    else if (mode == Mode::EDIT)
    {
        this->setWindowTitle("Edit account");
    }
}
