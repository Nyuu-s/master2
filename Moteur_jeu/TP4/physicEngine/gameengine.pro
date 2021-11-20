QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    camera.cpp \
    gameObject.cpp \
    graph.cpp \
    mesh.cpp \
    physics/BoundingSphere.cpp \
    physics/aabb.cpp \
    physics/collider.cpp \
    physics/intersectdata.cpp \
    physics/physicobject.cpp \
    physics/physicsengine.cpp \
    physics/plane.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    BasicIO.hpp \
    ReferenceCounter.h \
    camera.h \
    componnent.h \
    gameObject.h \
    graph.h \
    mainwidget.h \
    geometryengine.h \
    mesh.h \
    physics/BoundingSphere.h \
    physics/aabb.h \
    physics/collider.h \
    physics/intersectdata.h \
    physics/physicobject.h \
    physics/physicsengine.h \
    physics/plane.h \
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
