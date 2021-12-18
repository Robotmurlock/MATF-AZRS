QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_testparser.cpp \
    ../Parser/txtparser.cpp \
    ../Parser/tsvparser.cpp \
    ../Parser/csvparser.cpp

HEADERS += \
    ../Parser/txtparser.h \
    ../Parser/tsvparser.h \
    ../Parser/csvparser.h
