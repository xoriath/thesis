#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QElapsedTimer>

#include <opencv2/opencv.hpp>

#include "gaussianblurdata.h"
#include "laplaciandata.h"

namespace Ui {
class MainWindow;
}

enum ActiveTransform {NONE = 0, GAUSSIAN_BLUR, FLIP, LAPLACIAN, FLOW};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    GaussianBlurData *gaussian;
    LaplacianData *laplacian;

    cv::VideoCapture cam;
    cv::Mat rawImage;
    cv::Mat transformedImage;

    QElapsedTimer *ticTimer;
    ActiveTransform transform;
    quint64 iteration;
    quint64 mean;

    QTimer* captureTimer;

    void resetAverageTimer();
    void doCapture();
    void doGaussianBlur();
    void doFlip();
    void doLaplacian();
    void doMotionTrack();

    bool init;
private slots:
    void capture();
    void updateGui();

    void on_noTransformRadioButton_clicked();

    void on_gaussianBlurRadioBox_clicked();

    void on_flipRadioButton_clicked();

    void on_laplacianRadioButton_clicked();

    void on_motionTrackRadioButton_clicked();

protected:
    void runImageTransform();
};

#endif // MAINWINDOW_H
