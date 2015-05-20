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
    tokens/EqualityToken.cpp \
    tokens/VariableToken.cpp \
    tokens/InitializationToken.cpp \
    tokens/ForToken.cpp \
    tokens/AddToken.cpp \
    tokens/SubtractToken.cpp \
    tokens/MultiplyToken.cpp \
    tokens/DivideToken.cpp \
    tokens/BlockToken.cpp \
    tokens/AssignmentToken.cpp \
    tokens/OrToken.cpp \
    tokens/ConstIntToken.cpp \
    tokens/AndToken.cpp \
    tokens/DereferenceToken.cpp \
    tokens/AddressToken.cpp \
    tokens/UnaryMinusToken.cpp \
    tokens/UnaryPlusToken.cpp \
    tokens/ReturnToken.cpp \
    tokens/IfToken.cpp \
    lib/Utils.cpp \
    tokens/AsmToken.cpp \
    tokens/FunctionCallToken.cpp \
    tokens/ConstCharToken.cpp

HEADERS += \
    CodeGenerator.h \
    Preprocessor.h \
    tokens/FunctionToken.h \
    tokens/Token.h \
    parser/Parser.h \
    parser/ParsingException.h \
    tokens/EqualityToken.h \
    tokens/VariableToken.h \
    tokens/InitializationToken.h \
    Variable.h \
    tokens/ForToken.h \
    tokens/AddToken.h \
    tokens/SubtractToken.h \
    tokens/MultiplyToken.h \
    tokens/DivideToken.h \
    tokens/BlockToken.h \
    tokens/AssignmentToken.h \
    tokens/OrToken.h \
    tokens/ConstIntToken.h \
    tokens/AndToken.h \
    tokens/DereferenceToken.h \
    tokens/AddressToken.h \
    tokens/UnaryMinusToken.h \
    tokens/UnaryPlusToken.h \
    tokens/ReturnToken.h \
    tokens/IfToken.h \
    lib/Utils.h \
    tokens/AsmToken.h \
    tokens/FunctionCallToken.h \
    tokens/ConstCharToken.h

OTHER_FILES += \
    tests/test0.cmm \
    tests/test1.cmm \
    parser/ReadMe
