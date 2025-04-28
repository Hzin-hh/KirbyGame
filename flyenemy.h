#ifndef FLYENEMY_H
#define FLYENEMY_H

#include <QObject>
#include"enemy.h"
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>

class FlyEnemy : public Enemy
{
    Q_OBJECT
public:
    explicit FlyEnemy();
    void move();
    void swallowedLeft() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedFlyingEnemy%1.png").arg(swallowedMin++);
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
        walkLeftTimer->stop();
        walkRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedFlyingEnemy%1.png").arg(swallowedMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(swallowedMin>swallowedMax)
        {
            swallowedMin=1;
        }
    }
    void stopSwallowed() override{
        walkLeftTimer->start(100);
    }
    void judgeDirection();
private:
    QTimer* walkLeftTimer;
    QTimer* walkRightTimer;
    QTimer* moveTimer;
    int walkMin=1;
    int walkMax=5;
    int speedX=5;
    int speedY=5;
    int directionX=-1;
    int directionY=-1;
    int swallowedMin=1;
    int swallowedMax=2;
signals:
};

#endif // FLYENEMY_H
