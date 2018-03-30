#ifndef MANAGEACCOUNTSDIALOG_H
#define MANAGEACCOUNTSDIALOG_H

#include <QDialog>
#include <userAccounts/useraccount.h>
#include <userAccounts/useraccountslistmodel.h>
#include "edituseraccountdialog.h"
#include "userAccounts/iuseraccountsreaderwriter.h"
#include "userAccounts/xmluseraccountsreaderwriter.h"
#include "tools/constants.h"

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
    void on_btnEdit_clicked();
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();

signals:
    void addUserAccount(UserAccount *account);
    void editUserAccount(QModelIndex index, UserAccount *account);
    void removeUserAccount(QModelIndex index);
    void initializeEditDialog(UserAccount *account, EditUserAccountDialog::Mode mode);

public slots:
    void receiveNewUserAccount(UserAccount *account, EditUserAccountDialog::Mode mode);

private:
    Ui::ManageAccountsDialog *ui;
    UserAccountsListModel *model;
    EditUserAccountDialog *editDialog;
};

#endif // MANAGEACCOUNTSDIALOG_H
