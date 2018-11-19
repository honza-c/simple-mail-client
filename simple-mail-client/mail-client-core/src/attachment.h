#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QObject>
#include <QDataStream>
#include <QDebug>

class Attachment : public QObject
{
    Q_OBJECT
public:
    explicit Attachment(QObject *parent = nullptr)
        : QObject(parent) {}
    Attachment(const Attachment &other);
    Attachment &operator=(const Attachment &other);
    bool operator==(const Attachment &other);
    bool operator!=(const Attachment &other);

    QString name() const;
    QString mimeType() const;
    QByteArray data() const;

    void setName(const QString name);
    void setMimeType(const QString mimeType);
    void setData(const QByteArray data);
signals:

public slots:

protected:
    QString m_name;
    QString m_mimeType;
    QByteArray m_data;
};

QDebug operator <<(QDebug debug, const Attachment &attachment);
QDataStream& operator<<(QDataStream &dataStream, const Attachment &attachment);
QDataStream& operator>>(QDataStream &dataStream, Attachment &attachment);

#endif // ATTACHMENT_H
