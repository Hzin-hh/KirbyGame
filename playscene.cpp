#include "playscene.h"
#include"mainwindow.h"
#include<QApplication>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QGraphicsScene>
#include<QBrush>
#include<QDebug>
#include"mypushbutton.h"
#include"mykirby.h"
#include"kirbypuff.h"
#include<QSound>

PlayScene::PlayScene(QGraphicsScene *scene,QWidget * parent)
    : QGraphicsView(scene,parent), m_scene(scene)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用水平和垂直滚动条
    setFixedSize(1000,800);
    setWindowIcon(QIcon(":/res/Kirby.png"));
    setWindowTitle("星之卡比");
    scene->setBackgroundBrush(QBrush(QColor("0,0,0")));
    //QSoundEffect
    flySound->setSource(QUrl("qrc:/res/fly_s.wav"));
    airPuff->setSource(QUrl("qrc:/res/airPuff_s.wav"));
    hitSound->setSource(QUrl("qrc:/res/starHit_s.wav"));
    hitByEnemySound->setSource(QUrl("qrc:/res/hitByEnemy_s.wav"));
    suckSound->setSource(QUrl("qrc:/res/airSuck_s.wav"));
    starSound->setSource(QUrl("qrc:/res/starShoot_s.wav"));
    enemyDead->setSource(QUrl("qrc:/res/enemyDead_s.wav"));
    superPower->setSource(QUrl("qrc:/res/soperPower_s.wav"));
    iceSound->setSource(QUrl("qrc:/res/shootingIce.wav"));
    fireSound->setSource(QUrl("qrc:/res/fire_s.wav"));
    sparkSound->setSource(QUrl("qrc:/res/sparkSound.wav"));

    //设置背景
    QPixmap backgroundPixmap(":/res/BG.png");
    QPixmap scaledBackgroundPixmap=backgroundPixmap.scaled(2000*scale,1610*scale,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background1=scene->addPixmap(scaledBackgroundPixmap);
    background1->setPos(0,-800);
    background2=scene->addPixmap(scaledBackgroundPixmap);
    background2->setPos(2000,-800);
    background3=scene->addPixmap(scaledBackgroundPixmap);
    background3->setPos(4000,-800);
    background4=scene->addPixmap(scaledBackgroundPixmap);
    background4->setPos(6000,-800);

    //设置关卡1
    QPixmap backgroundPixmap01(":/res/Kirby_level1_map1.png");
    QPixmap scaledBackgroundPixmap01=backgroundPixmap01.scaled(2000,1600,Qt::KeepAspectRatio);
    background01=scene->addPixmap(scaledBackgroundPixmap01);
    m_backgroundWidth=scaledBackgroundPixmap01.width();
    m_backgroundHeight=scaledBackgroundPixmap01.height();

    //设置关卡2
    QPixmap backgroundPixmap02(":/res/Kirby_level1_map2.png");
    QPixmap scaledBackgroundPixmap02=backgroundPixmap02.scaled(3000,2400,Qt::KeepAspectRatio);
    background02=scene->addPixmap(scaledBackgroundPixmap02);
    background02->setPos(2000*scale, -800);

    //设置关卡3
    QPixmap backgroundPixmap03(":/res/Kirby_level1_map3.png");
    QPixmap scaledBackgroundPixmap03=backgroundPixmap03.scaled(3000,2400,Qt::KeepAspectRatio);
    background03=scene->addPixmap(scaledBackgroundPixmap03);
    background03->setPos(4000*scale, -800);

    //设置角色
    kirby=new MyKirby();
    scene->addItem(kirby);
    kirby->setPos(40,m_backgroundHeight-170);
    centerOn(kirby);

    //设置生命值
    life();

    //设置苹果
    addApple();

    //设置回血
    addEnergy();

    //设置无敌道具
    addInvincible();
    //设置得分板
    score();

    //初始化敌人
    initializeEnemy();

    //静音实现
    MyPushButton * openmusicBtn=new MyPushButton(":/res/openmusic.png");
    openmusicBtn->setParent(this);
    openmusicBtn->move(this->width()*0.95,this->height()*0.05);
    MyPushButton * closemusicBtn=new MyPushButton(":/res/closemusic.png");
    closemusicBtn->setParent(this);
    closemusicBtn->move(this->width()*0.95, this->height()*0.05);
    closemusicBtn->hide();
    connect(openmusicBtn,&MyPushButton::clicked,[=]()
            {
                openmusicBtn->hide();
                MainWindow::gameSound->stop();

                closemusicBtn->show();
            });
    connect(closemusicBtn,&MyPushButton::clicked,[=]()
            {
                closemusicBtn->hide();
                MainWindow::gameSound->play();
                openmusicBtn->show();
            });


    //移动定时器
    moveTimer=new QTimer(this);
    connect(moveTimer,&QTimer::timeout,this,&PlayScene::update);
    moveTimer->start(30);

    //飞行重力定时器
    gravityTimer=new QTimer(this);
    connect(gravityTimer,&QTimer::timeout,this,&PlayScene::applyGravity);
    gravityTimer->start(30);

    //无敌定时器
    invincibleTimer=new QTimer(this);
    connect(invincibleTimer,&QTimer::timeout,[this](){
        kirby->invincible=false;
        invincibleTimer->stop();
    });

    //得分计时器
    scoreBoard->setFixedSize(200,100);
    scoreTimer=new QTimer(this);
    connect(scoreTimer,&QTimer::timeout,this,&PlayScene::score);
    scoreTimer->start(100);

    //星星碰撞敌人定时器
    starCollidesTimer=new QTimer(this);
    connect(starCollidesTimer,&QTimer::timeout,[this](){
        for(Enemy* enemy:enemies)
        {
            if(star&&!kirby->isHurting)
            {
                if(star->collidesWithItem(enemy))
                {
                    enemyIsDead=true;
                    enemyPos=enemy->pos();
                    hitEnemy=enemy;
                    m_scene->removeItem(star);
                    delete star;
                    star=nullptr;
                    break;
                }
            }
        }
    });

    //星星掉落定时器
    fallTimer=new QTimer(this);
    connect(fallTimer,&QTimer::timeout,[this](){
        if(star->collidesWithItem(background01)||star->collidesWithItem(background02)||star->collidesWithItem(background03))
        {
            fallTimer->stop();
            star->moveTimer->stop();
        }
        else
        {
            if(starSpeedX>0&&starSpeedY>0)
            {
                star->setPos(star->x()-starSpeedX--,star->y() + starSpeedY--);
            }
        }
    });
    //通关计时器
    passTimer=new QTimer(this);
    connect(passTimer,&QTimer::timeout,[this](){
        kirby->invincible=true;
        if(isPass1)
        {
            if(kirby->x()<2240*scale)
            {
                kirby->setX(kirby->x()+speedX);
            }
            if(kirby->y()<1400*scale-800)
            {
                kirby->setY(kirby->y()+speedY);
            }
            kirby->fly();
            centerOn(kirby);
            if(kirby->x()>=2240*scale&&kirby->y()>=1400*scale-800)
            {
                kirby->invincible=false;
                passTimer->stop();
            }
        }
        else if(isPass2)
        {
            if(kirby->x()<4428*scale-100)
            {
                kirby->setX(kirby->x()+speedX);
            }
            if(kirby->y()<900)
            {
                kirby->setY(kirby->y()+speedY);
            }
            if(kirby->y()>1000)
            {
                kirby->setY(kirby->y()-speedY);
            }
            kirby->fly();
            centerOn(kirby);
            if(kirby->x()>=4428*scale-100&&kirby->y()>=900)
            {
                kirby->invincible=false;
                passTimer->stop();
            }
        }
    });
}


//*****重力函数*****
void PlayScene::applyGravity()
{
    QPointF oldPos=kirby->pos();
    QPointF newPos=oldPos;
    newPos.setY(newPos.y()+flyGravity);
    if((!checkCollides1(newPos)&&!isPass1&&!isPass2)||(!checkCollides2(newPos)&&isPass1)||(!checkCollides3(newPos)&&isPass2))
    {
        kirby->setY(newPos.y());
    }
}


//*****碰撞检测*****
//关卡1
bool PlayScene::checkCollides1(QPointF newPos)
{
    return CheckCollides::checkCollides1(kirby, background01, newPos);
}
//关卡2
bool PlayScene::checkCollides2(QPointF newPos)
{
    return CheckCollides::checkCollides2(kirby,newPos);
}
//关卡3
bool PlayScene::checkCollides3(QPointF newPos)
{
    return CheckCollides::checkCollides3(kirby,background03,newPos);
}

//*****是否在坡上*****
//关卡1
bool PlayScene::isOnSlope1(QPointF newPos)
{
    return CheckCollides::isOnSlope1(newPos,isPass1);
}
//关卡3
bool PlayScene::isOnSlope3(QPointF newPos)
{
    return CheckCollides::isOnSlope3(newPos,isPass2);
}


//*****是否在地面上*****
//关卡1
bool PlayScene::isOnGround1(QPointF newPos)
{
    return CheckCollides::isOnGround1(kirby,newPos,isPass1);
}
//关卡2
bool PlayScene::isOnGround2(QPointF newPos)
{
    return CheckCollides::isOnGround2(kirby,newPos);
}
//关卡3
bool PlayScene::isOnGround3(QPointF newPos)
{
    return CheckCollides::isOnGround3(kirby,newPos,isPass2);
}
bool PlayScene::isOneWayPlatform(QPointF newPos,QPointF oldPos)
{
    return CheckCollides::isOneWayPlatform(kirby,newPos,oldPos);
}
QRectF PlayScene::getOneWayPlatform(QPointF newPos,QPointF oldPos)
{
    return CheckCollides::getOneWayPlatform(kirby,newPos,oldPos);
}
bool PlayScene::sticked(QPointF newPos)
{
    return CheckCollides::sticked(kirby,newPos);
}

//*****线性插值法*****
qreal lerp(qreal x, qreal x1, qreal y1, qreal x2, qreal y2)
{
    if (x1 == x2) return y1; // 避免除零
    return y1 + ((x - x1) / (x2 - x1)) * (y2 - y1);
}

//*****主控制函数*****
void PlayScene::update()
{
    hitByEnemy();
    updatePosition();
    QPointF oldPos=kirby->pos();
    QPointF newPos=oldPos;
    QPointF newPos2(newPos.x(),newPos.y()+10);
    if(sticked(newPos))
    {
        hurt();
    }
    if(!keyLeft&&!keyRight && !keyUp && !keyDown && !kirby->isFlying&&!keyZ&&!kirby->isJumping&&!kirby->isLanding&&!kirby->isFighting&&!kirby->isSwallowing&&!kirby->isSpitting&&!kirby->isHurting)
    {
        if((isOnGround1(newPos2)||(isOnGround2(newPos2)&&isPass1)||isOnGround3(newPos2))||(isOnSlope1(newPos2)&&kirby->collidesWithItem(background01))||(isOnSlope3(newPos2)&&kirby->collidesWithItem(background03))||isOneWayPlatform(newPos,oldPos))
        {
            kirby->origin();
        }
    }
    //按下攻击键
    if(keyZ==true)
    {
        fightEnemy(newPos2);
    }
    //取消变身
    if(keyV==true&&(kirby->isIceKirby||kirby->isFireKirby||kirby->isSwordKirby))
    {
        doStar2();
    }
    //按下空格键
    if(keySpace==true&&!keyLeft&&!keyRight && !keyUp && !keyDown && !kirby->isFlying&&!keyZ&&!kirby->isJumping&&!kirby->isLanding&&!kirby->isFighting&&!kirby->fat)
    {
        swallowEnemy();
        if(star&&!invincibleTimer->isActive())
        {
            swallowStar();
        }
    }
    updateState();
    if(centerOnKirby)
    {
        centerOn(kirby);//使角色始终在视图中心附近
    }
}


//*****更新位置*****
void PlayScene::updatePosition()
{
    QPointF oldPos=kirby->pos();
    QPointF newPos=oldPos;
    QPointF newPos2(newPos.x(),newPos.y()+10);

    //按左键
    if(keyLeft==true&&!kirby->isBending&&!kirby->isHurting&&!kirby->isSparking)
    {
        if(!kirby->isJumping)
        {
            kirby->towardLeft=true;
            kirby->towardRight=false;
        }
        if(kirby->isLanding)
        {
            kirby->stopLand();
        }
        //没在飞
        if(kirby->isFlying==false)
        {
            //没在坡上
            if(!isOnSlope1(newPos)&&!isOnSlope3(newPos))
            {
                newPos.setX(newPos.x()-10);
            }
            //在坡上
            else if(isOnSlope1(newPos))
            {
                newPos.setX(newPos.x()-10);
                if(newPos.x()>=270&&newPos.x()<=590&&newPos.y()>=1280&&newPos.y()<=1450)
                {
                    qreal expectedY = lerp(newPos.x(), 270, 1450, 590, 1310);
                    //误差范围，避免瞬移
                    if(qAbs(newPos.y()-expectedY)<20)
                    {
                        newPos.setY(lerp(newPos.x(), 270, 1450, 590, 1310));
                    }
                }
                else if(newPos.x()>=350&&newPos.x()<=500&&newPos.y()>=800&&newPos.y()<=920)
                {
                    qreal expectedY = lerp(newPos.x(), 350, 900, 500, 825);
                    if(qAbs(newPos.y()-expectedY)<20)
                    {
                        newPos.setY(lerp(newPos.x(), 350, 900, 500, 825));
                    }
                }
                else if(newPos.x()>=650&&newPos.x()<=800&&newPos.y()>=800&&newPos.y()<=920)
                {
                    qreal expectedY = lerp(newPos.x(), 650, 830, 810, 900);
                    if(qAbs(newPos.y()-expectedY)<20)
                    {
                        newPos.setY(lerp(newPos.x(), 650, 830, 810, 900));
                    }
                }
            }
            else if(isOnSlope3(newPos))
            {
                newPos.setX(newPos.x()-10);
                if(newPos.x()>=8265&&newPos.x()<=8865&&newPos.y()>=490&&newPos.y()<=1115)
                {
                    qreal expectedY = lerp(newPos.x(), 8225, 1115, 8865, 490);
                    //误差范围，避免瞬移
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 8225, 1115, 8865, 490));
                    }
                }
                else if(newPos.x()>=8350&&newPos.x()<=8680&&newPos.y()>=105&&newPos.y()<=435)
                {
                    qreal expectedY = lerp(newPos.x(), 8330, 105, 8665, 435);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 8330, 105, 8665, 435));
                    }
                }
                else if(newPos.x()>=6005&&newPos.x()<=6635&&newPos.y()>=-185&&newPos.y()<=440)
                {
                    qreal expectedY = lerp(newPos.x(), 6005, -185, 6635, 440);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 6005, -185, 6635, 440));
                    }
                }
                else if(newPos.x()>=6210&&newPos.x()<=6510&&newPos.y()>=-570&&newPos.y()<=-240)
                {
                    qreal expectedY = lerp(newPos.x(), 6195, -240, 6535, -570);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 6195, -240, 6535, -570));
                    }
                }
                else if(newPos.x()>=7085&&newPos.x()<=7380&&newPos.y()>=-570&&newPos.y()<=-245)
                {
                    qreal expectedY = lerp(newPos.x(), 7070, -245, 7405, -570);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 7070, -245, 7405, -570));
                    }
                }
                else if(newPos.x()>=7955&&newPos.x()<=8250&&newPos.y()>=-570&&newPos.y()<=-245)
                {
                    qreal expectedY = lerp(newPos.x(), 7940, -245, 8275, -570);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 7940, -245, 8275, -570));
                    }
                }
            }
            if(!(isOnGround1(newPos2)||(isOnGround2(newPos2)&&isPass1)||isOnGround3(newPos2)))
            {
                if(!kirby->isJumping)
                {
                    flyGravity=8;
                }
            }
            if(!kirby->fat)
            {
                if(!kirby->isJumping&&!kirby->isFighting)
                {
                    kirby->walk();
                }
            }
            else
            {
                kirby->fatMove();
            }
        }
        //在飞
        else
        {
            kirby->fly();
            newPos.setX(newPos.x()-10);
        }
        qDebug() << "X坐标: " << kirby->pos().x() << " Y坐标: " << kirby->pos().y();
    }
    //按右键
    if(keyRight==true&&!kirby->isBending&&!kirby->isHurting&&!kirby->isSparking)
    {
        if(!kirby->isJumping)
        {
            kirby->towardRight=true;
            kirby->towardLeft=false;
        }
        if(kirby->isLanding)
        {
            kirby->stopLand();
        }
        //没在飞
        if(kirby->isFlying==false)
        {
            //没在坡上
            if(!isOnSlope1(newPos)&&!isOnSlope3(newPos))
            {
                newPos.setX(newPos.x()+10);
            }
            //在坡上
            else if(isOnSlope1(newPos))
            {
                newPos.setX(newPos.x()+10);
                if(newPos.x()>=270&&newPos.x()<=590&&newPos.y()>=1280&&newPos.y()<=1450)
                {
                    qreal expectedY = lerp(newPos.x(), 270, 1450, 590, 1310);
                    //误差范围，避免瞬移
                    if(qAbs(newPos.y()-expectedY)<20)
                    {
                        newPos.setY(lerp(newPos.x(), 270, 1450, 590, 1310));
                    }
                }
                else if(newPos.x()>=350&&newPos.x()<=500&&newPos.y()>=800&&newPos.y()<=920)
                {
                    qreal expectedY = lerp(newPos.x(), 350, 900, 500, 825);
                    if(qAbs(newPos.y()-expectedY)<20)
                    {
                        newPos.setY(lerp(newPos.x(), 350, 900, 500, 825));
                    }
                }
                else if(newPos.x()>=650&&newPos.x()<=800&&newPos.y()>=800&&newPos.y()<=920)
                {
                    qreal expectedY = lerp(newPos.x(), 650, 830, 810, 900);
                    if(qAbs(newPos.y()-expectedY)<20)
                    {
                        newPos.setY(lerp(newPos.x(), 650, 830, 810, 900));
                    }
                }
            }
            else if(isOnSlope3(newPos))
            {
                newPos.setX(newPos.x()+10);
                if(newPos.x()>=8225&&newPos.x()<=8865&&newPos.y()>=490&&newPos.y()<=1115)
                {
                    qreal expectedY = lerp(newPos.x(), 8225, 1115, 8865, 490);
                    //误差范围，避免瞬移
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 8225, 1115, 8865, 490));
                    }
                }
                else if(newPos.x()>=8350&&newPos.x()<=8635&&newPos.y()>=105&&newPos.y()<=435)
                {
                    qreal expectedY = lerp(newPos.x(), 8330, 105, 8665, 435);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 8330, 105, 8665, 435));
                    }
                }
                else if(newPos.x()>=6005&&newPos.x()<=6620&&newPos.y()>=-185&&newPos.y()<=440)
                {
                    qreal expectedY = lerp(newPos.x(), 6005, -185, 6635, 440);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 6005, -185, 6635, 440));
                    }
                }
                else if(newPos.x()>=6175&&newPos.x()<=6510&&newPos.y()>=-570&&newPos.y()<=-240)
                {
                    qreal expectedY = lerp(newPos.x(), 6195, -240, 6535, -570);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 6195, -240, 6535, -570));
                    }
                }
                else if(newPos.x()>=7070&&newPos.x()<=7380&&newPos.y()>=-570&&newPos.y()<=-245)
                {
                    qreal expectedY = lerp(newPos.x(), 7070, -245, 7405, -570);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 7070, -245, 7405, -570));
                    }
                }
                else if(newPos.x()>=7940&&newPos.x()<=8250&&newPos.y()>=-570&&newPos.y()<=-245)
                {
                    qreal expectedY = lerp(newPos.x(), 7940, -245, 8275, -570);
                    if(qAbs(newPos.y()-expectedY)<30)
                    {
                        newPos.setY(lerp(newPos.x(), 7940, -245, 8275, -570));
                    }
                }
            }
            if(!(isOnGround1(newPos2)||(isOnGround2(newPos2)&&isPass1)||isOnGround3(newPos2)))
            {
                if(!kirby->isJumping)
                {
                    flyGravity=8;
                }
            }
            if(!kirby->fat)
            {
                if(!kirby->isJumping&&!kirby->isFighting)
                {
                    kirby->walk();
                }
            }
            else
            {
                kirby->fatMove();
            }
        }
        //在飞
        else
        {
            kirby->fly();
            newPos.setX(newPos.x()+10);
        }
        qDebug() << "X坐标: " << kirby->pos().x() << " Y坐标: " << kirby->pos().y();
    }

    //按上键
    if(keyUp==true&&!kirby->isBending&&!kirby->isFighting&&!kirby->isJumping&&!kirby->isSparking)
    {
        kirby->isFlying=true;
        if(currentFlyHeight<maxFlyHeight)
        {
            if(!kirby->isFighting)
            {
                kirby->fly();
            }
            newPos.setY(newPos.y()-15);
            currentFlyHeight+=15;
        }
        flyGravity=2;

        qDebug() << "X坐标: " << kirby->pos().x() << " Y坐标: " << kirby->pos().y();
    }

    //按下键
    if(keyDown==true&&!kirby->isSparking)
    {
        //飞行状态时按下键
        if(kirby->isFlying==true)
        {
            newPos.setY(newPos.y()+10);
            if(isOnGround1(newPos)||(isOnGround2(newPos)&&isPass1)||isOnGround3(newPos)||isOneWayPlatform(newPos,oldPos))
            {
                kirby->isFlying=false;
                kirby->origin();
                doPuff();
            }
        }
        //行走状态时按下键
        else
        {
            //是否通关
            if(kirby->x()>=860&&kirby->x()<=950&&kirby->y()<=280&&kirby->y()>=220&&!isPass1)
            {
                isPass1=true;
                kirby->isFlying=true;
                passTimer->start(100);
                starSound->play();
                return;
            }
            if(kirby->x()>=2070*scale&&kirby->x()<=2125*scale&&kirby->y()<=250*scale-800&&kirby->y()>=210*scale-800&&!isPass2)
            {
                isPass2=true;
                isPass1=false;
                kirby->isFlying=true;
                passTimer->start(100);
                starSound->play();
                return;
            }
            if(kirby->x()>=8765&&kirby->x()<=8860&&kirby->y()<=-90&&kirby->y()>=-200)
            {
                isPass3=true;
                win();
            }
            if(((!checkCollides1(newPos)&&!isPass1&&!isPass2)||(!checkCollides2(newPos)&&isPass1)||!checkCollides3(newPos))&&kirby->isBending==false&&!isOnSlope1(newPos)&&!isOnSlope3(newPos))
            {
                newPos.setY(newPos.y()+10);
            }
            if(kirby->collidesWithItem(background01)||isOnGround1(newPos)||(isOnGround2(newPos)&&isPass1)||isOnGround3(newPos)||isOnSlope3(newPos)||isOneWayPlatform(newPos,oldPos))
            {
                kirby->isBending=true;
                kirby->bend();
                kirby->setPos(oldPos);
            }
        }
        qDebug() << "X坐标: " << kirby->pos().x() << " Y坐标: " << kirby->pos().y();
    }

    //按跳跃键
    if(keyX==true&&!kirby->isFlying&&!kirby->isBending&&!kirby->isFighting&&!kirby->walkTimer->isActive()&&!kirby->isJumping)
    {
        if(!kirby->isFighting&&!kirby->fat)
        {
            kirby->jump();
            kirby->isJumping=true;
            jumpSpeed=-14;
            flyGravity=0.5;
        }
    }
    if(kirby->isJumping)
    {
        newPos.setY(newPos.y()+jumpSpeed);
        jumpSpeed+=flyGravity;
    }

    if((!checkCollides1(newPos)&&!isPass1&&!isPass2)||(!checkCollides2(newPos)&&isPass1)||(!checkCollides3(newPos)&&isPass2/*&&!isOneWayPlatform(newPos,oldPos)*/))
    {
        if(!gravityTimer->isActive()&&!isOneWayPlatform(newPos,oldPos))
        {
            gravityTimer->start(30);
        }
        kirby->setPos(newPos);
    }
    else
    {
        if(!kirby->isJumping)
        {
            gravityTimer->stop();
            if(isOneWayPlatform(newPos,oldPos))
            {
                kirby->setY(oldPos.y());
            }
            else
            {
                kirby->setPos(oldPos);
            }
        }
    }
    if((isOnGround1(newPos2)||(isOnGround2(newPos2)&&isPass1)||isOnGround3(newPos2))||(isOnSlope1(newPos2)&&kirby->collidesWithItem(background01))||(isOnSlope3(newPos)&&kirby->collidesWithItem(background03))||isOneWayPlatform(newPos,oldPos))
    {
        kirby->isLanding=false;
        kirby->isJumping=false;
        jumpSpeed=-14;
        flyGravity=2;
    }
    if((kirby->collidesWithItem(background01)&&isOnSlope1(newPos)&&kirby->isFlying&&!keyUp)||(kirby->collidesWithItem(background03)&&isOnSlope3(newPos2)&&kirby->isFlying&&!keyUp))
    {
        gravityTimer->stop();
        if(isOneWayPlatform(newPos,oldPos))
        {
            kirby->setY(oldPos.y());
        }
        else
        {
            kirby->setPos(oldPos);
        }
    }
    if((!kirby->isFlying&&isOnSlope1(newPos)&&kirby->collidesWithItem(background01))||(!kirby->isFlying&&isOnSlope3(newPos)&&kirby->collidesWithItem(background03)))
    {
        gravityTimer->stop();
    }
    if (isOneWayPlatform(newPos,oldPos))
    {
        gravityTimer->stop();
        QRectF platform = getOneWayPlatform(newPos, oldPos);
        if (!platform.isNull())
        {
            // 调整位置到平台顶部
            newPos.setY(platform.y() - kirby->boundingRect().height());
            kirby->setPos(newPos);
            // 停止重力，重置跳跃状态
            gravityTimer->stop();
            kirby->isJumping = false;
            kirby->isLanding=false;
            isStandingOnPlatform=true;
        }
    }
}


//*****更新状态*****
void PlayScene::updateState()
{
    //敌人死亡
    if(enemyIsDead)
    {
        deadEnemy();
    }

    //蹲下复原
    if(!kirby->isBending)
    {
        kirby->stopBend();
    }

    //吸气复原
    if(!kirby->isSwallowing)
    {
        kirby->stopSwallow();
        hasPlayedMusic=false;
        if(!hasPlayedMusic)
        {
            suckSound->stop();
            iceSound->stop();
            fireSound->stop();
        }
    }
    if(!kirby->isSparking)
    {
        kirby->stopSpark();
        //centerOn(kirby);
        sparkSound->stop();
    }

    //吃苹果
    for(Apple* apple:apples)
    {
        if(kirby->collidesWithItem(apple))
        {
            apples.removeOne(apple);
            m_scene->removeItem(apple);
            delete apple;
            apple=nullptr;
            currScore+=20;
            break;
        }
    }

    //吃回血道具
    for(Energy* energy:energies)
    {
        if(kirby->collidesWithItem(energy))
        {
            energies.removeOne(energy);
            m_scene->removeItem(energy);
            delete energy;
            energy=nullptr;
            currentLife++;
            kirby->kirbyLife++;
            life();
            break;
        }
    }

    //吃无敌道具
    if(kirby->collidesWithItem(invincible1)||kirby->collidesWithItem(invincible2))
    {
        if(kirby->collidesWithItem(invincible1))
        {
            m_scene->removeItem(invincible1);
            delete invincible1;
            invincible1=nullptr;
        }
        if(kirby->collidesWithItem(invincible2))
        {
            m_scene->removeItem(invincible2);
            delete invincible2;
            invincible2=nullptr;
        }
        invincibleTimer->start(10000);
        kirby->invincible=true;
    }
}


//*****重写键盘按下事件*****
void PlayScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
        keyLeft=true;
        break;
    case Qt::Key_Right:
        keyRight=true;
        break;
    case Qt::Key_Up:
        keyUp=true;
        if(!kirby->isBending&&!kirby->isFighting&&!kirby->isJumping)
        {
            if(!isPlayingSound)
            {
                flySound->play();
                isPlayingSound=true;
                QTimer::singleShot(300,this,[this]{
                    isPlayingSound=false;
                });
            }
        }
        break;
    case Qt::Key_Down:
        keyDown=true;
        if(!kirby->isFlying)
        {
            if(isSwallowingIceEnemy||(isIceStar&&hasSwallowedStar))
            {
                kirby->isIceKirby=true;
                kirby->isFireKirby=false;
                kirby->isSwordKirby=false;
                QPixmap pixmap;
                QString str=QString(":/res/iceKirby_Normal.png");
                pixmap.load(str);
                QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                kirby->setPixmap(scaledPixmap);
                superPower->play();
                if(isSwallowingIceEnemy)
                {
                    isSwallowingIceEnemy=false;
                }
                if(hasSwallowedStar)
                {
                    hasSwallowedStar=false;
                }
            }
            else if(isSwallowingFireEnemy||(isFireStar&&hasSwallowedStar))
            {
                kirby->isFireKirby=true;
                kirby->isIceKirby=false;
                kirby->isSwordKirby=false;
                QPixmap pixmap;
                QString str=QString(":/res/fireKirby_Normal.png");
                pixmap.load(str);
                QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                kirby->setPixmap(scaledPixmap);
                superPower->play();
                if(isSwallowingFireEnemy)
                {
                    isSwallowingFireEnemy=false;
                }
                if(hasSwallowedStar)
                {
                    hasSwallowedStar=false;
                }
            }
            else if(isSwallowingSwordEnemy||(isSwordStar&&hasSwallowedStar))
            {
                kirby->isSwordKirby=true;
                kirby->isIceKirby=false;
                kirby->isFireKirby=false;
                QPixmap pixmap;
                QString str=QString(":/res/swordKirby_Normal.png");
                pixmap.load(str);
                QPixmap scaledPixmap=pixmap.scaled(60,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                kirby->setPixmap(scaledPixmap);
                superPower->play();
                if(isSwallowingSwordEnemy)
                {
                    isSwallowingSwordEnemy=false;
                }
                if(hasSwallowedStar)
                {
                    hasSwallowedStar=false;
                }
            }
        }
        break;
    case Qt::Key_Z:
        keyZ=true;
        break;
    case Qt::Key_Space:
        keySpace=true;
        break;
    case Qt::Key_X:
        keyX=true;
        break;
    case Qt::Key_V:
        keyV=true;
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        return;
    }
}


//*****重写键盘松开事件*****
void PlayScene::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Left:
        keyLeft = false;
        break;
    case Qt::Key_Right:
        keyRight = false;
        break;
    case Qt::Key_Up:
        currentFlyHeight=0;
        keyUp = false;
        break;
    case Qt::Key_Down:
        if(kirby->isBending==true)
        {
            kirby->isBending=false;
        }
        keyDown = false;
        break;
    case Qt::Key_Z:
        keyZ=false;
        break;
    case Qt::Key_Space:
        keySpace=false;
        kirby->isSwallowing=false;
        kirby->isSparking=false;
        centerOnKirby=true;
        break;
    case Qt::Key_X:
        keyX=false;
        break;
    case Qt::Key_V:
        keyV=false;
        break;
    default:
        QGraphicsView::keyReleaseEvent(event);
        return;
    }
}


void PlayScene::mousePressEvent(QMouseEvent *event)
{
    // 获取不同坐标系中的坐标，进行比较
    QPoint viewPos = event->pos();  // 视图坐标
    QPointF scenePos = mapToScene(viewPos);  // 转换到场景坐标

    qDebug() << "Scene Coordinates (mapped): " << scenePos;


    // 基类处理
    QGraphicsView::mousePressEvent(event);
}


//*****初始化敌人函数*****
void PlayScene::initializeEnemy()
{
    OrangeEnemy* waddle1_1=new OrangeEnemy(true,270,590);
    m_scene->addItem(waddle1_1);
    waddle1_1->setPos(590,1280);
    enemies.append(waddle1_1);

    OrangeEnemy* waddle1_2=new OrangeEnemy(false,590,700);
    m_scene->addItem(waddle1_2);
    waddle1_2->setPos(590,1310);
    enemies.append(waddle1_2);

    OrangeEnemy* waddle2_1=new OrangeEnemy(false,2165*scale,2225*scale);
    m_scene->addItem(waddle2_1);
    waddle2_1->setPos(2165*scale,830*scale-770);
    enemies.append(waddle2_1);

    OrangeEnemy* waddle2_2=new OrangeEnemy(false,2290*scale,2360*scale);
    m_scene->addItem(waddle2_2);
    waddle2_2->setPos(2290*scale,410*scale-770);
    enemies.append(waddle2_2);

    OrangeEnemy* waddle3_1=new OrangeEnemy(false,7610,7780);
    m_scene->addItem(waddle3_1);
    waddle3_1->setPos(7610,1110);
    enemies.append(waddle3_1);

    OrangeEnemy* waddle3_2=new OrangeEnemy(true,8265,8470);
    m_scene->addItem(waddle3_2);
    waddle3_2->setPos(8470,490);
    enemies.append(waddle3_2);

    SparkEnemy* sparkEnemy=new SparkEnemy(530,670);
    m_scene->addItem(sparkEnemy);
    sparkEnemy->setPos(530,830);
    enemies.append(sparkEnemy);

    // SwordEnemy* swordEnemy1_1=new SwordEnemy(1,1000,true);
    // m_scene->addItem(swordEnemy1_1);
    // swordEnemy1_1->setPos(560,830);
    // enemies.append(swordEnemy1_1);

    SwordEnemy* swordEnemy1_2=new SwordEnemy(-1,2000,true);
    m_scene->addItem(swordEnemy1_2);
    swordEnemy1_2->setPos(830,900);
    enemies.append(swordEnemy1_2);

    SwordEnemy* swordEnemy2_1=new SwordEnemy(1,1000,false);
    m_scene->addItem(swordEnemy2_1);
    swordEnemy2_1->setPos(2390*scale,1340*scale-775);
    enemies.append(swordEnemy2_1);

    SwordEnemy* swordEnemy3_1=new SwordEnemy(1,1000,true);
    m_scene->addItem(swordEnemy3_1);
    swordEnemy3_1->setPos(6405,-440);
    enemies.append(swordEnemy3_1);

    PlantEnemy* plantEnemy1_1=new PlantEnemy();
    m_scene->addItem(plantEnemy1_1);
    plantEnemy1_1->setPos(223,685);
    enemies.append(plantEnemy1_1);

    PlantEnemy* plantEnemy1_2=new PlantEnemy();
    m_scene->addItem(plantEnemy1_2);
    plantEnemy1_2->setPos(782,545);
    enemies.append(plantEnemy1_2);

    PlantEnemy* plantEnemy2_1=new PlantEnemy();
    m_scene->addItem(plantEnemy2_1);
    plantEnemy2_1->setPos(2390*scale+10,1154*scale-775);
    enemies.append(plantEnemy2_1);

    PlantEnemy* plantEnemy2_2=new PlantEnemy();
    m_scene->addItem(plantEnemy2_2);
    plantEnemy2_2->setPos(2251*scale+10,1058*scale-775);
    enemies.append(plantEnemy2_2);

    PlantEnemy* plantEnemy2_3=new PlantEnemy();
    m_scene->addItem(plantEnemy2_3);
    plantEnemy2_3->setPos(2410*scale+15,222*scale-770);
    enemies.append(plantEnemy2_3);

    PlantEnemy* plantEnemy3_1=new PlantEnemy();
    m_scene->addItem(plantEnemy3_1);
    plantEnemy3_1->setPos(7970,140);
    enemies.append(plantEnemy3_1);

    PlantEnemy* plantEnemy3_2=new PlantEnemy();
    m_scene->addItem(plantEnemy3_2);
    plantEnemy3_2->setPos(7675,235);
    enemies.append(plantEnemy3_2);

    BackStarEnemy* backStarEnemy1_1=new BackStarEnemy(-1);
    m_scene->addItem(backStarEnemy1_1);
    backStarEnemy1_1->setPos(257,360);
    enemies.append(backStarEnemy1_1);

    BackStarEnemy* backStarEnemy1_2=new BackStarEnemy(-1);
    m_scene->addItem(backStarEnemy1_2);
    backStarEnemy1_2->setPos(690,220);
    enemies.append(backStarEnemy1_2);

    BackStarEnemy* backStarEnemy2_1=new BackStarEnemy(-1);
    m_scene->addItem(backStarEnemy2_1);
    backStarEnemy2_1->setPos(3505,-700);
    enemies.append(backStarEnemy2_1);

    BackStarEnemy* backStarEnemy2_2=new BackStarEnemy(-1);
    m_scene->addItem(backStarEnemy2_2);
    backStarEnemy2_2->setPos(2070*scale,455*scale-760);
    enemies.append(backStarEnemy2_2);

    BackStarEnemy* backStarEnemy2_3=new BackStarEnemy(1);
    m_scene->addItem(backStarEnemy2_3);
    backStarEnemy2_3->setPos(2205*scale,430*scale-750);
    enemies.append(backStarEnemy2_3);

    BackStarEnemy* backStarEnemy3_1=new BackStarEnemy(-1);
    m_scene->addItem(backStarEnemy3_1);
    backStarEnemy3_1->setPos(6615,-670);
    enemies.append(backStarEnemy3_1);

    BackStarEnemy* backStarEnemy3_2=new BackStarEnemy(-1);
    m_scene->addItem(backStarEnemy3_2);
    backStarEnemy3_2->setPos(7490,-670);
    enemies.append(backStarEnemy3_2);

    BackStarEnemy* backStarEnemy3_3=new BackStarEnemy(-1);
    m_scene->addItem(backStarEnemy3_3);
    backStarEnemy3_3->setPos(8570,-545);
    enemies.append(backStarEnemy3_3);

    FlyEnemy* flyEnemy1=new FlyEnemy();
    m_scene->addItem(flyEnemy1);
    flyEnemy1->setPos(560,340);
    enemies.append(flyEnemy1);

    FlyEnemy* flyEnemy2=new FlyEnemy();
    m_scene->addItem(flyEnemy2);
    flyEnemy2->setPos(6850,-590);
    enemies.append(flyEnemy2);

    FlyEnemy* flyEnemy3=new FlyEnemy();
    m_scene->addItem(flyEnemy3);
    flyEnemy3->setPos(7700,-590);
    enemies.append(flyEnemy3);

    IceManEnemy* iceManEnemy1=new IceManEnemy();
    m_scene->addItem(iceManEnemy1);
    iceManEnemy1->setPos(2500*scale,825*scale-770);
    enemies.append(iceManEnemy1);

    FireEnemy* fireEnemy1=new FireEnemy(2163*scale,2210*scale);
    m_scene->addItem(fireEnemy1);
    fireEnemy1->setPos(2163*scale,227*scale-775);
    enemies.append(fireEnemy1);

    FireEnemy* fireEnemy2=new FireEnemy(7030,7220);
    m_scene->addItem(fireEnemy2);
    fireEnemy2->setPos(7030,430);
    enemies.append(fireEnemy2);
}


//*****攻击敌人函数*****
void PlayScene::fightEnemy(const QPointF& newPos2)
{
    if(kirby->walkTimer->isActive())
    {
        kirby->walkTimer->stop();
    }
    //在飞
    if(kirby->isFlying)
    {
        for(Enemy* enemy:enemies)
        {
            if((!dynamic_cast<BackStarEnemy*>(enemy)&&!kirby->isIceKirby&&!kirby->isFireKirby&&!kirby->isSwordKirby)||kirby->isIceKirby||kirby->isFireKirby||kirby->isSwordKirby)
            {
                qreal result=enemy->x()-kirby->x();
                if(abs(result)<=150&&abs(enemy->y()-kirby->y())<=80)
                {
                    if((result<=150&&result>=0&&kirby->towardRight)||(result>=-150&&result<0&&kirby->towardLeft))
                    {
                        enemyIsDead=true;
                        enemyPos=enemy->pos();
                        hitEnemy=enemy;
                        break;
                    }
                }
            }
        }
        kirby->isLanding=true;
        flyGravity=8;
        if(!kirby->fat)
        {
            doPuff();
        }
        else
        {
            kirby->isSpitting=true;
            kirby->spit();
            doStar();
            isSwallowingIceEnemy=false;
            isSwallowingFireEnemy=false;
            isSwallowingSwordEnemy=false;
        }
        kirby->origin();
        kirby->land();
        kirby->isFlying=false;
    }
    //不在飞
    else
    {
        for(Enemy* enemy:enemies)
        {
            if((!dynamic_cast<BackStarEnemy*>(enemy)&&!kirby->isIceKirby&&!kirby->isFireKirby&&!kirby->isSwordKirby)||kirby->isIceKirby||kirby->isFireKirby||kirby->isSwordKirby)
            {
                qreal result=enemy->x()-kirby->x();
                if(abs(result)<=80&&abs(enemy->y()-kirby->y())<=80)
                {
                    if((result<=80&&result>=0&&kirby->towardRight)||(result>=-80&&result<0&&kirby->towardLeft))
                    {
                        enemyIsDead=true;
                        enemyPos=enemy->pos();
                        hitEnemy=enemy;
                        break;
                    }
                }
            }
        }
        if(kirby->fat)
        {
            kirby->isSpitting=true;
            kirby->spit();
            doStar();
            return;
        }
        if((isOnGround1(newPos2)||(isOnGround2(newPos2)&&isPass1)||isOnGround3(newPos2))||(isOnSlope1(newPos2)&&kirby->collidesWithItem(background01))||(isOnSlope3(newPos2)&&kirby->collidesWithItem(background03)))
        {
            if(!kirby->isBending&&!kirby->isSpitting&&!kirby->isPuffing)
            {
                kirby->fight();
                kirby->isFighting=true;
                if(enemyIsDead)
                {
                    hitSound->play();
                }
            }
        }
    }
}


//*****吞噬敌人函数*****
void PlayScene::swallowEnemy()
{
    if(!playSucked&&keySpace)
    {
        doSuck();
    }
    if(!kirby->isSwordKirby)
    {
        kirby->swallow();
        kirby->isSwallowing=true;
    }
    for(Enemy* enemy:enemies)
    {
        if(kirby->isIceKirby||kirby->isFireKirby||kirby->isSwordKirby)
        {
            if(enemy)
            {
                if(abs(enemy->x()-kirby->x())<=150&&abs(enemy->y()-kirby->y())<=80)
                {
                    if((enemy->x()-kirby->x()>0&&kirby->towardRight)||(enemy->x()-kirby->x()<0&&kirby->towardLeft)||kirby->isSwordKirby)
                    {
                    enemyIsDead=true;
                    enemyPos=enemy->pos();
                    hitEnemy=enemy;
                    break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        if(!dynamic_cast<PlantEnemy*>(enemy)&&!dynamic_cast<BackStarEnemy*>(enemy))
        {
            if((!kirby->isIceKirby&&!kirby->isFireKirby&&!kirby->isSwordKirby))
            {
                qreal result=enemy->x()-kirby->x();
                if(abs(result)<=150&&abs(enemy->y()-kirby->y())<=80)
                {
                    enemyPos=enemy->pos();
                    hitEnemy=enemy;
                    if((result>60&&kirby->towardRight)||(result<-60&&kirby->towardLeft))
                    {
                        if(kirby->towardRight&&result>0)
                        {
                            enemy->swallowedLeft();
                            enemy->setPos(enemy->x()-3,enemy->y());
                        }
                        if(kirby->towardLeft&&result<0)
                        {
                            enemy->swallowedRight();
                            enemy->setPos(enemy->x()+3,enemy->y());
                        }
                    }
                    if(enemy)
                    {
                        if((result<=70&&result>=0&&kirby->towardRight)||(result>=-70&&result<=0&&kirby->towardLeft))
                        {
                            if(dynamic_cast<IceManEnemy*>(enemy))
                            {
                                isIceStar=true;
                                isFireStar=false;
                                isSwordStar=false;
                                isSwallowingIceEnemy=true;
                            }
                            else if(dynamic_cast<FireEnemy*>(enemy))
                            {
                                isIceStar=false;
                                isFireStar=true;
                                isSwordStar=false;
                                isSwallowingFireEnemy=true;
                            }
                            else if(dynamic_cast<SparkEnemy*>(enemy))
                            {
                                isIceStar=false;
                                isFireStar=false;
                                isSwordStar=true;
                                isSwallowingSwordEnemy=true;
                            }
                            deleteEnemy();
                            kirby->finishSwallow();
                            currScore+=5;
                        }
                    }
                    enemy->stopSwallowed();
                    break;
                }
            }
        }
    }
}

//吞噬星星函数
void PlayScene::swallowStar()
{
    qreal result=star->x()-kirby->x();
    if(!playSucked&&keySpace)
    {
        doSuck();
    }
    if(!kirby->isSwordKirby)
    {
        kirby->swallow();
        kirby->isSwallowing=true;
    }
    if(abs(result)<=150&&abs(star->y()-kirby->y())<=80)
    {
        if((result>60&&kirby->towardRight)||(result<-60&&kirby->towardLeft))
        {
            if(kirby->towardRight)
            {
                star->setPos(star->x()-3,star->y());
            }
            if(kirby->towardLeft)
            {
                star->setPos(star->x()+3,star->y());
            }
        }
    }
    if(abs(result)<=70)
    {
        hasSwallowedStar=true;
        m_scene->removeItem(star);
        delete star;
        star = nullptr;
        kirby->finishSwallow();
    }
}

//*****喷气*****
void PlayScene::doPuff()
{
    if(!kirby->isPuffing)
    {
        kirby->isPuffing=true;
        if(!puff)
        {
            puff=new KirbyPuff();
            m_scene->addItem(puff);
        }

        if(kirby->towardRight==true)
        {
            puff->setPos(kirby->pos().x()+30,kirby->pos().y()+25);
            puff->setDirection(1);
        }
        if(kirby->towardLeft==true)
        {
            puff->setPos(kirby->pos().x()-30,kirby->pos().y()+25);
            puff->setDirection(-1);
        }

        // 启动定时器
        QTimer::singleShot(40, this, [=]() {
            puff->puff1Timer->start(30);  // 启动 puff1 定时器
        });
        airPuff->play();

        // 设置定时器停止后销毁 puff
        QTimer::singleShot(200, this, [this]() {
            if (puff) {
                puff->puff1Timer->stop();
                m_scene->removeItem(puff);
                delete puff;
                puff = nullptr;
                kirby->isPuffing=false;
            }
        });
    }
}


//*****吐星星*****
void PlayScene::doStar()
{
    kirby->fat=false;
    star=new Star();
    m_scene->addItem(star);

    if(kirby->towardRight==true)
    {
        star->setPos(kirby->pos().x()+30,kirby->pos().y()-20);
        star->setDirection(1);
    }
    if(kirby->towardLeft==true)
    {
        star->setPos(kirby->pos().x()-30,kirby->pos().y()-20);
        star->setDirection(-1);
    }

    // 启动定时器
    QTimer::singleShot(40, this, [=]() {
        star->star1Timer->start(30);  // 启动 star1 定时器
    });
    if(!(kirby->isIceKirby||kirby->isFireKirby||kirby->isSwordKirby))
    {
        starSound->play();
    }
    starCollidesTimer->start(30);
    //设置定时器停止后销毁 star
    QTimer::singleShot(500, this, [this]() {
        kirby->isSpitting=false;
        if (star) {
            star->star1Timer->stop();
            starCollidesTimer->stop();
            m_scene->removeItem(star);
            delete star;
            star = nullptr;
        }
    });
    isSwallowingFireEnemy=false;
    isSwallowingIceEnemy=false;
    isSwallowingSwordEnemy=false;
}

void PlayScene::doStar2()
{
    hasSwallowedStar=false;
    kirby->fat=false;
    star=new Star();
    m_scene->addItem(star);

    if(kirby->towardRight==true)
    {
        star->setPos(kirby->pos().x()+30,kirby->pos().y()-50);
        star->setDirection(-1);
    }
    if(kirby->towardLeft==true)
    {
        star->setPos(kirby->pos().x()-30,kirby->pos().y()-50);
        star->setDirection(1);
    }
    // 启动定时器
    QTimer::singleShot(40, this, [=]() {
        star->star1Timer->start(100);  // 启动 star 定时器
    });
    starSound->play();
    fallTimer->start(50);
    //设置定时器停止后销毁 star
    QTimer::singleShot(4000, this, [this]() {
        kirby->isSpitting=false;
        if (star)
        {
            if(!fallTimer->isActive())
            {
                starSpeedX=20;
                starSpeedY=20;
            }
            star->star1Timer->stop();
            m_scene->removeItem(star);
            delete star;
            star = nullptr;
        }
    });
    isSwallowingFireEnemy=false;
    isSwallowingIceEnemy=false;
    isSwallowingSwordEnemy=false;
    kirby->isIceKirby=false;
    kirby->isFireKirby=false;
    kirby->isSwordKirby=false;
}

//*****吸气*****
void PlayScene::doSuck()
{
    if(!kirby->isIceKirby&&!kirby->isFireKirby&&!kirby->isSwordKirby)
    {
        if (suck != nullptr) {
            return;  // 如果已经存在，直接返回
        }
        if(!hasPlayedMusic)
        {
            suckSound->play();
            hasPlayedMusic=true;
        }
        suck=new SwallowAirSuck();
        m_scene->addItem(suck);
        playSucked=true;
        if(kirby->towardRight==true)
        {
            suck->setPos(kirby->pos().x()+60,kirby->pos().y()-20);
            suck->towardRight(kirby->towardRight);
        }
        if(kirby->towardLeft==true)
        {
            suck->setPos(kirby->pos().x()-120,kirby->pos().y()-20);
            suck->towardRight(kirby->towardRight);
        }

        // 启动定时器
        QTimer::singleShot(35, this, [=]() {
            suck->suckTimer->start(100);  // 启动 suck 定时器
        });

        QTimer::singleShot(500, this, [this]() {
            if (suck) {
                suck->suckTimer->stop();
                m_scene->removeItem(suck);
                delete suck;
                suck = nullptr;
                playSucked=false;
            }
        });
    }
    else if(kirby->isIceKirby)
    {
        if (iceSuck != nullptr) {
            return;  // 如果已经存在，直接返回
        }
        if(!hasPlayedMusic)
        {
            iceSound->play();
            hasPlayedMusic=true;
        }
        iceSuck=new IceSuck();
        m_scene->addItem(iceSuck);
        playSucked=true;
        if(kirby->towardRight==true)
        {
            iceSuck->setPos(kirby->pos().x()+60,kirby->pos().y()-20);
            iceSuck->towardRight(kirby->towardRight);
        }
        if(kirby->towardLeft==true)
        {
            iceSuck->setPos(kirby->pos().x()-120,kirby->pos().y()-20);
            iceSuck->towardRight(kirby->towardRight);
        }

        // 启动定时器
        QTimer::singleShot(35, this, [=]() {
            iceSuck->suckTimer->start(100);  // 启动 suck 定时器
        });

        QTimer::singleShot(500, this, [this]() {
            if (iceSuck) {
                iceSuck->suckTimer->stop();
                m_scene->removeItem(iceSuck);
                delete iceSuck;
                iceSuck = nullptr;
                playSucked=false;
            }
        });
    }
    else if(kirby->isFireKirby)
    {
        if (fireSuck != nullptr) {
            return;  // 如果已经存在，直接返回
        }
        if(!hasPlayedMusic)
        {
            fireSound->play();
            hasPlayedMusic=true;
        }
        fireSuck=new FireSuck();
        m_scene->addItem(fireSuck);
        playSucked=true;
        if(kirby->towardRight==true)
        {
            fireSuck->setPos(kirby->pos().x()+60,kirby->pos().y()-20);
            fireSuck->towardRight(kirby->towardRight);
        }
        if(kirby->towardLeft==true)
        {
            fireSuck->setPos(kirby->pos().x()-120,kirby->pos().y()-20);
            fireSuck->towardRight(kirby->towardRight);
        }

        // 启动定时器
        QTimer::singleShot(35, this, [=]() {
            fireSuck->suckTimer->start(100);  // 启动 suck 定时器
        });

        QTimer::singleShot(500, this, [this]() {
            if (fireSuck) {
                fireSuck->suckTimer->stop();
                m_scene->removeItem(fireSuck);
                delete fireSuck;
                fireSuck = nullptr;
                playSucked=false;
            }
        });
    }
    else if(kirby->isSwordKirby)
    {
        kirby->isSparking=true;
        centerOnKirby=false;
        kirby->spark();
        sparkSound->play();
    }
}


//*****敌人死亡函数*****
void PlayScene::deadEnemy()
{
    enemyIsDead=false;
    boom=new Boom();
    m_scene->addItem(boom);
    boom->setPos(enemyPos.x()-50,enemyPos.y()-50);
    // 启动定时器
    QTimer::singleShot(40, this, [=]() {
        boom->boomTimer->start(40);
    });
    QTimer::singleShot(500, this, [=]() {
        enemyDead->play();
    });
    // 设置定时器停止后销毁 boom
    QTimer::singleShot(500, this, [this]() {
        if (boom) {
            boom->boomTimer->stop();
            m_scene->removeItem(boom);
            delete boom;
            boom = nullptr;
        }
    });
    currScore+=5;
    deleteEnemy();
}


//*****删除敌人*****
void PlayScene::deleteEnemy()
{
    if (hitEnemy) {
        m_scene->removeItem(hitEnemy);
        enemies.removeOne(hitEnemy);
        delete hitEnemy;
        hitEnemy = nullptr;
    }
}


//*****生命值创建*****
void PlayScene::life()
{
    for (QLabel* label : lifes) {
        label->hide();
        delete label;
    }
    lifes.clear();
    for(int i=0;i<currentLife;i++)
    {
        QLabel* life=new QLabel(this);
        QPixmap* pixmap=new QPixmap();
        pixmap->load(":/res/tiny_kirby.png");
        QPixmap scaledPixmap=pixmap->scaled(40,40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        life->setPixmap(scaledPixmap);
        life->setGeometry(20+i*50,this->height()-50,40,40);
        life->show();
        lifes.append(life);
    }
}


//*****设置苹果*****
void PlayScene::addApple()
{
    Apple* apple1=new Apple();
    apples.append(apple1);
    apple1->setPos(80,1110);
    m_scene->addItem(apple1);
    Apple* apple2=new Apple();
    apples.append(apple2);
    apple2->setPos(506,615);
    m_scene->addItem(apple2);
    Apple* apple3=new Apple();
    apples.append(apple3);
    apple3->setPos(2120*scale,377*scale-800);
    m_scene->addItem(apple3);
}


//*****设置回血道具*****
void PlayScene::addEnergy()
{
    Energy* energy1=new Energy();
    energies.append(energy1);
    energy1->setPos(3870,-565);
    m_scene->addItem(energy1);
    Energy* energy2=new Energy();
    energies.append(energy2);
    energy2->setPos(6355,-540);
    m_scene->addItem(energy2);
}


//设置无敌道具
void PlayScene::addInvincible()
{
    invincible1->setPos(2257*scale,1257*scale-775);
    m_scene->addItem(invincible1);
    invincible2->setPos(7135,225);
    m_scene->addItem(invincible2);
}


//*****得分板创建*****
void PlayScene::score()
{
    int fontId=QFontDatabase::addApplicationFont(":/res/ka1.ttf");
    QString fontFamily=QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily);
    font.setPointSize(36);
    QString showScore=QString::number(currScore);
    scoreBoard->setFont(font);
    scoreBoard->setStyleSheet("QLabel{color:rgb(179,24,164);}");
    scoreBoard->setText(showScore);
    scoreBoard->setAlignment(Qt::AlignCenter);
    scoreBoard->setGeometry(this->width()-200,this->height()-100,200,100);
    scoreBoard->show();
}


//*****被攻击*****
void PlayScene::hitByEnemy()
{
    for(Enemy* enemy:enemies)
    {
        if(kirby->kirbyLife<=0)
        {
            gameOver();
        }
        else
        {
            if(kirby->collidesWithItem(enemy)&&!kirby->invincible)
            {
                hitByEnemySound->play();
                kirby->invincible=true;
                kirby->kirbyLife--;
                QLabel* loseLife=lifes.takeLast();
                loseLife->hide();
                delete loseLife;
                currentLife--;
                life();
                invincibleTimer->start(1000);
                if(kirby->isIceKirby||kirby->isFireKirby||kirby->isSwordKirby||isSwallowingFireEnemy||isSwallowingIceEnemy||isSwallowingSwordEnemy)
                {
                    doStar2();
                }
            }
        }
    }
}


//*****被刺*****
void PlayScene::hurt()
{
    currentLife--;
    if(kirby->kirbyLife<=0)
    {
        gameOver();
    }
    else
    {
        if(!kirby->invincible)
        {
            hitSound->play();
            kirby->invincible=true;
            kirby->kirbyLife--;
            QLabel* loseLife=lifes.takeLast();
            loseLife->hide();
            delete loseLife;
            life();
            invincibleTimer->start(1500);
            kirby->hurt();
            if(kirby->isIceKirby||kirby->isFireKirby||kirby->isSwordKirby)
            {
                doStar2();
                QTimer::singleShot(200,this,[this]{
                    starSound->play();
                });
            }
            kirby->setPos(kirby->x()+150,kirby->y()-340);
        }
    }
}


//*****游戏结束*****
void PlayScene::gameOver()
{
    if(!isGameOver)
    {
        gameOverWidget=new GameOver(this);
        gameOverWidget->showGameOver();
        connect(gameOverWidget, &GameOver::backClicked, this, &PlayScene::onBackClicked);
        MainWindow::gameSound->stop();
        isGameOver=true;
    }
    else
    {
        return;
    }
}

//*****游戏胜利*****
void PlayScene::win()
{
    if(!isWin)
    {
        winWidget=new Win(this);
        winWidget->showWin();
        connect(winWidget, &Win::backClicked, this, &PlayScene::onBackClicked);
        MainWindow::gameSound->stop();
        isWin=true;
    }
    else
    {
        return;
    }
}

void PlayScene::onBackClicked(){
    // 隐藏PlayScene窗口
    this->hide();
    // 显示MainWindow
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}
