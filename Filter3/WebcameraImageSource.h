#ifndef WEBCAMERAIMAGESOURCE_H
#define WEBCAMERAIMAGESOURCE_H

#include "AbstractLinearMovieSource.h"

#include <QWidget>

#include <opencv2/opencv.hpp>

class WebcameraImageSource : public AbstractLinearMovieSource
{
    Q_OBJECT
public:
    explicit WebcameraImageSource(int source, QWidget *parent = 0);
    explicit WebcameraImageSource(QString source, QWidget *parent = 0);
    virtual bool resume();
    virtual bool stop();
    
private:
    QWidget *parent;
    bool isIntialized;
    cv::VideoCapture *capture;

public slots:
    virtual bool capture();

signals:
    void captured(cv::Mat image);

};

#endif // WEBCAMERAIMAGESOURCE_H
