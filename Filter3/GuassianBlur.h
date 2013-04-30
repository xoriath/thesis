#ifndef GUASSIANBLUR_H
#define GUASSIANBLUR_H

#include "AbstractImageProcessor.h"

#include <QTabWidget>
#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>

class OddSpinBox : public QSpinBox {
public:
    OddSpinBox() : QSpinBox() {}
private:
    QValidator::State validate(QString &input, int &pos) const;
};

class GuassianBlurSettings : public QWidget
{
    Q_OBJECT
public:
    explicit GuassianBlurSettings()
        : QWidget() {
        Sigma1 = Sigma2 = 0;
        xKernel = yKernel = 9;

        QLabel *xKernelL = new QLabel(QString("Kernel X size:"));
        QLabel *yKernelL = new QLabel(QString("Kernel Y size:"));
        OddSpinBox *xKernelS = new OddSpinBox();
        OddSpinBox *yKernelS = new OddSpinBox();
        xKernelS->setValue(xKernel);
        yKernelS->setValue(yKernel);
        xKernelS->setSingleStep(2);
        yKernelS->setSingleStep(2);
        xKernelS->setMaximum(999);
        yKernelS->setMaximum(999);
        xKernelS->setMinimum(1);
        yKernelS->setMinimum(1);

        QLabel *sigma1 = new QLabel(QString("Sigma 1:"));
        QLabel *sigma2 = new QLabel(QString("Sigma 1:"));
        OddSpinBox *sigma1S = new OddSpinBox();
        OddSpinBox *sigma2S = new OddSpinBox();
        sigma1S->setValue(Sigma1);
        sigma2S->setValue(Sigma2);


        connect(yKernelS, SIGNAL(valueChanged(int)), this, SLOT(setYKernel(int)));
        connect(xKernelS, SIGNAL(valueChanged(int)), this, SLOT(setXKernel(int)));
        connect(sigma1S, SIGNAL(valueChanged(int)), this, SLOT(setSigma1(int)));
        connect(sigma2S, SIGNAL(valueChanged(int)), this, SLOT(setSigma2(int)));

        QGridLayout *cont = new QGridLayout(this);
        cont->addWidget(xKernelL, 0,0);
        cont->addWidget(yKernelL, 1, 0);
        cont->addWidget(xKernelS, 0,1);
        cont->addWidget(yKernelS, 1,1);
        cont->addWidget(sigma1, 2,0);
        cont->addWidget(sigma2, 3,0);
        cont->addWidget(sigma1S, 2,1);
        cont->addWidget(sigma2S, 3,1);

        this->setLayout(cont);
    }

    int xKernel;
    int yKernel;
    int Sigma1;
    int Sigma2;
private slots:
    void setXKernel(int val) { xKernel = val;}
    void setYKernel(int val) { yKernel = val;}
    void setSigma1(int val) { Sigma1 = val;}
    void setSigma2(int val) { Sigma2 = val;}

};

class GuassianBlur : public AbstractImageProcessor
{
    Q_OBJECT
public:
    GuassianBlur(QWidget *parent, QTabWidget *settings);
    virtual bool isInitialized() { return true; }
public slots:
    virtual bool process(cv::Mat image);

signals:
    //void processed(cv::Mat image);
private:
    QWidget *parent;
    QTabWidget *settings;
    GuassianBlurSettings *settingsWidget;
};

#endif // GUASSIANBLUR_H
