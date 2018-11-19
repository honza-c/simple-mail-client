#ifndef MANAGEUSERACCCOUNTSDIALOG_H
#define MANAGEUSERACCCOUNTSDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "addedituseraccountdialog.h"
#include "src/useraccount.h"
#include "src/useraccountslistmodel.h"

namespace Ui {
class ManageUserAcccountsDialog;
}

class ManageUserAcccountsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageUserAcccountsDialog(QWidget *parent = nullptr);
    ~ManageUserAcccountsDialog();

    void setUserAccounts(QList<UserAccount> *userAccountsList);

signals:
    void userAcccountsConfigurationChanged();

private slots:
    void onBtnCloseClicked(bool);
    void onBtnAddAccountClicked(bool);
    void onBtnEditAccountClicked(bool);
    void onBtnRemoveAccountClicked(bool);
    void onAccountListViewSelectedIndexesChanged(const QModelIndex &, const QModelIndex &);
    void newUserAccountReceived(const UserAccount &);

private:
    Ui::ManageUserAcccountsDialog *ui;

    void initializeWidgets();
    void installLayouts();

    void addNewAccount(const UserAccount &userAccount);
    void editExistingAccount(const UserAccount &editedUserAccount, const int positionInList);

    QListView *m_accountsListView;

    QPushButton *m_btnAddAccount;
    QPushButton *m_btnEditAccount;
    QPushButton *m_btnRemoveAccount;

    QPushButton *m_btnClose;

    QHBoxLayout *m_dialogContentLayout;
    QVBoxLayout *m_actionButtonsLayout;
    QHBoxLayout *m_dialogButtonsLayout;

    QWidget *m_dialogContentWidget;
    QWidget *m_actionButtonsWidget;
    QWidget *m_dialogButtonsWidget;

    QList<UserAccount> *m_userAccountsList;
    UserAccountsListModel *m_userAccountListModel;

    AddEditUserAccountDialog *m_addEditUserAccountDialog;
};

#endif // MANAGEUSERACCCOUNTSDIALOG_H
