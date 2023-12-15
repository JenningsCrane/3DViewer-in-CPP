QT       += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# LIBS += -lopengl32 -lglu32 -lgdi32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += view model controller

SOURCES += \
    gif_library/gif.cpp \
    main.cc \
    model/processing_file/open_file.cc \
    model/processing_file/processing_file.cc \
    model/processing_file/read_file.cc \
    model/rotation_strategy/rotation_strategy.cc \
    view/mainwindow.cc \
    view/myglwidget.cc \
    controller/controller.cc \
    model/model_affine_transfer.cc \
    model/model.cc

HEADERS += \
    gif_library/gif.hpp \
    model/processing_file/open_file.h \
    model/processing_file/processing_file.h \
    model/processing_file/read_file.h \
    model/rotation_strategy/rotation_strategy.h \
    view/mainwindow.h \
    view/myglwidget.h \
    controller/controller.h \
    model/model_affine_transfer.h \
    model/model.h \
    viewer_data.h

FORMS += \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
