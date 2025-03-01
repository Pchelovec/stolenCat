#-------------------------------------------------
#
# Project created by QtCreator 2025-02-07T15:35:40
#
#-------------------------------------------------
include($$PWD/Admob/Admob.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stolenCat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += resources_big

SOURCES += \
        main.cpp \
        widget.cpp \
        patched_game_painter.cpp \
        clickablelabel.cpp \
    game.cpp \
    level.cpp \
    screen.cpp \
    gameprogress.cpp

HEADERS += \
        widget.h \
        patched_game_painter.h \
        clickablelabel.h \
        loader.h \
    game.h \
    level.h \
    screen.h \
    item.h \
    itemtype.h \
    gameprogress.h \
    progress.h \
    language.h

FORMS += \
        widget.ui


DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/org/qtproject/QtAdMobActivity.java

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pack.qrc


#QMAKE_LINK+=-nostdlib++
contains(ANDROID_TARGET_ARCH,x86) {
    QMAKE_LINK+=-nostdlib++
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

# armeabi-v7a architecture
contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    QMAKE_LINK+=-nostdlib++
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

# arm64-v8a architecture
contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    QMAKE_LINK+=-nostdlib++
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
