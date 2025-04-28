#ifndef ENERGY_H
#define ENERGY_H

#include <QObject>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Energy : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Energy();

signals:
};

#endif // ENERGY_H
