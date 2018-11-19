#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDebug>
#include "src/attachment.h"
#include "src/contact.h"
#include "embeddedobject.h"
#include <QDateTime>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr) : QObject(parent) {}
    Message(const Message &other);
    Message &operator=(const Message &other);

    Contact sender() const;
    void setSender(const Contact sender);

    QString subject() const;
    void setSubject(const QString subject);

    QList<Contact> addressListTo() const;
    void setAddressListTo(const QList<Contact> addressListTo);

    QList<Contact> addressListInCopy() const;
    void setAddressListInCopy(const QList<Contact> addressListInCopy);

    QList<Contact> addressListInBlindCopy() const;
    void setAddressListInBlindCopy(const QList<Contact> addressListInBlindCopy);

    QList<Contact> replyTo() const;
    void setReplyTo(const QList<Contact> replyTo);

    QString plainTextContent() const;
    void setPlainTextContent(const QString plainTextContent);

    QString htmlContent() const;
    void setHtmlContent(const QString htmlContent);

    QList<Attachment> attachments() const;
    void setAttachments(const QList<Attachment> attachments);

    QList<EmbeddedObject> embeddedObjects() const;
    void setEmbeddedObjects(QList<EmbeddedObject> embeddedObjects);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime dateTime);

signals:

public slots:

private:
    Contact m_sender;
    QString m_subject;

    QList<Contact> m_addressListTo;
    QList<Contact> m_addressListInCopy;
    QList<Contact> m_addressListInBlindCopy;
    QList<Contact> m_addressListReplyTo;

    QString m_plainTextContent;
    QString m_htmlContent;

    QList<Attachment> m_attachments;
    QList<EmbeddedObject> m_embeddedObjects;

    QDateTime m_dateTime;
};

QDebug operator<<(QDebug debug, const Message &message);

#endif // MESSAGE_H
