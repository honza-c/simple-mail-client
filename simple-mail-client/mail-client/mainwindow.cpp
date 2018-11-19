#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_btnGetMessages = new QPushButton("Get Messages");
    m_btnGetMessages->setIcon(QIcon::fromTheme("mail-send-receive"));
    m_btnWriteMessage = new QPushButton("Write Message");
    m_btnWriteMessage->setIcon(QIcon::fromTheme("mail-send"));

    ui->mainToolBar->addWidget(m_btnGetMessages);
    ui->mainToolBar->addWidget(m_btnWriteMessage);

    m_unreadMessagesCount = 0;

    initializeDataStructures();
    initializeUserAccounts();
    initializeDataModels();
    initializeApplicationWindows();
    initializeAndInstallWidgets();
    expandAllNodesInFolderTreeView();
    cleanUnusedDataFromDatabase();

    QList<int> sizes;
    int folderTreeViewWidth = m_inboxFolderTreeView->sizeHint().rwidth();

    sizes << folderTreeViewWidth << m_mainHorizontalSplitter->size().width() - folderTreeViewWidth;
    m_mainHorizontalSplitter->setSizes(sizes);
    m_mainHorizontalSplitter->setStretchFactor(0, 0);
    m_mainHorizontalSplitter->setStretchFactor(1, 1);


    QObject::connect(m_manageUserAccountsDialog,
                     SIGNAL(userAcccountsConfigurationChanged()),
                     this,
                     SLOT(userAcccountsConfigurationChanged()));

    // closes automatically, when main window is closed
    m_manageUserAccountsDialog->setAttribute(Qt::WA_QuitOnClose, false);

    QObject::connect(m_btnForward,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnForwardClicked(bool)));

    QObject::connect(m_btnReply,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnReplyClicked(bool)));

    QObject::connect(m_btnReplyAll,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnReplyAllClicked(bool)));

    m_messagesMetadataTableView->setContextMenuPolicy(Qt::CustomContextMenu);


    QObject::connect(m_messagesMetadataTableView,
                     SIGNAL(customContextMenuRequested(QPoint)),
                     this,
                     SLOT(messageMetadataTableViewContextMenuRequested(QPoint)));

    QObject::connect(m_btnGetMessages,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnGetMessagesClicked(bool)));

    QObject::connect(m_btnWriteMessage,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnWriteMessageClicked(bool)));

    QObject::connect(m_btnArchive,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnArchiveClicked(bool)));

    QObject::connect(m_btnDelete,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnDeleteMessageClicked(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cleanUnusedDataFromDatabase()
{
    QStringList emailAddresses;

    for (UserAccount userAccount : *m_userAccountsList)
    {
        emailAddresses << userAccount.emailAddress();
    }

    DatabaseManager::cleanUnusedDataFromDatabase(emailAddresses);
    // updateFolderTreeModel();
    updateWindowTitle();
}

void MainWindow::initializeDataStructures()
{
    m_databaseManager = new DatabaseManager(Constants::DATABASE_FILE_NAME);
    m_userAccountsList = new QList<UserAccount>();
}

void MainWindow::initializeUserAccounts()
{
    QFile file(Constants::USER_ACCOUNT_SETTINGS_FILE);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "Error while opening user accounts settings file: " << file.errorString();

        if (QFile::exists(Constants::USER_ACCOUNT_SETTINGS_FILE))
        {
            file.close();
            QFile::remove(Constants::USER_ACCOUNT_SETTINGS_FILE);
        }

        m_databaseManager->clearDatabase();

        return;
    }

    XmlUserAccountsReaderWriter xmlReaderWriter;
    QList<UserAccount> *users = new QList<UserAccount>();

    xmlReaderWriter.setEncryptionKey(Constants::PASSWORD_AES_CBC_ENCRYPTION_KEY);
    xmlReaderWriter.setEncryptionIV(Constants::PASSWORD_AES_CBC_ENCRYPTION_IV);
    xmlReaderWriter.setUserAccounts(users);

    if (!xmlReaderWriter.loadUserAccounts(&file))
    {
        file.close();

        QFile::remove(Constants::USER_ACCOUNT_SETTINGS_FILE);
        m_databaseManager->clearDatabase();

        return;
    }

    m_userAccountsList = users;

    file.close();

    for (UserAccount& userAccount : *m_userAccountsList)
    {
        QObject::connect(&userAccount,
                         SIGNAL(inboxStructureChanged()),
                         this,
                         SLOT(inboxStructureChanged()));

        QObject::connect(&userAccount,
                         SIGNAL(messageContentFetched(int)),
                         this,
                         SLOT(messageContentFetched(int)));

        QObject::connect(&userAccount,
                         SIGNAL(newMessagesReceived(QString, int)),
                         this,
                         SLOT(newMessagesReceived(QString, int)));

        userAccount.initializeInbox();

    }

    updateWindowTitle();
}

void MainWindow::initializeDataModels()
{
    m_inboxFolderTreeView = new QTreeView();
    updateFolderTreeModel();
    m_messageMetadataSqlTableModel = new MessageMetadataSqlTableModel();
    m_messageMetadataSqlTableModel->setTable("MessageData");
    m_userAccountsListModel = new UserAccountsListModel(*m_userAccountsList);
}

void MainWindow::initializeApplicationWindows()
{
    m_manageUserAccountsDialog = new ManageUserAcccountsDialog();
    m_manageUserAccountsDialog->setUserAccounts(m_userAccountsList);
}

void MainWindow::initializeWidgetsAndLayouts()
{
    m_mainHorizontalSplitter = new QSplitter();

    m_messageMetadataHBoxLayout = new QVBoxLayout();
    m_messageMetadataWidget = new QWidget();
    m_editMessageMetadataFilter = new QLineEdit();
    m_editMessageMetadataFilter->setPlaceholderText("Filter messages");

    m_messagesMetadataTableView = new QTableView();

    m_messagesMetadataTableView->setModel(m_messageMetadataSqlTableModel);

    m_messagesMetadataTableView->horizontalHeader()->moveSection(11, 0);
    m_messagesMetadataTableView->horizontalHeader()->moveSection(10, 1);
    m_messagesMetadataTableView->horizontalHeader()->moveSection(11, 2);

    m_messagesMetadataTableView->hideColumn(1);
    m_messagesMetadataTableView->hideColumn(2);
    m_messagesMetadataTableView->hideColumn(3);
    m_messagesMetadataTableView->hideColumn(4);
    m_messagesMetadataTableView->hideColumn(5);
    m_messagesMetadataTableView->hideColumn(6);
    m_messagesMetadataTableView->hideColumn(7);
    m_messagesMetadataTableView->hideColumn(12);
    m_messagesMetadataTableView->hideColumn(13);
    m_messagesMetadataTableView->hideColumn(14);
    m_messagesMetadataTableView->hideColumn(15);
    m_messagesMetadataTableView->hideColumn(16);
    m_messagesMetadataTableView->hideColumn(17);
    m_messagesMetadataTableView->hideColumn(18);
    m_messagesMetadataTableView->hideColumn(19);



    m_messagesMetadataTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_messagesMetadataTableView->verticalHeader()->hide();
    m_messagesMetadataTableView->horizontalHeader()->moveSection(3, 0);

    m_msgInfoWidget = new QWidget();
    m_msgInfoLayout = new QVBoxLayout();
    m_lblFrom = new QLabel();
    m_lblSubject = new QLabel();
    m_lblTo = new QLabel();
    m_lblInCopy = new QLabel();
    m_lblReplyTo = new QLabel();

    m_msgAttachmentsAndActionsLayout = new QHBoxLayout();

    m_msgButtonsWidget = new QWidget();
    m_msgActionsLayout = new QHBoxLayout();

    m_btnJunk = new QPushButton("Junk");
    m_btnArchive = new QPushButton("Archive");
    m_btnDelete = new QPushButton();
    m_btnReply = new QPushButton("Reply");
    m_btnReplyAll = new QPushButton("Reply to all");
    m_btnForward = new QPushButton("Forward");

    m_msgButtonsLayout = new QHBoxLayout();
    m_msgContentView = new QWebEngineView();
    m_messageDataSplitter = new QSplitter();

    m_msgButtonsAndContentLayout = new QVBoxLayout();
    m_msgActionsWidget = new QWidget();
    m_msgAttachmentsAndActionsWidget = new QWidget();
    m_msgButtonsAndContentWidget = new QWidget();

    m_attachmentsWidget = new QWidget();

    QObject::connect(m_messagesMetadataTableView->selectionModel(),
                     SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
                     m_messageMetadataSqlTableModel,
                     SLOT(currentRowChanged(const QModelIndex &, const QModelIndex &)));

    QObject::connect(m_messagesMetadataTableView->horizontalHeader(),
                     SIGNAL(sectionClicked(int)),
                     m_messageMetadataSqlTableModel,
                     SLOT(onTableHeaderClicked(int)));

    QObject::connect(m_editMessageMetadataFilter,
                     SIGNAL(textChanged(const QString &)),
                     this,
                     SLOT(changeMessageMetadataTableFilter(const QString &)));

    QObject::connect(m_messagesMetadataTableView->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
                     this,
                     SLOT(messageMetadataTableViewSelectionChanged(const QModelIndex &, const QModelIndex &)));

    m_msgAttachmentsAndActionsWidget->setVisible(false);
}

void MainWindow::installLayouts()
{
    m_msgActionsLayout->addWidget(m_btnDelete);
    m_msgActionsLayout->addWidget(m_btnJunk);
    m_msgActionsLayout->addWidget(m_btnArchive);
    m_msgActionsLayout->addWidget(m_btnReply);
    m_msgActionsLayout->addWidget(m_btnReplyAll);
    m_msgActionsLayout->addWidget(m_btnForward);

    m_msgActionsWidget->setLayout(m_msgActionsLayout);
    m_msgButtonsLayout->addWidget(m_msgActionsWidget);

    m_msgButtonsWidget->setLayout(m_msgButtonsLayout);

    m_msgInfoLayout->addWidget(m_lblFrom);
    m_msgInfoLayout->addWidget(m_lblSubject);
    m_msgInfoLayout->addWidget(m_lblTo);
    m_msgInfoLayout->addWidget(m_lblInCopy);
    m_msgInfoLayout->addWidget(m_lblReplyTo);

    m_msgInfoWidget->setLayout(m_msgInfoLayout);

    m_msgAttachmentsAndActionsLayout->addWidget(m_msgInfoWidget);
    m_msgAttachmentsAndActionsLayout->addWidget(m_msgButtonsWidget);
    m_msgAttachmentsAndActionsWidget->setLayout(m_msgAttachmentsAndActionsLayout);

    m_msgButtonsAndContentLayout->addWidget(m_msgAttachmentsAndActionsWidget);
    m_msgButtonsAndContentLayout->addWidget(m_msgContentView);
    m_msgButtonsAndContentLayout->addWidget(m_attachmentsWidget);

    m_msgButtonsAndContentWidget->setLayout(m_msgButtonsAndContentLayout);

    m_messageMetadataHBoxLayout->addWidget(m_editMessageMetadataFilter);
    m_messageMetadataHBoxLayout->addWidget(m_messagesMetadataTableView);
    m_messageMetadataWidget->setLayout(m_messageMetadataHBoxLayout);

    m_messageDataSplitter->addWidget(m_messageMetadataWidget);
    m_messageDataSplitter->addWidget(m_msgButtonsAndContentWidget);

    m_mainHorizontalSplitter->addWidget(m_inboxFolderTreeView);
    m_mainHorizontalSplitter->addWidget(m_messageDataSplitter);

    ui->horizontalLayout->addWidget(m_mainHorizontalSplitter);
}

void MainWindow::initializeAndInstallWidgets()
{
    setWindowIcon(QIcon::fromTheme("mail-send"));
    QCoreApplication::setApplicationName("Simple Mail Client");

    initializeWidgetsAndLayouts();
    installLayouts();

    m_inboxFolderTreeView->setHeaderHidden(true);
    m_messagesMetadataTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    m_messagesMetadataTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_messagesMetadataTableView->setSelectionMode(QTableView::SingleSelection);
    m_messagesMetadataTableView->setShowGrid(false);

    m_msgActionsLayout->setContentsMargins(0, 0, 0, 0);

    QSizePolicy sizePolicy;
    sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
    m_msgContentView->setSizePolicy(sizePolicy);

    m_messageDataSplitter->setOrientation(Qt::Vertical);
    m_msgActionsLayout->setAlignment(Qt::AlignRight);
    m_msgButtonsLayout->setContentsMargins(0, 0, 0, 0);

    m_btnArchive->setIcon(QIcon::fromTheme("archive-insert"));
    m_btnDelete->setIcon(QIcon::fromTheme("user-trash"));
    m_btnReply->setIcon(QIcon::fromTheme("mail-reply-sender"));
    m_btnReplyAll->setIcon(QIcon::fromTheme("mail-reply-all"));
    m_btnForward->setIcon(QIcon::fromTheme("mail-forward"));
}

void MainWindow::on_actionAccount_Settings_triggered()
{
    m_manageUserAccountsDialog->show();
}

void MainWindow::on_actionNew_Message_triggered()
{
    WriteMessageWindow *writeMessageWindow = new WriteMessageWindow(WriteMessageWindow::Mode::WriteMessage);
    writeMessageWindow->setAttribute(Qt::WA_QuitOnClose, false);
    writeMessageWindow->setUserAccounts(m_userAccountsList);

    writeMessageWindow->show();
}

void MainWindow::updateMessageMetadataTableFilter(QModelIndex currentIndex, QString filterText)
{
    QString emailAddress = getEmailAddressFromFolderTreeItemIndex(currentIndex);
    QString folderPath = getFolderPathFromFolderTreeItemIndex(currentIndex);
    int folderId = DatabaseManager::getFolderId(emailAddress, folderPath);

    if (folderId > 0)
    {
        if (filterText == QString())
        {
            m_messageMetadataSqlTableModel->setFilter(QString("folderId = %1").arg(folderId));
            m_messageMetadataSqlTableModel->select();
        }
        else
        {
            m_messageMetadataSqlTableModel->setFilter(QString("folderId = %1 AND (sender LIKE '%%2%' OR subject LIKE '%%2%' OR plainTextContent LIKE '%%2%' OR htmlContent LIKE '%%2%')")
                                       .arg(folderId)
                                       .arg(filterText));
            m_messageMetadataSqlTableModel->select();
        }
    }

    while (m_messageMetadataSqlTableModel->canFetchMore())
    {
        m_messageMetadataSqlTableModel->fetchMore();
    }

    m_messagesMetadataTableView->scrollToBottom();
    m_messagesMetadataTableView->selectRow(m_messagesMetadataTableView->model()->rowCount() - 1);
}

void MainWindow::changeMessageMetadataTableFilter(const QString input)
{
    QItemSelectionModel *treeViewSelectionModel = this->m_inboxFolderTreeView->selectionModel();

    updateMessageMetadataTableFilter(treeViewSelectionModel->currentIndex(), input);
}

void MainWindow::folderTreeViewSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QString filterText = m_editMessageMetadataFilter->text();

    updateMessageMetadataTableFilter(current, filterText);
}

void MainWindow::messageMetadataTableViewSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    m_currentMessageId = m_messageMetadataSqlTableModel->data(current.sibling(current.row(), 0), Qt::DisplayRole).toInt();
    QString htmlContent = DatabaseManager::getHtmlContent(m_currentMessageId);
    QString plainTextContent = DatabaseManager::getTextContent(m_currentMessageId);

    if (htmlContent == QString() && plainTextContent == QString())
    {
        if (m_currentMessageId > 0)
        {
            int folderId = m_messageMetadataSqlTableModel->data(current.sibling(current.row(), 1), Qt::DisplayRole).toInt();

            QString folderPath = DatabaseManager::getFolderPath(folderId);
            QString emailAddress = DatabaseManager::getEmailAddress(folderId);

            int positionInFolder = DatabaseManager::getPositionInFolder(m_currentMessageId);

            if (positionInFolder > 0)
            {
                for (UserAccount &userAccount : *m_userAccountsList)
                {
                    if (userAccount.emailAddress() == emailAddress)
                    {
                        userAccount.fetchMissingMessageContent(folderPath, positionInFolder);
                    }
                }
            }
        }
    }
    else
    {
        showMessageContent(m_currentMessageId);
    }

    updateWindowTitle();
}

void MainWindow::onAttachmentButtonClicked(bool checked)
{
    QPushButtonWithId *button = static_cast<QPushButtonWithId*>(QObject::sender());
    Attachment attachment = DatabaseManager::getAttachments(m_currentMessageId).at(button->id());

    QFileDialog dialog;

    QString defaultPath = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first();
    dialog.setDirectory(defaultPath);
    dialog.setWindowTitle("Save attachment");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.selectFile(attachment.name());
    dialog.setMimeTypeFilters(QStringList(attachment.mimeType()));

    if (dialog.exec() == QDialog::Accepted)
    {
        QString fileName = dialog.selectedFiles().first();

        if (fileName != QString())
        {
            QFile file(fileName);
            file.open(QIODevice::WriteOnly);
            file.write(attachment.data());
            file.close();
        }
    }
}

void MainWindow::expandAllNodesInFolderTreeView()
{
    QModelIndexList inboxFolderIndexes = m_inboxFolderTreeModel->match(m_inboxFolderTreeModel->index(0, 0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard | Qt::MatchRecursive);

    for (QModelIndex index : inboxFolderIndexes)
    {
        m_inboxFolderTreeView->expand(index);
    }
}

void MainWindow::userAcccountsConfigurationChanged()
{
    QFile::remove(Constants::USER_ACCOUNT_SETTINGS_FILE);
    QFile file(Constants::USER_ACCOUNT_SETTINGS_FILE);

    if (!file.open(QFile::ReadWrite | QFile::Text))
    {
        qWarning() << "Error while opening user accounts settings file: " << file.errorString();
        file.close();
        return;
    }

    XmlUserAccountsReaderWriter xmlReaderWriter;

    xmlReaderWriter.setEncryptionKey(Constants::PASSWORD_AES_CBC_ENCRYPTION_KEY);
    xmlReaderWriter.setEncryptionIV(Constants::PASSWORD_AES_CBC_ENCRYPTION_IV);
    xmlReaderWriter.setUserAccounts(m_userAccountsList);

    if (!xmlReaderWriter.storeUserAccounts(&file))
    {
        file.close();
        qWarning() << "Error while writing user acccounts settings into file";
    }

    cleanUnusedDataFromDatabase();

    QObject::connect(m_inboxFolderTreeView->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
                     this,
                     SLOT(folderTreeViewSelectionChanged(const QModelIndex &, const QModelIndex &)));

    for (UserAccount& userAccount : *m_userAccountsList)
    {
        QObject::connect(&userAccount,
                         SIGNAL(inboxStructureChanged()),
                         this,
                         SLOT(inboxStructureChanged()));

        QObject::connect(&userAccount,
                         SIGNAL(messageContentFetched(int)),
                         this,
                         SLOT(messageContentFetched(int)));

        QObject::connect(&userAccount,
                         SIGNAL(newMessagesReceived(QString, int)),
                         this,
                         SLOT(newMessagesReceived(QString, int)));

        userAccount.initializeInbox();

    }

    updateWindowTitle();
}

Message MainWindow::getMessage(int messageId) const
{
    QString htmlContent = DatabaseManager::getHtmlContent(messageId);
    QString plainTextContent = DatabaseManager::getTextContent(messageId);
    QString subject = DatabaseManager::getSubject(messageId);
    Contact from = DatabaseManager::getSender(messageId);
    QList<Contact> to = DatabaseManager::getRecipients(messageId);
    QDateTime date = DatabaseManager::getDate(messageId);
    QList<Attachment> attachments = DatabaseManager::getAttachments(messageId);
    QList<EmbeddedObject> embeddedObjects = DatabaseManager::getEmbeddedObjects(messageId);

    Message message;
    message.setHtmlContent(htmlContent);
    message.setPlainTextContent(plainTextContent);
    message.setSubject(subject);
    message.setSender(from);
    message.setAddressListTo(to);
    message.setDateTime(date);
    message.setAttachments(attachments);
    message.setEmbeddedObjects(embeddedObjects);

    return message;
}

void MainWindow::onBtnReplyClicked(bool checked)
{
    QItemSelectionModel *selectionModel = m_messagesMetadataTableView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QModelIndex index = selectionModel->selectedRows().at(0);
        int currentMessageId = m_messageMetadataSqlTableModel->data(QModelIndex(index.sibling(index.row(), 0)), Qt::DisplayRole).toInt();

        Message message = getMessage(currentMessageId);

        WriteMessageWindow *writeMessageWindow = new WriteMessageWindow(WriteMessageWindow::Mode::Reply);

        writeMessageWindow->setAttribute(Qt::WA_QuitOnClose, false);
        writeMessageWindow->setUserAccounts(m_userAccountsList);
        writeMessageWindow->setWindowContent(message);

        writeMessageWindow->show();
    }
}

QString MainWindow::getEmailAddressFromFolderTreeItemIndex(QModelIndex currentIndex)
{
    QString path = getFullFolderPathFromFolderTreeItemIndex(currentIndex);

    return path.split("/")[0];
}

QString MainWindow::getFullFolderPathFromFolderTreeItemIndex(QModelIndex currentIndex)
{
    InboxFolderTreeItem* item = static_cast<InboxFolderTreeItem*>(currentIndex.internalPointer());

    if (item != nullptr)
    {
        QString path = item->data(0).toString();
        QModelIndex index = currentIndex;

        while(index.parent() != QModelIndex())
        {
            index = index.parent();
            item = static_cast<InboxFolderTreeItem*>(index.internalPointer());
            path = item->data(0).toString() + "/" + path;
        }

        return path;
    }
    else
    {
        return QString();
    }

}

QString MainWindow::getFolderPathFromFolderTreeItemIndex(QModelIndex currentIndex)
{
    QString path = getFullFolderPathFromFolderTreeItemIndex(currentIndex);
    QString emailAddress = getEmailAddressFromFolderTreeItemIndex(currentIndex);

    return path.right(path.length() - emailAddress.length());
}

void MainWindow::onBtnReplyAllClicked(bool checked)
{
    QItemSelectionModel *selectionModel = m_messagesMetadataTableView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QModelIndex index = selectionModel->selectedRows().at(0);
        int currentMessageId = m_messageMetadataSqlTableModel->data(QModelIndex(index.sibling(index.row(), 0)), Qt::DisplayRole).toInt();

        Message message = getMessage(currentMessageId);

        WriteMessageWindow *writeMessageWindow = new WriteMessageWindow(WriteMessageWindow::Mode::ReplyAll);

        writeMessageWindow->setAttribute(Qt::WA_QuitOnClose, false);
        writeMessageWindow->setUserAccounts(m_userAccountsList);
        writeMessageWindow->setWindowContent(message);

        writeMessageWindow->show();
    }
}

void MainWindow::onBtnForwardClicked(bool checked)
{
    QItemSelectionModel *selectionModel = m_messagesMetadataTableView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QModelIndex index = selectionModel->selectedRows().at(0);
        int currentMessageId = m_messageMetadataSqlTableModel->data(QModelIndex(index.sibling(index.row(), 0)), Qt::DisplayRole).toInt();

        Message message = getMessage(currentMessageId);

        WriteMessageWindow *writeMessageWindow = new WriteMessageWindow(WriteMessageWindow::Mode::Forward);

        writeMessageWindow->setAttribute(Qt::WA_QuitOnClose, false);
        writeMessageWindow->setUserAccounts(m_userAccountsList);
        writeMessageWindow->setWindowContent(message);

        writeMessageWindow->show();
    }
}

void MainWindow::inboxStructureChanged()
{
     updateFolderTreeModel();
     updateWindowTitle();
}

void MainWindow::updateFolderTreeModel()
{
    m_inboxFolderTreeModel = new InboxFolderTreeModel(DatabaseManager::getInboxFolders());
    m_inboxFolderTreeView->setModel(m_inboxFolderTreeModel);
    expandAllNodesInFolderTreeView();

    QObject::connect(m_inboxFolderTreeView->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
                     this,
                     SLOT(folderTreeViewSelectionChanged(const QModelIndex &, const QModelIndex &)));

    m_inboxFolderTreeView->setContextMenuPolicy(Qt::CustomContextMenu);

    QObject::connect(m_inboxFolderTreeView,
                     SIGNAL(customContextMenuRequested(QPoint)),
                     this,
                     SLOT(folderTreeViewContextMenuRequested(QPoint)));
}

void MainWindow::messageContentFetched(int messageId)
{
    QItemSelectionModel *selectionModel = m_messagesMetadataTableView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QModelIndex index = selectionModel->selectedRows().at(0);
        int currentMessageId = m_messageMetadataSqlTableModel->data(QModelIndex(index.sibling(index.row(), 0)), Qt::DisplayRole).toInt();

        if (messageId == currentMessageId)
        {
            showMessageContent(messageId);
        }
    }
}

void MainWindow::deleteOldAttachmentsLayout(QLayout *layout)
{
    if (layout != nullptr)
    {
        QLayoutItem *item;
        QWidget *widget;

        while ((item = layout->takeAt(0)) != nullptr)
        {
            if ((widget = item->widget()) != nullptr)
            {
                widget->hide();
                delete widget;
            }
        }
    }

    delete layout;
}

QHBoxLayout* MainWindow::createAttachmentsLayout(QString caption, QList<Attachment> attachments)
{
    QHBoxLayout *layout = new QHBoxLayout();
    QLabel *attachmentsLabel = new QLabel(caption);
    layout->addWidget(attachmentsLabel);

    for (int i = 0; i < attachments.size(); i++)
    {
        QPushButtonWithId *button = new QPushButtonWithId(attachments.at(i).name());
        button->setId(i);
        button->setIcon(QIcon::fromTheme("mail-attachment"));

        if (caption.contains("Attachments"))
        {
            QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(onAttachmentButtonClicked(bool)));
        }
        else if (caption.contains("Embedded"))
        {
            QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(onEmbeddedObjectButtonClicked(bool)));
        }

        layout->addWidget(button);
    }

    layout->setAlignment(Qt::AlignLeft);
    layout->setContentsMargins(0, 0, 0, 0);

    return layout;
}

void MainWindow::setupAttachmentsPanel(const QList<Attachment> attachments)
{
    if (attachments.size() > 0)
    {
        QLayout *oldLayout = m_attachmentsWidget->layout();
        deleteOldAttachmentsLayout(oldLayout);
        m_attachmentsWidget->setLayout(createAttachmentsLayout("<b>Attachments:</b>", attachments));
        m_attachmentsWidget->show();
    }
    else
    {
        m_attachmentsWidget->hide();
    }
}

void MainWindow::showMessageContent(int messageId)
{
    if (messageId > 0)
    {
        m_msgAttachmentsAndActionsWidget->setVisible(true);
        m_btnReplyAll->setVisible(false);

        QString subject = DatabaseManager::getSubject(messageId);

        QString htmlContent = DatabaseManager::getHtmlContent(messageId);
        QString plainTextContent = DatabaseManager::getTextContent(messageId);

        QList<Attachment> attachments = DatabaseManager::getAttachments(messageId);
        QList<EmbeddedObject> embeddedObjects = DatabaseManager::getEmbeddedObjects(messageId);

        if (!embeddedObjects.isEmpty())
        {
            for (EmbeddedObject embeddedObject : embeddedObjects)
            {
                QString srcOld = "src=\"cid:" + embeddedObject.name() + "\"";
                QString srcNew = "src=\"data:" + embeddedObject.mimeType() + ";base64," + embeddedObject.data().toBase64() + "\"";

                htmlContent.replace(srcOld, srcNew);
            }
        }

        QList<Contact> recipients = DatabaseManager::getRecipients(messageId);
        QList<Contact> copyRecipients = DatabaseManager::getCopyRecipients(messageId);
        QList<Contact> replyTo = DatabaseManager::getReplyTo(messageId);

        Contact from = DatabaseManager::getSender(messageId);

        m_lblSubject->setText("<b>Subject:</b> " + subject);
        m_lblFrom->setText("<b>From:</b> "
                           + Contact::toString(from)
                           .replace("<", "&lt;")
                           .replace(">", "&gt;"));

        m_lblTo->setText("<b>To:</b> "
                         + Contact::toString(recipients)
                         .replace("<", "&lt;")
                         .replace(">", "&gt;"));

        if (replyTo.isEmpty())
        {
            m_lblReplyTo->setVisible(false);
        }
        else
        {
            m_lblReplyTo->setVisible(true);
            m_lblReplyTo->setText("<b>Reply to:</b> "
                                  + Contact::toString(replyTo)
                                  .replace("<", "&lt;")
                                  .replace(">", "&gt;"));
        }

        if (copyRecipients.isEmpty())
        {
            m_lblInCopy->setVisible(false);
        }
        else
        {
            m_lblInCopy->setVisible(true);
            m_lblInCopy->setText("<b>In copy:</b> "
                                 + Contact::toString(copyRecipients)
                                 .replace("<", "&lt;")
                                 .replace(">", "&gt;"));
        }

        if (htmlContent != QString())
        {
            m_msgContentView->setHtml(htmlContent);
        }
        else if (plainTextContent != QString())
        {
            m_msgContentView->setHtml(plainTextContent);
        }
        else
        {
            m_msgContentView->setHtml(QString());
        }

        if (!replyTo.isEmpty() || !copyRecipients.isEmpty())
        {
            m_btnReplyAll->setVisible(true);
        }
        else
        {
            m_btnReplyAll->setVisible(false);
        }

        setupAttachmentsPanel(attachments);

        QItemSelectionModel *selectionModel = m_messagesMetadataTableView->selectionModel();

        if (selectionModel->hasSelection())
        {
            QModelIndex index = selectionModel->selectedRows().at(0);
            int folderId = m_messageMetadataSqlTableModel->data(QModelIndex(index.sibling(index.row(), 1)), Qt::DisplayRole).toInt();

            if (DatabaseManager::isFolderJunk(folderId))
            {
                m_btnJunk->setText("Not junk");
                m_btnJunk->setIcon(QIcon::fromTheme("mail-mark-nojunk"));
            }
            else
            {
                m_btnJunk->setText("Junk");
                m_btnJunk->setIcon(QIcon::fromTheme("mail-mark-junk"));
            }

            if (DatabaseManager::isFolderTrash(folderId))
            {
                m_btnDelete->setText("Delete");
            }
            else
            {
                m_btnDelete->setText("Move to trash");
            }

            if (DatabaseManager::isFolderArchive(folderId))
            {
                m_btnArchive->setVisible(false);
            }
            else
            {
                m_btnArchive->setVisible(true);
            }

            m_btnDelete->setVisible(true);
            m_btnJunk->setVisible(true);
        }
        else
        {
            m_btnDelete->setVisible(false);
            m_btnJunk->setVisible(false);
        }

        updateFolderTreeModel();
        updateWindowTitle();
    }
}

void MainWindow::updateWindowTitle()
{
    m_unreadMessagesCount = DatabaseManager::getTotalCountOfUnreadMessages();

    if (m_unreadMessagesCount > 0)
    {
        QString windowTitle;

        windowTitle.append("(");
        windowTitle.append(QString::number(m_unreadMessagesCount));
        windowTitle.append(") ");
        windowTitle.append("Simple Mail Client");

        setWindowTitle(windowTitle);
    }
    else
    {
        setWindowTitle("Simple Mail Client");
    }
}

void MainWindow::newMessagesReceived(QString emailAddress, int count)
{
    QMessageBox messageBox;

    QString result;
    result.append("Account ");
    result.append(emailAddress);
    result.append(" has ");
    result.append(QString::number(count));
    result.append(" new unread messages");

    messageBox.setWindowTitle("You have new messages");
    messageBox.setText(result);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.exec();
}

void MainWindow::messageMetadataTableViewContextMenuRequested(QPoint position)
{
    QItemSelectionModel *selectionModel = m_messagesMetadataTableView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QMenu *menu = new QMenu();

        QModelIndex index = selectionModel->selectedRows().at(0);
        int folderId = m_messageMetadataSqlTableModel->data(QModelIndex(index.sibling(index.row(), 1)), Qt::DisplayRole).toInt();
        QString emailAddress = DatabaseManager::getEmailAddress(folderId);

        QList<InboxFolder> folders = DatabaseManager::getInboxFolders(emailAddress);


        QMenu *moveMessageMenu = new QMenu("Move to");

        for (InboxFolder folder : folders)
        {
            if (folder.path() != "/")
            {
                QAction *action = new QAction(folder.path());
                action->setIcon(folder.getIcon());
                moveMessageMenu->addAction(action);

                QObject::connect(action,
                                 SIGNAL(triggered(bool)),
                                 this,
                                 SLOT(moveMessageActionTriggered(bool)));
            }
        }

        QMenu *copyMessageMenu = new QMenu("Copy to");

        for (InboxFolder folder : folders)
        {
            if (folder.path() != "/")
            {
                QAction *action = new QAction(folder.path());
                action->setIcon(folder.getIcon());
                copyMessageMenu->addAction(action);

                QObject::connect(action,
                                 SIGNAL(triggered(bool)),
                                 this,
                                 SLOT(copyMessageActionTriggered(bool)));
            }
        }

        QAction *deleteAction = new QAction("Delete Message");

        QObject::connect(deleteAction,
                         SIGNAL(triggered(bool)),
                         this,
                         SLOT(deleteMessageActionTriggered(bool)));

        menu->addMenu(moveMessageMenu);
        menu->addMenu(copyMessageMenu);
        menu->addAction(deleteAction);

        menu->popup(m_messagesMetadataTableView->viewport()->mapToGlobal(position));
    }
}

void MainWindow::folderTreeViewContextMenuRequested(QPoint position)
{
    QItemSelectionModel *selectionModel = m_inboxFolderTreeView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QMenu *menu = new QMenu();

        InboxFolderTreeItem* selectedItem = static_cast<InboxFolderTreeItem*>(selectionModel->selectedIndexes().first().internalPointer());
        QString caption = selectedItem->data(0).toString();

        QRegExp emailAddressRegexPattern("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        emailAddressRegexPattern.setCaseSensitivity(Qt::CaseInsensitive);
        emailAddressRegexPattern.setPatternSyntax(QRegExp::RegExp);

        emailAddressRegexPattern.indexIn(caption);

        if (emailAddressRegexPattern.capturedTexts().last() != QString())
        {
            return;
        }
        else if (caption == "INBOX")
        {
            QAction *newFolderAction = new QAction("New Folder");

            QObject::connect(newFolderAction,
                             SIGNAL(triggered(bool)),
                             this,
                             SLOT(createNewFolderActionTriggered(bool)));

            menu->addAction(newFolderAction);
        }
        else
        {
            QAction *newSubfolderAction = new QAction("New Subfolder");
            QAction *deleteFolderAction = new QAction("Delete Folder");
            QAction *renameFolderAction = new QAction("Rename Folder");

            QObject::connect(newSubfolderAction,
                             SIGNAL(triggered(bool)),
                             this,
                             SLOT(createNewSubfolderActionTriggered(bool)));

            QObject::connect(deleteFolderAction,
                             SIGNAL(triggered(bool)),
                             this,
                             SLOT(deleteFolderActionTriggered(bool)));

            QObject::connect(renameFolderAction,
                             SIGNAL(triggered(bool)),
                             this,
                             SLOT(renameFolderActionTriggered(bool)));

            menu->addAction(newSubfolderAction);
            menu->addAction(deleteFolderAction);
            menu->addAction(renameFolderAction);
        }



        menu->popup(m_inboxFolderTreeView->viewport()->mapToGlobal(position));
    }
}

void MainWindow::deleteMessageActionTriggered(bool checked)
{
    qWarning() << "Message will be deleted";
}

void MainWindow::moveMessageActionTriggered(bool checked)
{
    qWarning() << "Message will be moved";
}

void MainWindow::copyMessageActionTriggered(bool checked)
{
    qWarning() << "Message will be copied";
}

void MainWindow::createNewFolderActionTriggered(bool checked)
{
    QItemSelectionModel *selectionModel = m_inboxFolderTreeView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QModelIndex index = selectionModel->selectedIndexes().first();

        QString emailAddress = getEmailAddressFromFolderTreeItemIndex(index);
        QString folderPath = getFolderPathFromFolderTreeItemIndex(index);
        // int folderId = DatabaseManager::getFolderId(emailAddress, folderPath);

        NewFolderDialog *dialog = new NewFolderDialog();
        dialog->setWindowTitle("New Folder");

        if (dialog->exec())
        {
            QString folderName = dialog->getFolderName();

            if (folderName != QString())
            {
                qWarning() << "Folder " << folderName << " will be created in INBOX folder of account " << emailAddress;
                // TODO: validace na lomitka a existujici adresare ve stejnem adresari
            }
        }
    }
}

void MainWindow::createNewSubfolderActionTriggered(bool checked)
{
    QItemSelectionModel *selectionModel = m_inboxFolderTreeView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QModelIndex index = selectionModel->selectedIndexes().first();

        QString emailAddress = getEmailAddressFromFolderTreeItemIndex(index);
        QString folderPath = getFolderPathFromFolderTreeItemIndex(index);
        // int folderId = DatabaseManager::getFolderId(emailAddress, folderPath);

        NewFolderDialog *dialog = new NewFolderDialog();
        dialog->setWindowTitle("New Subfolder");

        if (dialog->exec())
        {
            QString folderName = dialog->getFolderName();

            if (folderName != QString())
            {
                qWarning() << "Folder " << folderName << " will be created on path " << folderPath << " in account " << emailAddress;
                // TODO: validace na lomitka a existujici adresare ve stejnem adresari
            }
        }
    }

}

void MainWindow::deleteFolderActionTriggered(bool)
{
    QItemSelectionModel *selectionModel = m_inboxFolderTreeView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QModelIndex index = selectionModel->selectedIndexes().first();

        QString emailAddress = getEmailAddressFromFolderTreeItemIndex(index);
        QString folderPath = getFolderPathFromFolderTreeItemIndex(index);
        // int folderId = DatabaseManager::getFolderId(emailAddress, folderPath);

        QMessageBox messageBox;

        messageBox.setWindowTitle("Delete Folder");
        messageBox.setText("Are you sure to delete the folder " + folderPath.split("/").last() + "?");
        messageBox.setIcon(QMessageBox::Question);
        messageBox.addButton(new QPushButton("Cancel"), QMessageBox::ButtonRole::RejectRole);
        messageBox.addButton(new QPushButton("Delete Folder"), QMessageBox::ButtonRole::AcceptRole);

        if (messageBox.exec())
        {
           qWarning() << "Folder " << folderPath << " of account " << emailAddress << " will be deleted";
        }
    }
}

void MainWindow::renameFolderActionTriggered(bool checked)
{
    QItemSelectionModel *selectionModel = m_inboxFolderTreeView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QModelIndex index = selectionModel->selectedIndexes().first();

        QString emailAddress = getEmailAddressFromFolderTreeItemIndex(index);
        QString folderPath = getFolderPathFromFolderTreeItemIndex(index);
        // int folderId = DatabaseManager::getFolderId(emailAddress, folderPath);

        RenameFolderDialog *dialog = new RenameFolderDialog();
        dialog->setFolderName(folderPath.split("/").last());

        if (dialog->exec())
        {
            QString folderName = dialog->getFolderName();

            if (folderName != QString())
            {
                qWarning() << "Renaming a directory. Original name:  " << folderPath.split("/").last() << " New name: " << folderName;
            }
        }
    }
}

void MainWindow::onBtnWriteMessageClicked(bool checked)
{
    WriteMessageWindow *writeMessageWindow = new WriteMessageWindow(WriteMessageWindow::Mode::WriteMessage);
    writeMessageWindow->setAttribute(Qt::WA_QuitOnClose, false);
    writeMessageWindow->setUserAccounts(m_userAccountsList);

    writeMessageWindow->show();
}

void MainWindow::onBtnGetMessagesClicked(bool checked)
{
    for (UserAccount& userAccount : *m_userAccountsList)
    {
        userAccount.initializeInbox();
    }
}

void MainWindow::onBtnArchiveClicked(bool checked)
{
    QString archiveFolderPath;

    QItemSelectionModel *messageMetadataTableViewSelectionModel = m_messagesMetadataTableView->selectionModel();

    if (messageMetadataTableViewSelectionModel->hasSelection())
    {
        QModelIndex index = messageMetadataTableViewSelectionModel->selectedIndexes().first();
        int messageId = m_messageMetadataSqlTableModel->data(QModelIndex(index.sibling(index.row(), 0)), Qt::DisplayRole).toInt();
        int folderId = m_messageMetadataSqlTableModel->data(QModelIndex(index.sibling(index.row(), 1)), Qt::DisplayRole).toInt();

        QString emailAddress = DatabaseManager::getEmailAddress(folderId);
        QString folderPath = DatabaseManager::getFolderPath(folderId);

        qWarning() << "Message with id " << QString::number(messageId) << " in folder " << folderPath << " of account " << emailAddress << " will be archived";

        archiveFolderPath = DatabaseManager::getArchiveFolderPathForAccount(emailAddress);

        qWarning() << "Path to archive folder is: " << archiveFolderPath;

        for (UserAccount& account : *m_userAccountsList)
        {
            if (account.emailAddress() == emailAddress)
            {
                account.moveMessage(folderPath, messageId, archiveFolderPath);
            }
        }
    }

    // move in database

    // move in remote folder
}

void MainWindow::onBtnDeleteMessageClicked(bool checked)
{
    qWarning() << "message will be deleted";
}
