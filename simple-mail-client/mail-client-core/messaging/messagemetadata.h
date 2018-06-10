#ifndef MESSAGEMETADATA_H
#define MESSAGEMETADATA_H

#include <QObject>
#include <QDateTime>

class MessageMetadata : public QObject
{
    Q_OBJECT
public:
    explicit MessageMetadata();
    MessageMetadata(const MessageMetadata &other);
    MessageMetadata &operator=(const MessageMetadata &other);
    operator QString() const;

    void setId(unsigned long id);
    void setSize(unsigned long size);
    void setDate(QDateTime date);
    void setFromName(QString fromName);
    void setFromAddress(QString fromAddress);
    void setSubject(QString subject);
    void setIsDeleted(bool isDeleted);
    void setIsDraft(bool isDraft);
    void setIsRecent(bool isRecent);
    void setIsReplied(bool isReplied);
    void setIsSeen(bool isSeen);

    unsigned long getId();
    unsigned long getSize();
    QDateTime getDate();
    QString getFromName();
    QString getFromAddress();
    QString getSubject();
    bool getIsDeleted();
    bool getIsDraft();
    bool getIsRecent();
    bool getIsReplied();
    bool getIsSeen();

signals:

public slots:

private:
    unsigned long id;
    unsigned long size;
    QDateTime date;
    QString fromName;
    QString fromAddress;
    QString subject;
    bool isDeleted;
    bool isDraft;
    bool isRecent;
    bool isReplied;
    bool isSeen;
};

#endif // MESSAGEMETADATA_H
