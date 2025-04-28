#include "mykirby.h"
#include<QDebug>
#include"playscene.h"

MyKirby::MyKirby()
{

    walkTimer=new QTimer(this);
    flyTimer=new QTimer(this);
    bendTimer=new QTimer(this);
    landTimer=new QTimer(this);
    fightTimer=new QTimer(this);
    swallowTimer=new QTimer(this);
    swallowTimer2=new QTimer(this);
    fatTimer=new QTimer(this);
    jumpTimer=new QTimer(this);
    spitTimer=new QTimer(this);
    hurtTimer=new QTimer(this);
    sparkTimer=new QTimer(this);

    //定时器操作
    connect(walkTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str;
        if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
        {
            str=QString(":/res/Kirby_walk%1.png").arg(walkMin++);
        }
        else if(isIceKirby)
        {
            str=QString(":/res/iceKirby_walk%1.png").arg(walkMin++);
        }
        else if(isFireKirby)
        {
            str=QString(":/res/fireKirby_walk%1.png").arg(walkMin++);
        }
        else if(isSwordKirby)
        {
            str=QString(":/res/swordKirby_walk%1.png").arg(walkMin++);
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(walkMin>walkMax)
        {
            walkMin=1;
        }
    });

    connect(flyTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str;
        if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
        {
            str=QString(":/res/Kirby_fly%1.png").arg(flyMax--);
        }
        else if(isIceKirby)
        {
            str=QString(":/res/iceKirby_fly%1.png").arg(flyMax--);
        }
        else if(isFireKirby)
        {
            str=QString(":/res/fireKirby_fly%1.png").arg(flyMax--);
        }
        else if(isSwordKirby)
        {
            str=QString(":/res/swordKirby_fly%1.png").arg(flyMax--);
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(flyMax<flyMin)
        {
            flyMax=8;
        }
    });

    connect(bendTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str;
        if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
        {
            str=QString(":/res/Kirby_Bend2.png");
        }
        else if(isIceKirby)
        {
            str=QString(":/res/iceKirby_bend.png");
        }
        else if(isFireKirby)
        {
            str=QString(":/res/fireKirby_bend.png");
        }
        else if(isSwordKirby)
        {
            str=QString(":/res/swordKirby_bend.png");
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
    });

    connect(landTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str;
        if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
        {
            str=QString(":/res/Kirby_Land%1.png").arg(landMin++);
        }
        else if(isIceKirby)
        {
            str=QString(":/res/iceKirby_Land%1.png").arg(landMin++);
        }
        else if(isFireKirby)
        {
            str=QString(":/res/fireKirby_Land%1.png").arg(landMin++);
        }
        else if(isSwordKirby)
        {
            str=QString(":/res/swordKirby_Land%1.png").arg(landMin++);
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
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
        QString str;
        if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
        {
            str=QString(":/res/Kirby_Fight%1.png").arg(fightMin++);
        }
        else if(isIceKirby)
        {
            str=QString(":/res/iceKirby_Fight%1.png").arg(fightMin++);
        }
        else if(isFireKirby)
        {
            str=QString(":/res/fireKirby_Fight%1.png").arg(fightMin++);
        }
        else if(isSwordKirby)
        {
            str=QString(":/res/swordKirby_Fight%1.png").arg(fightMin++);
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
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
        QString str;
        if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
        {
            str=QString(":/res/Kirby_Swallow%1.png").arg(swallowMin++);
        }
        else if(isIceKirby)
        {
            str=QString(":/res/iceKirby_Swallow%1.png").arg(swallowMin++);
        }
        else if(isFireKirby)
        {
            str=QString(":/res/fireKirby_Swallow%1.png").arg(swallowMin++);
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
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
        QString str;
        if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
        {
            str=QString(":/res/Kirby_Swallow5.png");
        }
        else if(isIceKirby)
        {
            str=QString(":/res/iceKirby_Swallow5.png");
        }
        else if(isFireKirby)
        {
            str=QString(":/res/fireKirby_Swallow5.png");
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
    });

    connect(fatTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Fatwalk%1.png").arg(fatWalkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(fatWalkMin>fatWalkMax)
        {
            fatWalkMin=1;
        }
    });

    connect(jumpTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str;
        if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
        {
            str=QString(":/res/Kirby_Jump%1.png").arg(jumpMin++);
        }
        else if(isIceKirby)
        {
            str=QString(":/res/iceKirby_Jump%1.png").arg(jumpMin++);
        }
        else if(isFireKirby)
        {
            str=QString(":/res/fireKirby_Jump%1.png").arg(jumpMin++);
        }
        else if(isSwordKirby)
        {
            str=QString(":/res/swordKirby_Jump%1.png").arg(jumpMin++);
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(jumpMin>jumpMax)
        {
            jumpTimer->stop();
        }
    });

    connect(spitTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Spit%1.png").arg(spitMin++);
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(spitMin>spitMax)
        {
            spitTimer->stop();
        }
    });

    connect(hurtTimer,&QTimer::timeout,[this](){
        if(walkTimer->isActive())
        {
            walkTimer->stop();
        }
        isHurting=true;
        QPixmap pixmap;
        QString str;
        str=QString(":/res/Kirby_hurt%1.png").arg(hurtMin++);
        if(isIceKirby)
        {
            isIceKirby=false;
        }
        else if(isFireKirby)
        {
            isFireKirby=false;
        }
        else if(isSwordKirby)
        {
            isSwordKirby=false;
        }
        pixmap.load(str);
        QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(towardLeft)
        {
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(hurtMin>hurtMax)
        {
            isHurting=false;
            hurtTimer->stop();
        }
    });

    connect(sparkTimer,&QTimer::timeout,[this](){
        QPixmap pixmap;
        QString str=QString(":/res/Kirby_Spark%1.png").arg(sparkMin++);
        pixmap.load(str);
        QPixmap scaledPixmap;
        scaledPixmap=pixmap.scaled(200,200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledPixmap);
        if(!hasSet)
        {
            setPos(x()-70,y()-70);
            hasSet=true;
        }
        if(sparkMin>sparkMax)
        {
            sparkMin=1;
        }
    });

    flyTimer->start(100);
}

//正常状态往右走
void MyKirby::walk()
{
    if(!walkTimer->isActive())
    {
        walkTimer->start(50);
    }
}

//图片翻转
QPixmap MyKirby::flip(QImage image)
{
    image=image.mirrored(true,false);
    QPixmap pix1=QPixmap::fromImage(image);
    return pix1;
}

//静止不动
void MyKirby::origin()
{
    fightTimer->stop();
    bendTimer->stop();
    flyTimer->stop();
    walkTimer->stop();
    landTimer->stop();
    fatTimer->stop();
    jumpTimer->stop();
    spitTimer->stop();
    if(towardRight)
    {
        QPixmap walkPixmap;
        if(!fat)
        {
            if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
            {
                walkPixmap.load(":/res/Kirby_Origin.png");
            }
            else if(isIceKirby)
            {
                walkPixmap.load(":/res/iceKirby_Normal.png");
            }
            else if(isFireKirby)
            {
                walkPixmap.load(":/res/fireKirby_Normal.png");
            }
            else if(isSwordKirby)
            {
                walkPixmap.load(":/res/swordKirby_Normal.png");
            }
        }
        else
        {
            walkPixmap.load(":/res/Kirby_Fat.png");
        }
        QPixmap scaledWalkPixmap=walkPixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPixmap(scaledWalkPixmap);
        towardRight=true;
    }
    if(towardLeft)
    {
        QPixmap walkPixmap;
        if(!fat)
        {
            if(!isIceKirby&&!isFireKirby&&!isSwordKirby)
            {
                walkPixmap.load(":/res/Kirby_Origin.png");
            }
            else if(isIceKirby)
            {
                walkPixmap.load(":/res/iceKirby_Normal.png");
            }
            else if(isFireKirby)
            {
                walkPixmap.load(":/res/fireKirby_Normal.png");
            }
            else if(isSwordKirby)
            {
                walkPixmap.load(":/res/swordKirby_Normal.png");
            }
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
void MyKirby::fly()
{
    if(!flyTimer->isActive())
    {
        walkTimer->stop();
        fatTimer->stop();
        flyTimer->start(50);
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
        swallowSound->play();
        if(fatTimer->isActive())
        {
            fatTimer->stop();
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

//停止下落动作
void MyKirby::stopLand()
{
    landTimer->stop();
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
    walkTimer->stop();
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

//吞噬状态行走
void MyKirby::fatMove()
{
    if(!fatTimer->isActive())
    {
        fatTimer->start(100);
    }
}

//跳跃
void MyKirby::jump()
{
    if(!jumpTimer->isActive())
    {
        jumpMin=1;
        jumpTimer->start(100);
    }
}

//吐
void MyKirby::spit()
{
    if(!spitTimer->isActive())
    {
        spitMin=1;
        spitTimer->start(100);
    }
}

//被刺
void MyKirby::hurt()
{
    if(!hurtTimer->isActive())
    {
        hurtMin=1;
        hurtTimer->start(100);
    }
}

//放电
void MyKirby::spark()
{
    if(!sparkTimer->isActive())
    {
        sparkTimer->start();
    }
}

//停止放电
void MyKirby::stopSpark()
{
    if(hasSet)
    {
    setPos(x()+70,y()+70);
        hasSet=false;
    }
    if(sparkTimer->isActive())
    {
        sparkTimer->stop();
    }
}


