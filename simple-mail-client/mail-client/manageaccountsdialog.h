#ifndef MANAGEACCOUNTSDIALOG_H
#define MANAGEACCOUNTSDIALOG_H

#include <QDialog>

namespace Ui {
class ManageAccountsDialog;
}

class ManageAccountsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageAccountsDialog(QWidget *parent = 0);
    ~ManageAccountsDialog();

private slots:
    void on_btnClose_clicked();

private:
    Ui::ManageAccountsDialog *ui;
};

#endif // MANAGEACCOUNTSDIALOG_H
