#ifndef VMIMEMESSAGEMETADATAPARSER_H
#define VMIMEMESSAGEMETADATAPARSER_H

#include <QObject>
#include <vmime/vmime.hpp>
#include "src/messagemetadata.h"
#include "src/contact.h"

class VmimeMessageMetadataParser : public QObject
{
    Q_OBJECT
public:
    explicit VmimeMessageMetadataParser(QObject *parent = nullptr)
        : QObject(parent) {}

    MessageMetadata parse(const vmime::shared_ptr<vmime::net::message> message);

signals:

public slots:

private:
    QString vmimeDecodedStringToQString(vmime::string input);
    QString parseSubject(vmime::shared_ptr<const vmime::header> header);
    QString parseContactName(QString extractedHeader);
    QString parseContactEmailAddress(QString extractedHeader);
    QDateTime parseDateTime(vmime::shared_ptr<const vmime::header> header);
    QRegExp getEmailAddressRegexPattern() const;
    int getTimeZoneOffsetInUnixTime(const QString timezone);

    Contact parseExpeditor(vmime::shared_ptr<const vmime::header> header);
    QList<Contact> parseReplyTo(vmime::shared_ptr<const vmime::header> header);
};

#endif // VMIMEMESSAGEMETADATAPARSER_H
