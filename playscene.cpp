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
#include"gameover.h"

PlayScene::PlayScene(QGraphicsScene *scene,QWidget * parent)
    : QGraphicsView(scene,parent), m_scene(scene)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用水平和垂直滚动条
    setFixedSize(1000,800);
    setWindowIcon(QIcon(":/res/Kirby.png"));
    setWindowTitle("星之卡比");
    scene->setBackgroundBrush(QBrush(QColor("0,0,0")));

    //设置背景
    QPixmap backgroundPixmap(":/res/BG.png");
    QPixmap scaledBackgroundPixmap=backgroundPixmap.scaled(2000,1610,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background=scene->addPixmap(scaledBackgroundPixmap);
    background->setPos(0,0);

    //设置关卡1
    QPixmap backgroundPixmap01(":/res/Kirby_level1_map1.png");
    QPixmap scaledBackgroundPixmap01=backgroundPixmap01.scaled(2000,1600,Qt::KeepAspectRatio);
    background01=scene->addPixmap(scaledBackgroundPixmap01);
    m_backgroundWidth=scaledBackgroundPixmap01.width();
    m_backgroundHeight=scaledBackgroundPixmap01.height();

    //设置关卡2
    QPixmap backgroundPixmap02(":/res/Kirby_level1_map2.png");
    QPixmap scaledBackgroundPixmap02=backgroundPixmap02.scaled(2000,1600,Qt::KeepAspectRatio);
    background02=scene->addPixmap(scaledBackgroundPixmap02);
    background02->setPos(2000, 0);
    // m_backgroundWidth=scaledBackgroundPixmap02.width();
    // m_backgroundHeight=scaledBackgroundPixmap02.height();

    //设置角色
    kirby=new MyKirby();
    scene->addItem(kirby);
    kirby->setPos(40,m_backgroundHeight-170);
    centerOn(kirby);

    //设置生命值
    life();

    //设置苹果
    addApple();
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
    });

    //得分计时器
    scoreBoard->setFixedSize(125,80);
    scoreTimer=new QTimer(this);
    connect(scoreTimer,&QTimer::timeout,this,&PlayScene::score);
    scoreTimer->start(100);

    //星星碰撞敌人定时器
    starCollidesTimer=new QTimer(this);
    connect(starCollidesTimer,&QTimer::timeout,[this](){
        for(Enemy* enemy:enemies)
        {
            if(star)
            {
                if(star->collidesWithItem(enemy))
                {
                    enemyIsdead=true;
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

    //苹果计时器
    eatAppleTimer=new QTimer(this);
    connect(eatAppleTimer,&QTimer::timeout,[this](){
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
    });
    eatAppleTimer->start(100);

    //通关计时器
    passTimer=new QTimer(this);
    connect(passTimer,&QTimer::timeout,[this](){
        if(kirby->x()<2200)
        {
            kirby->setX(kirby->x()+speedX);
        }
        if(kirby->y()<1400)
        {
            kirby->setY(kirby->y()+speedY);
        }
        kirby->flyRight();
        centerOn(kirby);
        if(kirby->x()>=2200&&kirby->y()>=1400)
        {
            passTimer->stop();
        }
    });
}


//*****重力函数*****
void PlayScene::applyGravity()
{
    QPointF oldPos=kirby->pos();
    QPointF newPos=oldPos;
    newPos.setY(newPos.y()+flyGravity);
    if(!checkCollides1(newPos))
    {
        kirby->setY(newPos.y());
    }
}


//*****碰撞检测*****
//关卡1
bool PlayScene::checkCollides1(QPointF newPos)
{
    return CheckCollides::checkCollides1(kirby, background01, newPos, isPass1);
}



//*****是否在坡上*****
bool PlayScene::isOnSlope1(QPointF newPos)
{
    return CheckCollides::isOnSlope1(newPos,isPass1);
}


//*****是否在地面上*****
bool PlayScene::isOnGround1(QPointF newPos)
{
    return CheckCollides::isOnGround1(kirby,newPos,isPass1);
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
    if(!keyLeft&&!keyRight && !keyUp && !keyDown && !kirby->isFlying&&!keyZ&&!kirby->isLanding&&!kirby->isFighting&&!kirby->isSwallowing)
    {
        if(isOnGround1(newPos2)||(isOnSlope1(newPos2)&&kirby->collidesWithItem(background01)))
        {
            kirby->origin();
        }
    }
    //按下攻击键
    if(keyZ==true)
    {
        fightEnemy(newPos2);
    }
    //按下空格键
    if(keySpace==true&&!keyLeft&&!keyRight && !keyUp && !keyDown && !kirby->isFlying&&!keyZ&&!kirby->isLanding&&!kirby->isFighting&&!kirby->fat)
    {
        swallowEnemy();
    }
    updateState();
    centerOn(kirby);//使角色始终在视图中心附近
}


//*****更新位置*****
void PlayScene::updatePosition()
{
    QPointF oldPos=kirby->pos();
    QPointF newPos=oldPos;
    QPointF newPos2(newPos.x(),newPos.y()+10);

    //按左键
    if(keyLeft==true&&!kirby->isBending)
    {
        kirby->towardLeft=true;
        kirby->towardRight=false;
        //没在飞
        if(kirby->isFlying==false)
        {
            if(!isOnSlope1(newPos))
            {
                newPos.setX(newPos.x()-10);
            }
            else
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
            if(!isOnGround1(newPos2))
            {
                flyGravity=8;
            }
            if(!kirby->fat)
            {
                kirby->moveLeft();
            }
            else
            {
                kirby->fatMoveLeft();
            }
        }
        //在飞
        else
        {
            kirby->flyLeft();
            newPos.setX(newPos.x()-10);
        }
        qDebug() << "X坐标: " << kirby->pos().x() << " Y坐标: " << kirby->pos().y();
    }

    //按右键
    if(keyRight==true&&!kirby->isBending)
    {
        kirby->towardRight=true;
        kirby->towardLeft=false;
        //没在飞
        if(kirby->isFlying==false)
        {
            //没在坡上
            if(!isOnSlope1(newPos))
            {
                newPos.setX(newPos.x()+10);
            }
            //在坡上
            else
            {
                newPos.setX(newPos.x()+10);
                if(newPos.x()>=270&&newPos.x()<=590&&newPos.y()>=1280&&newPos.y()<=1450)
                {
                    qreal expectedY = lerp(newPos.x(), 270, 1450, 590, 1310);
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
            if(!isOnGround1(newPos2))
            {
                flyGravity=8;
            }
            if(!kirby->fat)
            {
                kirby->moveRight();
            }
            else
            {
                kirby->fatMoveRight();
            }
        }
        //在飞
        else
        {
            kirby->flyRight();
            newPos.setX(newPos.x()+10);
        }
        qDebug() << "X坐标: " << kirby->pos().x() << " Y坐标: " << kirby->pos().y();
    }

    //按上键
    if(keyUp==true&&!kirby->isBending&&!kirby->isFighting)
    {
        kirby->isFlying=true;
        if(currentFlyHeight<maxFlyHeight)
        {
            if(kirby->towardRight==true&&!kirby->isFighting)
            {
                kirby->flyRight();
            }
            else if(kirby->towardLeft==true&&!kirby->isFighting)
            {
                kirby->flyLeft();
            }
            newPos.setY(newPos.y()-15);
            currentFlyHeight+=15;
        }
        flyGravity=2;

        qDebug() << "X坐标: " << kirby->pos().x() << " Y坐标: " << kirby->pos().y();
    }

    //按下键
    if(keyDown==true)
    {
        //是否通关
        if(kirby->x()>=860&&kirby->x()<=950&&kirby->y()<=280&&kirby->y()>=220)
        {
            isPass1=true;
            moveTimer->stop();
            gravityTimer->stop();
            passTimer->start(100);
            starSound->play();
            return;
        }
        //飞行状态时按下键
        if(kirby->isFlying==true)
        {
            newPos.setY(newPos.y()+10);
            if(isOnGround1(newPos))
            {
                kirby->isFlying=false;
                kirby->origin();
                puff=new KirbyPuff();
                m_scene->addItem(puff);
                if(kirby->towardRight==true)
                {
                    puff->setPos(kirby->pos().x()+30,kirby->pos().y()+20);
                    puff->setDirection(1);
                }
                if(kirby->towardLeft==true)
                {
                    puff->setPos(kirby->pos().x()-30,kirby->pos().y()+20);
                    puff->setDirection(-1);
                }

                doPuff();

            }
        }
        //行走状态时按下键
        else
        {
            if(checkCollides1(newPos)==false&&kirby->isBending==false&&!isOnSlope1(newPos))
            {
                newPos.setY(newPos.y()+10);
            }
            if(kirby->collidesWithItem(background01)||isOnGround1(newPos))
            {
                kirby->isBending=true;
                kirby->bend();
                kirby->setPos(oldPos);
            }
        }
        qDebug() << "X坐标: " << kirby->pos().x() << " Y坐标: " << kirby->pos().y();
    }
    if(!checkCollides1(newPos)||isPass1)
    {
        if(!gravityTimer->isActive())
        {
            gravityTimer->start(30);
        }
        kirby->setPos(newPos);
    }
    else
    {
        gravityTimer->stop();
        kirby->setPos(oldPos);
    }
    if(isOnGround1(newPos2)||(isOnSlope1(newPos2)&&kirby->collidesWithItem(background01)))
    {
        kirby->isLanding=false;
        flyGravity=2;
    }
    if(kirby->collidesWithItem(background01)&&isOnSlope1(newPos)&&kirby->isFlying==true&&!isPass1)
    {
        gravityTimer->stop();
        kirby->setPos(oldPos);
    }
    if(kirby->isFlying==false&&isOnSlope1(newPos)&&kirby->collidesWithItem(background01))
    {
        gravityTimer->stop();

    }
}


//*****更新状态*****
void PlayScene::updateState()
{
    if(enemyIsdead)
    {
        deadEnemy();
    }

    if(!kirby->isBending)
    {
        kirby->stopBend();
    }

    if(!kirby->isSwallowing)
    {
        kirby->stopSwallow();
        hasPlayedMusic=false;
        if(!hasPlayedMusic)
        {
            suckSound->stop();
        }
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
        break;
    case Qt::Key_Down:
        keyDown=true;
        break;
    case Qt::Key_Z:
        keyZ=true;
        break;
    case Qt::Key_Space:
        keySpace=true;
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
        if(!kirby->isBending&&!kirby->isFighting)
        {
            flySound->play();
        }
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
        // hasSucked=false;
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
    OrangeEnemy* waddle1=new OrangeEnemy(true);
    m_scene->addItem(waddle1);
    waddle1->setPos(590,1280);
    enemies.append(waddle1);
    OrangeEnemy* waddle2=new OrangeEnemy(false);
    m_scene->addItem(waddle2);
    waddle2->setPos(590,1310);
    enemies.append(waddle2);
    SwordEnemy* swordEnemy1=new SwordEnemy(1,1000);
    m_scene->addItem(swordEnemy1);
    swordEnemy1->setPos(560,830);
    enemies.append(swordEnemy1);
    SwordEnemy* swordEnemy2=new SwordEnemy(-1,2000);
    m_scene->addItem(swordEnemy2);
    swordEnemy2->setPos(830,900);
    enemies.append(swordEnemy2);
    PlantEnemy* plantEnemy1=new PlantEnemy();
    m_scene->addItem(plantEnemy1);
    plantEnemy1->setPos(223,685);
    enemies.append(plantEnemy1);
    PlantEnemy* plantEnemy2=new PlantEnemy();
    m_scene->addItem(plantEnemy2);
    plantEnemy2->setPos(782,545);
    enemies.append(plantEnemy2);
    BackStarEnemy* backStarEnemy1=new BackStarEnemy();
    m_scene->addItem(backStarEnemy1);
    backStarEnemy1->setPos(260,360);
    enemies.append(backStarEnemy1);
    BackStarEnemy* backStarEnemy2=new BackStarEnemy();
    m_scene->addItem(backStarEnemy2);
    backStarEnemy2->setPos(690,220);
    enemies.append(backStarEnemy2);
    FlyEnemy* flyEnemy=new FlyEnemy();
    m_scene->addItem(flyEnemy);
    flyEnemy->setPos(560,340);
    enemies.append(flyEnemy);
}


//*****攻击敌人函数*****
void PlayScene::fightEnemy(const QPointF& newPos2)
{
    //在飞
    if(kirby->isFlying)
    {
        for(Enemy* enemy:enemies)
        {
            if(!dynamic_cast<BackStarEnemy*>(enemy))
            {
                qreal result=enemy->x()-kirby->x();
                if(abs(result)<=150&&abs(enemy->y()-kirby->y())<=80)
                {
                    if((result<=150&&result>=0&&kirby->towardRight)||(result>=-150&&result<0&&kirby->towardLeft))
                    {
                        enemyIsdead=true;
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
            doStar();
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
            if(!dynamic_cast<BackStarEnemy*>(enemy))
            {
                qreal result=enemy->x()-kirby->x();
                if(abs(result)<=80&&abs(enemy->y()-kirby->y())<=80)
                {
                    if((result<=80&&result>=0&&kirby->towardRight)||(result>=-80&&result<0&&kirby->towardLeft))
                    {
                        enemyIsdead=true;
                        enemyPos=enemy->pos();
                        hitEnemy=enemy;
                        break;
                    }
                }
            }
        }
        if(kirby->fat)
        {
            doStar();
            return;
        }
        if(isOnGround1(newPos2)||(isOnSlope1(newPos2)&&kirby->collidesWithItem(background01)))
        {
            if(!kirby->isBending)
            {
                kirby->fight();
                kirby->isFighting=true;
                if(enemyIsdead)
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
    kirby->swallow();
    kirby->isSwallowing=true;
    for(Enemy* enemy:enemies)
    {
        if(!dynamic_cast<PlantEnemy*>(enemy)&&!dynamic_cast<BackStarEnemy*>(enemy))
        {
            qreal result=enemy->x()-kirby->x();
            if(abs(enemy->x()-kirby->x())<=150&&abs(enemy->y()-kirby->y())<=80)
            {
                enemyPos=enemy->pos();
                hitEnemy=enemy;
                if((result>60&&kirby->towardRight)||(result<-60&&kirby->towardLeft))
                {
                    if(kirby->towardRight)
                    {
                        enemy->swallowedLeft();
                        enemy->setPos(enemy->x()-3,enemy->y());
                    }
                    if(kirby->towardLeft)
                    {
                        enemy->swallowedRight();
                        enemy->setPos(enemy->x()+3,enemy->y());
                    }
                }
                if(enemy)
                {
                    if(abs(enemy->x()-kirby->x())<=60)
                    {
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


//*****喷气*****
void PlayScene::doPuff()
{
    puff=new KirbyPuff();
    m_scene->addItem(puff);

    if(kirby->towardRight==true)
    {
        puff->setPos(kirby->pos().x()+30,kirby->pos().y()+20);
        puff->setDirection(1);
    }
    if(kirby->towardLeft==true)
    {
        puff->setPos(kirby->pos().x()-30,kirby->pos().y()+20);
        puff->setDirection(-1);
    }

    // 启动定时器
    QTimer::singleShot(40, this, [=]() {
        puff->puff1Timer->start();  // 启动 puff1 定时器
    });
    airPuff->play();

    // 设置定时器停止后销毁 puff
    QTimer::singleShot(200, this, [this]() {
        if (puff) {
            puff->puff1Timer->stop();
            m_scene->removeItem(puff);
            delete puff;
            puff = nullptr;
        }
    });
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
        star->star1Timer->start();  // 启动 star1 定时器
    });
    starSound->play();
    starCollidesTimer->start();
    //设置定时器停止后销毁 star
    QTimer::singleShot(500, this, [this]() {
        if (star) {
            star->star1Timer->stop();
            starCollidesTimer->stop();
            m_scene->removeItem(star);
            delete star;
            star = nullptr;
        }
    });
}


//*****吸气*****
void PlayScene::doSuck()
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
        suck->suckTimer->start(100);  // 启动 puff1 定时器
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
    //}
}


//*****敌人死亡函数*****
void PlayScene::deadEnemy()
{
    enemyIsdead=false;
    boom=new Boom();
    m_scene->addItem(boom);
    boom->setPos(enemyPos.x()-50,enemyPos.y()-50);
    // 启动定时器
    QTimer::singleShot(40, this, [=]() {
        boom->boomTimer->start(50);
    });
    enemyDead->play();
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
    for(int i=0;i<startLife;i++)
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
    scoreBoard->setGeometry(this->width()-150,this->height()-100,50,50);
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
                invincibleTimer->start(1000);
            }
        }
    }
}


//*****游戏结束*****
void PlayScene::gameOver()
{

    GameOver* gameOverWidget=new GameOver();
    gameOverWidget->showGameOver();
    MainWindow::gameSound->stop();
    gameOverSound->play();
    this->deleteLater();
}
