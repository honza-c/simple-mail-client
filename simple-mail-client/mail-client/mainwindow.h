#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <userAccounts/useraccount.h>
#include <QDebug>
#include <QtWidgets>
#include "manageaccountsdialog.h"
#include "writemessagewindow.h"
#include "useraccountslistmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAccount_Settings_triggered();

    void on_actionNew_Message_triggered();

private:
    void initializeStructures();
    void createTestUserAccounts();

    Ui::MainWindow *ui;
    QList<UserAccount> users;
    UserAccountsListModel *usersModel;

    ManageAccountsDialog *manageAccountsDialog;
    WriteMessageWindow *writeMessageWindow;
};

#endif // MAINWINDOW_H
