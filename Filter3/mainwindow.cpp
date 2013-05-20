#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Filter3");

    mov = new WebcameraImageSource(-1, 30, this, ui->choiceWidget);
    //mov = new FileImageSource(this);
    //processor = new CannyImageProcessor(20, this);
    processor = new HoughCircles(this, ui->choiceWidget);
    preprocessor = new GuassianBlur(this, ui->choiceWidget);

    connect(mov, SIGNAL(captured(cv::Mat)), preprocessor, SLOT(process(cv::Mat)));
    connect(preprocessor, SIGNAL(processed(cv::Mat)), processor, SLOT(process(cv::Mat)));
    connect(mov, SIGNAL(captured(cv::Mat)), this, SLOT(displayIncoming(cv::Mat)));
    connect(processor, SIGNAL(processed(cv::Mat)), this, SLOT(display(cv::Mat)));

    mov->capture();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mov;
}

void MainWindow::displayIncoming(cv::Mat image)
{
    QImage img;
    if (image.channels() == 3)
    {
        cv::cvtColor(image, image, CV_BGR2RGB);
        img = QImage( (uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    }
    else if (image.channels() == 1)
    {
        img = QImage( (uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
    }
    ui->image->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::display(cv::Mat image)
{
    QImage img;
    if (image.channels() == 3)
    {
        cv::cvtColor(image, image, CV_BGR2RGB);
        img = QImage( (uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    }
    else if (image.channels() == 1)
    {
        img = QImage( (uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
    }
    ui->outImage->setPixmap(QPixmap::fromImage(img));
}

