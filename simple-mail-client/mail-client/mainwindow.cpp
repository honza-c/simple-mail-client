#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadUserSettings();
    initializeStructures();
    initializeUi();

    this->setWindowTitle("Simple Mail Clinet (based on mail-client-core 0.1)");
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

    this->mainHorizontalSplitter = new QSplitter();
    this->userAccountsListView = new QListView();
    this->messagesMetadataTableView = new QTableView();
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

void MainWindow::initializeUi()
{
    this->userAccountsListView->setModel(this->usersModel);
    this->mainHorizontalSplitter->addWidget(this->userAccountsListView);
    this->mainHorizontalSplitter->addWidget(this->messagesMetadataTableView);

    ui->horizontalLayout->addWidget(this->mainHorizontalSplitter);
}
