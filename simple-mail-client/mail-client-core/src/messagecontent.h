#ifndef MESSAGECONTENT_H
#define MESSAGECONTENT_H

#include <QObject>
#include "src/attachment.h"
#include "src/contact.h"
#include "embeddedobject.h"

class MessageContent : public QObject
{
    Q_OBJECT
public:
    explicit MessageContent(QObject *parent = nullptr)
        :QObject(parent) {}

    MessageContent(const MessageContent &other);

    MessageContent &operator=(const MessageContent &other);
    bool operator==(const MessageContent &other);
    bool operator!=(const MessageContent &other);
    bool operator==(MessageContent &other);
    bool operator!=(MessageContent &other);

    QString htmlContent() const;
    void setHtmlContent(const QString htmlContent);

    QString plainTextContent() const;
    void setPlainTextContent(const QString plainTextContent);

    QList<Attachment> attachments() const;
    void setAttachments(const QList<Attachment> attachments);

    QList<EmbeddedObject> embeddedObjects() const;
    void setEmbeddedObjects(const QList<EmbeddedObject> embeddedObjects);

    QList<Contact> recipients() const;
    void setRecipients(const QList<Contact> recipients);

    QList<Contact> copyRecipients() const;
    void setCopyRecipients(const QList<Contact> copyRecipients);

    QList<Contact> blindCopyRecipients() const;
    void setBlindCopyRecipients(const QList<Contact> blindCopyRecipients);

signals:

public slots:

private:
    QString m_htmlContent;
    QString m_plainTextContent;

    QList<Attachment> m_attachments;
    QList<EmbeddedObject> m_embeddedObjects;

    QList<Contact> m_recipients;
    QList<Contact> m_copyRecipients;
    QList<Contact> m_blindCopyRecipients;
};

QDebug operator<<(QDebug debug, const MessageContent &messageContent);

#endif // MESSAGECONTENT_H
