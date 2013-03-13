#include "FileImageSource.h"

#include <QFileDialog>

#include <opencv2/opencv.hpp>

FileImageSource::FileImageSource(QWidget *parent) : parent(parent)
{
    isInitialized = false;
    filename = QString();
    dir = QString();
    capture();
}

FileImageSource::~FileImageSource()
{
    if (isInitialized)
        isInitialized = false;
}

bool FileImageSource::capture()
{
    if (!isInitialized)
        Initialize();
    bool isOk = readImage();
    if (isOk)
        emit captured(image);
    return isOk;
}

void FileImageSource::Initialize()
{
    filename = QFileDialog::getOpenFileName(parent,
                                            tr("Open Image"),
                                            dir,
                                            tr("Image files (*.png *.jpg *.jpeg *.bmp)")
                                            );
    dir = QFileInfo(filename).absolutePath();
    isInitialized = true;
}

bool FileImageSource::readImage()
{
    if (!isInitialized)
        return false;
    image = cv::imread(filename.toAscii().constData());
    if (image.empty())
        return false;
    return true;
}
