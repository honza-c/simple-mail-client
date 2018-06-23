#include "vmimemessagemetadataparser.h"

VmimeMessageMetadataParser::VmimeMessageMetadataParser(QString emailAddress, QString path, QObject *parent)
    : QObject(parent)
{
    this->emailAddress = emailAddress;
    this->path = path;
}

void VmimeMessageMetadataParser::setEmailAddress(QString emailAddress)
{
    this->emailAddress = emailAddress;
}

void VmimeMessageMetadataParser::setPath(QString path)
{
    this->path = path;
}

QString VmimeMessageMetadataParser::getEmailAddress()
{
    return this->emailAddress;
}

QString VmimeMessageMetadataParser::getPath()
{
    return this->path;
}

MessageMetadata VmimeMessageMetadataParser::parse(vmime::shared_ptr<vmime::net::message> message)
{
    MessageMetadata msgMetadata;
    vmime::shared_ptr<const vmime::header> header = message->getHeader();

    msgMetadata.setId(message->getNumber());

    const int flags = message->getFlags();

    msgMetadata.setIsSeen(flags & vmime::net::message::FLAG_SEEN);
    msgMetadata.setIsDeleted(flags & vmime::net::message::FLAG_DELETED);
    msgMetadata.setIsRecent(flags & vmime::net::message::FLAG_RECENT);
    msgMetadata.setIsReplied(flags & vmime::net::message::FLAG_REPLIED);
    msgMetadata.setIsDraft(flags & vmime::net::message::FLAG_DRAFT);

    msgMetadata.setDate(parseDateTime(header));
    msgMetadata.setFromAddress(parseFromEmail(header));
    msgMetadata.setFromName(parseFromName(header));
    msgMetadata.setSize(message->getSize());
    msgMetadata.setSubject(parseSubject(header));

    msgMetadata.setFolderPath(this->path);
    msgMetadata.setEmailAddress(this->emailAddress);
    msgMetadata.setPlainTextContent("");
    msgMetadata.setHtmlContent("");
    msgMetadata.setRecipients(parseRecipients(header));
    msgMetadata.setInCopy(parseInCopy(header));

    return msgMetadata;
}

QString VmimeMessageMetadataParser::parseSubject(vmime::shared_ptr<const vmime::header> header)
{
    QString extractedSubject = vmimeDecodedStringToQString(header->Subject()->generate());

    // Extracted data is in format: "Subject: desired data..."
    // Removing "Subject: " from the extracted string

    return extractedSubject.right(extractedSubject.size() - 9);
}

QDateTime VmimeMessageMetadataParser::parseDateTime(vmime::shared_ptr<const vmime::header> header)
{
    QString extractedDate = vmimeDecodedStringToQString(header->Date()->generate());

    // extracted data is in format: "Date: desired data..."
    // removing "Date: " part from the extracted string
    extractedDate = extractedDate.right(extractedDate.size() - 6);

    // Date is in format ""Fri, 5 Aug 2011 05:22:45 -0700"
    // Extracting information about date and time without timezone
    QString dateTimeInformation = extractedDate.left(extractedDate.length() - 6);
    // Extracting just timezone information
    QString timeZoneInformation = extractedDate.right(5);

    QDateTime dateTime = QDateTime::fromString(dateTimeInformation, "ddd, d MMM yyyy HH:mm:ss");
    int timezoneOffset = getTimeZoneOffsetInUnixTime(timeZoneInformation);
    dateTime.setOffsetFromUtc(timezoneOffset);

    return dateTime;
}

int VmimeMessageMetadataParser::getTimeZoneOffsetInUnixTime(QString timezone)
{
    QChar sign = timezone[0];
    QString hoursStr = timezone.mid(1, 2);
    QString minutesStr = timezone.right(2);

    int offset = minutesStr.toInt() * 60 + hoursStr.toInt() * 3600;

    if (sign == '-')
    {
        offset = -offset;
    }

    return offset;
}

QRegExp VmimeMessageMetadataParser::getEmailAddressRegexPattern()
{
    QRegExp emailAddressRegexPattern("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    emailAddressRegexPattern.setCaseSensitivity(Qt::CaseInsensitive);
    emailAddressRegexPattern.setPatternSyntax(QRegExp::RegExp);

    return emailAddressRegexPattern;
}

QString VmimeMessageMetadataParser::parseFromName(vmime::shared_ptr<const vmime::header> header)
{
    QString extractedFromHeader = vmimeDecodedStringToQString(header->From()->generate());

    // extracted data is in format: "From: desired data..."
    // removing "From: " part from the extracted string
    extractedFromHeader = extractedFromHeader.right(extractedFromHeader.size() - 6);

    QRegExp emailAddressRegex = getEmailAddressRegexPattern();
    emailAddressRegex.indexIn(extractedFromHeader);
    QStringList capturedEmailAddresses = emailAddressRegex.capturedTexts();

    // if From header is in format "From: john.doe@example.com" return this address as name
    if (capturedEmailAddresses.last() == extractedFromHeader)
    {
        return extractedFromHeader;
    }

    // if From header is in format "From: John Doe <john.doe@example.com>"
    // or "From: "John Doe" <john.doe@example.com>"
    // remove part with e-mail address and keep only the name
    QString fromName = extractedFromHeader.left(extractedFromHeader.lastIndexOf(' '));

    // if the are at the name's begin and end quoted marks, remove them and return name
    if (fromName.at(0) == '"' && fromName.at(fromName.length() - 1) == '"')
    {
        return fromName.mid(1, fromName.length() - 2);
    }

    // else name isn't covered with quote marks, so return it as it is
    return fromName;
}

QString VmimeMessageMetadataParser::parseFromEmail(vmime::shared_ptr<const vmime::header> header)
{
    QString extractedFromHeader = vmimeDecodedStringToQString(header->From()->generate());

    QRegExp emailAddressRegex = getEmailAddressRegexPattern();
    emailAddressRegex.indexIn(extractedFromHeader);
    QStringList capturedEmailAddresses = emailAddressRegex.capturedTexts();

    return capturedEmailAddresses.last();
}


QString VmimeMessageMetadataParser::vmimeDecodedStringToQString(vmime::string input)
{
    vmime::text output;
    vmime::text::decodeAndUnfold(input, &output);
    return QString(output.getConvertedText(vmime::charsets::UTF_8).c_str());
}

QString VmimeMessageMetadataParser::parseRecipients(vmime::shared_ptr<const vmime::header> header)
{
    QString extractedRecipients = vmimeDecodedStringToQString(header->To()->generate());

    // Extracted data is in format: "To: desired data..."
    // Removing "To: " from the extracted string

    return extractedRecipients.right(extractedRecipients.size() - 4);
}

QString VmimeMessageMetadataParser::parseInCopy(vmime::shared_ptr<const vmime::header> header)
{
    if (header->hasField("Cc"))
    {
        QString extractedInCopy = vmimeDecodedStringToQString(header->Cc()->generate());
        return extractedInCopy;
    }
    else
    {
        return "";
    }
}
