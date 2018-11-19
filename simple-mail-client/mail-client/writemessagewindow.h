#ifndef WRITEMESSAGEWINDOW_H
#define WRITEMESSAGEWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QWebEngineView>
#include <QMimeDatabase>

#include "attachmentslistmodel.h"
#include "constants.h"

#include "src/useraccount.h"
#include "src/useraccountslistmodel.h"
#include "src/attachment.h"
#include "src/message.h"
#include "src/contact.h"
#include "src/multiselectcompleter.h"
#include "src/databasemanager.h"

namespace Ui {
class WriteMessageWindow;
}

class WriteMessageWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Mode { WriteMessage, Reply, ReplyAll, Forward };

    explicit WriteMessageWindow(Mode mode, QWidget *parent = nullptr);
    ~WriteMessageWindow();



    void setWindowContent(const Message message);

    void setUserAccounts(QList<UserAccount> *userAccounts);
    void setSenderComboBoxEditable(bool value);

signals:

public slots:

private slots:
    void onBtnAddAttachmentClicked(bool);
    void onBtnRemoveAttachmentClicked(bool);
    void onBtnSendClicked(bool);

private:
    Ui::WriteMessageWindow *ui;

    void initializeGuiObjects();
    void setUpWidgets();
    void installLayouts();


    void setSubject();
    void setPlainTextAndHtmlText();
    void setRecipients();
    void setAttachments();
    void setEmbeddedObjects();
    void setHtmlContent(QString content);
    void setSenderIndex();
    QRegExp getEmailAddressRegexPattern() const;

    QList<Contact> parseContacts(const QString rawdata) const;

    QHBoxLayout *m_messageActionsButtonsLayout;
    QWidget *m_messageActionsButtonsWidget;

    QPushButton *m_btnSend;
    QPushButton *m_btnAttachFile;
    QPushButton *m_btnSave;

    QHBoxLayout *m_messageInfoAndAttachmentsLayout;
    QWidget *m_messageInfoAndAttachmentsWidget;

    QGridLayout *m_messageInfoGridLayout;
    QWidget *m_messageInfoGridWidget;

    QLabel *m_lblFrom;
    QLabel *m_lblTo;
    QLabel *m_lblInCopy;
    QLabel *m_lblInBlindCopy;
    QLabel *m_lblSubject;

    QComboBox *m_comboBoxFrom;
    QLineEdit *m_editTo;
    QLineEdit *m_editInCopy;
    QLineEdit *m_editInBlindCopy;
    QLineEdit *m_editSubject;

    QVBoxLayout *m_attachmentsLayout;
    QWidget *m_attachmentsWidget;

    QLabel *m_lblAttachments;

    QHBoxLayout *m_attachmentsContentLayout;
    QWidget *m_attachmentsContentWidget;

    QListView *m_attachmentsListView;

    QVBoxLayout *m_attachmentsButtonLayout;
    QWidget *m_attachmentsButtonsWidget;

    QPushButton *m_btnAddAttachment;
    QPushButton *m_btnRemoveAttachment;

    QTextEdit *m_editMessageContent;
    QWebEngineView *m_htmlContentView;

    QList<UserAccount> *m_userAccounts;
    UserAccountsListModel *m_userAccountsListModel;

    QList<Attachment> m_attachments;
    AttachmentsListModel *m_attachmentsListModel;

    QList<EmbeddedObject> m_embeddedObjects;

    QString m_htmlContent;
    QString m_plainTextContent;

    Mode m_mode;
    Message m_message;
};

#endif // WRITEMESSAGEWINDOW_H
