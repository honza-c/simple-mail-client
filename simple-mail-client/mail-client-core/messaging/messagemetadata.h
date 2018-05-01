#ifndef MESSAGEMETADATA_H
#define MESSAGEMETADATA_H

#include <QObject>

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
    void setDate(QString date);
    void setFrom(QString from);
    void setSender(QString sender);
    void setSubject(QString subject);
    void setTo(QString to);
    void setIsDeleted(bool isDeleted);
    void setIsDraft(bool isDraft);
    void setIsRecent(bool isRecent);
    void setIsReplied(bool isReplied);
    void setIsSeen(bool isSeen);

    unsigned long getId();
    unsigned long getSize();
    QString getDate();
    QString getFrom();
    QString getSender();
    QString getSubject();
    QString getTo();
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
    QString date;
    QString from;
    QString sender;
    QString subject;
    QString to;
    bool isDeleted;
    bool isDraft;
    bool isRecent;
    bool isReplied;
    bool isSeen;
};

#endif // MESSAGEMETADATA_H
