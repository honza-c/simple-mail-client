#ifndef WRITEMESSAGEWINDOW_H
#define WRITEMESSAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class WriteMessageWindow;
}

class WriteMessageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WriteMessageWindow(QWidget *parent = 0);
    ~WriteMessageWindow();

private:
    Ui::WriteMessageWindow *ui;
};

#endif // WRITEMESSAGEWINDOW_H
