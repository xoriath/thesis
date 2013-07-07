#ifndef LAPLACIANDATA_H
#define LAPLACIANDATA_H

#include <QDialog>

namespace Ui {
class laplaciandata;
}

class LaplacianData : public QDialog
{
    Q_OBJECT
    
public:
    explicit LaplacianData(QWidget *parent = 0);
    ~LaplacianData();
    int depth;
    
private slots:
    void on_spinBox_editingFinished();

    void on_okButton_clicked();

private:
    Ui::laplaciandata *ui;
};

#endif // LAPLACIANDATA_H
