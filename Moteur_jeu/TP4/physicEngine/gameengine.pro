QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    BoundingSphere.cpp \
    aabb.cpp \
    camera.cpp \
    collider.cpp \
    gameObject.cpp \
    graph.cpp \
    intersectdata.cpp \
    mesh.cpp \
    physicobject.cpp \
    physicsengine.cpp \
    plane.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    BasicIO.hpp \
    BoundingSphere.h \
    aabb.h \
    camera.h \
    collider.h \
    componnent.h \
    gameObject.h \
    graph.h \
    intersectdata.h \
    mainwidget.h \
    geometryengine.h \
    mesh.h \
    physicobject.h \
    physicsengine.h \
    plane.h \
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
