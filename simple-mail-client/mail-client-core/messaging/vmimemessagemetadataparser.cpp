#include "vmimemessagemetadataparser.h"

VmimeMessageMetadataParser::VmimeMessageMetadataParser(QObject *parent) : QObject(parent)
{

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

    msgMetadata.setDate(vmimeDecodedStringToQString(header->Date()->generate()));
    msgMetadata.setFrom(vmimeDecodedStringToQString(header->From()->generate()));
    msgMetadata.setSize(message->getSize());
    msgMetadata.setSubject(vmimeDecodedStringToQString(header->Subject()->generate()));
    msgMetadata.setSender(vmimeDecodedStringToQString(header->Sender()->generate()));
    msgMetadata.setTo(vmimeDecodedStringToQString(header->To()->generate()));

    return msgMetadata;
}

QString VmimeMessageMetadataParser::vmimeDecodedStringToQString(vmime::string input)
{
    vmime::text output;
    vmime::text::decodeAndUnfold(input, &output);
    return QString(output.getConvertedText(vmime::charsets::UTF_8).c_str());
}
