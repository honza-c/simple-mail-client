#include "embeddedobject.h"

EmbeddedObject::EmbeddedObject(const EmbeddedObject &other)
{
    m_name = other.m_name;
    m_mimeType = other.m_mimeType;
    m_contentId = other.m_contentId;
    m_data = other.m_data;
}

EmbeddedObject& EmbeddedObject::operator=(const EmbeddedObject &other)
{
    m_name = other.m_name;
    m_mimeType = other.m_mimeType;
    m_contentId = other.m_contentId;
    m_data = other.m_data;

    return *this;
}

bool EmbeddedObject::operator==(const EmbeddedObject &other)
{
    return m_name == other.m_name &&
           m_mimeType == other.m_mimeType &&
           m_contentId == other.m_contentId &&
           m_data == other.m_data;
}

bool EmbeddedObject::operator!=(const EmbeddedObject &other)
{
    return m_name != other.m_name ||
            m_mimeType != other.m_mimeType ||
            m_contentId != other.m_contentId ||
            m_data != other.m_data;
}

QString EmbeddedObject::contentId() const
{
    return m_contentId;
}

void EmbeddedObject::setContentId(const QString contentId)
{
    m_contentId = contentId;
}

QDebug operator <<(QDebug debug, const EmbeddedObject &embeddedObject)
{
    QDebugStateSaver saver(debug);

    debug.noquote() << "Name: " << embeddedObject.name()
                    << "\nMimeType: " << embeddedObject.mimeType()
                    << "\nContentId: " << embeddedObject.contentId()
                    << "\nData: " << embeddedObject.data();

    return debug;
}

QDataStream& operator<<(QDataStream &dataStream, const EmbeddedObject &embeddedObject)
{
    dataStream << embeddedObject.name()
               << embeddedObject.mimeType()
               << embeddedObject.contentId()
               << embeddedObject.data();

    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, EmbeddedObject &embeddedObject)
{
    QString name;
    QString mimeType;
    QString contentId;
    QByteArray data;

    dataStream >> name >> mimeType >> contentId >> data;

    embeddedObject.setName(name);
    embeddedObject.setMimeType(mimeType);
    embeddedObject.setContentId(contentId);
    embeddedObject.setData(data);

    return dataStream;
}
