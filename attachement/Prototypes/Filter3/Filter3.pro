#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T10:18:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filter3
TEMPLATE = app

CONFIG += debug


SOURCES += main.cpp\
        mainwindow.cpp \
    FileImageSource.cpp \
    WebcameraImageSource.cpp \
    CannyImageProcessor.cpp \
    HoughCircles.cpp \
    GuassianBlur.cpp #\
#   ../libVISCA/visca/libvisca_win32.c \
#   ../libVISCA/visca/libvisca.c

HEADERS  += mainwindow.h \
    AbstractImageSource.h \
    FileImageSource.h \
    WebcameraImageSource.h \
    AbstractPauseable.h \
    AbstractLinearMovieSource.h \
    AbstractImageProcessor.h \
    CannyImageProcessor.h \
    HoughCircles.h \
    GuassianBlur.h #\
#    ../libVISCA/visca/libvisca.h

FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

win32 {

INCLUDEPATH += C:\\opencv2_bin\\install\\include
INCLUDEPATH += C:\\opencv\\opencv\\include
INCLUDEPATH += C:\\opencv\\opencv\\build\\include
#INCLUDEPATH += ..\\libVISCA\\visca

LIBS += -LC:\\opencv\\opencv\\build\\x86\\mingw\\lib
LIBS += -LC:\\opencv2_bin\\install\\lib \
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
