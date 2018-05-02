#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <userAccounts/useraccount.h>
#include <QDebug>
#include <QtWidgets>
#include "manageaccountsdialog.h"
#include "writemessagewindow.h"
#include "tools/constants.h"
#include "userAccounts/xmluseraccountsreaderwriter.h"
#include "userAccounts/iuseraccountsreaderwriter.h"
#include <userAccounts/useraccountslistmodel.h>
#include "messaging/messagemetadata.h"
#include "messaging/vmimeimapstore.h"
#include "messaging/messagemetadatatablemodel.h"

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
    void initializeDataModels();
    void initializeApplicationWindows();
    void initializeAndInstallWidgets();

    Ui::MainWindow *ui;

    QList<UserAccount> *userAccountsList;
    QList<VmimeImapStore> *inboxesList;
    QList<QList<MessageMetadata>> *inboxesMessageMetadataList;

    UserAccountsListModel *userAccountsListModel;
    MessageMetadataTableModel *messageMetadataTableModel;

    QSplitter *mainHorizontalSplitter;
    QListView *userAccountsListView;
    QTableView *messagesMetadataTableView;

    ManageAccountsDialog *manageAccountsDialog;
    WriteMessageWindow *writeMessageWindow;
};

#endif // MAINWINDOW_H
