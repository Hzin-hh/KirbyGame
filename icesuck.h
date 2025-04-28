#ifndef ICESUCK_H
#define ICESUCK_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QApplication>
#include<QPixmap>
#include<QGraphicsScene>
#include"mykirby.h"

class IceSuck : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit IceSuck();
    QTimer * suckTimer;
    void towardRight(bool toRight)
    {
        suckRight=toRight;
    }
    int suckMin=1;
    int suckMax=7;
    bool suckRight;
    QPixmap flip(QImage image);
signals:
};

#endif // ICESUCK_H
