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

void MainWindow::initializeWidgetsAndLayouts()
{
    this->mainHorizontalSplitter = new QSplitter();
    this->inboxFolderTreeView = new QTreeView();
    this->messagesMetadataTableView = new QTableView();

    this->attachmentsLayout = new QHBoxLayout();
    this->btnAttachment1 = new QPushButton("foo.txt");
    this->btnAttachment2 = new QPushButton("bar.doc");
    this->btnAttachment3 = new QPushButton("baz.jpg");
    this->lblAttachments = new QLabel("Attachments:");

    this->msgActionsLayout = new QHBoxLayout();
    this->btnReply = new QPushButton("Reply");
    this->btnReplyToAll = new QPushButton("Reply to all");
    this->btnForward = new QPushButton("Forward");

    this->msgButtonsLayout = new QHBoxLayout();
    this->msgContentView = new QWebEngineView();

    QString htmlString = this->inboxesList->at(0)->getHtmlMessageContent("foo", 666);
    // this->msgContentView->load(QUrl("https://www.google.com"));
    this->msgContentView->setHtml(htmlString);
    this->messageDataSplitter = new QSplitter();

    this->msgButtonsAndContentLayout = new QVBoxLayout();

    this->attachmentsWidget = new QWidget();
    this->msgActionsWidget = new QWidget();
    this->msgAttachmentsAndActionsWidget = new QWidget();
    this->msgButtonsAndContentWidget = new QWidget();
}

void MainWindow::installLayouts()
{
    this->attachmentsLayout->addWidget(this->lblAttachments);
    this->attachmentsLayout->addWidget(this->btnAttachment1);
    this->attachmentsLayout->addWidget(this->btnAttachment2);
    this->attachmentsLayout->addWidget(this->btnAttachment3);

    this->attachmentsWidget->setLayout(this->attachmentsLayout);

    this->msgActionsLayout->addWidget(this->btnReply);
    this->msgActionsLayout->addWidget(this->btnReplyToAll);
    this->msgActionsLayout->addWidget(this->btnForward);

    this->msgActionsWidget->setLayout(this->msgActionsLayout);

    this->msgButtonsLayout->addWidget(this->attachmentsWidget);
    this->msgButtonsLayout->addWidget(this->msgActionsWidget);

    this->msgAttachmentsAndActionsWidget->setLayout(this->msgButtonsLayout);

    this->msgButtonsAndContentLayout->addWidget(this->msgAttachmentsAndActionsWidget);
    this->msgButtonsAndContentLayout->addWidget(this->msgContentView);

    this->msgButtonsAndContentWidget->setLayout(this->msgButtonsAndContentLayout);

    this->messageDataSplitter->addWidget(this->messagesMetadataTableView);
    this->messageDataSplitter->addWidget(this->msgButtonsAndContentWidget);

    this->mainHorizontalSplitter->addWidget(inboxFolderTreeView);
    this->mainHorizontalSplitter->addWidget(this->messageDataSplitter);

    ui->horizontalLayout->addWidget(this->mainHorizontalSplitter);
}

void MainWindow::initializeAndInstallWidgets()
{
    this->setWindowTitle("Simple Mail Client");
    this->setWindowIcon(QIcon::fromTheme("mail-send"));
    QCoreApplication::setApplicationName("Simple Mail Client");

    initializeWidgetsAndLayouts();
    installLayouts();

    this->inboxFolderTreeView->setHeaderHidden(true);
    this->inboxFolderTreeView->setModel(this->inboxFolderTreeModel);
    this->messagesMetadataTableView->setModel(this->messageMetadataTableModel);

    QModelIndexList inboxFolderIndexes = inboxFolderTreeModel->match(inboxFolderTreeModel->index(0, 0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard | Qt::MatchRecursive);

    for (QModelIndex index : inboxFolderIndexes)
    {
        inboxFolderTreeView->expand(index);
    }

    this->messagesMetadataTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->messagesMetadataTableView->setShowGrid(false);

    this->messageDataSplitter->setOrientation(Qt::Vertical);
    this->attachmentsLayout->setAlignment(Qt::AlignLeft);
    this->msgActionsLayout->setAlignment(Qt::AlignRight);
    this->msgButtonsLayout->setContentsMargins(0, 0, 0, 0);

    this->btnAttachment1->setIcon(QIcon::fromTheme("mail-attachment"));
    this->btnAttachment2->setIcon(QIcon::fromTheme("mail-attachment"));
    this->btnAttachment3->setIcon(QIcon::fromTheme("mail-attachment"));

    this->btnReply->setIcon(QIcon::fromTheme("mail-reply-sender"));
    this->btnReplyToAll->setIcon(QIcon::fromTheme("mail-reply-all"));
    this->btnForward->setIcon(QIcon::fromTheme("mail-forward"));
}

void MainWindow::on_actionAccount_Settings_triggered()
{
    manageAccountsDialog->show();
}

void MainWindow::on_actionNew_Message_triggered()
{
    writeMessageWindow->show();
}
