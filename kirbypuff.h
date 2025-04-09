#ifndef KIRBYPUFF_H
#define KIRBYPUFF_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QApplication>
#include<QPixmap>
#include<QGraphicsScene>

class KirbyPuff : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit KirbyPuff();
    QTimer* puff1Timer;
    QTimer* puff2Timer;
    QTimer* puff3Timer;
    QTimer* moveTimer;
    void setDirection(int dir)
    {
        direction=dir;
    }
    int direction;
    ~KirbyPuff()
    {
        delete puff1Timer;
        delete puff2Timer;
        delete puff3Timer;
    }
signals:
};

#endif // KIRBYPUFF_H
