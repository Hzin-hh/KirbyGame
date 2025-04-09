#include "apple.h"

Apple::Apple()
{
    QPixmap pixmap;
    QString str=QString(":/res/apple.png");
    pixmap.load(str);
    QPixmap scaledPixmap=pixmap.scaled(50,50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);
}
