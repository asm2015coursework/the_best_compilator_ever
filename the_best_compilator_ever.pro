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
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    CodeGenerator.cpp \
    Preprocessor.cpp \
    Variable.cpp \
    tokens/FunctionToken.cpp \
    parser/Parser.cpp \
    parser/Result.cpp \
    tokens/EqualityToken.cpp \
    tokens/VariableToken.cpp \
    tokens/InitializationToken.cpp

HEADERS += \
    CodeGenerator.h \
    Preprocessor.h \
    tokens/FunctionToken.h \
    tokens/Token.h \
    parser/Parser.h \
    parser/Result.h \
    parser/ParsingException.h \
    tokens/EqualityToken.h \
    tokens/VariableToken.h \
    tokens/InitializationToken.h \
    Variable.h
