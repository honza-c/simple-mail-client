#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeStructures();
    createTestUserAccounts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeStructures()
{
    usersModel = new UserAccountsListModel(users);
}

void MainWindow::createTestUserAccounts()
{
    UserAccount u1;
    UserAccount u2;
    UserAccount u3;

    u1.setAccountName("Account 1");
    u1.setYourName("John Doe");
    u1.setEmailAddress("j.doe@example.com");
    u1.setPassword("pass");
    u1.setSmtpServerUrl("smtp://example.com");
    u1.setPopServerUrl("pop3://example.com");
    u1.setSmtpServerPort(666);
    u1.setPopServerPort(999);

    u2.setAccountName("Account 2");
    u2.setYourName("John Doe");
    u2.setEmailAddress("john.doe@example.com");
    u2.setPassword("password");
    u2.setSmtpServerUrl("smtp://example.com");
    u2.setPopServerUrl("pop3://example.com");
    u2.setSmtpServerPort(666);
    u2.setPopServerPort(999);

    u3.setAccountName("Account 3");
    u3.setYourName("John Doe");
    u3.setYourName("doe.j@example.com");
    u3.setPassword("Pass1234");
    u3.setSmtpServerUrl("smtp://example.com");
    u3.setSmtpServerPort(666);
    u3.setPopServerPort(999);

    users << u1 << u2 << u3;
}
