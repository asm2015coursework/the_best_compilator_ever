#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T17:38:09
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = the_best_compilator_ever
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    preprocessor.cpp \
    parser.cpp \
    code_generator.cpp

HEADERS += \
    preprocessor.h \
    parser.h \
    code_generator.h
