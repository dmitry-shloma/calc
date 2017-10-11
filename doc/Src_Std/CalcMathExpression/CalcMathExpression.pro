TEMPLATE = app

unix {
    VERSION = 0.0.1
}

CONFIG -= qt

HEADERS += \
    ../Src/RpnCalc/rpncalc.h

SOURCES += \
    main.cpp

unix {
    LIBS += -ldl
}

# BuildEssentials
BUILD_ESSENTIALS_DIR = $$PWD/../BuildEssentials

include($${BUILD_ESSENTIALS_DIR}/environment.pri)
include($${BUILD_ESSENTIALS_DIR}/helper.pri)
#
