#ifndef MAILMESSAGE_H
#define MAILMESSAGE_H

#include <QObject>

class MailMessage : public QObject
{
    Q_OBJECT
public:
    explicit MailMessage() {}
    MailMessage(const MailMessage &other);
    MailMessage &operator=(const MailMessage &other);
    operator QString() const;

    void setSubject(QString subject);
    void setMessageContent(QString messageContent);
    void setAddressListto(QStringList addressListTo);
    void setAddressListBlindCopyTo(QStringList addressListBlindCopoyTo);

    QString getSubject();
    QString getMessageContent();
    QStringList getAddressListTo();
    QStringList getAddressListBlindCopyTo();

signals:

public slots:

private:
    QString subject;
    QString messageContent;
    QStringList addressListTo;
    QStringList addressListBlindCopyTo;
};

#endif // MAILMESSAGE_H
