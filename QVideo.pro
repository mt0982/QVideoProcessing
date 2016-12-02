#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T11:49:27
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QVideo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videowidget.cpp \
    videosurface.cpp \
    bma.cpp

HEADERS  += mainwindow.h \
    videowidget.h \
    videosurface.h \
    bma.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp






















