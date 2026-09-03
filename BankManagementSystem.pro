QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Suppress deprecated API warnings
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/loginwindow.cpp \
    src/account.cpp \
    src/transaction.cpp \
    src/customer.cpp \
    src/database.cpp \
    src/dashboard.cpp

HEADERS += \
    include/mainwindow.h \
    include/loginwindow.h \
    include/account.h \
    include/transaction.h \
    include/customer.h \
    include/database.h \
    include/dashboard.h

FORMS += \
    ui/mainwindow.ui \
    ui/loginwindow.ui \
    ui/dashboard.ui

TRANSLATIONS += BankManagementSystem_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
