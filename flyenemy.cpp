#include "flyenemy.h"

FlyEnemy::FlyEnemy()
{
    walkLeftTimer = new QTimer(this);
    walkRightTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    connect(walkLeftTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/flyingEnemy%1.png").arg(walkMin++);
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
        QString str=QString(":/res/flyingEnemy%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });
    connect(moveTimer,&QTimer::timeout,this,&FlyEnemy::move);
    walkLeftTimer->start(100);
    moveTimer->start(100);
}
void FlyEnemy::move()
{
    setPos(x()+speedX*directionX,y()+speedY*directionY);
        if(x()<=350)
        {
            directionX=1;
            judgeDirection();
        }
        if(x()>=560)
        {
            directionX=-1;
            judgeDirection();
        }
        if(y()<=330)
        {
             directionY=1;
        }
        if(y()>=350)
        {
            directionY=-1;
        }
}

void FlyEnemy::judgeDirection()
{
    if(directionX==1)
    {
        if(!walkRightTimer->isActive())
        {
            walkLeftTimer->stop();
            walkRightTimer->start(100);
        }
    }
    else if(directionX==-1)
    {
        if(!walkLeftTimer->isActive())
        {
            walkRightTimer->stop();
            walkLeftTimer->start(100);
        }
    }
}


