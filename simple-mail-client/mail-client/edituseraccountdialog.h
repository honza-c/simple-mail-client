#ifndef EDITUSERACCOUNTDIALOG_H
#define EDITUSERACCOUNTDIALOG_H

#include <QDialog>
#include "userAccounts/useraccount.h"
#include <QDebug>

namespace Ui {
class EditUserAccountDialog;
}

class EditUserAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserAccountDialog(QWidget *parent = 0);
    ~EditUserAccountDialog();

    enum Mode
    {
        ADD, EDIT
    };

signals:
    void returnNewUser(UserAccount *account, EditUserAccountDialog::Mode mode);

private slots:
    void on_btnCancel_clicked();
    void on_btnSave_clicked();

public slots:
    void initializeDialog(UserAccount *account, EditUserAccountDialog::Mode mode);

private:
    Ui::EditUserAccountDialog *ui;
    Mode mode;
};

#endif // EDITUSERACCOUNTDIALOG_H
