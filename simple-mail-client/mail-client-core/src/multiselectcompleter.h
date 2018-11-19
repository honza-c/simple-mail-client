#ifndef MULTISELECTCOMPLETER_H
#define MULTISELECTCOMPLETER_H

#include <QObject>
#include <QCompleter>
#include <QLineEdit>

class MultiSelectCompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit MultiSelectCompleter(const QStringList &items, QObject *parent = nullptr)
        : QCompleter(items, parent) {}

    ~MultiSelectCompleter() {}

    QString pathFromIndex(const QModelIndex &index) const;
    QStringList splitPath(const QString &path) const;
};

#endif // MULTISELECTCOMPLETER_H
