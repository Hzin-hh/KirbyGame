#include "enemy.h"

Enemy::Enemy()
{

}
qreal Enemy::lerp(qreal x, qreal x1, qreal y1, qreal x2, qreal y2)
{
    if (x1 == x2) return y1; // 避免除零
    return y1 + ((x - x1) / (x2 - x1)) * (y2 - y1);
}

QPixmap Enemy::flip(const QImage& image)
{
     return QPixmap::fromImage(image.mirrored(true, false));
}


