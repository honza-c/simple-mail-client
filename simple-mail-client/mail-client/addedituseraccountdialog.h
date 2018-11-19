#ifndef ADDEDITUSERACCOUNTDIALOG_H
#define ADDEDITUSERACCOUNTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "src/useraccount.h"

namespace Ui {
class AddEditUserAccountDialog;
}

class AddEditUserAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditUserAccountDialog(QWidget *parent = nullptr);
    ~AddEditUserAccountDialog();

    void setUserAccount(const UserAccount &userAccount);

signals:
    void newUserAccountCreated(const UserAccount &);

private slots:
    void configurationComboBoxActivated(const QString &);
    void onBtnSaveClicked(bool);
    void onBtnCancelClicked(bool);

private:
    void initializeWidgets();
    void setUpWidgets();
    void installLayout();

    Ui::AddEditUserAccountDialog *ui;

    QLabel *m_lblConfiguration;
    QLabel *m_lblAccountName;
    QLabel *m_lblContactName;
    QLabel *m_lblEmailAddress;
    QLabel *m_lbluserName;
    QLabel *m_lblPassword;
    QLabel *m_lblIncomingServerType;
    QLabel *m_lblIncomingServerUrl;
    QLabel *m_lblIncomingServerPort;
    QLabel *m_lblSmtpServerUrl;
    QLabel *m_lblSmtpServerPort;

    QComboBox *m_comboBoxConfiguration;
    QLineEdit *m_editAccountName;
    QLineEdit *m_editContactName;
    QLineEdit *m_editEmailAddress;
    QLineEdit *m_editUserName;
    QLineEdit *m_editPassword;
    QComboBox *m_comboBoxIncomingServerType;
    QLineEdit *m_editIncomingServerUrl;
    QSpinBox *m_spinBoxIncomingServerPort;
    QLineEdit *m_editSmtpServerUrl;
    QSpinBox *m_spinBoxSmtpServerPort;

    QWidget *m_buttonsWidget;
    QHBoxLayout *m_buttonsLayout;
    QPushButton *m_btnSave;
    QPushButton *m_btnCancel;
};

#endif // ADDEDITUSERACCOUNTDIALOG_H
