#include "playscene.h"
#include"mainwindow.h"
#include<QApplication>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QGraphicsScene>
#include<QBrush>

PlayScene::PlayScene(QGraphicsScene *scene,QWidget * parent)
    : QGraphicsView(scene,parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用水平和垂直滚动条
    setFixedSize(1000,800);
    setWindowIcon(QIcon(":/res/Kirby.png"));
    setWindowTitle("星之卡比");
    scene->setBackgroundBrush(QBrush(QColor("0,0,0")));

    //设置背景
    QPixmap backgroundPixmap(":/res/BG.png");
    background=scene->addPixmap(backgroundPixmap);
    background->setPos(0,0);

    //设置背景1
    QPixmap backgroundPixmap01(":/res/Kirby_level1_map1.png");
    QPixmap scaledBackgroundPixmap01=backgroundPixmap01.scaled(2000,1600,Qt::KeepAspectRatio);
    background01=scene->addPixmap(scaledBackgroundPixmap01);

    m_backgroundWidth=scaledBackgroundPixmap01.width();
    m_backgroundHeight=scaledBackgroundPixmap01.height();

    //设置角色
    QPixmap kirbyPixmap(":/res/Kirby.png");
    kirby=scene->addPixmap(kirbyPixmap);
    kirby->setPos(0,m_backgroundHeight-180);
    centerOn(kirby);




}

 void PlayScene::keyPressEvent(QKeyEvent *event)
{
    QPointF oldPos=kirby->pos();
    QPointF newPos=oldPos;
     switch(event->key())
    {
    case Qt::Key_Left:
         newPos.setX(newPos.x()-10);
        break;
    case Qt::Key_Right:
        newPos.setX(newPos.x()+10);
        break;
    case Qt::Key_Up:
        newPos.setY(newPos.y()-10);
        break;
    case Qt::Key_Down:
        newPos.setY(newPos.y()+10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        return;
     }

    kirby->setPos(newPos);
    if(kirby->collidesWithItem(background01))
     {
        kirby->setPos(oldPos);
    }

     centerOn(kirby);//使角色始终在视图中心附近
}

