#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H

#include <opencv2/opencv.hpp>

#include <QImage>

class ImageHelper
{
private:
    ImageHelper();
    static cv::Mat getChannel(const cv::Mat &image, uint channel);

public:
    static QImage cv2qt(const cv::Mat &image, enum QImage::Format format);
    static cv::Mat getRed(const cv::Mat &image);
};

#endif // IMAGEHELPER_H
