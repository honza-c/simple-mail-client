#ifndef ABSTRACTINBOXSERVICE_H
#define ABSTRACTINBOXSERVICE_H

#include "messagemetadata.h"

class AbstractInboxService : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractInboxService() {}
    virtual QList<MessageMetadata> getMessageMetadata() = 0;

signals:

public slots:
};

#endif // ABSTRACTINBOXSERVICE_H