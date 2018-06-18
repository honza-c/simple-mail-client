#ifndef VMIMEMESSAGECONTENTPARSER_H
#define VMIMEMESSAGECONTENTPARSER_H

#include <QObject>
#include <vmime/vmime.hpp>

class VmimeMessageContentParser : public QObject
{
    Q_OBJECT
public:
    explicit VmimeMessageContentParser(QObject *parent = nullptr)
        : QObject(parent) {}

    QString parseHtmlContent(vmime::shared_ptr<vmime::message> message);
    QString parsePlainTextContent(vmime::shared_ptr<vmime::message> message);

signals:

public slots:

private:
    QString parseTextParts(vmime::shared_ptr<vmime::message> message, const char *type);
};

#endif // VMIMEMESSAGECONTENTPARSER_H
