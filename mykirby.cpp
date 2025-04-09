#include "mykirby.h"
#include<QDebug>
#include"playscene.h"

MyKirby::MyKirby()
{

    timerR=new QTimer(this);
    timerL=new QTimer(this);
    flyRightTimer=new QTimer(this);
    flyLeftTimer=new QTimer(this);
    bendTimer=new QTimer(this);
    bendTimer2=new QTimer(this);
    landTimer=new QTimer(this);
    fightTimer=new QTimer(this);
    swallowTimer=new QTimer(this);
    swallowTimer2=new QTimer(this);
    fatTimerR=new QTimer(this);
    fatTimerL=new QTimer(this);

    //定时器操作
    connect(timerR,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_walk%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio/*忽略原本宽高比*/, Qt::SmoothTransformation/*平滑变换算法*/);
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
            {
            walkMin=1;
        }
    });

    connect(timerL,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_walk%1.png").arg(walkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });

    connect(flyRightTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_fly%1.png").arg(flyMax--);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(flyMax<flyMin)
        {
            flyMax=8;
        }
    });

    connect(flyLeftTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_fly%1.png").arg(flyMax--);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(flyMax<flyMin)
        {
            flyMax=8;
        }
    });

    connect(bendTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Bend2.png");
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
    });

    connect(bendTimer2,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Bend1.png");
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
    });

    connect(landTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Land%1.png").arg(landMin++);
        pixmap.load(str);
        QPixmap scaledPixmap;
        if(towardRight==true)
            {
        scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        if(towardLeft==true)
        {
            scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(landMin>landMax)
        {
            landTimer->stop();

        }

    });

    connect(fightTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Fight%1.png").arg(fightMin++);
        pixmap.load(str);
        QPixmap scaledPixmap;
        if(towardRight==true)
        {
            scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        if(towardLeft==true)
        {
            scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(fightMin>fightMax)
        {
            isFighting=false;
            fightTimer->stop();
        }

    });

    connect(swallowTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Swallow%1.png").arg(swallowMin++);
        pixmap.load(str);
        QPixmap scaledPixmap;
        if(towardRight==true)
        {
            scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        if(towardLeft==true)
        {
            scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(swallowMin>swallowMax)
        {
            isSwallowing=false;
            swallowTimer->stop();
            swallowTimer2->start();
        }
    });

    connect(swallowTimer2,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Swallow5.png");
        pixmap.load(str);
        QPixmap scaledPixmap;
        if(towardRight==true)
        {
            scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        if(towardLeft==true)
        {
            scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
    });

    connect(fatTimerR,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Fatwalk%1.png").arg(fatWalkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(fatWalkMin>fatWalkMax)
        {
            fatWalkMin=1;
        }
    });

    connect(fatTimerL,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Fatwalk%1.png").arg(fatWalkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
        if(fatWalkMin>fatWalkMax)
        {
            fatWalkMin=1;
        }
    });
    flyRightTimer->start(100);
}

//正常状态往右走
void MyKirby::moveRight()
{
    if(!timerR->isActive())
    {
    timerL->stop();
    timerR->start(100);
    }
}

//图片翻转
QPixmap MyKirby::flip(QImage image)
{
    image=image.mirrored(true,false);
    QPixmap pix1=QPixmap::fromImage(image);
    return pix1;
}

void MyKirby::moveLeft()
{
    if(!timerL->isActive())
    {
    timerR->stop();
    timerL->start(100);
    }
}

//静止不动
void MyKirby::origin()
{
    fightTimer->stop();
    bendTimer->stop();
    bendTimer2->stop();
    flyRightTimer->stop();
    flyLeftTimer->stop();
    timerR->stop();
    timerL->stop();
    landTimer->stop();
    fatTimerL->stop();
    fatTimerR->stop();
    if(towardRight==true)
    {
        QPixmap walkPixmap;
        if(!fat)
        {
        walkPixmap.load(":/res/Kirby_Origin.png");
        }
        else
        {
            walkPixmap.load(":/res/Kirby_Fat.png");
        }
        QPixmap scaledWalkPixmap=walkPixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledWalkPixmap);
        towardRight=true;
    }
    if(towardLeft==true)
    {
        QPixmap walkPixmap;
        if(!fat)
        {
            walkPixmap.load(":/res/Kirby_Origin.png");
        }
        else
        {
            walkPixmap.load(":/res/Kirby_Fat.png");
        }
        QPixmap scaledWalkPixmap=walkPixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledWalkPixmap=flip(scaledWalkPixmap.toImage());
        setPixmap(scaledWalkPixmap);
        towardLeft=true;
    }
}

//飞行状态朝右
void MyKirby::flyRight()
{
    if(!flyRightTimer->isActive())
    {
    timerL->stop();
    timerR->stop();
    fatTimerL->stop();
    fatTimerR->stop();
    flyLeftTimer->stop();
    flyRightTimer->start(50);
    towardRight=true;
    towardLeft=false;
    }
}

//飞行状态朝左
void MyKirby::flyLeft()
{
    if(!flyLeftTimer->isActive())
    {
    timerL->stop();
    timerR->stop();
    fatTimerL->stop();
    fatTimerR->stop();
    flyRightTimer->stop();
    flyLeftTimer->start(50);
    towardLeft=true;
    towardRight=false;
    }
}

//蹲下
void MyKirby::bend()
{
    isBending=true;
    if(!fat)
    {
        if(!bendTimer->isActive())
        {
            bendTimer->start();
        }
    }
    else
    {
        fat=false;
        if(!bendTimer2->isActive())
        {
            bendTimer2->start();
        }
    swallowSound->play();
    if(fatTimerL->isActive())
    {
    fatTimerL->stop();
    }
    if(fatTimerR->isActive())
    {
    fatTimerR->stop();
    }
    }
}

//落地
void MyKirby::land()
{
    if(!landTimer->isActive())
    {
    landMin = 1;
    landTimer->start(100);
    isLanding=true;
    }


}

//攻击
void MyKirby::fight()
{
    if(!fightTimer->isActive())
    {
        fightMin=1;
        fightTimer->start(50);
    }
}

//停止蹲下
void MyKirby::stopBend()
{
    bendTimer->stop();
}

//吞噬敌人
void MyKirby::swallow()
{
    if(!swallowTimer->isActive())
    {
        swallowMin=1;
        swallowTimer->start(60);
    }
}

//停止吞噬敌人
void MyKirby::stopSwallow()
{
    swallowTimer->stop();
    swallowTimer2->stop();
}

//吞噬成功
void MyKirby::finishSwallow()
{
    fat=true;
    timerL->stop();
    timerR->stop();
    swallowTimer->stop();
    swallowTimer2->stop();
    QPixmap pixmap;
    QString str=QString(":/res/Kirby_Fat.png");
    pixmap.load(str);
    QPixmap scaledPixmap;
    if(towardRight==true)
    {
        scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    if(towardLeft==true)
    {
        scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=flip(scaledPixmap.toImage());
    }
    setPixmap(scaledPixmap);
}

//吞噬状态往右走
void MyKirby::fatMoveRight()
{
    if(!fatTimerR->isActive())
    {
        fatTimerL->stop();
        fatTimerR->start(100);
    }
}

//吞噬状态往左走
void MyKirby::fatMoveLeft()
{
    if(!fatTimerL->isActive())
    {
        fatTimerR->stop();
        fatTimerL->start(100);
    }
}
