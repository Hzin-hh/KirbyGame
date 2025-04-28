#include "icemanenemy.h"

IceManEnemy::IceManEnemy()
{
    walkLeftTimer = new QTimer(this);
    walkRightTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    connect(walkLeftTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/iceManEnemy%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });
    connect(walkRightTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/iceManEnemy%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });
    connect(moveTimer,&QTimer::timeout,this,&IceManEnemy::move);
    walkLeftTimer->start(100);
    moveTimer->start(100);
}

void IceManEnemy::move()
{
    setPos(x()+speed*direction,825*scale-770);
    if(x()<=2500*scale)
    {
        direction=1;
        judgeDirection();
    }
    if(x()>=2550*scale)
    {
        direction=-1;
        judgeDirection();
    }
}

void IceManEnemy::judgeDirection()
{
    if(direction==1)
    {
        if(!walkRightTimer->isActive())
        {
            walkLeftTimer->stop();
            walkRightTimer->start(100);
        }
    }
    else if(direction==-1)
    {
        if(!walkLeftTimer->isActive())
        {
            walkRightTimer->stop();
            walkLeftTimer->start(100);
        }
    }
}
