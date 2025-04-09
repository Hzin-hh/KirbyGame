#ifndef SWORDENEMY_H
#define SWORDENEMY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>
#include"enemy.h"

class SwordEnemy : public Enemy
{
    Q_OBJECT
public:
    explicit SwordEnemy(int dir,int t);
    ~SwordEnemy()
    {
        delete towardLeftTimer;
        delete towardRightTimer;
        delete changeDirection;
    }
    void swallowedLeft() override{
        towardLeftTimer->stop();
        towardRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedSwordEnemy%1.png").arg(swallowedMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(swallowedMin>swallowedMax)
        {
            swallowedMin=1;
        }
    }
    void swallowedRight() override{
        towardLeftTimer->stop();
        towardRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedSwordEnemy%1.png").arg(swallowedMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(swallowedMin>swallowedMax)
        {
            swallowedMin=1;
        }
    }
    void stopSwallowed() override{
        towardLeftTimer->start(100);
    }
    void judgeDirection();
private:
    QTimer* towardLeftTimer;
    QTimer* towardRightTimer;
    QTimer* changeDirection;
    int walkMin=1;
    int walkMax=4;
    int swallowedMin=1;
    int swallowedMax=2;
    int direction;
    int time;
signals:
};

#endif // SWORDENEMY_H
