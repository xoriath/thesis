#include "WebcameraImageSource.h"

WebcameraImageSource::WebcameraImageSource(int source, QWidget *parent) : parent(parent)
{
    capture = new cv::VideoCapture(source);
    isIntialized = capture->isOpened();
}

WebcameraImageSource::WebcameraImageSource(QString source, QWidget *parent) : parent(parent)
{
    capture = new cv::VideoCapture(source.toStdString());
    isIntialized = capture->isOpened();
}

bool WebcameraImageSource::resume()
{
    if (!isIntialized)
        return false;
}

bool WebcameraImageSource::stop()
{
    if (!isIntialized)
        return false;

}

bool WebcameraImageSource::capture()
{
    if (!isIntialized)
        return false;

}
