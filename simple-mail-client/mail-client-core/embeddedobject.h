#ifndef EMBEDDEDOBJECT_H
#define EMBEDDEDOBJECT_H

#include <QObject>
#include "src/attachment.h"

class EmbeddedObject : public Attachment
{
    Q_OBJECT
public:
    EmbeddedObject(QObject *parent = nullptr)
        : Attachment(parent) {}

    EmbeddedObject(const EmbeddedObject &other);
    EmbeddedObject &operator=(const EmbeddedObject &other);
    bool operator==(const EmbeddedObject &other);
    bool operator!=(const EmbeddedObject &other);

    QString contentId() const;
    void setContentId(const QString contentId);

signals:

public slots:

private:
    QString m_contentId;
};

QDebug operator <<(QDebug debug, const EmbeddedObject &embeddedObject);
QDataStream& operator<<(QDataStream &dataStream, const EmbeddedObject &embeddedObject);
QDataStream& operator>>(QDataStream &dataStream, EmbeddedObject &embeddedObject);

#endif // EMBEDDEDOBJECT_H
