#include "HoughCircles.h"

HoughCircles::HoughCircles(QWidget* parent, QTabWidget *settings)
{
    initialized = true;
    this->parent = parent;
    this->settings = settings;
    this->settingsWidget = new HoughSettings();

    this->settings->addTab(settingsWidget, QString("Hough Circles"));
}

bool HoughCircles::process(cv::Mat image)
{
    cv::Mat grey;
    cv::Mat result;
    cv::Rect roi(image.cols/3,image.rows/3,image.cols/3,image.rows/3);
    image.copyTo(grey);
    image.copyTo(result);
    if (grey.channels() == 3)
        cv::cvtColor(grey, grey, CV_BGR2GRAY);
    cv::GaussianBlur(grey, grey, cv::Size(9,9), 20, 20);

    std::vector<cv::Vec3f> circles;
    std::vector<cv::Point> centers;

    cv::HoughCircles(grey, circles,CV_HOUGH_GRADIENT,
                     2,
                     settingsWidget->distValue,
                     settingsWidget->Param1,
                     settingsWidget->Param2,
                     settingsWidget->minRadius,
                     settingsWidget->maxRadius
                     );

    //cv::rectangle(result, roi,cv::Scalar(255,0,0));
    for (size_t i = 0; i < circles.size(); ++i)
    {
        cv::Point center(round(circles[i][0]), round(circles[i][1]));
        //if (!roi.contains(center))
        //    continue;
        centers.push_back(center);
        int radius = round(circles[i][2]);
        cv::circle(result, center, 3, cv::Scalar(0,255,0),-1,8,0);
        cv::circle(result, center,radius, cv::Scalar(0,0,255),3,8,0);

    }

    emit processed(result);
    return true;
}
