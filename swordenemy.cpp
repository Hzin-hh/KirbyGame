#include "swordenemy.h"

SwordEnemy::SwordEnemy(int dir,int t,bool change)
    :direction(dir),time(t),change(change)
{
    towardLeftTimer = new QTimer(this);
    towardRightTimer = new QTimer(this);
    changeDirection=new QTimer(this);
    connect(towardLeftTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/swordEnemy%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });
    connect(towardRightTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/swordEnemy%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });
    connect(changeDirection,&QTimer::timeout,this,&SwordEnemy::judgeDirection);
    towardLeftTimer->start(100);
    changeDirection->start(time);
}


void SwordEnemy::judgeDirection()
{
    if(direction==1)
    {
        if(!towardLeftTimer->isActive())
        {
            towardRightTimer->stop();
            towardLeftTimer->start(100);
        }
        direction=-1;
    }
    else if(direction==-1)
    {
        if(change)
        {
            if(!towardRightTimer->isActive())
            {
                towardLeftTimer->stop();
                towardRightTimer->start(100);
            }
        }
        direction=1;
    }
}


