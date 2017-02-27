QT += core
QT -= gui

CONFIG += c++11

TARGET = BinarySearchTree
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += BinarySearchTree.cpp \
           Main.cpp \

HEADERS +=  BinarySearchTree.h \

DEFINES += QT_DEPRECATED_WARNINGS
