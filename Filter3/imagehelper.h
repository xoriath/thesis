#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H

#include <opencv2/opencv.hpp>

#include <QImage>

class ImageHelper
{
private:
    ImageHelper();

public:
    static QImage cv2qt(const cv::Mat &image, enum QImage::Format format);
};

#endif // IMAGEHELPER_H
