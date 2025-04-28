#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>
#include<QGraphicsView>
#include<QKeyEvent>
#include<QMouseEvent>
#include<QTimer>
#include"gameover.h"
#include"win.h"
#include"mykirby.h"
#include"kirbypuff.h"
#include"star.h"
#include"apple.h"
#include"energy.h"
#include"invincible.h"
#include"swallowairsuck.h"
#include"icesuck.h"
#include"firesuck.h"
#include"orangeenemy.h"
#include"swordenemy.h"
#include"plantenemy.h"
#include"backstarenemy.h"
#include"flyenemy.h"
#include"icemanenemy.h"
#include"fireenemy.h"
#include"swordenemy.h"
#include"sparkenemy.h"
#include"boom.h"
#include"enemy.h"
#include"checkcollides.h"
#include<QList>
#include<QLabel>
#include<QFontDatabase>
#include<QSoundEffect>
//添加MainWindow的前向声明,让编译器知道MainWindow的存在，减少头文件依赖，不需要包含完整头文件
class MainWindow;
class PlayScene : public QGraphicsView
{
    Q_OBJECT
public:
    PlayScene(QGraphicsScene* scene,QWidget* parent = nullptr);
   MyKirby *kirby;
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void update();
    void updatePosition();
    void updateState();
    void applyGravity();
    void doPuff();
    void doSuck();
    void doStar();
    void doStar2();
    void initializeEnemy();
    void fightEnemy(const QPointF& newPos2);
    void swallowEnemy();
    void swallowStar();
    void deadEnemy();
    void deleteEnemy();
    void life();
    void score();
    void addApple();
    void addEnergy();
    void addInvincible();
    void hitByEnemy();
    void hurt();
    void gameOver();
    void win();
    bool checkCollides1(QPointF newPos);
    bool checkCollides2(QPointF newPos);
    bool checkCollides3(QPointF newPos);
    bool isOnSlope1(QPointF newPos);
    bool isOnSlope3(QPointF newPos);
    bool isOnGround1(QPointF newPos);
    bool isOnGround2(QPointF newPos);
    bool isOnGround3(QPointF newPos);
    bool isOneWayPlatform(QPointF newPos,QPointF oldPos);
    QRectF getOneWayPlatform(QPointF newPos,QPointF oldPos);
    bool sticked(QPointF newPos);
private:
    MainWindow* m_mainWindow;
    QGraphicsScene* m_scene;
    QList<Enemy*> enemies;//敌人列表
    QList<QLabel*>lifes;
    QList<Apple*> apples;
    QList<Energy*> energies;
    Enemy* hitEnemy=nullptr;
    KirbyPuff* puff=nullptr;
    Star* star=nullptr;
    SwallowAirSuck* suck=nullptr;
    IceSuck* iceSuck=nullptr;
    FireSuck* fireSuck=nullptr;
    Boom* boom=nullptr;
    Invincible* invincible1=new Invincible();
    Invincible* invincible2=new Invincible();
    QGraphicsPixmapItem* background1;
    QGraphicsPixmapItem* background2;
    QGraphicsPixmapItem* background3;
    QGraphicsPixmapItem* background4;
    QGraphicsPixmapItem* background01;
    QGraphicsPixmapItem* background02;
    QGraphicsPixmapItem* background03;
    QGraphicsPixmapItem* background04;
    QTimer* moveTimer;
    QTimer* gravityTimer;
    QTimer* invincibleTimer;
    QTimer* starCollidesTimer;
    QTimer* scoreTimer;
    QTimer* passTimer;
    QTimer* fallTimer;
    bool centerOnKirby=true;
    bool keyLeft = false;
    bool keyRight = false;
    bool keyUp = false;
    bool keyDown = false;
    bool keyZ=false;
    bool keySpace=false;
    bool keyX=false;
    bool keyV=false;
    bool isCollisides;
    bool enemyIsDead=false;
    bool playSucked=false;
    bool hasPlayedMusic=false;
    bool isPass=false;
    bool isPass1=false;
    bool isPass2=false;
    bool isPass3=false;
    bool isSwallowingIceEnemy=false;
    bool isSwallowingFireEnemy=false;
    bool isSwallowingSwordEnemy=false;
    bool isStandingOnPlatform = false;
    bool isGameOver=false;
    bool isWin=false;
    bool isPlayingSound=false;
    bool isIceStar=false;
    bool isFireStar=false;
    bool isSwordStar=false;
    bool hasSwallowedStar=false;
    int m_backgroundWidth;
    int m_backgroundHeight;
    int currentLife=5;
    int currScore=0;
    int speedX=200;//通关时移动速度
    int speedY=100;
    qreal flyGravity=2;
    const qreal maxFlyHeight=100;
    qreal currentFlyHeight=0;
    qreal jumpSpeed=-14;
    const qreal scale = 1.5;
    qreal starSpeedX=20;
    qreal starSpeedY=20;
    QPointF enemyPos;
    QSoundEffect* flySound = new QSoundEffect(this);
    QSoundEffect* airPuff = new QSoundEffect(this);
    QSoundEffect* hitSound = new QSoundEffect(this);
    QSoundEffect* hitByEnemySound = new QSoundEffect(this);
    QSoundEffect* suckSound = new QSoundEffect(this);
    QSoundEffect* iceSound = new QSoundEffect(this);
    QSoundEffect* fireSound = new QSoundEffect(this);
    QSoundEffect* starSound = new QSoundEffect(this);
    QSoundEffect* enemyDead = new QSoundEffect(this);
    QSoundEffect* superPower = new QSoundEffect(this);
    QSoundEffect* sparkSound= new QSoundEffect(this);
    QLabel* scoreBoard=new QLabel(this);
    GameOver* gameOverWidget;
    Win* winWidget;
signals:
private slots:
    void onBackClicked() ;
};

#endif // PLAYSCENE_H
