#ifndef WEBCAMERAIMAGESOURCE_H
#define WEBCAMERAIMAGESOURCE_H

#include "AbstractLinearMovieSource.h"

#include <QWidget>

class WebcameraImageSource : public AbstractLinearMovieSource
{
    Q_OBJECT
public:
    explicit WebcameraImageSource(QWidget *parent = 0);

signals:
    
public slots:
    
private:
    QWidget *parent;
};

#endif // WEBCAMERAIMAGESOURCE_H
