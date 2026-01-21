QT       += core gui widgets

TEMPLATE = app
TARGET   = OrganizeFiles

# C++ Standard
CONFIG  += c++17

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    worker.cpp

# Header files
HEADERS += \
    mainwindow.h \
    worker.h

# UI files
FORMS += \
    mainwindow.ui

# Warnings & compatibility
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG  += warn_on

# Application icon (Windows)
RC_FILE = icon.rc


