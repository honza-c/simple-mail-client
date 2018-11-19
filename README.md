# Simple Mail Client
This repository contains `simple-mail-client`, a simple Qt/C++ GUI application for reading and writing e-mail messages. The final goal is to use this prototype as e-mail plugin to Otter Browser, which is also goal of my bachelor thesis. Application is tested on Linux operating system, there is not used any platform dependent code, so the program should work on MS Windows and Mac OS X too.


![screenshot](https://files.culik.net/simple-mail-client-1.png "screenshot")
![screenshot](https://files.culik.net/simple-mail-client-2.png "screenshot")
![screenshot](https://files.culik.net/simple-mail-client-3.png "screenshot")

## Basic features
- Support for multiple e-mail accounts via POP3 and IMAP protocols: displaying messages accross folders, fulltext search
- Sending (replying, forwarding) messages via SMTP protocol
- All program data is stored in SQLite database (except user accounts cofiguration, which is stored in XML file)
- All network requests are executed in threads
- Downloading and sending attachments
- Displaying embedded objects content in HTML messages
- Notifications about unread messages in window title and folder tree view + messagebox, when a new message is received

## What needs to be done
- Support for moving, copying and deleting messages (GUI is done)
- Support for creating and deleting folders (GUI is done)
- tags
- drafts
- error handling
- refactoring
- bugfixing

## Dependencies
List of external components and libraries:
- Qt framework
- VMime: C++ library providing the interface to e-mail protocols
- Crypto++: C++ library for encryption / decryption, here used for encrypted storing user passwords in the configuration file.

## Install dependencies on Fedora Linux
- Install C/C++ development tools, sendmail, OpenSSL, SASL and TLS libraries:
```
sudo dnf install cmake? libgsasl libgsasl-devel gnutls-devel openssl-devel sendmail
sudo dnf install @development-tools
sudo dnf group install "C Development Tools and Libraries"
```

- install Qt framework:
```
sudo dnf install qt5*-devel
sudo dnf install qt-creator
```

- install Crypto++ library:

```
sudo dnf install cryptopp cryptopp-devel
```

- Download and install newest stable version of vmime library:

```
wget https://github.com/kisli/vmime/archive/v0.9.2.tar.gz
tar -xf v0.9.2.tar.gz
mkdir vmime-0.9.2/build
cd vmime-0.9.2/build
cmake -DVMIME_BUILD_SAMPLES=OFF -DVMIME_SHARED_PTR_USE_BOOST=OFF -DVMIME_SHARED_PTR_USE_CXX=ON -DVMIME_SENDMAIL_PATH=/run/sendmail -DCMAKE_BUILD_TYPE=RELEASE ..
make
sudo make install
sudo ldconfig /usr/local/lib64
```

## Install dependencies on Debian GNU/Linux
TODO

## Chaning constant values before the build
In `simple-mail-client/mail-client/constants.h` file are placed some constant values you may want to change before the build:
```
    // filename constants for files used in application
    const QString ERROR_LOG_FILE_NAME = "error.log";
    const QString USER_ACCOUNT_SETTINGS_FILE = "users.xml";
    const QString DATABASE_FILE_NAME = "database.sqlite";

    // password encryption keys
    const QString PASSWORD_AES_CBC_ENCRYPTION_KEY = "1234567890123456789012345678901234567890123456789012345678901234";
    const QString PASSWORD_AES_CBC_ENCRYPTION_IV = "1111111111222222222233333333334444444444555555555566666666667777";
```
- `ERROR_LOG_FILE_NAME` is the name of the file, where error log is located. Default file name is `error.log` and its default location is in the same folder where the binary of client application is.
- `USER_ACCOUNT_SETTINGS_FILE` is the name of the XML file, where the configuration of user accounts is stored. Default file name is `users.xml` and its default location is in the same folder where the binary of client application is.
- `DATABASE_FILE_NAME` is the name of the .sqlite file, where is the database data stored.
- `PASSWORD_AES_CBC_ENCRYPTION_KEY` and `PASSWORD_AES_CBC_ENCRYPTION_IV` are the vaules that are used for encrypting and decrypting the user passwords, that are stored in the `USER_ACCOUNT_SETTINGS_FILE`. It is strongly recommended to change default values before the build.

In `simple-mail-client/mail-client-core/src/logger.cpp` is function to handle logging. Default behavior is that every log level information is printed into `std::err` stream and information with `Critical` and `Fatal` log levels are stored in `ERROR_LOG_FILE_NAME` file. You may want to change the behavior of the logger:

```
void Tools::Utils::customLogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile logFile(Constants::ERROR_LOG_FILE_NAME);
    QTextStream errorLogStream(&logFile);
    QString logLine;
    QString currentDate = QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:s");
    QByteArray localMsg = msg.toLocal8Bit();

    switch (type)
    {
    case QtDebugMsg:
        logLine = QString("%1 Debug: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        break;
    case QtInfoMsg:
        logLine = QString("%1 Info: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        break;
    case QtWarningMsg:
        logLine = QString("%1 Warning: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        break;
    case QtCriticalMsg:
        logLine = QString("%1 Critical: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
        errorLogStream << logLine;
        logFile.close();
        break;
    case QtFatalMsg:
        logLine = QString("%1 Fatal: %2 in %3, function %4 on line %5 %6").arg(currentDate).arg(localMsg.constData()).arg(context.file).arg(context.function).arg(context.line).arg('\n');
        fprintf(stderr, logLine.toStdString().c_str());
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
        errorLogStream << logLine;
        logFile.close();
        abort();
    }
}
```

## Build Simple Mail Client on Linux
Path to `qmake` binary may differ on your system. In my case I have Qt framework from official installer installed in /opt directory and I use 5.10.1 version. If you use Qt framework from packages provided by your distribution, calling just `qmake` without the absolute path should be good enough.

```bash
git clone https://github.com/honza-c/simple-mail-client
mkdir simple-mail-client/build
cd simple-mail-client/build
/opt/Qt/5.10.1/gcc_64/bin/qmake ../simple-mail-client/simple-mail-client.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug && /usr/bin/make qmake_all
/usr/bin/make
```
or open `simple-mail-client/simple-mail-client.pro` in QtCreator and hit the run button.

## Location of build artefacts
- Location of static library `mail-client-core` is `build/mail-client-core/libmailclient-core.a`.
- Location of `simple-mail-client` application is `build/mail-client/mail-client`