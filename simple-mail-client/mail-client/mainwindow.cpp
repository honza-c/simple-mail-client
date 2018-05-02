#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeDataStructures();
    initializeUserAccounts();
    initializeDataModels();
    initializeApplicationWindows();
    initializeAndInstallWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeDataStructures()
{
    this->userAccountsList = new QList<UserAccount>();
    this->inboxesMessageMetadataList = new QList<QList<MessageMetadata>>();
    this->inboxesList = new QList<VmimeImapStore>();
}

void MainWindow::initializeUserAccounts()
{
    QFile file(Constants::USER_ACCOUNT_SETTINGS_FILE);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "Error while opening user accounts settings file: " << file.errorString();
        file.close();
        return;
    }

    QList<UserAccount> *users = new QList<UserAccount>();

    IUserAccountsReaderWriter *xmlReaderWriter = new XmlUserAccountsReaderWriter(users);

    if (!xmlReaderWriter->loadUserAccounts(&file))
    {
        file.close();
        return;
    }

    this->userAccountsList = users;
    file.close();

    initializeInboxMetadata();
}

void MainWindow::initializeInboxMetadata()
{
    for (UserAccount user : *userAccountsList)
    {
        VmimeImapStore imapStore(user.getPopServerUrl(),
                                 user.getEmailAddress(),
                                 user.getPassword(),
                                 user.getPopServerPort());

        inboxesList->push_back(imapStore);
    }

    for (VmimeImapStore imapStore : *inboxesList)
    {
        QList<MessageMetadata> messagesMetadata = imapStore.getMessagesMetadata();
        this->inboxesMessageMetadataList->push_back(messagesMetadata);
    }
}

void MainWindow::initializeDataModels()
{
    userAccountsListModel = new UserAccountsListModel(userAccountsList);
    this->messageMetadataTableModel = new MessageMetadataTableModel(this->inboxesMessageMetadataList->at(0));
}

void MainWindow::initializeApplicationWindows()
{
    manageAccountsDialog = new ManageAccountsDialog(userAccountsListModel);
    writeMessageWindow = new WriteMessageWindow(userAccountsListModel);
}

void MainWindow::initializeAndInstallWidgets()
{
    this->setWindowTitle("Simple Mail Clinet (based on mail-client-core 0.1)");

    this->mainHorizontalSplitter = new QSplitter();
    this->userAccountsListView = new QListView();
    this->messagesMetadataTableView = new QTableView();

    this->userAccountsListView->setModel(this->userAccountsListModel);
    this->messagesMetadataTableView->setModel(this->messageMetadataTableModel);

    this->mainHorizontalSplitter->addWidget(this->userAccountsListView);
    this->mainHorizontalSplitter->addWidget(this->messagesMetadataTableView);

    ui->horizontalLayout->addWidget(this->mainHorizontalSplitter);
}

void MainWindow::on_actionAccount_Settings_triggered()
{
    manageAccountsDialog->show();
}

void MainWindow::on_actionNew_Message_triggered()
{
    writeMessageWindow->show();
}
