#ifndef ICEMANENEMY_H
#define ICEMANENEMY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>
#include"enemy.h"

class IceManEnemy : public Enemy
{
    Q_OBJECT
public:
    explicit IceManEnemy();
    void move();
    void swallowedLeft() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedIceManEnemy1.png");
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
    }
    void swallowedRight() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedIceManEnemy1.png");;
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
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
    int walkMax=4;
    int speed=5;
    int direction=-1;
    const qreal scale=1.5;
signals:
};

#endif // ICEMANENEMY_H
