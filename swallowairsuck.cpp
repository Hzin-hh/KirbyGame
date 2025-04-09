#include "swallowairsuck.h"

SwallowAirSuck::SwallowAirSuck()
{
    suckTimer=new QTimer(this);
    if(suckRight)
    {
    setPixmap(QPixmap(":/res/SwallowAirSuck1.png").scaled(120, 90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        QPixmap pixmap;
        QString str=QString(":/res/SwallowAirSuck1.png");
        pixmap.load(str);
        QPixmap scaledPixmap;
        scaledPixmap=pixmap.scaled(120,60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaledPixmap=flip(scaledPixmap.toImage());
        setPixmap(scaledPixmap);
    }
    connect(suckTimer, &QTimer::timeout, this, [this]() {
        QPixmap pixmap;
        QString str=QString(":/res/SwallowAirSuck%1.png").arg(suckMin++);
        pixmap.load(str);
        QPixmap scaledPixmap;
        if(suckRight)
        {
            scaledPixmap=pixmap.scaled(120,90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        else
        {
            scaledPixmap=pixmap.scaled(120,90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            scaledPixmap=flip(scaledPixmap.toImage());
        }
        setPixmap(scaledPixmap);
        if(suckMin>suckMax)
        {
            suckMin=1;
        }
    });

}

QPixmap SwallowAirSuck::flip(QImage image)
{
    image=image.mirrored(true,false);
    QPixmap pix1=QPixmap::fromImage(image);
    return pix1;
}
