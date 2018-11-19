#include "attachment.h"

Attachment::Attachment(const Attachment &other)
{
    m_name = other.m_name;
    m_mimeType = other.m_mimeType;
    m_data = other.m_data;
}

Attachment& Attachment::operator=(const Attachment &other)
{
    m_name = other.m_name;
    m_mimeType = other.m_mimeType;
    m_data = other.m_data;

    return *this;
}

bool Attachment::operator==(const Attachment &other)
{
    return (m_name == other.m_name) && (m_data == other.m_data) && (m_mimeType == other.m_mimeType);
}

bool Attachment::operator!=(const Attachment &other)
{
    return (m_name != other.m_name) || (m_data != other.m_data) || (m_mimeType != other.m_mimeType);
}

QString Attachment::name() const
{
    return m_name;
}

QString Attachment::mimeType() const
{
    return m_mimeType;
}

QByteArray Attachment::data() const
{
    return m_data;
}

void Attachment::setName(const QString name)
{
    m_name = name;
}

void Attachment::setMimeType(const QString mimeType)
{
    m_mimeType = mimeType;
}

void Attachment::setData(const QByteArray data)
{
    m_data = data;
}

QDebug operator <<(QDebug debug, const Attachment &attachment)
{
    QDebugStateSaver saver(debug);
    debug.noquote() << "Name: " << attachment.name() << " MimeType: " << attachment.mimeType() << " Data: " << attachment.data();

    return debug;
}

QDataStream& operator<<(QDataStream &dataStream, const Attachment &attachment)
{
    dataStream << attachment.name() << attachment.mimeType() << attachment.data();

    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, Attachment &attachment)
{
    QString name;
    QString mimeType;
    QByteArray data;

    dataStream >> name >> mimeType >> data;

    attachment.setName(name);
    attachment.setMimeType(mimeType);
    attachment.setData(data);

    return dataStream;
}
