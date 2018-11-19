#include "writemessagewindow.h"
#include "ui_writemessagewindow.h"

WriteMessageWindow::WriteMessageWindow(Mode mode, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WriteMessageWindow)
{
    ui->setupUi(this);

    m_mode = mode;

    initializeGuiObjects();
    installLayouts();
    setUpWidgets();

    m_attachments = QList<Attachment>();
    m_embeddedObjects = QList<EmbeddedObject>();

    m_attachmentsWidget->setVisible(false);

    QStringList contactsData = DatabaseManager::getDataForContactsCompleter();
    MultiSelectCompleter *completer = new MultiSelectCompleter(contactsData, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);

    m_editTo->setCompleter(completer);
    m_editInCopy->setCompleter(completer);
    m_editInBlindCopy->setCompleter(completer);
}

WriteMessageWindow::~WriteMessageWindow()
{
    delete ui;
}

void WriteMessageWindow::initializeGuiObjects()
{
    m_messageActionsButtonsLayout = new QHBoxLayout();
    m_messageActionsButtonsWidget = new QWidget();

    m_btnSend = new QPushButton("Send");
    m_btnAttachFile = new QPushButton("Attach");
    m_btnSave = new QPushButton("Save");

    m_messageInfoAndAttachmentsLayout = new QHBoxLayout();
    m_messageInfoAndAttachmentsWidget = new QWidget();

    m_messageInfoGridLayout = new QGridLayout();
    m_messageInfoGridWidget = new QWidget();

    m_lblFrom = new QLabel("From");
    m_lblTo = new QLabel("To");
    m_lblInCopy = new QLabel("In copy");
    m_lblInBlindCopy = new QLabel("In blind copy");
    m_lblSubject = new QLabel("Subject");

    m_comboBoxFrom = new QComboBox();
    m_editTo = new QLineEdit();
    m_editInCopy = new QLineEdit();
    m_editInBlindCopy = new QLineEdit();
    m_editSubject = new QLineEdit();

    m_attachmentsContentLayout = new QHBoxLayout();
    m_attachmentsContentWidget = new QWidget();


    m_attachmentsLayout = new QVBoxLayout();
    m_attachmentsWidget = new QWidget();

    m_lblAttachments = new QLabel("Attachments:");
    m_attachmentsListView = new QListView();

    m_attachmentsButtonLayout = new QVBoxLayout();
    m_attachmentsButtonsWidget = new QWidget();

    m_btnAddAttachment = new QPushButton("+");
    m_btnRemoveAttachment = new QPushButton("-");

    m_editMessageContent = new QTextEdit();
    m_htmlContentView = new QWebEngineView();
}

void WriteMessageWindow::setUpWidgets()
{
    setWindowTitle("Write message");

    m_btnSend->setIcon(QIcon::fromTheme("mail-send"));
    m_btnAttachFile->setIcon(QIcon::fromTheme("mail-attachment"));
    m_btnSave->setIcon(QIcon::fromTheme("document-save"));

    m_messageActionsButtonsLayout->setAlignment(Qt::AlignLeft);

    m_attachmentsListView->setFixedWidth(m_attachmentsListView->sizeHint().width());
    m_messageInfoAndAttachmentsWidget->setFixedHeight(m_messageInfoAndAttachmentsWidget->sizeHint().height());

    m_attachmentsContentWidget->setFixedWidth(m_attachmentsContentWidget->sizeHint().width());
    m_attachmentsWidget->setFixedWidth(m_attachmentsWidget->sizeHint().width());

    m_editMessageContent->setContentsMargins(0, 0, 0, 0);
    m_htmlContentView->setContentsMargins(0, 0, 0, 0);

    QObject::connect(m_btnAttachFile,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnAddAttachmentClicked(bool)));

    QObject::connect(m_btnAddAttachment,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnAddAttachmentClicked(bool)));

    QObject::connect(m_btnRemoveAttachment,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnRemoveAttachmentClicked(bool)));

    QObject::connect(m_btnSend,
                     SIGNAL(clicked(bool)),
                     this,
                     SLOT(onBtnSendClicked(bool)));
}

void WriteMessageWindow::installLayouts()
{
    m_messageActionsButtonsLayout->addWidget(m_btnSend);
    m_messageActionsButtonsLayout->addWidget(m_btnAttachFile);
    m_messageActionsButtonsLayout->addWidget(m_btnSave);

    m_messageActionsButtonsWidget->setLayout(m_messageActionsButtonsLayout);
    ui->verticalLayout->addWidget(m_messageActionsButtonsWidget);

    m_messageInfoGridLayout->addWidget(m_lblFrom, 0, 0, 1, 1);
    m_messageInfoGridLayout->addWidget(m_lblTo, 1, 0, 1, 1);
    m_messageInfoGridLayout->addWidget(m_lblInCopy, 2, 0, 1, 1);
    m_messageInfoGridLayout->addWidget(m_lblInBlindCopy, 3, 0, 1, 1);
    m_messageInfoGridLayout->addWidget(m_lblSubject, 4, 0, 1, 1);

    m_messageInfoGridLayout->addWidget(m_comboBoxFrom, 0, 1, 1, 1);
    m_messageInfoGridLayout->addWidget(m_editTo, 1, 1, 1, 1);
    m_messageInfoGridLayout->addWidget(m_editInCopy, 2, 1, 1, 1);
    m_messageInfoGridLayout->addWidget(m_editInBlindCopy, 3, 1, 1, 1);
    m_messageInfoGridLayout->addWidget(m_editSubject, 4, 1, 1, 1);

    m_messageInfoGridWidget->setLayout(m_messageInfoGridLayout);

    m_messageInfoAndAttachmentsLayout->addWidget(m_messageInfoGridWidget);

    m_attachmentsButtonLayout->addWidget(m_btnAddAttachment);
    m_attachmentsButtonLayout->addWidget(m_btnRemoveAttachment);
    m_attachmentsButtonsWidget->setLayout(m_attachmentsButtonLayout);

    m_attachmentsContentLayout->addWidget(m_attachmentsListView);
    m_attachmentsContentLayout->addWidget(m_attachmentsButtonsWidget);
    m_attachmentsContentWidget->setLayout(m_attachmentsContentLayout);

    m_attachmentsLayout->addWidget(m_lblAttachments);
    m_attachmentsLayout->addWidget(m_attachmentsContentWidget);
    m_attachmentsWidget->setLayout(m_attachmentsLayout);

    m_messageInfoAndAttachmentsLayout->addWidget(m_attachmentsWidget);

    m_messageInfoAndAttachmentsWidget->setLayout(m_messageInfoAndAttachmentsLayout);

    ui->verticalLayout->addWidget(m_messageInfoAndAttachmentsWidget);
    ui->verticalLayout->addWidget(m_editMessageContent);
    ui->verticalLayout->addWidget(m_htmlContentView);
}

void WriteMessageWindow::setWindowContent(const Message message)
{
    m_message = message;

    setSenderIndex();
    setSubject();
    setPlainTextAndHtmlText();
    setRecipients();
    setAttachments();
    setEmbeddedObjects();
}

void WriteMessageWindow::setPlainTextAndHtmlText()
{
    if (m_mode == Mode::Reply || m_mode == Mode::ReplyAll || m_mode == Mode::Forward)
    {
        m_htmlContentView->setVisible(true);

        if (m_message.htmlContent() != QString())
        {
            setHtmlContent(m_message.htmlContent());
        }
        else
        {
            setHtmlContent(m_message.plainTextContent());
        }
    }
}

void WriteMessageWindow::setHtmlContent(QString content)
{
    if (m_mode == Mode::Forward)
    {
        QString forwardContent;

        forwardContent.append("--------Forwarded Message--------<br>");
        forwardContent.append("<b>Subject:</b> " + m_message.subject() + "<br>");
        forwardContent.append("<b>Date:</b> " + m_message.dateTime().toString(Constants::DATETIME_FORMAT) + "<br>");
        forwardContent.append("<b>From:</b> " + m_message.sender().name() + " <" + m_message.sender().emailAddress() + ">" + "<br>");
        forwardContent.append("<b>To:</b> ");

        QString recipients = Contact::toString(m_message.addressListTo());
        recipients.replace("<", "&lt;");
        recipients.replace(">", "&gt;");

        forwardContent.append(recipients);
        forwardContent.append(content);

        m_htmlContent = forwardContent;
        m_htmlContentView->setHtml(forwardContent);

    }
    else if (m_mode == Mode::Reply || m_mode == Mode::ReplyAll)
    {
        QString replyHtmlContent;

        replyHtmlContent.append("<p>On ");

        replyHtmlContent.append(m_message.dateTime().toString(Constants::DATETIME_FORMAT));
        replyHtmlContent.append(", ");

        QString sender = Contact::toString(m_message.sender());

        sender.replace("<", "&lt;");
        sender.replace(">", "&gt;");

        replyHtmlContent.append(sender);
        replyHtmlContent.append(" wrote:<br></p>");

        replyHtmlContent.append("<div style=\"border-left: thick solid #201e50; margin-left: 15px;\">");
        replyHtmlContent.append(content);
        replyHtmlContent.append("</div>");

        m_htmlContent = replyHtmlContent;
        m_htmlContentView->setHtml(replyHtmlContent);
    }
}

void WriteMessageWindow::setRecipients()
{
    QString recipients;

    if (m_mode != Mode::Forward && m_mode != Mode::WriteMessage)
    {
        if (!m_message.replyTo().isEmpty())
        {
            recipients.append(Contact::toString(m_message.replyTo()));
        }
        else
        {
            recipients.append(Contact::toString(m_message.sender()));
        }

        if (m_mode == Mode::ReplyAll)
        {
            if (m_message.addressListTo().size() > 1)
            {

                recipients.append(", ");

                for (int i = 0; i < m_message.addressListTo().size(); i++)
                {
                    Contact contact = m_message.addressListTo().at(i);

                    if (m_comboBoxFrom->currentText().contains(contact.emailAddress()))
                    {
                        continue;
                    }

                    recipients.append(Contact::toString(contact));

                    if (i < m_message.addressListTo().size() - 1)
                    {
                        recipients.append(", ");
                    }
                }
            }

            if (recipients.lastIndexOf(",") != recipients.size() - 2)
            {
                recipients.append(", ");
            }

            if (!m_message.addressListInCopy().isEmpty())
            {
                recipients.append(Contact::toString(m_message.addressListInCopy()));
            }
        }

        m_editTo->setText(recipients);
    }
}

void WriteMessageWindow::setSubject()
{
    if (m_mode == Mode::Forward)
    {
        setWindowTitle("Write: Fwd: " + m_message.subject());
        m_editSubject->setText("Fwd: " + m_message.subject());
    }
    else if (m_mode == Mode::Reply || m_mode == Mode::ReplyAll)
    {
        setWindowTitle("Write: Re: " + m_message.subject());
        m_editSubject->setText("Re: " + m_message.subject());
    }
    else if (m_mode == Mode::WriteMessage)
    {
        setWindowTitle("Write Message:");
    }
}

void WriteMessageWindow::setUserAccounts(QList<UserAccount> *userAccounts)
{
    m_userAccounts = userAccounts;
    m_userAccountsListModel = new UserAccountsListModel(*m_userAccounts);
    m_comboBoxFrom->setModel(m_userAccountsListModel);
}

void WriteMessageWindow::setSenderIndex()
{
    if (m_mode == Mode::Reply || m_mode == Mode::ReplyAll || m_mode == Mode::Forward)
    {
        QList<Contact> recipients = m_message.addressListTo();

        for (int i = 0; i < recipients.size(); i++)
        {
            for (int j = 0; j < m_userAccounts->size(); j++)
            {
                if (recipients.at(i).emailAddress() == m_userAccounts->at(j).emailAddress())
                {
                    m_comboBoxFrom->setCurrentIndex(j);
                    m_comboBoxFrom->setEnabled(false);
                }
            }
        }
    }
}

void WriteMessageWindow::setSenderComboBoxEditable(bool value)
{
    m_comboBoxFrom->setEnabled(value);
}

void WriteMessageWindow::setAttachments()
{
    m_attachments = m_message.attachments();
    m_attachmentsListModel = new AttachmentsListModel(m_attachments);
    m_attachmentsListView->setModel(m_attachmentsListModel);

    if (m_attachments.size() <= 0)
    {
        m_attachmentsWidget->setVisible(false);
    }
    else
    {
        m_attachmentsWidget->setVisible(true);
    }
}

void WriteMessageWindow::onBtnAddAttachmentClicked(bool)
{
    QFileDialog dialog;
    QString defaultPath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();
    dialog.setDirectory(defaultPath);
    dialog.setWindowTitle("Choose attachments");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);

    if (dialog.exec() == QDialog::Accepted)
    {
        QStringList fileNames = dialog.selectedFiles();

        for (QString fileName : fileNames)
        {
            if (fileName != QString())
            {
                QString name = fileName.split("/").last();

                QFile file(fileName);
                file.open(QIODevice::ReadOnly);


                if (file.size() > Constants::ATTACHMENT_MAXIMUM_SIZE_IN_MB * 1024 * 1024)
                {
                    QMessageBox messageBox;
                    messageBox.setWindowTitle("Error while adding the attachment");
                    messageBox.setText("Error: File is too big. Maximum allowed size is " + QString::number(Constants::ATTACHMENT_MAXIMUM_SIZE_IN_MB) + " MB");
                    messageBox.setIcon(QMessageBox::Warning);
                    messageBox.exec();
                    return;
                }

                QMimeDatabase mimeDatabase;
                QMimeType mimeType = mimeDatabase.mimeTypeForFile(fileName);

                QByteArray data = file.readAll();
                file.close();

                Attachment attachment;
                attachment.setData(data);
                attachment.setMimeType(mimeType.name());
                attachment.setName(name);

                m_attachments.push_back(attachment);
            }
        }

        m_attachmentsListModel = new AttachmentsListModel(m_attachments);
        m_attachmentsListView->setModel(m_attachmentsListModel);

        if (m_attachments.size() > 0)
        {
            m_attachmentsWidget->setVisible(true);
        }
    }
}

void WriteMessageWindow::onBtnRemoveAttachmentClicked(bool)
{
    QItemSelectionModel *selectionModel = m_attachmentsListView->selectionModel();

    if (selectionModel->hasSelection())
    {
        int index = selectionModel->selectedRows().at(0).row();
        m_attachmentsListModel->removeRows(index, 1);
    }

    if (m_attachments.size() == 0)
    {

        m_attachmentsWidget->setVisible(false);
    }
}

void WriteMessageWindow::setEmbeddedObjects()
{
    m_embeddedObjects = m_message.embeddedObjects();
}

QRegExp WriteMessageWindow::getEmailAddressRegexPattern() const
{
    QRegExp emailAddressRegexPattern("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    emailAddressRegexPattern.setCaseSensitivity(Qt::CaseInsensitive);
    emailAddressRegexPattern.setPatternSyntax(QRegExp::RegExp);

    return emailAddressRegexPattern;
}

QList<Contact> WriteMessageWindow::parseContacts(const QString rawdata) const
{
    QList<Contact> contacts;
    QStringList contactsData;

    if (!rawdata.contains(","))
    {
        contactsData << rawdata;
    }
    else
    {
        contactsData = rawdata.split(",");
    }

    for (QString contactData : contactsData)
    {
        QRegExp emailAddressRegex = getEmailAddressRegexPattern();
        emailAddressRegex.indexIn(contactData);

        if (emailAddressRegex.capturedTexts().last() != QString())
        {
            Contact contact;
            contact.setEmailAddress(emailAddressRegex.capturedTexts().last());
            contacts.append(contact);
        }
        else
        {
            qWarning() << "Failed to parse contact: " << contactData;
            return QList<Contact>();
        }
    }

    return contacts;
}

void WriteMessageWindow::onBtnSendClicked(bool checked)
{
    // sender
    Contact sender;
    sender.setEmailAddress(m_userAccounts->at(m_comboBoxFrom->currentIndex()).emailAddress());
    sender.setName(m_userAccounts->at(m_comboBoxFrom->currentIndex()).contactName());

    // to

    QList<Contact> recipients = parseContacts(m_editTo->text());

    if (recipients.isEmpty())
    {
        qWarning() << "Failed to parse recipients";
        close();
        return;
    }

    // in copy

    QList<Contact> copyRecipients;

    if (m_editInCopy->text() != QString())
    {
        copyRecipients = parseContacts(m_editInCopy->text());

        if (copyRecipients.isEmpty())
        {
            qWarning() << "Failed to parse copy recipients";
            close();
            return;
        }
    }

    // in blind copy

    QList<Contact> blindCopyRecipients;

    if (m_editInBlindCopy->text() != QString())
    {
        blindCopyRecipients = parseContacts(m_editInBlindCopy->text());

        if (blindCopyRecipients.isEmpty())
        {
            qWarning() << "Failed to parse blind copy recipients";
            close();
            return;
        }
    }

    // subject

    QString subject = m_editSubject->text();

    if (subject == QString())
    {
        qWarning() << "Subject cannot be empty";
        close();
        return;
    }
    else
    {
        qWarning() << "subject: " << subject;
    }

    // content

    QString plainTextContent;
    QString htmlContent;

    if (!m_htmlContentView->isVisible())
    {
        plainTextContent = m_editMessageContent->toPlainText();
    }
    else
    {
        htmlContent.append(m_editMessageContent->toHtml());
        htmlContent.append(m_htmlContent);

        plainTextContent.append(m_editMessageContent->toPlainText());

        QTextEdit textEdit;
        textEdit.setHtml(m_htmlContent);

        plainTextContent.append(textEdit.toPlainText());
    }

    Message message;
    message.setSender(sender);
    message.setAddressListTo(recipients);
    message.setAddressListInCopy(copyRecipients);
    message.setAddressListInBlindCopy(blindCopyRecipients);
    message.setSubject(subject);
    message.setPlainTextContent(plainTextContent);
    message.setHtmlContent(htmlContent);
    message.setDateTime(QDateTime::currentDateTime());
    message.setAttachments(m_attachments);
    message.setEmbeddedObjects(m_embeddedObjects);

    int senderId = m_comboBoxFrom->currentIndex();
    m_userAccounts->at(senderId).sendMessage(message);
    close();
}
