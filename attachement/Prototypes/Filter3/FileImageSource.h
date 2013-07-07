#ifndef FILEIMAGESOURCE_H
#define FILEIMAGESOURCE_H

#include "AbstractImageSource.h"

#include <QString>
#include <QWidget>
#include <QTimer>

#include <opencv2/opencv.hpp>

class FileImageSource : public AbstractImageSource
{
    Q_OBJECT
public:
    explicit FileImageSource(QWidget *parent = 0);
    ~FileImageSource();

    
public slots:
    virtual bool capture();
    void sendCaptured() { emit captured(image); }

signals:
    //void captured(cv::Mat image);
    
private:
    bool isInitialized;

    QString filename;
    QString dir;
    QWidget *parent;

    cv::Mat image;
    QTimer *timer;

    void Initialize();
    bool readImage();
};

#endif // FILEIMAGESOURCE_H
