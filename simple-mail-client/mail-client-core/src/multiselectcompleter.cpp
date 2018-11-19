#include "multiselectcompleter.h"

QString MultiSelectCompleter::pathFromIndex(const QModelIndex &index) const
{
    QString path = QCompleter::pathFromIndex(index);
    QString text = static_cast<QLineEdit*>(widget())->text();

    int position = text.lastIndexOf(",");

    if (position >= 0)
    {
        path = path.left(position) + ", " + path;
    }

    return path;
}

QStringList MultiSelectCompleter::splitPath(const QString &path) const
{
    int position = path.lastIndexOf(",") + 1;

    while (position < path.length() && path.at(position) == ' ')
    {
        position++;
    }

    return QStringList(path.mid(position));
}
