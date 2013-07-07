#ifndef HOUGHCIRCLES_H
#define HOUGHCIRCLES_H

#include <vector>
#include <opencv2/opencv.hpp>

#include <QTabWidget>
#include <QSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "AbstractImageProcessor.h"

class HoughSettings;

class HoughCircles : public AbstractImageProcessor
{
    Q_OBJECT
public:
    HoughCircles(QWidget *parent, QTabWidget *settings);
    virtual bool isInitialized() { return initialized; }

public slots:
    virtual bool process(cv::Mat image);

signals:
    void processed(cv::Mat image);

private:
    bool initialized;
    QWidget *parent;
    QTabWidget* settings;
    HoughSettings *settingsWidget;
};

class HoughSettings : public QWidget
{
    Q_OBJECT

public:
    explicit HoughSettings(QWidget *parent = 0)
        : QWidget(parent) {
        Param1 = 200;
        Param2 = 100;
        minRadius = 0;
        maxRadius = 0;
        distValue = 50;

        QSpinBox *param1 = new QSpinBox();
        param1->setMaximum(1000);
        param1->setValue(Param1);
        QLabel *param1_text = new QLabel(QString("Param 1:"));

        QSpinBox *param2 = new QSpinBox();
        param2->setMaximum(1000);
        param2->setValue(Param2);
        QLabel *param2_text = new QLabel(QString("Param 2:"));

        QSpinBox *dist = new QSpinBox();
        dist->setMaximum(1000);
        dist->setValue(distValue);
        QLabel *dist_text = new QLabel(QString("Distance:"));

        QSpinBox *minR = new QSpinBox();
        minR->setMaximum(1000);
        minR->setValue(minRadius);
        QLabel *minR_text = new QLabel(QString("Minimal radius:"));

        QSpinBox *maxR = new QSpinBox();
        maxR->setMaximum(1000);
        maxR->setValue(maxRadius);
        QLabel *maxR_text = new QLabel(QString("Maximal Radius:"));

        connect(param1, SIGNAL(valueChanged(int)),this, SLOT(setParam1(int)));
        connect(param2, SIGNAL(valueChanged(int)),this, SLOT(setParam2(int)));
        connect(dist, SIGNAL(valueChanged(int)),this, SLOT(setDistance(int)));
        connect(maxR, SIGNAL(valueChanged(int)),this, SLOT(setMaxRadius(int)));
        connect(minR, SIGNAL(valueChanged(int)),this, SLOT(setMinRadius(int)));



        QGridLayout *cont = new QGridLayout();

        cont->addWidget(param1_text,1,1);
        cont->addWidget(param1, 1,2);

        cont->addWidget(param2_text,2,1);
        cont->addWidget(param2, 2,2);

        cont->addWidget(dist_text,3,1);
        cont->addWidget(dist, 3,2);

        cont->addWidget(minR_text,4,1);
        cont->addWidget(minR, 4,2);

        cont->addWidget(maxR_text,5,1);
        cont->addWidget(maxR, 5,2);

        this->setLayout(cont);
    }
    virtual ~HoughSettings(){}

    int Param1;
    int Param2;
    int minRadius;
    int maxRadius;
    int distValue;

private slots:
    void setParam1(int val) { Param1 = val;}
    void setParam2(int val) { Param2 = val;}
    void setDistance(int val) { distValue = val; }
    void setMinRadius(int val) { minRadius = val; }
    void setMaxRadius(int val) { maxRadius = val; }
};

#endif // HOUGHCIRCLES_H
