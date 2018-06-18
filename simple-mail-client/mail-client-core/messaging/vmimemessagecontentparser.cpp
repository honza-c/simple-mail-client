#include "vmimemessagecontentparser.h"

QString VmimeMessageContentParser::parseHtmlContent(vmime::shared_ptr<vmime::message> message)
{

    return parseTextParts(message, vmime::mediaTypes::TEXT_HTML);
}

QString VmimeMessageContentParser::parsePlainTextContent(vmime::shared_ptr<vmime::message> message)
{
    return parseTextParts(message, vmime::mediaTypes::TEXT_PLAIN);
}

QString VmimeMessageContentParser::parseTextParts(vmime::shared_ptr<vmime::message> message, const char *type)
{
    vmime::messageParser messageParser(message);
    QString result;

    for (vmime::size_t i = 0; i < messageParser.getTextPartCount(); i++)
    {
        vmime::shared_ptr<const vmime::textPart> textPart = messageParser.getTextPartAt(i);

        if (textPart->getType().getSubType() == type)
        {
            vmime::string extractedText;
            vmime::utility::outputStreamStringAdapter exxtractedTextOutputStringAdapter(extractedText);
            textPart->getText()->extract(exxtractedTextOutputStringAdapter);
            result.append(extractedText.c_str());
        }
    }

    return result;
}
