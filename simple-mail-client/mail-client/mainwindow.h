#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <userAccounts/useraccount.h>
#include <QDebug>
#include <QtWidgets>
#include "manageaccountsdialog.h"
#include "edituseraccountdialog.h"
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

private:
    void initializeStructures();
    void createTestUserAccounts();

    Ui::MainWindow *ui;
    QList<UserAccount> users;
    UserAccountsListModel *usersModel;
};

#endif // MAINWINDOW_H
