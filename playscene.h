#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>
#include<QGraphicsView>
#include<QKeyEvent>
class PlayScene : public QGraphicsView
{
    Q_OBJECT
public:
    PlayScene(QGraphicsScene * scene,QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsPixmapItem *kirby;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *background01;
    QGraphicsPixmapItem *background02;
    QGraphicsPixmapItem *background03;
    QGraphicsPixmapItem *background04;
    int m_backgroundWidth;
    int m_backgroundHeight;
signals:
};

#endif // PLAYSCENE_H
