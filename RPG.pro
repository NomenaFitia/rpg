QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/adventurer.cpp \
    src/adventurerType/assassin.cpp \
    src/adventurerType/tank.cpp \
    src/appmanager.cpp \
    src/characterselectionwindow.cpp \
    src/combatsystem.cpp \
    src/decor.cpp \
    src/enemy.cpp \
    src/entity.cpp \
    src/game.cpp \
    src/gameoverwindow.cpp \
    src/gamewindow.cpp \
    src/map.cpp \
    src/objectloader.cpp \
    src/personage.cpp \
    src/main.cpp \

HEADERS += \
    src/adventurer.h \
    src/adventurerType/assassin.h \
    src/adventurerType/tank.h \
    src/AppManager.h \
    src/characterselectionwindow.h \
    src/combatsystem.h \
    src/decor.h \
    src/enemy.h \
    src/entity.h \
    src/Game.h \
    src/gameoverwindow.h \
    src/gamewindow.h \
    src/map.h \
    src/objectloader.h \
    src/personage.h \
    src/vector2.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += inc/

RESOURCES += \
    resources.qrc

DISTFILES += \
    .gitignore \
    shaders/simple.frag \
    shaders/simple.vert

win32 {
    LIBS += -lopengl32
}

unix {
    LIBS += -lGL
}
