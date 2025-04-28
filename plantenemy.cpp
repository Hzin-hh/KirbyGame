#include "plantenemy.h"

PlantEnemy::PlantEnemy()
{
    moveTimer=new QTimer(this);
    connect(moveTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/plantEnemy%1.png").arg(moveMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(moveMin>moveMax)
        {
            moveMin=1;
        }
    });
    moveTimer->start(200);
}
