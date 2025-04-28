#include "backstarenemy.h"

BackStarEnemy::BackStarEnemy(int dir)
    :direction(dir)
{
    figureTimer=new QTimer(this);
    moveTimer = new QTimer(this);
    changeDirection=new QTimer(this);
    connect(figureTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/backStarEnemy%1.png").arg(min++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(min>max)
        {
            min=1;
        }
    });
    connect(moveTimer,&QTimer::timeout,this,&BackStarEnemy::move);
    connect(changeDirection,&QTimer::timeout,this,&BackStarEnemy::judgeDirection);
    figureTimer->start(100);
    moveTimer->start(100);
    changeDirection->start(2000);
}

void BackStarEnemy::judgeDirection()
{
    if(direction==1)
    {
        direction=-1;
    }
    else if(direction==-1)
    {
        direction=1;
    }
}

void BackStarEnemy::move()
{
    setPos(x(),y()+speed*direction);
}
