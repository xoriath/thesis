#ifndef WEBCAMERAIMAGESOURCE_H
#define WEBCAMERAIMAGESOURCE_H

#include "AbstractLinearMovieSource.h"

#include <QWidget>
#include <QTimer>

#include <opencv2/opencv.hpp>

class WebcameraImageSource : public AbstractLinearMovieSource
{
    Q_OBJECT
public:
    explicit WebcameraImageSource(int source, int fps, QWidget *parent = 0);
    explicit WebcameraImageSource(QString source, int fps, QWidget *parent = 0);

    ~WebcameraImageSource();
    virtual bool resume();
    virtual bool stop();
    
    void setupTimer(int fps);
private:
    QWidget *parent;
    QTimer  *timer;

    cv::VideoCapture *mCapture;
    cv::Mat imageBuffer;

    bool isIntialized;
public slots:
    virtual bool capture();

signals:
    void captured(cv::Mat image);

};

#endif // WEBCAMERAIMAGESOURCE_H
