#ifndef FILEIMAGESOURCE_H
#define FILEIMAGESOURCE_H

#include "AbstractImageSource.h"

#include <QString>
#include <QWidget>

#include <opencv2/opencv.hpp>

class FileImageSource : public AbstractImageSource
{
    Q_OBJECT
public:
    explicit FileImageSource(QWidget *parent = 0);
    ~FileImageSource();

    
public slots:
    virtual bool capture();

signals:
    void captured(cv::Mat image);
    
private:
    bool isInitialized;

    QString filename;
    QString dir;
    QWidget *parent;

    cv::Mat image;

    void Initialize();
    bool readImage();
};

#endif // FILEIMAGESOURCE_H
