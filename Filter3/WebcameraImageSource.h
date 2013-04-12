#ifndef WEBCAMERAIMAGESOURCE_H
#define WEBCAMERAIMAGESOURCE_H

#include "AbstractLinearMovieSource.h"

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QGridLayout>
#include <QTabWidget>

#include <opencv2/opencv.hpp>


class WebcameraImageSourceSettings : public QWidget
{
    Q_OBJECT
private:
    QLabel *fps_info;
    QLabel *dev_info;
public:
    explicit WebcameraImageSourceSettings()
        : QWidget() {

        QLabel *fps = new QLabel(QString("Frames per second: "));
        fps_info = new QLabel();

        QLabel *dev = new QLabel(QString("File: "));
        dev_info = new QLabel();

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(fps, 0, 0);
        layout->addWidget(fps_info, 0, 1);
        layout->addWidget(dev, 1, 0);
        layout->addWidget(dev_info, 1, 1);

        this->setLayout(layout);
    }

    void setFPS(double fps) {
        QString _fps = QString::number(fps);
        fps_info->setText(_fps);
    }

    void setDevice(const QString& dev) {
        dev_info->setText(dev);
    }
};

class WebcameraImageSource : public AbstractLinearMovieSource
{
    Q_OBJECT
public:
    explicit WebcameraImageSource(int source, int fps = 0, QWidget *parent = 0, QTabWidget *settings = 0);
    explicit WebcameraImageSource(QString source, int fps = 0, QWidget *parent = 0, QTabWidget *settings = 0);

    ~WebcameraImageSource();
    virtual bool resume();
    virtual bool stop();
    
    void setupTimer(int fps);
private:
    QWidget *parent;
    QTimer  *timer;
    QTabWidget *settingsWidget;
    WebcameraImageSourceSettings *settings;

    cv::VideoCapture *mCapture;
    QString dev;
    cv::Mat imageBuffer;

    bool isIntialized;

    void updateInfo() {
        if (this->settings == NULL)
            return;
        this->settings->setFPS(mCapture->get(CV_CAP_PROP_FPS));
        this->settings->setDevice(dev);
    }

public slots:
    virtual bool capture();

signals:
    void captured(cv::Mat image);

};


#endif // WEBCAMERAIMAGESOURCE_H
