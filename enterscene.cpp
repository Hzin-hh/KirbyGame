#include "enterscene.h"
#include<QApplication>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QIcon>

EnterScene::EnterScene(QGraphicsScene *scene,QWidget * parent)
    : QGraphicsView(scene,parent), m_scene(scene)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用水平和垂直滚动条
    setFixedSize(1000,800);
    setWindowIcon(QIcon(":/res/Kirby.png"));
    setWindowTitle("星之卡比");
    QPixmap backgroundPixmap(":/res/BG.png");
    QPixmap scaledBackgroundPixmap=backgroundPixmap.scaled(2000,1610,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background1=scene->addPixmap(scaledBackgroundPixmap);
}
