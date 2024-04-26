QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChartView/abstractchartview.cpp \
    ChartView/chartview.cpp \
    ChartView/extendedseries.cpp \
    ChartView/linetochart.cpp \
    ChartView/settingextseries.cpp \
    ChartView/tooltip.cpp \
    filedata.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ChartView/abstractchartview.h \
    ChartView/chartview.h \
    ChartView/extendedseries.h \
    ChartView/linetochart.h \
    ChartView/settingextseries.h \
    ChartView/tooltip.h \
    ChartView/ui_settingextseries.h \
    filedata.h \
    mainwindow.h

FORMS += \
    ChartView/settingextseries.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
