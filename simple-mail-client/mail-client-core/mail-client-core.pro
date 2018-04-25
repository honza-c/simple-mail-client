#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T19:49:55
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mail-client-core
TEMPLATE = lib
CONFIG += staticlib c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lvmime -lcryptopp

SOURCES += \
        mailclientcore.cpp \
        userAccounts/useraccount.cpp \
        userAccounts/useraccountslistmodel.cpp \
    userAccounts/useraccount.cpp \
    userAccounts/useraccountslistmodel.cpp \
    mailclientcore.cpp \
    tools/utils.cpp \
    userAccounts/iuseraccountsreaderwriter.cpp \
    userAccounts/xmluseraccountsreaderwriter.cpp \
    tools/ipasswordencryptordecryptor.cpp \
    tools/aespasswordencryptordecryptor.cpp \
    messaging/vmimerootcertificateshelper.cpp \
    messaging/mailmessage.cpp

HEADERS += \
        mailclientcore.h \
        userAccounts/useraccount.h \
        userAccounts/useraccountslistmodel.h \
    userAccounts/useraccount.h \
    userAccounts/useraccountslistmodel.h \
    mailclientcore.h \
    tools/utils.h \
    tools/constants.h \
    userAccounts/usersettingswriterandloader.h \
    userAccounts/iuseraccountsreaderwriter.h \
    userAccounts/xmluseraccountsreaderwriter.h \
    tools/ipasswordencryptordecryptor.h \
    tools/aespasswordencryptordecryptor.h \
    messaging/vmimerootcertificateshelper.h \
    messaging/mailmessage.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
