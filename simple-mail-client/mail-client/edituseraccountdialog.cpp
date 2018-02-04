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
