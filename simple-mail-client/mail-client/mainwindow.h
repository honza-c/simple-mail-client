#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtWidgets>
#include <QWebEngineView>

#include "src/databasemanager.h"
#include "src/useraccount.h"
#include "src/inboxfoldertreemodel.h"
#include "src/messagemetadatasqltablemodel.h"
#include "src/attachment.h"
#include "src/qpushbuttonwithid.h"
#include "src/xmluseraccountsreaderwriter.h"
#include "src/useraccountslistmodel.h"

//#include "constants.h"

#include "manageuseracccountsdialog.h"
#include "writemessagewindow.h"
#include "newfolderdialog.h"
#include "renamefolderdialog.h"
#include "embeddedobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAccount_Settings_triggered();
    void on_actionNew_Message_triggered();
    void changeMessageMetadataTableFilter(const QString input);
    void folderTreeViewSelectionChanged(const QModelIndex &, const QModelIndex &);
    void messageMetadataTableViewSelectionChanged(const QModelIndex &, const QModelIndex &);
    void onAttachmentButtonClicked(bool);
    void userAcccountsConfigurationChanged();

    void onBtnReplyClicked(bool);
    void onBtnReplyAllClicked(bool);
    void onBtnForwardClicked(bool);

    void inboxStructureChanged();
    void messageContentFetched(int);
    void newMessagesReceived(QString, int);
    void messageMetadataTableViewContextMenuRequested(QPoint);
    void folderTreeViewContextMenuRequested(QPoint);

    void deleteMessageActionTriggered(bool);
    void moveMessageActionTriggered(bool);
    void copyMessageActionTriggered(bool);

    void createNewFolderActionTriggered(bool);
    void createNewSubfolderActionTriggered(bool);
    void deleteFolderActionTriggered(bool);
    void renameFolderActionTriggered(bool);

    void onBtnWriteMessageClicked(bool);
    void onBtnGetMessagesClicked(bool);

    void onBtnArchiveClicked(bool);
    void onBtnDeleteMessageClicked(bool);

private:
    void initializeDataStructures();
    void initializeUserAccounts();
    void initializeDataModels();
    void initializeApplicationWindows();
    void initializeAndInstallWidgets();
    void initializeWidgetsAndLayouts();
    void installLayouts();
    void expandAllNodesInFolderTreeView();
    void cleanUnusedDataFromDatabase();
    void showMessageContent(int messageId);
    void updateWindowTitle();
    void updateMessageMetadataTableFilter(QModelIndex currentIndex, QString filterText);
    QString getEmailAddressFromFolderTreeItemIndex(QModelIndex currentIndex);
    QString getFolderPathFromFolderTreeItemIndex(QModelIndex currentIndex);
    QString getFullFolderPathFromFolderTreeItemIndex(QModelIndex currentIndex);
    void updateFolderTreeModel();
    void setupAttachmentsPanel(const QList<Attachment> attachments);
    void deleteOldAttachmentsLayout(QLayout *layout);
    QHBoxLayout *createAttachmentsLayout(QString caption, QList<Attachment> attachments);
    Message getMessage(int messageId) const;

    Ui::MainWindow *ui;

    // data structures
    DatabaseManager *m_databaseManager;
    QList<UserAccount> *m_userAccountsList;

    // widgets and layouts
    UserAccountsListModel *m_userAccountsListModel;
    InboxFolderTreeModel *m_inboxFolderTreeModel;
    MessageMetadataSqlTableModel *m_messageMetadataSqlTableModel;

    QSplitter *m_mainHorizontalSplitter;
    QLineEdit *m_editMessageMetadataFilter;
    QTableView *m_messagesMetadataTableView;
    QTreeView *m_inboxFolderTreeView;

    QVBoxLayout *m_messageMetadataHBoxLayout;
    QWidget *m_messageMetadataWidget;

    QHBoxLayout *m_msgActionsLayout;
    QPushButton *m_btnArchive;
    QPushButton *m_btnJunk;
    QPushButton *m_btnDelete;
    QPushButton *m_btnReply;
    QPushButton *m_btnReplyAll;
    QPushButton *m_btnForward;

    QWidget *m_msgInfoWidget;
    QVBoxLayout *m_msgInfoLayout;
    QLabel *m_lblFrom;
    QLabel *m_lblSubject;
    QLabel *m_lblTo;
    QLabel *m_lblInCopy;
    QLabel *m_lblReplyTo;

    QWidget *m_msgButtonsWidget;
    QHBoxLayout *m_msgButtonsLayout;
    QWebEngineView *m_msgContentView;
    QSplitter *m_messageDataSplitter;

    QVBoxLayout *m_msgButtonsAndContentLayout;

    QWidget *m_msgActionsWidget;
    QWidget *m_msgAttachmentsAndActionsWidget;
    QHBoxLayout *m_msgAttachmentsAndActionsLayout;
    QWidget *m_msgButtonsAndContentWidget;

    QWidget *m_attachmentsWidget;

    int m_currentMessageId;
    int m_unreadMessagesCount;

    ManageUserAcccountsDialog *m_manageUserAccountsDialog;

    QPushButton *m_btnGetMessages;
    QPushButton *m_btnWriteMessage;
};

#endif // MAINWINDOW_H
