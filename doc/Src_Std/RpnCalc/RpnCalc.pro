TEMPLATE = lib

unix {
    VERSION = 0.0.0.1
}

CONFIG -= qt

SOURCES += \
    rpncalc.cpp

HEADERS += rpncalc.h \
    conversionhelper.h

# BuildEssentials
BUILD_ESSENTIALS_DIR = $$PWD/../BuildEssentials

include($${BUILD_ESSENTIALS_DIR}/environment.pri)
include($${BUILD_ESSENTIALS_DIR}/helper.pri)
#
