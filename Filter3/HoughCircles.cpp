#include "HoughCircles.h"

HoughCircles::HoughCircles()
{
    initialized = true;
}

bool HoughCircles::process(cv::Mat image)
{
    cv::Mat grey;
    image.copyTo(grey);
    if (grey.channels() == 3)
        cv::cvtColor(grey, grey, CV_BGR2GRAY);
    cv::GaussianBlur(grey, grey, cv::Size(9,9), 20, 20);
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(grey, circles,CV_HOUGH_GRADIENT,
                     2, image.rows/16
                     );
    for (size_t i = 0; i < circles.size(); ++i)
    {
        cv::Point center(round(circles[i][0]), round(circles[i][1]));
        int radius = round(circles[i][2]);
        cv::circle(image, center, 3, cv::Scalar(0,255,0));
        cv::circle(image, center,radius, cv::Scalar(0,0,255));
    }
    emit this->processed(image);
    return true;
}
