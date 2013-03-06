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
