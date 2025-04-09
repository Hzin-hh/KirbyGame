#ifndef BOOM_H
#define BOOM_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPixmap>

class Boom : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Boom();
    QTimer * boomTimer;
~Boom()
    {
    delete boomTimer;
    }
private:
    int boomMin=1;
    int boomMax=7;
signals:
};

#endif // BOOM_H
