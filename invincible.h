#ifndef INVINCIBLE_H
#define INVINCIBLE_H

#include <QObject>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Invincible : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Invincible();

signals:
};

#endif // INVINCIBLE_H
