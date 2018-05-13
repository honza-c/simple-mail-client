# Simple Mail Client & Mail Client Core
This repository contains `mail-client-core`, a simple Qt/C++ library providing the core functionality of an e-mail client. The second part of this repository is `simple-mail-client`, a simple Qt/C++ GUI application, that integrates the `mail-client-core` library. Purpose of this application is to display how to integrate and use the library in your project. The final goal is to use `mail-client-core` library as backend for e-mail plugin to Otter Browser, which is also goal of my bachelor thesis.

Current temporary limitation is that library works only on GNU/Linux operating systems: Support for Debian-based distributions (Ubuntu, Debian, Mint, ...) and Red Hat-based distributions (RHEL, CentOS, Fedora, ...) is done. Support for MS Windows and Mac OS X is planned.

## Dependencies
`mail-client-core` uses this list of external components and libraries:
- Qt framework
- VMime: C++ library providing the interface to e-mail protocols
- Crypto++: C++ library for encryption / decryption, here used for encrypted storing user passwords in the configuration file.

## Install dependencies on Fedora Linux
- install Qt framework
- install Crypto++ library:
```
sudo dnf install cryptopp cryptopp-devel
```
- install C/C++ development tools:
```
sudo dnf install @development-tools
sudo dnf group install "C Development Tools and Libraries"
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
In `simple-mail-client/mail-client-core/tools/constants.h` file are placed some constant values you may want to change before the build:
```
    // filename constants for files used in application
    const QString ERROR_LOG_FILE_NAME = "error.log";
    const QString USER_ACCOUNT_SETTINGS_FILE = "users.xml";

    // password encryption keys
    const QString PASSWORD_AES_CBC_ENCRYPTION_KEY = "1234567890123456789012345678901234567890123456789012345678901234";
    const QString PASSWORD_AES_CBC_ENCRYPTION_IV = "1111111111222222222233333333334444444444555555555566666666667777";
```
- `ERROR_LOG_FILE_NAME` is the name of the file, where error log is located. Default file name is `error.log` and its default location is in the same folder where the binary of client application is.
- `USER_ACCOUNT_SETTINGS_FILE` is the name of the XML file, where the configuration of user accounts is stored. Default file name is `users.xml` and its default location is in the same folder where the binary of client application is.
- `PASSWORD_AES_CBC_ENCRYPTION_KEY` and `PASSWORD_AES_CBC_ENCRYPTION_IV` are the vaules that are used for encrypting and decrypting the user passwords, that are stored in the `USER_ACCOUNT_SETTINGS_FILE`. It is strongly recommended to change default values before the build.

In `simple-mail-client/mail-client-core/tools/utils.cpp` is function to handle logging. Default behavior is that every log level information is printed into `std::err` stream and information with `Critical` and `Fatal` log levels are stored in `ERROR_LOG_FILE_NAME` file. You may want to change the behavior of the logger:

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

## Build mail-client-core library on Linux
Path to `qmake` binary may differ on your system. In my case I have Qt framework from official installer installed in /opt directory and I use 5.10.1 version. If you use Qt framework from packages provided by your distribution, calling just `qmake` without the absolute path should be good enough.

```bash
git clone https://gitlab.com/honza-c/simple-mail-client
mkdir simple-mail-client/build
cd simple-mail-client/build
/opt/Qt/5.10.1/gcc_64/bin/qmake ../simple-mail-client/simple-mail-client.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug && /usr/bin/make qmake_all
/usr/bin/make
```
or open `simple-mail-client/simple-mail-client.pro` in QtCreator and hit the run button.

## Location of build artefacts
- Location of static library `mail-client-core` is `build/mail-client-core/libmailclient-core.a`.
- Location of `simple-mail-client` application is `build/mail-client/mail-client`

## Integration of mail-client-core to your Qt project
Add those lines to your .pro file:
```
INCLUDEPATH += $$PWD/path-to-mail-client-core-subproject
LIBS += -L$$PWD/path-where-is-built-library-file-placed -lmail-client-core
LIBS += -lcryptopp
LIBS += -lvmime
```
- Location in the first line must point to the sources of the mail-client-core subproject in this repo to proper use the headers provided by the library.
- Location in the second line must point to path where built `libmail-client-core.a` is located.