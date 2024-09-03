QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SerDeserWgt.cc \
    Serializer.cc \
    Deserializer.cc \
    file_service.cc \
    FileDialogService.cc \
    Data.cc \
    main.cpp \
    MainWindow.cc

HEADERS += \
    MainWindow.h \
    Serializer.h \
    Deserializer.h \
    file_service.h \
    FileDialogService.h \
    qt_macros.h \
    Data.h \
    SerDeserWgt.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
