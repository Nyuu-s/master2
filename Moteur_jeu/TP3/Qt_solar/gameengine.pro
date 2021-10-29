QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    gameObject.cpp \
    graph.cpp \
    mesh.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    BasicIO.h \
    componnent.h \
    gameObject.h \
    graph.h \
    mainwidget.h \
    geometryengine.h \
    mesh.h \
    transform.h

RESOURCES += \
    models.qrc \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

DISTFILES += \
    grass.png
