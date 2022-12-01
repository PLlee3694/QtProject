QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bookinformation.cpp \
    bookinformationtable.cpp \
    changedialog.cpp \
    deletedialog.cpp \
    editbooksdialog.cpp \
    finddialog.cpp \
    informationdialog.cpp \
    inputdialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    regisinfo.cpp \
    regisinfodialog.cpp \
    regisinfosdialog.cpp \
    usermainwindow.cpp

HEADERS += \
    bookinformation.h \
    bookinformationtable.h \
    changedialog.h \
    deletedialog.h \
    editbooksdialog.h \
    finddialog.h \
    informationdialog.h \
    inputdialog.h \
    logindialog.h \
    mainwindow.h \
    regisinfo.h \
    regisinfodialog.h \
    regisinfosdialog.h \
    usermainwindow.h

FORMS += \
    changedialog.ui \
    deletedialog.ui \
    editbooksdialog.ui \
    finddialog.ui \
    informationdialog.ui \
    inputdialog.ui \
    logindialog.ui \
    mainwindow.ui \
    regisinfodialog.ui \
    regisinfosdialog.ui \
    usermainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
