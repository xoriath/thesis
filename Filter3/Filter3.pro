#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T10:18:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filter3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagehelper.cpp

HEADERS  += mainwindow.h \
    imagehelper.h

FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

win32 {
INCLUDEPATH += C:\\OpenCV2.4\\opencv\\build\\include

LIBS += -LC:\\OpenCV2.4\\myBuild\\lib\\Debug \
    -lopencv_calib3d240d \
    -lopencv_contrib240d \
    -lopencv_core240d \
    -lopencv_features2d240d \
    -lopencv_flann240d \
    -lopencv_gpu240d \
    -lopencv_highgui240d \
    -lopencv_imgproc240d \
    -lopencv_legacy240d \
    -lopencv_ml240d \
    -lopencv_nonfree240d \
    -lopencv_objdetect240d \
    -lopencv_photo240d \
    -lopencv_stitching240d \
    -lopencv_ts240d \
    -lopencv_video240d \
    -lopencv_videostab240d
}
