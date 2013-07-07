#include "CannyImageProcessor.h"

#include <opencv2/opencv.hpp>

CannyImageProcessor::CannyImageProcessor(int threshold, QWidget *parent)
{
    initialized = true;
    this->threshold = threshold;
    this->parent = parent;
}

bool CannyImageProcessor::process(cv::Mat image)
{
    if (!initialized)
        return false;
    if (image.channels() == 3)
        cv::cvtColor(image, image, CV_BGR2GRAY);
    cv::Canny(image, image, threshold, threshold + 30);
    emit processed(image);
    return true;
}
