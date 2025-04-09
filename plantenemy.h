#ifndef PLANTENEMY_H
#define PLANTENEMY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>
#include"enemy.h"

class PlantEnemy : public Enemy
{
    Q_OBJECT
public:
    explicit PlantEnemy();
    ~PlantEnemy()
    {
        delete moveTimer;
    }
    QTimer* moveTimer;
    void swallowedLeft() override{
        return;
    }
    void swallowedRight() override{
        return;
    }
    void stopSwallowed() override{
        return;
    }
private:
    int moveMin=1;
    int moveMax=7;
signals:
};

#endif // PLANTENEMY_H
