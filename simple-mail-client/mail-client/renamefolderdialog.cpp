#include "renamefolderdialog.h"
#include "ui_renamefolderdialog.h"

RenameFolderDialog::RenameFolderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameFolderDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Rename");
    setFixedHeight(sizeHint().height());
    setWindowTitle("Rename Folder");

    QObject::connect(ui->editName,
                     SIGNAL(textEdited(const QString &)),
                     this,
                     SLOT(editNameTextEdited(const QString &)));
}

RenameFolderDialog::~RenameFolderDialog()
{
    delete ui;
}

void RenameFolderDialog::editNameTextEdited(const QString &text)
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

QString RenameFolderDialog::getFolderName() const
{
    return ui->editName->text();
}

void RenameFolderDialog::setFolderName(const QString folderName)
{
    ui->editName->setText(folderName);
    ui->editName->setFocus();
    ui->editName->selectAll();
}
