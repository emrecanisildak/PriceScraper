QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = myappico.ico

include(QXlsx/QXlsx.pri)

INCLUDEPATH += "C:\curl\include"

INCLUDEPATH += "C:\libxl\include_cpp"


LIBS+=C:/curl/lib/libcurl.a
LIBS+=C:/curl/lib/libcurl.dll.a

SOURCES += \
    amazonscraper.cpp \
    analyzelauncherwidget.cpp \
    analyzviewmodel.cpp \
    databuilder.cpp \
    exportcontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    refineddata.cpp \
    xmlreader.cpp

HEADERS += \
    amazonscraper.h \
    analyzelauncherwidget.h \
    analyzeparameters.h \
    analyzeprogressstatitics.h \
    analyzviewmodel.h \
    databuilder.h \
    exportcontroller.h \
    mainwindow.h \
    productinfo.h \
    refineddata.h \
    xmlreader.h

FORMS += \
    analyzelauncherwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc
