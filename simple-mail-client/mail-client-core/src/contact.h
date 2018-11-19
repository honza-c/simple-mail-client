#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class Contact : public QObject
{
    Q_OBJECT
public:
    explicit Contact(QObject *parent = nullptr)
        : QObject(parent) {}

    Contact(const Contact &other);
    Contact &operator=(const Contact &other);

    QString name() const;
    void setName(const QString name);

    QString emailAddress() const;
    void setEmailAddress(const QString emailAddress);

    static QString toString(const Contact contact);
    static QString toString(const QList<Contact> contacts);

    static Contact contactFromJson(QString jsonString);
    static QString toJson(Contact contact);
    static QList<Contact> contactsFromJson(QString jsonString);
    static QString toJson(QList<Contact> contacts);
signals:

public slots:

private:
    void readFromJson(const QJsonObject &json);
    void writeToJson(QJsonObject &json);

    QString m_name;
    QString m_emailAddress;
};

QDebug operator<<(QDebug debug, const Contact &contact);
bool operator==(const Contact first, const Contact second);

#endif // CONTACT_H
