QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    customer.cpp \
    euraccount.cpp \
    forgotdialog.cpp \
    invaccount.cpp \
    main.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    operation.cpp \
    signupdialog.cpp \
    tlaccount.cpp \
    usdaccount.cpp

HEADERS += \
    account.h \
    customer.h \
    euraccount.h \
    forgotdialog.h \
    invaccount.h \
    loginwindow.h \
    mainwindow.h \
    operation.h \
    signupdialog.h \
    tlaccount.h \
    usdaccount.h

FORMS += \
    forgotdialog.ui \
    loginwindow.ui \
    mainwindow.ui \
    signupdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    house.qrc \
    my.qrc \
    my2.qrc

RC_ICONS = house.ico

DISTFILES += \
    eeuro.ico \
    loan.ico
