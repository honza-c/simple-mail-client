#include "addedituseraccountdialog.h"
#include "ui_addedituseraccountdialog.h"

AddEditUserAccountDialog::AddEditUserAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditUserAccountDialog)
{
    ui->setupUi(this);
    initializeWidgets();
    setUpWidgets();
    installLayout();

    setFixedHeight(sizeHint().height());

    QObject::connect(m_comboBoxConfiguration,
                     SIGNAL(activated(const QString &)),
                     this,
                     SLOT(configurationComboBoxActivated(const QString &)));

    QObject::connect(m_btnSave,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnSaveClicked(bool)));

    QObject::connect(m_btnCancel,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnCancelClicked(bool)));
}

AddEditUserAccountDialog::~AddEditUserAccountDialog()
{
    delete ui;
}

void AddEditUserAccountDialog::initializeWidgets()
{
    m_lblConfiguration = new QLabel("Use predefined configuration for:");
    m_lblAccountName = new QLabel("Account name:");
    m_lblContactName = new QLabel("Your name:");
    m_lblEmailAddress = new QLabel("Email address:");
    m_lbluserName = new QLabel("User name:");
    m_lblPassword = new QLabel("Password");
    m_lblIncomingServerType = new QLabel("Incoming server type:");
    m_lblIncomingServerUrl = new QLabel("Incoming server URL:");
    m_lblIncomingServerPort = new QLabel("Incoming server port:");
    m_lblSmtpServerUrl = new QLabel("SMTP server URL:");
    m_lblSmtpServerPort = new QLabel("SMTP server port:");

    m_comboBoxConfiguration = new QComboBox();
    m_editAccountName = new QLineEdit();
    m_editContactName = new QLineEdit();
    m_editEmailAddress = new QLineEdit();
    m_editUserName = new QLineEdit();
    m_editPassword = new QLineEdit();
    m_comboBoxIncomingServerType = new QComboBox();
    m_editIncomingServerUrl = new QLineEdit();
    m_spinBoxIncomingServerPort = new QSpinBox();
    m_editSmtpServerUrl = new QLineEdit();
    m_spinBoxSmtpServerPort = new QSpinBox();

    m_buttonsWidget = new QWidget();
    m_buttonsLayout = new QHBoxLayout();
    m_btnSave = new QPushButton("Save");
    m_btnCancel = new QPushButton("Cancel");
}

void AddEditUserAccountDialog::setUpWidgets()
{
    m_editUserName->setPlaceholderText("Mostly same as the email address");
    m_comboBoxConfiguration->addItem("None");
    m_comboBoxConfiguration->addItem("Gmail");
    m_comboBoxConfiguration->addItem("Office 365");

    m_comboBoxIncomingServerType->addItem("IMAP");
    m_comboBoxIncomingServerType->addItem("POP3");

    m_spinBoxIncomingServerPort->setMinimum(0);
    m_spinBoxIncomingServerPort->setMaximum(65535);

    m_spinBoxSmtpServerPort->setMinimum(0);
    m_spinBoxSmtpServerPort->setMaximum(65535);

    m_editPassword->setEchoMode(QLineEdit::Password);
}

void AddEditUserAccountDialog::installLayout()
{
    m_buttonsLayout->addWidget(m_btnSave);
    m_buttonsLayout->addWidget(m_btnCancel);
    m_buttonsWidget->setLayout(m_buttonsLayout);
    m_buttonsLayout->setAlignment(Qt::AlignRight);

    ui->gridLayout->addWidget(m_lblConfiguration, 0, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblAccountName, 1, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblContactName, 2, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblEmailAddress, 3, 0, 1, 1);
    ui->gridLayout->addWidget(m_lbluserName, 4, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblPassword, 5, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblIncomingServerType, 6, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblIncomingServerUrl, 7, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblIncomingServerPort, 8, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblSmtpServerUrl, 9, 0, 1, 1);
    ui->gridLayout->addWidget(m_lblSmtpServerPort, 10, 0, 1, 1);

    ui->gridLayout->addWidget(m_comboBoxConfiguration, 0, 1, 1, 1);
    ui->gridLayout->addWidget(m_editAccountName, 1, 1, 1, 1);
    ui->gridLayout->addWidget(m_editContactName, 2, 1, 1, 1);
    ui->gridLayout->addWidget(m_editEmailAddress, 3, 1, 1, 1);
    ui->gridLayout->addWidget(m_editUserName, 4, 1, 1, 1);
    ui->gridLayout->addWidget(m_editPassword, 5, 1, 1, 1);
    ui->gridLayout->addWidget(m_comboBoxIncomingServerType, 6, 1, 1, 1);
    ui->gridLayout->addWidget(m_editIncomingServerUrl, 7, 1, 1, 1);
    ui->gridLayout->addWidget(m_spinBoxIncomingServerPort, 8, 1, 1, 1);
    ui->gridLayout->addWidget(m_editSmtpServerUrl, 9, 1, 1, 1);
    ui->gridLayout->addWidget(m_spinBoxSmtpServerPort, 10, 1, 1, 1);

    ui->gridLayout->addWidget(m_buttonsWidget, 11, 1, 1, 1);
}

void AddEditUserAccountDialog::configurationComboBoxActivated(const QString &text)
{
    if (text == "Gmail")
    {
        m_editSmtpServerUrl->setText("smtp://smtp.gmail.com");
        m_editIncomingServerUrl->setText("imap.gmail.com");
        m_spinBoxIncomingServerPort->setValue(993);
        m_spinBoxSmtpServerPort->setValue(465);
        m_comboBoxIncomingServerType->setCurrentIndex(0);
    }
    else if (text == "Office 365")
    {
        m_editSmtpServerUrl->setText("smtp://smtp.office365.com");
        m_editIncomingServerUrl->setText("outlook.office365.com");
        m_spinBoxIncomingServerPort->setValue(993);
        m_spinBoxSmtpServerPort->setValue(465);
        m_comboBoxIncomingServerType->setCurrentIndex(0);
    }
}

void AddEditUserAccountDialog::onBtnSaveClicked(bool checked)
{
    UserAccount userAccount;

    userAccount.setContactName(m_editContactName->text());
    userAccount.setAccountName(m_editAccountName->text());
    userAccount.setEmailAddress(m_editEmailAddress->text());
    userAccount.setUserName(m_editUserName->text());
    userAccount.setPassword(m_editPassword->text());
    userAccount.setIncomingServerAddress(m_editIncomingServerUrl->text());
    userAccount.setIncomingServerPort(m_spinBoxIncomingServerPort->value());
    userAccount.setSmtpServerUrl(m_editSmtpServerUrl->text());
    userAccount.setSmtpServerPort(m_spinBoxSmtpServerPort->value());

    switch (m_comboBoxIncomingServerType->currentIndex())
    {
    case 0:
        userAccount.setIncomingServerType(UserAccount::IMAP);
        break;
    case 1:
        userAccount.setIncomingServerType(UserAccount::POP3);
        break;
    default:
        break;
    }

    emit newUserAccountCreated(userAccount);

    close();
}

void AddEditUserAccountDialog::onBtnCancelClicked(bool checked)
{
    close();
}
void AddEditUserAccountDialog::setUserAccount(const UserAccount &userAccount)
{
    m_comboBoxConfiguration->setCurrentIndex(0);
    m_editAccountName->setText(userAccount.accountName());
    m_editContactName->setText(userAccount.contactName());
    m_editEmailAddress->setText(userAccount.emailAddress());
    m_editUserName->setText(userAccount.userName());
    m_editPassword->setText(userAccount.password());
    m_editIncomingServerUrl->setText(userAccount.incomingServerAddress());
    m_spinBoxIncomingServerPort->setValue(userAccount.incomingServerPort());
    m_editSmtpServerUrl->setText(userAccount.smtpServerUrl());
    m_spinBoxSmtpServerPort->setValue(userAccount.smtpServerPort());

    if (userAccount.incomingServerType() == UserAccount::IMAP)
    {
        m_comboBoxIncomingServerType->setCurrentIndex(0);
    }
    else
    {
        m_comboBoxIncomingServerType->setCurrentIndex(1);
    }
}
