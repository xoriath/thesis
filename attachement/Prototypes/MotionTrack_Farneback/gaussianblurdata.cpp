#include "gaussianblurdata.h"
#include "ui_gaussianblurdata.h"
#include "mainwindow.h"

GaussianBlurData::GaussianBlurData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianBlurData)
{
    ui->setupUi(this);
    setModal(true);
    sigma = 1.5;
    ySize = xSize = 9;
}

GaussianBlurData::~GaussianBlurData()
{
    delete ui;
}

void GaussianBlurData::on_sigmaBox_editingFinished()
{
    sigma = ui->sigmaBox->value();
}

void GaussianBlurData::on_ySizeBox_editingFinished()
{
    ySize = ui->ySizeBox->value();
}

void GaussianBlurData::on_xSizeBox_editingFinished()
{
    xSize = ui->xSizeBox->value();
}

void GaussianBlurData::on_okPushButon_clicked()
{
    close();
}
