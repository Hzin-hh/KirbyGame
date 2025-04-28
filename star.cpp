#include "star.h"
#include"mykirby.h"

Star::Star()
{
    setPixmap(QPixmap(":/res/kirbyStar1.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    star1Timer = new QTimer(this);
    star2Timer = new QTimer(this);
    star3Timer = new QTimer(this);
    moveTimer  = new QTimer(this); // 添加移动计时器

    connect(star1Timer, &QTimer::timeout, this, [this]() {
        setPixmap(QPixmap(":/res/kirbyStar2.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        star1Timer->stop();
        star2Timer->start(100);
    });

    connect(star2Timer, &QTimer::timeout, this, [this]() {
        setPixmap(QPixmap(":/res/kirbyStar3.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        star2Timer->stop();
        star3Timer->start(100);
    });

    connect(star3Timer, &QTimer::timeout, this, [this]() {
        setPixmap(QPixmap(":/res/kirbyStar4.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        star3Timer->stop();
    });

    // 让 star 移动
    connect(moveTimer, &QTimer::timeout, this, [this]() {
        setX(x() + 60*direction);
    });


    // 开始动画
    star1Timer->start(100);
    moveTimer->start(80);
}

