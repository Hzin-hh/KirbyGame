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
    void moveRight();
    void moveLeft();
    void flyRight();
    void flyLeft();
    void origin();
    void bend();
    void land();
    void fight();
    void stopBend();
    void swallow();
    void stopSwallow();
    void finishSwallow();
    void fatMoveLeft();
    void fatMoveRight();
    bool isFlying=true;
    bool isLanding=false;
    bool towardLeft=false;
    bool towardRight=true;
    bool isBending=false;
    bool isFighting=false;
    bool invincible=false;
    bool isSwallowing=false;
    bool fat=false;
    QPixmap flip(QImage image);
    QSound* flySound=new QSound(":/res/fly_s.wav");
    QSound* swallowSound=new QSound("/res/swallow_s.wav");
    int kirbyLife=5;//生命值
private:
    QTimer* timerR;
    QTimer* timerL;
    QTimer* flyRightTimer;
    QTimer* flyLeftTimer;
    QTimer* bendTimer;
    QTimer* bendTimer2;
    QTimer* landTimer;
    QTimer* fightTimer;
    QTimer* swallowTimer;
    QTimer* swallowTimer2;
    QTimer* fatTimerR;
    QTimer* fatTimerL;
    int walkMin=1;
    int walkMax=10;
    int fatWalkMin=1;
    int fatWalkMax=16;
    int flyMin=1;
    int flyMax=8;
    int flyFirst=9;
    int bendMin=1;
    int bendMax=2;
    int landMin=1;
    int landMax=3;
    int fightMin=1;
    int fightMax=12;
    int swallowMin=1;
    int swallowMax=5;
    ~MyKirby()
    {
        delete timerL;
        delete timerR;
        delete bendTimer;
        delete bendTimer2;
        delete fatTimerL;
        delete fatTimerR;
        delete fightTimer;
        delete flyLeftTimer;
        delete flyRightTimer;
        delete landTimer;
        delete swallowTimer;
        delete swallowTimer2;
    }
signals:

};

#endif // MYKIRBY_H
