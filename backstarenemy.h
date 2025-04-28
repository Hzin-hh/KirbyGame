#ifndef BACKSTARENEMY_H
#define BACKSTARENEMY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>
#include"enemy.h"

class BackStarEnemy : public Enemy
{
    Q_OBJECT
public:
    explicit BackStarEnemy(int dir);
    void move();
    void swallowedLeft() override{
        return;
    }
    void swallowedRight() override{
        return;
    }
    void stopSwallowed() override{
        return;
    }
    void judgeDirection();
private:
    QTimer* figureTimer;
    QTimer* changeDirection;
    QTimer* moveTimer;
    int min=1;
    int max=4;
    int direction;
    int speed=8;

signals:
};

#endif // BACKSTARENEMY_H
