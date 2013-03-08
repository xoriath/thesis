#ifndef CANNYIMAGEPROCESSOR_H
#define CANNYIMAGEPROCESSOR_H

#include "AbstractImageProcessor.h"

class CannyImageProcessor : public AbstractImageProcessor
{
    Q_OBJECT
public:
    CannyImageProcessor(int threshold);

    virtual bool isInitialized() { return initialized; }
public slots:
    virtual bool process(cv::Mat image);
signals:
    void processed(cv::Mat image);
private:
    bool initialized;
    int threshold;
};

#endif // CANNYIMAGEPROCESSOR_H
