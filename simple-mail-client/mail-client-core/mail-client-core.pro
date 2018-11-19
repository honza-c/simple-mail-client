#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T19:49:55
#
#-------------------------------------------------

QT       += core gui xml network sql

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
    mailclientcore.cpp \
    mailclientcore.cpp \
    src/vmimebasemessagingservice.cpp \
    src/vmimeinboxservice.cpp \
    src/vmimeimapservice.cpp \
    src/vmimeinboxfolder.cpp \
    src/vmimeinboxfolderparser.cpp \
    src/vmimemessagecontentparser.cpp \
    src/messagemetadata.cpp \
    src/contact.cpp \
    src/vmimemessagemetadataparser.cpp \
    src/inboxfoldertreeitem.cpp \
    src/inboxfoldertreemodel.cpp \
    src/databasemanager.cpp \
    src/messagemetadatasqltablemodel.cpp \
    src/attachment.cpp \
    src/qpushbuttonwithid.cpp \
    src/xmluseraccountsreaderwriter.cpp \
    src/aesencryptordecryptor.cpp \
    src/inboxfolder.cpp \
    src/message.cpp \
    src/vmimesmtpservice.cpp \
    src/messagecontent.cpp \
    src/multiselectcompleter.cpp \
    src/logger.cpp \
    src/useraccount.cpp \
    src/useraccountslistmodel.cpp \
    src/vmimepop3service.cpp \
    embeddedobject.cpp

HEADERS += \
        mailclientcore.h \
    mailclientcore.h \
    tools/constants.h \
    userAccounts/usersettingswriterandloader.h \
    tools/constants.h \
    mailclientcore.h \
    src/vmimebasemessagingservice.h \
    src/vmimeinboxservice.h \
    src/vmimeimapservice.h \
    src/vmimeinboxfolder.h \
    src/vmimeinboxfolderparser.h \
    src/vmimemessagecontentparser.h \
    src/messagemetadata.h \
    src/contact.h \
    src/vmimemessagemetadataparser.h \
    src/inboxfoldertreeitem.h \
    src/inboxfoldertreemodel.h \
    src/databasemanager.h \
    src/messagemetadatasqltablemodel.h \
    src/attachment.h \
    src/qpushbuttonwithid.h \
    src/xmluseraccountsreaderwriter.h \
    src/aesencryptordecryptor.h \
    src/inboxfolder.h \
    src/message.h \
    src/vmimesmtpservice.h \
    src/messagecontent.h \
    src/multiselectcompleter.h \
    src/logger.h \
    src/useraccount.h \
    src/useraccountslistmodel.h \
    src/vmimepop3service.h \
    embeddedobject.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
