#ifndef STAR_H
#define STAR_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QApplication>
#include<QPixmap>
#include<QGraphicsScene>

class Star : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Star();
    ~Star()
    {
        delete star1Timer;
        delete star2Timer;
        delete star3Timer;
        delete moveTimer;
    }
    QTimer * star1Timer;
    QTimer * star2Timer;
    QTimer * star3Timer;
    QTimer * moveTimer;
    void setDirection(int dir)
    {
        direction=dir;
    }
    int direction;
signals:
};

#endif // STAR_H
