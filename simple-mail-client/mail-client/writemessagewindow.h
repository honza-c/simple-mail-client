#ifndef WRITEMESSAGEWINDOW_H
#define WRITEMESSAGEWINDOW_H

#include <QMainWindow>
#include <userAccounts/useraccount.h>
#include <userAccounts/useraccountslistmodel.h>
#include "messaging/mailmessage.h"
#include <QDebug>

namespace Ui {
class WriteMessageWindow;
}

class WriteMessageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WriteMessageWindow(UserAccountsListModel *model, QWidget *parent = 0);
    ~WriteMessageWindow();

private slots:
    void on_btnSend_clicked();

private:
    Ui::WriteMessageWindow *ui;
    UserAccountsListModel *model;
};

#endif // WRITEMESSAGEWINDOW_H
