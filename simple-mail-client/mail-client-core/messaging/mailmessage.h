#ifndef MAILMESSAGE_H
#define MAILMESSAGE_H

#include <QObject>

class MailMessage : public QObject
{
    Q_OBJECT
public:
    explicit MailMessage(QObject *parent = nullptr) {}
    MailMessage(const MailMessage &other);
    MailMessage &operator=(const MailMessage &other);
    operator QString() const;

    void setSubject(QString subject);
    void setMessageContent(QString messageContent);
    void setAddressListTo(QStringList addressListTo);
    void setAddressListBlindCopy(QStringList addressListBlindCopy);

    QString getSubject();
    QString getMessageContent();
    QStringList getAddressListTo();
    QStringList getAddressListBlindCopy();

signals:

public slots:

private:
    QString subject;
    QString messageContent;
    QStringList addressListTo;
    QStringList addressListBlindCopy;
};

#endif // MAILMESSAGE_H
