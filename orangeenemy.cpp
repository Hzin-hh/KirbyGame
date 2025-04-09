#include "orangeenemy.h"


OrangeEnemy::OrangeEnemy(bool isSlope)
{
    this->isSlope=isSlope;
    walkLeftTimer = new QTimer(this);
    walkRightTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    connect(walkLeftTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/waddle%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });
    connect(walkRightTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/waddle%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });
    connect(moveTimer,&QTimer::timeout,this,&OrangeEnemy::move);
    walkLeftTimer->start(100);
    moveTimer->start(100);
}

void OrangeEnemy::move()
{

    if(isSlope)
    {
    setX(x()+speed*direction);
    setY(Enemy::lerp(x(),270, 1450, 590, 1310));
    if(x()<=270)
    {
        direction=1;
        judgeDirection();
    }
    if(x()>=590)
    {
        direction=-1;
        judgeDirection();

    }
    }
    else
    {
        setPos(x()+speed*direction,1310);
        if(x()<=590)
        {
            direction=1;
            judgeDirection();
        }
        if(x()>=700)
        {
            direction=-1;
            judgeDirection();
        }
    }
}

void OrangeEnemy::judgeDirection()
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
