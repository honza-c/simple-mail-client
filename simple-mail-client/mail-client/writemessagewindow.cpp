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

void WriteMessageWindow::on_btnSend_clicked()
{
    MailMessage message;

    QStringList addressListTo;
    QStringList addressListBlindCopy;

    addressListTo << this->ui->editTo->text();
    addressListBlindCopy << this->ui->editBcc->text();

    message.setSubject(this->ui->editSubject->text());
    message.setMessageContent(this->ui->editMessageContent->toPlainText());
    message.setAddressListTo(addressListTo);
    message.setAddressListBlindCopy(addressListBlindCopy);

    int index = this->ui->comboBoxFrom->currentIndex();
    UserAccount userAccount = this->model->getUserAccountList()->at(index);

    userAccount.sendMessage(message);

    this->close();
}
