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
    explicit SwordEnemy(int dir,int t,bool change);
    void swallowedLeft() override{
        towardLeftTimer->stop();
        towardRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedSwordEnemy1.png");
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
    }
    void swallowedRight() override{
        towardLeftTimer->stop();
        towardRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedSwordEnemy1.png");
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
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
    int direction;
    int time;
    bool change;
signals:
};

#endif // SWORDENEMY_H
