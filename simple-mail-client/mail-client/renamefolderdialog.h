#ifndef RENAMEFOLDERDIALOG_H
#define RENAMEFOLDERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class RenameFolderDialog;
}

class RenameFolderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenameFolderDialog(QWidget *parent = nullptr);
    ~RenameFolderDialog();

    void setFolderName(const QString folderName);
    QString getFolderName() const;

private slots:
    void editNameTextEdited(const QString &);

private:
    Ui::RenameFolderDialog *ui;
};

#endif // RENAMEFOLDERDIALOG_H
