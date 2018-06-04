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
    this->inboxesList = new QList<VmimeInboxService*>();
    this->inboxesFolderList = new QList<QList<InboxFolder>>();
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
    initializeInboxFolders();
}

void MainWindow::initializeInboxMetadata()
{
    for (UserAccount user : *userAccountsList)
    {
        VmimeImapService *imapService = new VmimeImapService
                                (user.getPopServerUrl(),
                                 user.getEmailAddress(),
                                 user.getPassword(),
                                 user.getPopServerPort());

        inboxesList->push_back(imapService);
    }

    for (VmimeInboxService *inboxService : *inboxesList)
    {
        QList<MessageMetadata> messagesMetadata = inboxService->getMessageMetadata();
        this->inboxesMessageMetadataList->push_back(messagesMetadata);
    }
}

void MainWindow::initializeInboxFolders()
{
    for (VmimeInboxService *inboxService : *inboxesList)
    {
        QList<InboxFolder> inboxFolders = inboxService->getInboxFolders();
        this->inboxesFolderList->push_back(inboxFolders);
    }
}

void MainWindow::initializeDataModels()
{
    this->userAccountsListModel = new UserAccountsListModel(userAccountsList);
    this->inboxFolderTreeModel = new InboxFolderTreeModel(*(this->inboxesFolderList));
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
    this->inboxFolderTreeView = new QTreeView();
    this->messagesMetadataTableView = new QTableView();

    this->inboxFolderTreeView->setModel(this->inboxFolderTreeModel);
    this->messagesMetadataTableView->setModel(this->messageMetadataTableModel);

    this->mainHorizontalSplitter->addWidget(inboxFolderTreeView);
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
