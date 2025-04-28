#ifndef SWALLOWAIRSUCK_H
#define SWALLOWAIRSUCK_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QApplication>
#include<QPixmap>
#include<QGraphicsScene>
#include"mykirby.h"

class SwallowAirSuck : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SwallowAirSuck();
    QTimer * suckTimer;
    void towardRight(bool toRight)
    {
        suckRight=toRight;
    }
    int suckMin=1;
    int suckMax=4;
    bool suckRight;
    QPixmap flip(QImage image);
signals:
};

#endif // SWALLOWAIRSUCK_H
