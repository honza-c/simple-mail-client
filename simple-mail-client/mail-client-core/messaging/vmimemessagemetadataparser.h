#ifndef VMIMEMESSAGEMETADATAPARSER_H
#define VMIMEMESSAGEMETADATAPARSER_H

#include <QObject>
#include <vmime/vmime.hpp>
#include "messagemetadata.h"


class VmimeMessageMetadataParser : public QObject
{
    Q_OBJECT
public:
    explicit VmimeMessageMetadataParser(QString emailAddress, QString path, QObject *parent = nullptr);

    MessageMetadata parse(vmime::shared_ptr<vmime::net::message> message);

    QString getEmailAddress();
    QString getPath();
    void setEmailAddress(QString emailAddress);
    void setPath(QString path);
signals:

public slots:

private:
    QString vmimeDecodedStringToQString(vmime::string input);
    QString parseSubject(vmime::shared_ptr<const vmime::header> header);
    QString parseFromName(vmime::shared_ptr<const vmime::header> header);
    QString parseFromEmail(vmime::shared_ptr<const vmime::header> header);
    QDateTime parseDateTime(vmime::shared_ptr<const vmime::header> header);
    QString parseRecipients(vmime::shared_ptr<const vmime::header> header);
    QString parseInCopy(vmime::shared_ptr<const vmime::header> header);
    QRegExp getEmailAddressRegexPattern();
    int getTimeZoneOffsetInUnixTime(QString timezone);

    QString emailAddress;
    QString path;
};

#endif // VMIMEMESSAGEMETADATAPARSER_H
