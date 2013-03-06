#include "imagehelper.h"

ImageHelper::ImageHelper()
{
}

QImage ImageHelper::cv2qt(const cv::Mat &image, QImage::Format format)
{
    if (image.empty())
        return QImage();

    return QImage( (uchar*)image.data, image.cols, image.rows, image.step, format);
}

cv::Mat ImageHelper::getRed(const cv::Mat &image)
{
    return getChannel(image, 0);
}

cv::Mat ImageHelper::getChannel(const cv::Mat &image, uint channel)
{
    cv::Mat out(image.rows, image.cols, CV_8U);
    for (uint i = 0; i < image.rows; ++i)
    {
        for (uint j = 0; j < image.cols; ++j)
        {
            out.at<uchar>(i,j) = image.at<cv::Vec3i>(i,j)[channel];
        }
    }

    return out;
}
