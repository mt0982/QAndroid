QT += core widgets opengl
QT -= gui

CONFIG += c++11

TARGET = QAndroid
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    glwidget.cpp \
    mesh.cpp \
    Interaction/camera.cpp \
    Object/box.cpp \
    Object/sphere.cpp

HEADERS += \
    glwidget.h \
    mesh.h \
    Interaction/camera.h \
    Object/box.h \
    Object/sphere.h

DISTFILES += \
    shader.vsh \
    shader.fsh \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

RESOURCES += \
    resource.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
