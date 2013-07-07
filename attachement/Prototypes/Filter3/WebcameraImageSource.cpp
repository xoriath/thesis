#include "WebcameraImageSource.h"

WebcameraImageSource::WebcameraImageSource(int source, int fps, QWidget *parent, QTabWidget *settings) : parent(parent)
{
    mCapture = new cv::VideoCapture(source);
    isIntialized = mCapture->isOpened();
    settingsWidget = settings;
    dev = QString(source);
    if (fps == 0)
    {
        double _fps = mCapture->get(CV_CAP_PROP_FPS);
        fps = (int) round(_fps);
    }
    this->settings = new WebcameraImageSourceSettings();
    this->settingsWidget->addTab(this->settings, QString("Movie"));
    setupTimer(fps);
}

WebcameraImageSource::WebcameraImageSource(QString source, int fps, QWidget *parent, QTabWidget *settings) : parent(parent)
{
    mCapture = new cv::VideoCapture(source.toStdString());
    isIntialized = mCapture->isOpened();
    dev = source;
    if (fps == 0)
    {
        double _fps = mCapture->get(CV_CAP_PROP_FPS);
        fps = (int) round(_fps);
    }
    settingsWidget = settings;
    this->settings = new WebcameraImageSourceSettings();
    this->settingsWidget->addTab(this->settings, QString("Movie"));
    setupTimer(fps);
}

WebcameraImageSource::~WebcameraImageSource()
{
    if (!isIntialized)
        return;
    timer->stop();

    delete timer;
    delete mCapture;
}

void WebcameraImageSource::setupTimer(int fps)
{
    timer = new QTimer();
    timer->setInterval(1.0/fps * 1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(capture()));
    timer->start();
}

bool WebcameraImageSource::resume()
{
    if (!isIntialized)
        return false;
    timer->start();
    return timer->isActive();
}

bool WebcameraImageSource::stop()
{
    if (!isIntialized)
        return false;
    timer->stop();
    return !timer->isActive();
}

bool WebcameraImageSource::capture()
{
    if (!isIntialized)
        return false;
    *mCapture >> imageBuffer;

    if (imageBuffer.empty())
        return false;
    updateInfo();
    emit captured(imageBuffer);
    return true;

}
