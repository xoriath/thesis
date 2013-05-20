#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "WebcameraImageSource.h"
#include "FileImageSource.h"
#include "CannyImageProcessor.h"
#include "HoughCircles.h"
#include "GuassianBlur.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    AbstractImageSource *mov;
    AbstractImageProcessor *processor;
    AbstractImageProcessor *preprocessor;

private slots:
    void display(cv::Mat image);
    void displayIncoming(cv::Mat image);
};

#endif // MAINWINDOW_H
