#include "kirbypuff.h"
#include"mykirby.h"

KirbyPuff::KirbyPuff()
{
    setPixmap(QPixmap(":/res/kirbySpit01.png").scaled(60, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    puff1Timer = new QTimer(this);
    puff2Timer = new QTimer(this);
    puff3Timer = new QTimer(this);
    moveTimer  = new QTimer(this); // 添加移动计时器

    connect(puff1Timer, &QTimer::timeout, this, [this]() {
        setPixmap(QPixmap(":/res/kirbySpit02.png").scaled(60, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        puff1Timer->stop();
        puff2Timer->start(100); // 100ms 后切换到 puff2
    });

    connect(puff2Timer, &QTimer::timeout, this, [this]() {
        setPixmap(QPixmap(":/res/kirbySpit03.png").scaled(60, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        puff2Timer->stop();
        puff3Timer->start(100); // 100ms 后切换到 puff3
    });

    connect(puff3Timer, &QTimer::timeout, this, [this]() {
        setPixmap(QPixmap(":/res/kirbySpit04.png").scaled(60, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        puff3Timer->stop();
    });

    // 让 puff 移动
    connect(moveTimer, &QTimer::timeout, this, [this]() {
        setPos(x() + 10*direction, y()); // 每次向右移动 10 像素
    });

    // 开始动画
    puff1Timer->start(100);  // 100ms 后切换 puff1
    moveTimer->start(40);    // 每 40ms 移动一次
}

