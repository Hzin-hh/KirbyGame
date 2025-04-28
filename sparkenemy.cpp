#include "sparkenemy.h"

SparkEnemy::SparkEnemy(qreal l,qreal y)
:leftX(l),rightX(y)
{
    walkLeftTimer = new QTimer(this);
    walkRightTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    connect(walkLeftTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/sparkEnemy%1.png").arg(walkMin++);
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
        QString str=QString(":/res/sparkEnemy%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=Enemy::flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });
    connect(moveTimer,&QTimer::timeout,this,&SparkEnemy::move);
    walkLeftTimer->start(100);
    moveTimer->start(100);
}

void SparkEnemy::move()
{
        setX(x()+speed*direction);
        if(x()<=leftX)
        {
            direction=1;
            judgeDirection();
        }
        if(x()>=rightX)
        {
            direction=-1;
            judgeDirection();
        }
}

void SparkEnemy::judgeDirection()
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
