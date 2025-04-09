#include "boom.h"

Boom::Boom()
{
    boomTimer=new QTimer(this);
    connect(boomTimer,&QTimer::timeout,[this]()
            {
                QPixmap pixmap;
                QString str=QString(":/res/deadAnimation%1.png").arg(boomMin++);
                pixmap.load(str);
                QPixmap scaledPixmap=pixmap.scaled(150,150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
               setPixmap(scaledPixmap);
                if(boomMin>boomMax)
                {
                    boomMin=1;
                }
            });
}
