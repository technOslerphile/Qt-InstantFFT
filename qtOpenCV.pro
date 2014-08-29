#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T13:11:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtOpenCV
TEMPLATE = app


SOURCES += main.cpp\
        dialogue.cpp

HEADERS  += dialogue.h

FORMS    += dialogue.ui

INCLUDEPATH += C:\\OpenCV\\OpenCV-install\\opencv\\build\\include

LIBS += -LC:\\OpenCV\OpenCV-install\opencv\build\x86\vc10\lib\
-lopencv_calib3d248d \
-lopencv_contrib248d \
-lopencv_core248d \
-lopencv_features2d248d \
-lopencv_flann248d \
-lopencv_gpu248d \
-lopencv_highgui248d \
-lopencv_imgproc248d \
-lopencv_legacy248d \
-lopencv_ml248d \
-lopencv_nonfree248d \
-lopencv_objdetect248d \
-lopencv_photo248d \
-lopencv_stitching248d \
-lopencv_superres248d \
-lopencv_ts248d \
-lopencv_video248d \
-lopencv_videostab248d
