#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mov = new WebcameraImageSource(0, 30, this);
    connect(mov, SIGNAL(captured(cv::Mat)), this, SLOT(display(cv::Mat)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display(cv::Mat image)
{
    QImage img = QImage( (uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    ui->image->setPixmap(QPixmap::fromImage(img));
}

