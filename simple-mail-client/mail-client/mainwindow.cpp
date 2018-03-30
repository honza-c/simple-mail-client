#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadUserSettings();
    initializeStructures();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeStructures()
{
    usersModel = new UserAccountsListModel(users);
    manageAccountsDialog = new ManageAccountsDialog(usersModel);
    writeMessageWindow = new WriteMessageWindow(usersModel);
}

void MainWindow::loadUserSettings()
{
    QFile file(Constants::USER_ACCOUNT_SETTINGS_FILE);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "Error while opening user accounts settings file: " << file.errorString();
        this->users = new QList<UserAccount>();
        file.close();
        return;
    }

    QList<UserAccount> *users = new QList<UserAccount>();

    IUserAccountsReaderWriter *xmlReaderWriter = new XmlUserAccountsReaderWriter(users);

    if (!xmlReaderWriter->loadUserAccounts(&file))
    {
        file.close();
        this->users = new QList<UserAccount>();
        return;
    }

    this->users = users;
    file.close();
}

void MainWindow::on_actionAccount_Settings_triggered()
{
    manageAccountsDialog->show();
}

void MainWindow::on_actionNew_Message_triggered()
{
    writeMessageWindow->show();
}
