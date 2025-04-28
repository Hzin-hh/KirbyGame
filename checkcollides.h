#ifndef CHECKCOLLIDES_H
#define CHECKCOLLIDES_H

#include <QObject>
#include <QRectF>
#include <QPointF>
#include <QGraphicsItem>
#include<QVector>
#include"playscene.h"

class CheckCollides : public QObject
{
    Q_OBJECT
public:
    explicit CheckCollides();
    static bool checkCollides1(QGraphicsItem* kirby, QGraphicsItem* background01, const QPointF& newPos);//静态函数，不用生成对象即可调用
    static bool checkCollides2(QGraphicsItem* kirby, const QPointF& newPos);
    static bool checkCollides3(QGraphicsItem* kirby,QGraphicsItem* background03, const QPointF& newPos);
    static bool isOnSlope1(const QPointF& newPos,bool isPass1);
    static bool isOnSlope3(const QPointF& newPos,bool isPass2);
    static bool isOnGround1(QGraphicsItem* kirby,const QPointF& newPos,bool isPass1);
    static bool isOnGround2(QGraphicsItem* kirby, const QPointF& newPos);
    static bool isOnGround3(QGraphicsItem* kirby, const QPointF& newPos,bool isPass2);
    static bool sticked(QGraphicsItem* kirby, const QPointF& newPos);
    //单向平台
    static bool isOneWayPlatform(QGraphicsItem* kirby, const QPointF& newPos,const QPointF& oldPos);
    static QRectF getOneWayPlatform(QGraphicsItem* kirby, const QPointF& newPos,const QPointF& oldPos);
private:
    static constexpr qreal scale=1.5;
    static QVector<QRectF> collides1;
    static QVector<QRectF> collides2;
    static QVector<QRectF> collides3;
    static QVector<QRectF> ground1;
    static QVector<QRectF> ground2;
    static QVector<QRectF> ground3;
    static QVector<QRectF> knife;
signals:
};

#endif // CHECKCOLLIDES_H
