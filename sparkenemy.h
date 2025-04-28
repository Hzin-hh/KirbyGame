#ifndef SPARKENEMY_H
#define SPARKENEMY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>
#include"enemy.h"

class SparkEnemy : public Enemy
{
    Q_OBJECT
public:
    explicit SparkEnemy(qreal l,qreal r);
    void move();
    void swallowedLeft() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
    }
    void swallowedRight() override{
        walkLeftTimer->stop();
        walkRightTimer->stop();
    }
    void stopSwallowed() override{
        walkLeftTimer->start(100);
    }
    void judgeDirection();
private:
    QTimer* walkLeftTimer;
    QTimer* walkRightTimer;
    QTimer* moveTimer;
    QTimer* changeTimer;
    qreal leftX;
    qreal rightX;
    int walkMin=1;
    int walkMax=8;
    int speed=5;
    int direction=-1;
signals:
};

#endif // SPARKENEMY_H
