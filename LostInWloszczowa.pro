QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    deadenemywidget.cpp \
    deadherowidget.cpp \
    gamescreen.cpp \
    main.cpp \
    mainwindow.cpp \
    prologuegameplay.cpp \
    prologuescreen.cpp \
    qclickablelabel.cpp \
    qclickablewidget.cpp \
    recovereditemdialog.cpp \
    sexscreen.cpp \
    titlebar.cpp \
    titlescreen.cpp \
    tutorialinfo.cpp

HEADERS += \
    deadenemywidget.h \
    deadherowidget.h \
    gamescreen.h \
    mainwindow.h \
    prologuegameplay.h \
    prologuescreen.h \
    qclickablelabel.h \
    qclickablewidget.h \
    recovereditemdialog.h \
    sexscreen.h \
    titlebar.h \
    titlescreen.h \
    tutorialinfo.h

FORMS += \
    deadenemywidget.ui \
    deadherowidget.ui \
    gamescreen.ui \
    mainwindow.ui \
    prologuegameplay.ui \
    prologuescreen.ui \
    recovereditemdialog.ui \
    sexscreen.ui \
    titlebar.ui \
    titlescreen.ui \
    tutorialinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    dialogs.qrc \
    images.qrc
