#ifndef MYKIRBY_H
#define MYKIRBY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QSound>
#include <QPropertyAnimation>

class MyKirby : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MyKirby();
    void walk();
    void fly();
    void origin();
    void bend();
    void stopBend();
    void land();
    void stopLand();
    void fight();
    void swallow();
    void stopSwallow();
    void finishSwallow();
    void fatMove();
    void jump();
    void spit();
    void hurt();
    void spark();
    void stopSpark();
    bool isFlying=true;
    bool isLanding=false;
    bool towardLeft=false;
    bool towardRight=true;
    bool isBending=false;
    bool isFighting=false;
    bool invincible=false;
    bool isSwallowing=false;
    bool isSparking=false;
    bool fat=false;
    bool isJumping=false;
    bool isIceKirby=false;
    bool isFireKirby=false;
    bool isSwordKirby=false;
    bool isSpitting=false;
    bool isPuffing=false;
    bool isHurting=false;
    bool hasSet=false;
    QPixmap flip(QImage image);
    QSound* flySound=new QSound(":/res/fly_s.wav");
    QSound* swallowSound=new QSound("/res/swallow_s.wav");
    int kirbyLife=5;//生命值
    QTimer* walkTimer;
private:
    QTimer* flyTimer;
    QTimer* bendTimer;
    QTimer* landTimer;
    QTimer* fightTimer;
    QTimer* swallowTimer;
    QTimer* swallowTimer2;
    QTimer* fatTimer;
    QTimer* jumpTimer;
    QTimer* spitTimer;
    QTimer* hurtTimer;
    QTimer* sparkTimer;
    int walkMin=1;
    int walkMax=10;
    int fatWalkMin=1;
    int fatWalkMax=16;
    int flyMin=1;
    int flyMax=8;
    int flyFirst=9;
    int landMin=1;
    int landMax=3;
    int fightMin=1;
    int fightMax=12;
    int swallowMin=1;
    int swallowMax=5;
    int jumpMin=1;
    int jumpMax=9;
    int spitMin=1;
    int spitMax=4;
    int hurtMin=1;
    int hurtMax=8;
    int sparkMin=1;
    int sparkMax=3;
signals:

};

#endif // MYKIRBY_H
