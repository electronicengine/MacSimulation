QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logging.cpp \
    main.cpp \
    mainwindow.cpp \
    peer.cpp \
    coordinator.cpp \
    peersimulation.cpp \
    simulation.cpp \
    simulationadder.cpp \
    simulationaddwindow.cpp \
    simulationoperator.cpp \
    simulationresultwindow.cpp \
    useradd.cpp

HEADERS += \
    logging.h \
    mainwindow.h \
    peer.h \
    coordinator.h \
    peersimulation.h \
    simulation.h \
    simulationadder.h \
    simulationaddwindow.h \
    simulationoperator.h \
    simulationresultwindow.h \
    useradd.h

FORMS += \
    mainwindow.ui \
    simulationaddwindow.ui \
    simulationresultwindow.ui \
    useradd.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    images/show_pressed.png \
    images/show_unpressed.png
