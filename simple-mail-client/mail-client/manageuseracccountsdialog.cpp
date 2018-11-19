#include "manageuseracccountsdialog.h"
#include "ui_manageuseracccountsdialog.h"
#include "src/useraccount.h"

ManageUserAcccountsDialog::ManageUserAcccountsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageUserAcccountsDialog)
{
    ui->setupUi(this);

    initializeWidgets();
    installLayouts();

    setWindowTitle("Manage accounts");

    setFixedWidth(sizeHint().width());
    m_dialogButtonsLayout->setAlignment(Qt::AlignRight);
    m_actionButtonsLayout->setAlignment(Qt::AlignTop);

    QObject::connect(m_btnClose,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnCloseClicked(bool)));

    QObject::connect(m_btnAddAccount,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnAddAccountClicked(bool)));

    QObject::connect(m_btnEditAccount,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnEditAccountClicked(bool)));

    QObject::connect(m_btnRemoveAccount,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnRemoveAccountClicked(bool)));

    QObject::connect(m_addEditUserAccountDialog,
                     SIGNAL(newUserAccountCreated(const UserAccount &)),
                     this,
                     SLOT(newUserAccountReceived(const UserAccount &)));

    // closes automatically, when main window is closed
    m_addEditUserAccountDialog->setAttribute(Qt::WA_QuitOnClose, false);
}

ManageUserAcccountsDialog::~ManageUserAcccountsDialog()
{
    delete ui;
}

void ManageUserAcccountsDialog::onBtnCloseClicked(bool checked)
{
    close();
}

void ManageUserAcccountsDialog::onBtnAddAccountClicked(bool checked)
{
    m_addEditUserAccountDialog->setWindowTitle("Add account");
    UserAccount *userAccount = new UserAccount();
    m_addEditUserAccountDialog->setUserAccount(*userAccount);
    m_addEditUserAccountDialog->show();
}

void ManageUserAcccountsDialog::onBtnEditAccountClicked(bool checked)
{
    if (m_accountsListView->selectionModel()->selectedIndexes().size() > 0)
    {
        int index = m_accountsListView->selectionModel()->selectedIndexes().at(0).row();

        if (index >= 0)
        {
            m_addEditUserAccountDialog->setWindowTitle("Edit account");
            m_addEditUserAccountDialog->setUserAccount(m_userAccountsList->at(index));
            m_addEditUserAccountDialog->show();
        }
    }
}

void ManageUserAcccountsDialog::onBtnRemoveAccountClicked(bool)
{
    if (m_accountsListView->selectionModel()->selectedIndexes().size() > 0)
    {
        int index = m_accountsListView->selectionModel()->selectedIndexes().at(0).row();

        if (index >= 0)
        {
            m_userAccountsList->removeAt(index);

            m_userAccountListModel = new UserAccountsListModel(*m_userAccountsList);
            m_accountsListView->setModel(m_userAccountListModel);

            emit userAcccountsConfigurationChanged();
        }
    }
}

void ManageUserAcccountsDialog::onAccountListViewSelectedIndexesChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (m_accountsListView->selectionModel()->selectedIndexes().size() == 0)
    {
        m_btnEditAccount->setEnabled(false);
        m_btnRemoveAccount->setEnabled(false);
    }
    else
    {
        m_btnEditAccount->setEnabled(true);
        m_btnRemoveAccount->setEnabled(true);
    }
}

void ManageUserAcccountsDialog::initializeWidgets()
{
    m_accountsListView = new QListView();

    m_btnAddAccount = new QPushButton("Add account");
    m_btnEditAccount = new QPushButton("Edit account");
    m_btnRemoveAccount = new QPushButton("Remove account");

    m_btnClose = new QPushButton("Close");

    m_dialogContentLayout = new QHBoxLayout();
    m_actionButtonsLayout = new QVBoxLayout();
    m_dialogButtonsLayout = new QHBoxLayout();

    m_dialogButtonsWidget = new QWidget();
    m_actionButtonsWidget = new QWidget();
    m_dialogContentWidget = new QWidget();

    m_addEditUserAccountDialog = new AddEditUserAccountDialog();
}

void ManageUserAcccountsDialog::installLayouts()
{
    m_actionButtonsLayout->addWidget(m_btnAddAccount);
    m_actionButtonsLayout->addWidget(m_btnEditAccount);
    m_actionButtonsLayout->addWidget(m_btnRemoveAccount);

    m_actionButtonsWidget->setLayout(m_actionButtonsLayout);

    m_dialogContentLayout->addWidget(m_accountsListView);
    m_dialogContentLayout->addWidget(m_actionButtonsWidget);

    m_dialogContentWidget->setLayout(m_dialogContentLayout);

    m_dialogButtonsLayout->addWidget(m_btnClose);

    m_dialogButtonsWidget->setLayout(m_dialogButtonsLayout);

    ui->verticalLayout->addWidget(m_dialogContentWidget);
    ui->verticalLayout->addWidget(m_dialogButtonsWidget);
}

void ManageUserAcccountsDialog::setUserAccounts(QList<UserAccount> *userAccountsList)
{
    m_userAccountsList = userAccountsList;
    m_userAccountListModel = new UserAccountsListModel(*m_userAccountsList);
    m_accountsListView->setModel(m_userAccountListModel);

    /*
    QObject::connect(m_accountsListView->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
                     this,
                     SLOT(onAccountListViewSelectedIndexesChanged(const QModelIndex &, const QModelIndex &)));
    */
}

void ManageUserAcccountsDialog::newUserAccountReceived(const UserAccount &userAccount)
{
    if (m_addEditUserAccountDialog->windowTitle() == "Add account")
    {
        addNewAccount(userAccount);
    }
    else if (m_addEditUserAccountDialog->windowTitle() == "Edit account")
    {
        if (m_accountsListView->selectionModel()->selectedIndexes().size() > 0)
        {
            int index = m_accountsListView->selectionModel()->selectedIndexes().at(0).row();

            if (index >= 0)
            {
                editExistingAccount(userAccount, index);
            }
        }
    }
}

void ManageUserAcccountsDialog::addNewAccount(const UserAccount &userAccount)
{
    bool accountNameNotUsed = true;
    bool emailAddressNotUsed = true;

    for (int i = 0; i < m_userAccountsList->size(); i++)
    {
        if (userAccount.accountName() == m_userAccountsList->at(i).accountName())
        {
            accountNameNotUsed = false;
            break;
        }

        if (userAccount.emailAddress() == m_userAccountsList->at(i).contactName())
        {
            emailAddressNotUsed = false;
            break;
        }
    }

    if (!accountNameNotUsed)
    {
        QMessageBox messageBox;

        messageBox.setWindowTitle("Error while adding the user account");
        messageBox.setText("User account with this name already exists");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
    }
    else if (!emailAddressNotUsed)
    {
        QMessageBox messageBox;

        messageBox.setWindowTitle("Error while adding the user account");
        messageBox.setText("User account with this email address already exists");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
    }
    else
    {
        m_userAccountsList->push_back(userAccount);

        (*m_userAccountsList)[m_userAccountsList->size() - 1].initializeInbox();

        emit userAcccountsConfigurationChanged();

        m_userAccountListModel = new UserAccountsListModel(*m_userAccountsList);
        m_accountsListView->setModel(m_userAccountListModel);
    }
}

void ManageUserAcccountsDialog::editExistingAccount(const UserAccount &editedUserAccount, const int positionInList)
{
    bool accountNameNotUsed = true;
    bool emailAddressNotUsed = true;

    for (int i = 0; i < m_userAccountsList->size(); i++)
    {
        if (i == positionInList)
        {
            continue;
        }

        if (editedUserAccount.accountName() == m_userAccountsList->at(i).accountName())
        {
            accountNameNotUsed = false;
            break;
        }

        if (editedUserAccount.emailAddress() == m_userAccountsList->at(i).contactName())
        {
            emailAddressNotUsed = false;
            break;
        }
    }

    if (!accountNameNotUsed)
    {
        QMessageBox messageBox;

        messageBox.setWindowTitle("Error while editing the user account");
        messageBox.setText("User account with this name already exists");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
    }
    else if (!emailAddressNotUsed)
    {
        QMessageBox messageBox;

        messageBox.setWindowTitle("Error while editing the user account");
        messageBox.setText("User account with this email address already exists");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
    }
    else
    {
        (*m_userAccountsList)[positionInList] = editedUserAccount;
        (*m_userAccountsList)[positionInList].initializeInbox();

        emit userAcccountsConfigurationChanged();

        m_userAccountListModel = new UserAccountsListModel(*m_userAccountsList);
        m_accountsListView->setModel(m_userAccountListModel);
    }
}
