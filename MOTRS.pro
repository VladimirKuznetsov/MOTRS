#-------------------------------------------------
#
# Project created by QtCreator 2015-02-01T21:49:00
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = MOTRS
TEMPLATE = app


SOURCES += main.cpp \
    player.cpp \
    enemy.cpp \
    cell.cpp \
    levelChase.cpp \
    level.cpp \
    game.cpp \
    dialogBox.cpp \
    levelInvestigate.cpp \
    levelIntro.cpp

HEADERS  += \
    player.h \
    enemy.h \
    cell.h \
    levelChase.h \
    level.h \
    game.h \
    dialogBox.h \
    levelInvestigate.h \
    levelIntro.h

TRANSLATIONS += motrs_ru.ts

FORMS    +=

RESOURCES += \
    res.qrc

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    ../android-template/gradle/wrapper/gradle-wrapper.jar \
    ../android-template/AndroidManifest.xml \
    ../android-template/res/values/libs.xml \
    ../android-template/build.gradle \
    ../android-template/gradle/wrapper/gradle-wrapper.properties \
    ../android-template/gradlew \
    ../android-template/gradlew.bat \
    ../android-template/res/values/strings.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/../android-template

