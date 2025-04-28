#ifndef APPLE_H
#define APPLE_H

#include <QObject>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Apple : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Apple();
signals:
};

#endif // APPLE_H
