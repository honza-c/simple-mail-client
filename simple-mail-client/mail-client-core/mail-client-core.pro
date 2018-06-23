#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T19:49:55
#
#-------------------------------------------------

QT       += core gui xml sql

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
    messaging/mailmessage.cpp \
    messaging/abstractmessagesenderservice.cpp \
    messaging/messagemetadata.cpp \
    messaging/vmimemessagemetadataparser.cpp \
    messaging/messagemetadatatablemodel.cpp \
    messaging/vmimemessagingbaseservice.cpp \
    messaging/vmimesmtpservice.cpp \
    messaging/abstractinboxservice.cpp \
    messaging/vmimeinboxservice.cpp \
    messaging/vmimeimapservice.cpp \
    messaging/inboxfoldertreeitem.cpp \
    messaging/inboxfoldertreemodel.cpp \
    messaging/inboxfolder.cpp \
    messaging/vmimeinboxfolderparser.cpp \
    messaging/vmimemessagecontentparser.cpp \
    messaging/abstractinboxservice.cpp \
    messaging/abstractmessagesenderservice.cpp \
    messaging/inboxfolder.cpp \
    messaging/inboxfoldertreeitem.cpp \
    messaging/inboxfoldertreemodel.cpp \
    messaging/mailmessage.cpp \
    messaging/messagemetadata.cpp \
    messaging/messagemetadatatablemodel.cpp \
    messaging/vmimeimapservice.cpp \
    messaging/vmimeinboxfolderparser.cpp \
    messaging/vmimeinboxservice.cpp \
    messaging/vmimemessagecontentparser.cpp \
    messaging/vmimemessagemetadataparser.cpp \
    messaging/vmimemessagingbaseservice.cpp \
    messaging/vmimerootcertificateshelper.cpp \
    messaging/vmimesmtpservice.cpp \
    tools/aespasswordencryptordecryptor.cpp \
    tools/ipasswordencryptordecryptor.cpp \
    tools/utils.cpp \
    userAccounts/iuseraccountsreaderwriter.cpp \
    userAccounts/useraccount.cpp \
    userAccounts/useraccountslistmodel.cpp \
    userAccounts/xmluseraccountsreaderwriter.cpp \
    mailclientcore.cpp \
    database/databasemanager.cpp

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
    messaging/mailmessage.h \
    messaging/abstractmessagesenderservice.h \
    messaging/messagemetadata.h \
    messaging/vmimemessagemetadataparser.h \
    messaging/messagemetadatatablemodel.h \
    messaging/vmimemessagingbaseservice.h \
    messaging/vmimesmtpservice.h \
    messaging/abstractinboxservice.h \
    messaging/vmimeinboxservice.h \
    messaging/vmimeimapservice.h \
    messaging/inboxfoldertreeitem.h \
    messaging/inboxfoldertreemodel.h \
    messaging/inboxfolder.h \
    messaging/vmimeinboxfolderparser.h \
    messaging/vmimemessagecontentparser.h \
    messaging/abstractinboxservice.h \
    messaging/abstractmessagesenderservice.h \
    messaging/inboxfolder.h \
    messaging/inboxfoldertreeitem.h \
    messaging/inboxfoldertreemodel.h \
    messaging/mailmessage.h \
    messaging/messagemetadata.h \
    messaging/messagemetadatatablemodel.h \
    messaging/vmimeimapservice.h \
    messaging/vmimeinboxfolderparser.h \
    messaging/vmimeinboxservice.h \
    messaging/vmimemessagecontentparser.h \
    messaging/vmimemessagemetadataparser.h \
    messaging/vmimemessagingbaseservice.h \
    messaging/vmimerootcertificateshelper.h \
    messaging/vmimesmtpservice.h \
    tools/aespasswordencryptordecryptor.h \
    tools/constants.h \
    tools/ipasswordencryptordecryptor.h \
    tools/utils.h \
    userAccounts/iuseraccountsreaderwriter.h \
    userAccounts/useraccount.h \
    userAccounts/useraccountslistmodel.h \
    userAccounts/xmluseraccountsreaderwriter.h \
    mailclientcore.h \
    database/databasemanager.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
