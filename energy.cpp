#include "energy.h"

Energy::Energy()
{
    QPixmap pixmap;
    QString str=QString(":/res/energy.png");
    pixmap.load(str);
    QPixmap scaledPixmap=pixmap.scaled(50,50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);
}
