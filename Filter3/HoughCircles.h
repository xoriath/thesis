#ifndef HOUGHCIRCLES_H
#define HOUGHCIRCLES_H

#include <vector>
#include <opencv2/opencv.hpp>

#include "AbstractImageProcessor.h"

class HoughCircles : public AbstractImageProcessor
{
    Q_OBJECT
public:
    HoughCircles();
    virtual bool isInitialized() { return initialized; }

public slots:
    virtual bool process(cv::Mat image);

signals:
    void processed(cv::Mat image);

private:
    bool initialized;
    QWidget *parent;
};

#endif // HOUGHCIRCLES_H
