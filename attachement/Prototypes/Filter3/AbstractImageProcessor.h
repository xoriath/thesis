#ifndef ABSTRACTIMAGEPROCESSOR_H
#define ABSTRACTIMAGEPROCESSOR_H

#include <QWidget>

#include <opencv2/opencv.hpp>

class AbstractImageProcessor : public QObject
{
    Q_OBJECT
public slots:
    virtual bool process(cv::Mat image) = 0;
signals:
    void processed(cv::Mat image);
public:
    virtual bool isInitialized() =  0;
};

#endif // ABSTRACTIMAGEPROCESSOR_H
