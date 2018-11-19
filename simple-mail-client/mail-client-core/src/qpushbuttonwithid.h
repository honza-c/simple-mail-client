#ifndef QPUSHBUTTONWITHID_H
#define QPUSHBUTTONWITHID_H

#include <QObject>
#include <QPushButton>

class QPushButtonWithId : public QPushButton
{
public:
    QPushButtonWithId() : QPushButton() {}
    QPushButtonWithId(QString name) : QPushButton(name) {}

    int id();
    void setId(int id);

private:
    int m_id;
};

#endif // QPUSHBUTTONWITHID_H
