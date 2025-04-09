#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPixmap>

class Enemy : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    virtual ~Enemy() {}//虚析构函数，防止内存泄漏
    virtual void swallowedLeft()=0;//纯虚函数。虚函数：它允许在基类指针或引用调用时，执行子类的重写函数。
    virtual void swallowedRight()=0;
    virtual void stopSwallowed()=0;
    explicit Enemy();
    static QPixmap flip(const QImage& image);
    static qreal lerp(qreal x, qreal x1, qreal y1, qreal x2, qreal y2);
private:


signals:
};

#endif // ENEMY_H
