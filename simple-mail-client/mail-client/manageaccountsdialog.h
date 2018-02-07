#ifndef MANAGEACCOUNTSDIALOG_H
#define MANAGEACCOUNTSDIALOG_H

#include <QDialog>
#include <userAccounts/useraccount.h>
#include <userAccounts/useraccountslistmodel.h>

namespace Ui {
class ManageAccountsDialog;
}

class ManageAccountsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageAccountsDialog(UserAccountsListModel *model, QWidget *parent = 0);
    ~ManageAccountsDialog();

private slots:
    void on_btnClose_clicked();

private:
    Ui::ManageAccountsDialog *ui;
    UserAccountsListModel *model;
};

#endif // MANAGEACCOUNTSDIALOG_H
