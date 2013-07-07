#-------------------------------------------------
#
# Project created by QtCreator 2013-02-19T10:51:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebCam
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gaussianblurdata.cpp \
    laplaciandata.cpp

HEADERS  += mainwindow.h \
    gaussianblurdata.h \
    laplaciandata.h

FORMS    += mainwindow.ui \
    gaussianblurdata.ui \
    laplaciandata.ui

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
