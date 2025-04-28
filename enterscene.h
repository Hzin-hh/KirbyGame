#ifndef ENTERSCENE_H
#define ENTERSCENE_H

#include <QWidget>
#include<QGraphicsView>
#include<QGraphicsPixmapItem>

class EnterScene : public QGraphicsView
{
    Q_OBJECT
public:
    explicit EnterScene(QGraphicsScene* scene,QWidget* parent = nullptr);
private:
    QGraphicsPixmapItem* background1;
    QGraphicsScene* m_scene;
signals:
};

#endif // ENTERSCENE_H
