#ifndef ABSTRACTIMAGESOURCE_H
#define ABSTRACTIMAGESOURCE_H

#include <QObject>

#include <opencv2/opencv.hpp>

class AbstractImageSource : public QObject {
    Q_OBJECT
public slots:
    virtual bool capture() = 0;

signals:
    void captured(cv::Mat image);

};
#endif // ABSTRACTIMAGESOURCE_H
