#include "invincible.h"

Invincible::Invincible()
{
    QPixmap pixmap;
    QString str=QString(":/res/invincible.png");
    pixmap.load(str);
    QPixmap scaledPixmap=pixmap.scaled(50,50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);
}
