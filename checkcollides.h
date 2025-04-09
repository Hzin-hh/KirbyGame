#ifndef CHECKCOLLIDES_H
#define CHECKCOLLIDES_H

#include <QObject>
#include <QRectF>
#include <QPointF>
#include <QGraphicsItem>
#include"playscene.h"

class CheckCollides : public QObject
{
    Q_OBJECT
public:
    explicit CheckCollides();
    static bool checkCollides1(QGraphicsItem* kirby, QGraphicsItem* background01, const QPointF& newPos, bool isPass1);//静态函数，不用生成对象即可调用
    static bool checkCollides2(QGraphicsItem* kirby, QGraphicsItem* background01, const QPointF& newPos, bool isPass1);
    static bool isOnSlope1(const QPointF& newPos,bool isPass1);
    static bool isOnSlope2(const QPointF& newPos);
    static bool isOnGround1(QGraphicsItem* kirby,const QPointF& newPos,bool isPass1);
    static bool isOnGround2(const QPointF& newPos);
signals:
};

#endif // CHECKCOLLIDES_H
