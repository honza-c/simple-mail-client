#ifndef EDITUSERACCOUNTDIALOG_H
#define EDITUSERACCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
class EditUserAccountDialog;
}

class EditUserAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserAccountDialog(QWidget *parent = 0);
    ~EditUserAccountDialog();

private slots:
    void on_btnCancel_clicked();

private:
    Ui::EditUserAccountDialog *ui;
};

#endif // EDITUSERACCOUNTDIALOG_H
