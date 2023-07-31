QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    view/graphwindow/graphwindow.cc \
    main.cc \
    model/model.cc \
    libs/qcustomplot/qcustomplot.cc \
    view/mainwindow/view.cc

HEADERS += \
    controller/controller.h \
    view/graphwindow/graphwindow.h \
    model/model.h \
    libs/qcustomplot/qcustomplot.h \
    view/mainwindow/view.h

FORMS += \
    view/graphwindow/graphwindow.ui \
    view/mainwindow/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ICON = icons/icon.icns

RESOURCES += \
    resources.qrc


