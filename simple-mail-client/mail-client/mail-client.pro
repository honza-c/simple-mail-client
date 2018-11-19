#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T14:55:27
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets

TARGET = mail-client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    addedituseraccountdialog.cpp \
    manageuseracccountsdialog.cpp \
    writemessagewindow.cpp \
    attachmentslistmodel.cpp \
    newfolderdialog.cpp \
    renamefolderdialog.cpp


HEADERS += \
        mainwindow.h \
    constants.h \
    addedituseraccountdialog.h \
    manageuseracccountsdialog.h \
    writemessagewindow.h \
    attachmentslistmodel.h \
    newfolderdialog.h \
    renamefolderdialog.h


FORMS += \
        mainwindow.ui \
    addedituseraccountdialog.ui \
    manageuseracccountsdialog.ui \
    writemessagewindow.ui \
    newfolderdialog.ui \
    renamefolderdialog.ui

INCLUDEPATH += $$PWD/../mail-client-core
LIBS += -L$$OUT_PWD/../mail-client-core/ -lmail-client-core
LIBS += -lcryptopp
LIBS += -lvmime
