QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    changedialog.cpp \
    course.cpp \
    coursedialog.cpp \
    coursesdialog.cpp \
    deletedialog.cpp \
    editcoursesdialog.cpp \
    finddialog.cpp \
    informationdialog.cpp \
    inputdialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    screeninbirthdialog.cpp \
    screeningenderdialog.cpp \
    screeningradedialog.cpp \
    screeninmarrydialog.cpp \
    screeninpositiondialog.cpp \
    teacherinformation.cpp \
    teacherinformationtable.cpp

HEADERS += \
    aboutdialog.h \
    changedialog.h \
    course.h \
    coursedialog.h \
    coursesdialog.h \
    deletedialog.h \
    editcoursesdialog.h \
    finddialog.h \
    informationdialog.h \
    inputdialog.h \
    logindialog.h \
    mainwindow.h \
    screeninbirthdialog.h \
    screeningenderdialog.h \
    screeningradedialog.h \
    screeninmarrydialog.h \
    screeninpositiondialog.h \
    teacherinformation.h \
    teacherinformationtable.h

FORMS += \
    aboutdialog.ui \
    changedialog.ui \
    coursedialog.ui \
    coursesdialog.ui \
    deletedialog.ui \
    editcoursesdialog.ui \
    finddialog.ui \
    informationdialog.ui \
    inputdialog.ui \
    logindialog.ui \
    mainwindow.ui \
    screeninbirthdialog.ui \
    screeningenderdialog.ui \
    screeningradedialog.ui \
    screeninmarrydialog.ui \
    screeninpositiondialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
