#ifndef NEWFOLDERDIALOG_H
#define NEWFOLDERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class NewFolderDialog;
}

class NewFolderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFolderDialog(QWidget *parent = nullptr);
    ~NewFolderDialog();

    QString getFolderName() const;

private slots:
    void editNameTextEdited(const QString &);

private:
    Ui::NewFolderDialog *ui;
};

#endif // NEWFOLDERDIALOG_H
