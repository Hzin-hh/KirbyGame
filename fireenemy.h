#ifndef FIREENEMY_H
#define FIREENEMY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>
#include"enemy.h"

class FireEnemy : public Enemy
{
    Q_OBJECT
public:
    explicit FireEnemy(int l,int r);
    void move();
    void swallowedLeft() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedFireEnemy.png");
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
    }
    void swallowedRight() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/swallowedFireEnemy.png");
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
    int walkMax=5;
    int speed=5;
    int direction=-1;
    int leftX;
    int rightX;
signals:
};

#endif // FIREENEMY_H
