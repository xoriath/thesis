#include "laplaciandata.h"
#include "ui_laplaciandata.h"

LaplacianData::LaplacianData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::laplaciandata)
{
    ui->setupUi(this);
    depth = 2;
}

LaplacianData::~LaplacianData()
{
    delete ui;
}

void LaplacianData::on_spinBox_editingFinished()
{
    depth = ui->spinBox->value();
}

void LaplacianData::on_okButton_clicked()
{
    close();
}
