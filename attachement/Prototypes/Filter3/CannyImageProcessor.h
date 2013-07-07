#ifndef CANNYIMAGEPROCESSOR_H
#define CANNYIMAGEPROCESSOR_H

#include <QWidget>

#include "AbstractImageProcessor.h"

class CannyWidget;

class CannyImageProcessor : public AbstractImageProcessor
{
    Q_OBJECT
public:
    CannyImageProcessor(int threshold, QWidget *parent = 0);

    virtual bool isInitialized() { return initialized; }
public slots:
    virtual bool process(cv::Mat image);
signals:
    //void processed(cv::Mat image);
private:
    bool initialized;
    int threshold;
    QWidget *parent;

};

class CannyWidget : public QWidget
{
    Q_OBJECT

public:
    CannyWidget(QObject *parent = 0);
};

#endif // CANNYIMAGEPROCESSOR_H
