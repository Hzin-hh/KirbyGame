#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>
#include<QGraphicsView>
#include<QKeyEvent>
#include<QMouseEvent>
#include<QTimer>
#include"mykirby.h"
#include"kirbypuff.h"
#include"star.h"
#include"apple.h"
#include"swallowairsuck.h"
#include"orangeenemy.h"
#include"swordenemy.h"
#include"plantenemy.h"
#include"backstarenemy.h"
#include"flyenemy.h"
#include"boom.h"
#include"enemy.h"
#include"checkcollides.h"
#include<QList>
#include<QLabel>
#include<QFontDatabase>
//添加MainWindow的前向声明,让编译器知道MainWindow的存在，减少头文件依赖，不需要包含完整头文件
class MainWindow;
class PlayScene : public QGraphicsView
{
    Q_OBJECT
public:
    PlayScene(QGraphicsScene* scene,QWidget* parent = nullptr);
   MyKirby *kirby;
~PlayScene()
    {
    delete moveTimer;
    delete eatAppleTimer;
    delete gravityTimer;
    delete invincibleTimer;
    delete scoreTimer;
    delete starCollidesTimer;
    }
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
    void initializeEnemy();
    void fightEnemy(const QPointF& newPos2);
    void swallowEnemy();
    void deadEnemy();
    void deleteEnemy();
    void life();
    void score();
    void addApple();
    void hitByEnemy();
    void gameOver();
    bool checkCollides1(QPointF newPos);
    bool checkCollides2(QPointF newPos);
    bool isOnSlope1(QPointF newPos);
    bool isOnSlope2(QPointF newPos);
    bool isOnGround1(QPointF newPos);
    bool isOnGround2(QPointF newPos);
private:
    MainWindow* m_mainWindow;
    QGraphicsScene* m_scene;
    QList<Enemy*> enemies;//敌人列表
    QList<QLabel*>lifes;
    QList<Apple*> apples;
    Enemy* hitEnemy=nullptr;
    KirbyPuff* puff;
    Star* star;
    SwallowAirSuck* suck=nullptr;
    Boom* boom;
    QGraphicsPixmapItem* background;
    QGraphicsPixmapItem* background01;
    QGraphicsPixmapItem* background02;
    QGraphicsPixmapItem* background03;
    QGraphicsPixmapItem* background04;
    QTimer* moveTimer;
    QTimer* gravityTimer;
    QTimer* invincibleTimer;
    QTimer* starCollidesTimer;
    QTimer* scoreTimer;
    QTimer* eatAppleTimer;
    QTimer* passTimer;
    bool keyLeft = false;
    bool keyRight = false;
    bool keyUp = false;
    bool keyDown = false;
    bool keyZ=false;
    bool keySpace=false;
    bool isCollisides;
    bool enemyIsdead=false;
    bool playSucked=false;
    bool hasPlayedMusic=false;
    bool isPass1=false;
    int m_backgroundWidth;
    int m_backgroundHeight;
    int startLife=5;
    int currScore=0;
    int speedX=100;
    int speedY=100;
    qreal flyGravity=2;
    const qreal maxFlyHeight=100;
    qreal currentFlyHeight=0;
    QPointF enemyPos;
    QSound* flySound=new QSound(":/res/fly_s.wav");
    QSound* airPuff=new QSound(":/res/airPuff_s.wav");
    QSound* hitSound=new QSound(":/res/starHit_s.wav");
    QSound* hitByEnemySound=new QSound(":/res/hitByEnemy_s.wav");
    QSound* gameOverSound=new QSound("/res/loseSong.wav");
    QSound* suckSound=new QSound(":/res/airSuck_s.wav");
    QSound* starSound=new QSound(":/res/starShoot_s.wav");
    QSound* enemyDead=new QSound(":/res/enemyDead_s.wav");
    QLabel* scoreBoard=new QLabel(this);
signals:
};

#endif // PLAYSCENE_H
