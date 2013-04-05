#include "GuassianBlur.h"


GuassianBlur::GuassianBlur(QWidget *parent, QTabWidget *settings)
{
    this->parent = parent;
    this->settings = settings;
    this->settingsWidget = new GuassianBlurSettings();
    this->settings->addTab(settingsWidget, QString("Gaussian Blur"));
}

bool GuassianBlur::process(cv::Mat image)
{
    cv::Mat out;
    cv::GaussianBlur(image, out, cv::Size(settingsWidget->xKernel,settingsWidget->yKernel),0,0);
    emit processed(out);
    return true;
}


QValidator::State OddSpinBox::validate(QString &input, int& /*pos*/) const
{
    bool isOK = false;
    int val = input.toInt(&isOK);
    if (!isOK)
        return QValidator::Intermediate;
    if (val % 2 == 0)
        return QValidator::Invalid;
    else
        return QValidator::Acceptable;
}
