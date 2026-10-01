QT       += core testlib
QT       -= gui

CONFIG   += console c++17 testcase
CONFIG   -= app_bundle

TARGET    = tst_bank
TEMPLATE  = app

INCLUDEPATH += ../include

SOURCES += \
    tst_bank.cpp \
    ../src/account.cpp \
    ../src/customer.cpp \
    ../src/database.cpp

HEADERS += \
    ../include/account.h \
    ../include/customer.h \
    ../include/database.h
