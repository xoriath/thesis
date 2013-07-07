#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gaussian(new GaussianBlurData(this)),
    laplacian(new LaplacianData(this))
{
    ui->setupUi(this);
    setWindowTitle("Cam Filters");

    iteration = 0;
    mean = 0;

    QString file = QFileDialog::getOpenFileName(this, QString("Open video file"));

    cam.open(file.toUtf8().data());
    if (!cam.isOpened()) {
        qDebug() << "Error opening " << file;
        QMessageBox box;
        box.setText("Error opening CAM0");
        box.setIcon(QMessageBox::Critical);
        box.setModal(true);
        box.show();
        QCoreApplication::exit();
    }
    else {
        captureTimer = new QTimer(this);
        connect(captureTimer, SIGNAL(timeout()), this, SLOT(capture()));
        MainWindow::on_motionTrackRadioButton_clicked();
        captureTimer->start(1.0/24);
        init = true;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::doGaussianBlur()
{
    if (!rawImage.empty()) {
        try {
            cv::GaussianBlur(rawImage, transformedImage, cv::Size(gaussian->xSize, gaussian->ySize), gaussian->sigma);
        }
        catch (cv::Exception e) {
            qDebug() << e.what();
            transform = NONE;
        }
    }

}

void MainWindow::doLaplacian()
{
    if (!rawImage.empty()) {
        try {
            cv::Laplacian(rawImage, transformedImage, laplacian->depth);
        }
        catch (cv::Exception e) {
            qDebug() << e.what();
            transform = NONE;
        }
    }

}

const int MAX_COUNT = 2500;

void MainWindow::doMotionTrack()
{
    static const cv::TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
    static cv::Mat gray, prevGray;

    static std::vector<cv::Point2f> points[2];

    if (!rawImage.empty()) {
        try {
            cv::cvtColor(rawImage, gray, CV_RGB2GRAY);
            rawImage.copyTo(transformedImage);

            if (init) {
                init = false;
                cv::goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 1);
                cv::cornerSubPix(gray, points[1],cv::Size(5,5), cv::Size(-1,-1),termcrit);
                qDebug() << "Doing flow init, found " << points[1].size() << " interesting points.";
            }
            else if( !points[0].empty() ) {
                std::vector<uchar> status;
                std::vector<float> err;
                if(prevGray.empty())
                    gray.copyTo(prevGray);
                calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err);
                size_t i, k;
                for(i = k = 0; i < points[1].size(); i++ ) {
                    if( !status[i] )
                        continue;
                    points[1][k++] = points[1][i];
                    cv::circle( transformedImage, points[1][i], 3, cv::Scalar(255,0,0));
                }
                points[1].resize(k);
            }
            std::swap(points[1], points[0]);
            cv::swap(prevGray, gray);
        }
        catch (cv::Exception e) {
            qDebug() << e.what();
            transform = NONE;
        }
    }
}

void MainWindow::doFlip()
{
    if (!rawImage.empty())
    {
        cv::flip(rawImage, transformedImage, 1);
    }
}

void MainWindow::doCapture()
{
    cam >> rawImage;
}

void MainWindow::capture()
{
    doCapture();
    if (rawImage.empty())
        return;
    cv::cvtColor(rawImage, rawImage, CV_BGR2RGB);
    runImageTransform();
    updateGui();
}

void MainWindow::updateGui()
{
    if (!rawImage.empty())
    {
        QImage img( (uchar*)rawImage.data, rawImage.cols, rawImage.rows, rawImage.step, QImage::Format_RGB888);

        ui->rawImage->setPixmap(QPixmap::fromImage(img));
        ui->rawImage->resize(img.size());
    }
    if (!transformedImage.empty())
    {
        QImage img( (uchar*)transformedImage.data, transformedImage.cols, transformedImage.rows, transformedImage.step, QImage::Format_RGB888);

        ui->transformedImage->setPixmap(QPixmap::fromImage(img));
        ui->transformedImage->resize(img.size());
    }
}

void MainWindow::runImageTransform()
{
    ticTimer = new QElapsedTimer();
    ticTimer->start();
    switch (transform)
    {
        case GAUSSIAN_BLUR:
            doGaussianBlur();
            break;
        case FLIP:
            doFlip();
            break;
        case LAPLACIAN:
            doLaplacian();
            break;
        case FLOW:
            doMotionTrack();
            break;
        case NONE:
        default:
            break;
    }
    quint64 nanoSec = ticTimer->nsecsElapsed();

    iteration++;
    mean = ((iteration-1.0)/iteration) * mean + (1.0/iteration)*nanoSec;
    ui->avgTimeLabel->setText(QString::number(mean));
    delete ticTimer;
}

void MainWindow::resetAverageTimer()
{
    iteration = 0;
    mean = 0;
    init = true;
}

void MainWindow::on_noTransformRadioButton_clicked()
{
    transform = NONE;
    qDebug() << "SET NONE";
    resetAverageTimer();
}

void MainWindow::on_gaussianBlurRadioBox_clicked()
{
    gaussian->show();
    transform = GAUSSIAN_BLUR;
    qDebug() << "SET GAUSSIAN";
    resetAverageTimer();

}

void MainWindow::on_flipRadioButton_clicked()
{
    transform = FLIP;
    qDebug() << "SET FLIP";
    resetAverageTimer();
}

void MainWindow::on_laplacianRadioButton_clicked()
{
    laplacian->show();
    transform = LAPLACIAN;
    qDebug() << "SET LAPLACIAN";
    resetAverageTimer();
}

void MainWindow::on_motionTrackRadioButton_clicked()
{
    transform = FLOW;
    qDebug() << "SET MOTION TRACKING";
    resetAverageTimer();
}
