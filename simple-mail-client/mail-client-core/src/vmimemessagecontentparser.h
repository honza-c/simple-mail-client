#ifndef VMIMEMESSAGECONTENTPARSER_H
#define VMIMEMESSAGECONTENTPARSER_H

#include <QObject>
#include <QTextCodec>
#include <vmime/vmime.hpp>
#include "attachment.h"
#include "contact.h"
#include "embeddedobject.h"

class VmimeMessageContentParser : public QObject
{
    Q_OBJECT
public:
    explicit VmimeMessageContentParser(vmime::shared_ptr<vmime::message> message, QObject *parent = nullptr);

    QString parseHtmlContent() const;
    QString parsePlaintextContent() const;
    QList<Attachment> parseAttachments() const;
    QList<EmbeddedObject> parseEmbeddedObjects() const;
    QList<Contact> parseRecipients() const;
    QList<Contact> parseInCopyRecipients() const;
    QList<Contact> parseBlindCopyRecipients() const;

signals:

public slots:

private:
    QString parseTextParts(const char *type) const;
    QByteArray parseContentHandler(vmime::shared_ptr<const vmime::contentHandler> contentHandler) const;
    QList<Contact> parseContacts(const vmime::shared_ptr<vmime::address> address) const;

    std::vector<vmime::shared_ptr<const vmime::htmlTextPart::embeddedObject>> extractEmbeddedObjects() const;
    vmime::shared_ptr<vmime::message> m_message;
    vmime::shared_ptr<vmime::messageParser> m_messageParser;
};

#endif // VMIMEMESSAGECONTENTPARSER_H
