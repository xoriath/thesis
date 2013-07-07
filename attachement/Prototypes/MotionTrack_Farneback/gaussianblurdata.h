#ifndef GAUSSIANBLURDATA_H
#define GAUSSIANBLURDATA_H

#include <QDialog>

namespace Ui {
class GaussianBlurData;
}

class GaussianBlurData : public QDialog
{
    Q_OBJECT
    
public:
    explicit GaussianBlurData(QWidget *parent = 0);
    ~GaussianBlurData();
    double xSize;
    double ySize;
    double sigma;
    
private slots:
    void on_sigmaBox_editingFinished();

    void on_ySizeBox_editingFinished();

    void on_xSizeBox_editingFinished();

    void on_okPushButon_clicked();

private:
    Ui::GaussianBlurData *ui;
};

#endif // GAUSSIANBLURDATA_H
