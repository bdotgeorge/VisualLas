QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChartView/src/abstractchartview.cpp \
    ChartView/src/chartview.cpp \
    ChartView/src/extendedseries.cpp \
    ChartView/src/linetochart.cpp \
    ChartView/src/markerline.cpp \
    ChartView/src/settingextseries.cpp \
    ChartView/src/tooltip.cpp \
    filedata.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ChartView/src/abstractchartview.h \
    ChartView/src/chartview.h \
    ChartView/src/extendedseries.h \
    ChartView/src/linetochart.h \
    ChartView/src/macros.h \
    ChartView/src/markerline.h \
    ChartView/src/settingextseries.h \
    ChartView/src/tooltip.h \
    ChartView/src/ui_settingextseries.h \
    filedata.h \
    mainwindow.h

FORMS += \
    ChartView/src/settingextseries.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
