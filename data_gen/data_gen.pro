#-------------------------------------------------
#
# Project created by QtCreator 2016-08-17T16:14:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = data_gen
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    pdo.cpp \
    rdo.cpp \
    form.cpp \
    vdo_2.cpp \
    vdo.cpp

HEADERS  += dialog.h \
    pdo.h \
    rdo.h \
    form.h \
    vdo_2.h \
    vdo.h

FORMS    += dialog.ui \
    pdo.ui \
    rdo.ui \
    form.ui \
    vdo_2.ui \
    vdo.ui
