#ifndef ORANGEENEMY_H
#define ORANGEENEMY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>
#include"enemy.h"

class OrangeEnemy : public Enemy
{
    Q_OBJECT
public:
    explicit OrangeEnemy(bool isSlope);
    ~OrangeEnemy()
    {
        delete walkLeftTimer;
        delete walkRightTimer;
        delete moveTimer;
    }
    void move();
    void swallowedLeft() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/waddleSuck.png");
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
    }
    void swallowedRight() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
        QPixmap pixmap;
        QString str=QString(":/res/waddleSuck.png");
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
    }
    void stopSwallowed() override{
        walkLeftTimer->start(100);
    }
    void judgeDirection();
    bool isSlope;
private:
    QTimer* walkLeftTimer;
    QTimer* walkRightTimer;
    QTimer* moveTimer;
    int walkMin=1;
    int walkMax=5;
    int speed=5;
    int direction=-1;
signals:
};

#endif // ORANGEENEMY_H
