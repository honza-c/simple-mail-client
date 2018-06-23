#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <userAccounts/useraccount.h>
#include <QDebug>
#include <QtWidgets>
#include <QWebEngineView>
#include "manageaccountsdialog.h"
#include "writemessagewindow.h"
#include "tools/constants.h"
#include "userAccounts/xmluseraccountsreaderwriter.h"
#include "userAccounts/iuseraccountsreaderwriter.h"
#include <userAccounts/useraccountslistmodel.h>
#include "messaging/messagemetadata.h"
#include "messaging/vmimeimapservice.h"
#include "messaging/vmimeinboxservice.h"
#include "messaging/messagemetadatatablemodel.h"
#include "messaging/inboxfoldertreemodel.h"
#include "messaging/inboxfolder.h"
#include "database/databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAccount_Settings_triggered();
    void on_actionNew_Message_triggered();

private:
    void initializeDataStructures();
    void initializeUserAccounts();
    void initializeInboxMetadata();
    void initializeInboxFolders();
    void initializeDataModels();
    void initializeApplicationWindows();
    void initializeAndInstallWidgets();
    void initializeWidgetsAndLayouts();
    void installLayouts();

    Ui::MainWindow *ui;

    QList<UserAccount> *userAccountsList;
    QList<VmimeInboxService*> *inboxesList;
    QList<QList<InboxFolder>> *inboxesFolderList;
    QList<QList<MessageMetadata>> *inboxesMessageMetadataList;

    DatabaseManager *dbManager;

    UserAccountsListModel *userAccountsListModel;
    InboxFolderTreeModel *inboxFolderTreeModel;
    MessageMetadataTableModel *messageMetadataTableModel;

    QSplitter *mainHorizontalSplitter;
    QTableView *messagesMetadataTableView;
    QTreeView *inboxFolderTreeView;

    QHBoxLayout *attachmentsLayout;
    QPushButton *btnAttachment1;
    QPushButton *btnAttachment2;
    QPushButton *btnAttachment3;
    QLabel *lblAttachments;

    QHBoxLayout *msgActionsLayout;
    QPushButton *btnReply;
    QPushButton *btnReplyToAll;
    QPushButton *btnForward;

    QHBoxLayout *msgButtonsLayout;
    QWebEngineView *msgContentView;
    QSplitter *messageDataSplitter;

    QVBoxLayout *msgButtonsAndContentLayout;

    QWidget *attachmentsWidget;
    QWidget *msgActionsWidget;
    QWidget *msgAttachmentsAndActionsWidget;
    QWidget *msgButtonsAndContentWidget;

    ManageAccountsDialog *manageAccountsDialog;
    WriteMessageWindow *writeMessageWindow;
};

#endif // MAINWINDOW_H
