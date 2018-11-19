#include "newfolderdialog.h"
#include "ui_newfolderdialog.h"

NewFolderDialog::NewFolderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFolderDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Create Folder");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    setFixedHeight(sizeHint().height());

    QObject::connect(ui->editName,
                     SIGNAL(textEdited(const QString &)),
                     this,
                     SLOT(editNameTextEdited(const QString &)));
}

NewFolderDialog::~NewFolderDialog()
{
    delete ui;
}

QString NewFolderDialog::getFolderName() const
{
    return ui->editName->text();
}

void NewFolderDialog::editNameTextEdited(const QString &text)
{
    if (text == QString())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}
