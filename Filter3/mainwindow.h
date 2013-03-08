#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "WebcameraImageSource.h"
#include "CannyImageProcessor.h"

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
    AbstractLinearMovieSource *mov;
    AbstractImageProcessor *processor;
private slots:
    void display(cv::Mat image);
};

#endif // MAINWINDOW_H
