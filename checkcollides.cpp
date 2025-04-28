#include "checkcollides.h"
QVector<QRectF> CheckCollides::collides1=
    {
        QRectF(7,7,30,1593),
        QRectF(7,7,1040,90),
        QRectF(1020,7,15,1590),
        QRectF(20,1510,1040,90),
        QRectF(640,1370,146,230),
        QRectF(750,1370,305,230),
        QRectF(45,960,135,50),
        QRectF(250,960,140,50),
        QRectF(550,890,100,205),
        QRectF(830,960,40,50),
        QRectF(190,750,120,120),
        QRectF(470,680,120,120),
        QRectF(750,610,120,120),
        QRectF(190,540,190,50),
        QRectF(400,470,190,50),
        QRectF(605,400,190,50),
        QRectF(815,330,190,50)
};
QVector<QRectF> CheckCollides::collides2=
    {
        QRectF(2000*scale,-800,66*scale,1600*scale),
        QRectF(2068*scale,790*scale-800,89*scale,810*scale),
        QRectF(2157*scale,883*scale-800,93*scale,717*scale),
        QRectF(2070*scale,-800,90*scale,135*scale),
        QRectF(2000*scale,280*scale-800,390*scale,85*scale),
        QRectF(2302*scale,187*scale-800,90*scale,180*scale),
        QRectF(2000*scale,-800,690*scale,40*scale),
        QRectF(2625*scale,-800,70*scale,1600*scale),
        QRectF(2253*scale,468*scale-800,275*scale,272*scale),
        QRectF(2533*scale,372*scale-800,97*scale,368*scale),
        QRectF(2441*scale,883*scale-800,187*scale,717*scale),
        QRectF(2535*scale,45*scale-800,187*scale,90*scale),
        QRectF(2000*scale,1505,690*scale,70*scale),
        QRectF(2070*scale,375*scale-800,40*scale,40*scale),
        QRectF(2397*scale,1400*scale-810,35*scale,12*scale),
        QRectF(2256*scale,1150,35*scale,12*scale),
        QRectF(2396*scale,1211*scale-800,35*scale,12*scale),
        QRectF(2256*scale,1118*scale-800,35*scale,12*scale),
        QRectF(2209*scale,700*scale-800,35*scale,12*scale),
        QRectF(2071*scale,607*scale-800,35*scale,12*scale),
        QRectF(2209*scale,514*scale-800,35*scale,12*scale),
        QRectF(2396*scale,283*scale-800,70*scale+12,12*scale)
};
QVector<QRectF> CheckCollides::collides3=
    {
        QRectF(6445,780,85,480),
        QRectF(6445,490,185,282),
        QRectF(6000,-800,42,2110),
        QRectF(6245,-191,100,91),
        QRectF(6345,-100,100,95),
        QRectF(6445,-5,100,95),
        QRectF(6540,90,190,105),
        QRectF(6550,-475,175,670),
        QRectF(7120,-193,215,285),
        QRectF(7420,-475,175,470),
        QRectF(6636,492,769,280),
        QRectF(7215,772,188,190),
        QRectF(6636,200,85,85),
        QRectF(6730,-90,385,375),
        QRectF(7120,100,90,85),
        QRectF(6000,-800,3000,20),
        QRectF(8960,-800,40,2110),
        QRectF(8870,-90,95,1400),
        QRectF(8475,-90,525,80),
        QRectF(8290,-475,175,475),
        QRectF(7990,-190,480,185),
        QRectF(8188,200,177,372),
        QRectF(8188,490,472,85),
        QRectF(6540,1070,290,230),
        QRectF(6835,880,280,430),
        QRectF(7120,1170,1880,140),
        QRectF(7410,490,770,85),
        QRectF(7605,-90,395,85),
        QRectF(7608,300,180,80),
        QRectF(7897,200,180,80),
};
QVector<QRectF> CheckCollides::ground1=
    {
        QRectF(20,1510,1040,90),
        QRectF(640,1370,146,230),
        QRectF(750,1370,305,230),
        QRectF(45,960,135,50),
        QRectF(250,960,140,50),
        QRectF(550,890,100,205),
        QRectF(820,950,40,50),
        QRectF(190,750,120,1),
        QRectF(470,680,120,1),
        QRectF(750,610,120,1),
        QRectF(190,540,190,1),
        QRectF(400,470,190,1),
        QRectF(605,400,190,1),
        QRectF(815,330,190,1)
};
QVector<QRectF> CheckCollides::ground2=
    {
        QRectF(2000*scale,1505,690*scale,70*scale),
        QRectF(2157*scale,883*scale-800,93*scale,717*scale),
        QRectF(2068*scale,790*scale-800,89*scale,810*scale),
        QRectF(2441*scale,883*scale-800,187*scale,717*scale),
        QRectF(2253*scale,468*scale-800,275*scale,272*scale),
        QRectF(2533*scale,372*scale-800,97*scale,368*scale),
        QRectF(2300*scale,185*scale-800,90*scale,180*scale),
        QRectF(2000*scale,280*scale-800,390*scale,85*scale),
        QRectF(2399*scale,1400*scale-810,35*scale,12*scale),
        QRectF(2256*scale,1150,35*scale,12*scale),
        QRectF(2399*scale,1211*scale-800,35*scale,12*scale),
        QRectF(2256*scale,1118*scale-800,35*scale,12*scale),
        QRectF(2212*scale,700*scale-800,35*scale,12*scale),
        QRectF(2071*scale,607*scale-800,35*scale,12*scale),
        QRectF(2212*scale,514*scale-800,35*scale,12*scale),
        QRectF(2396*scale,283*scale-800,75*scale,12*scale)
};
QVector<QRectF> CheckCollides::ground3=
    {
        QRectF(6540,1070,290,230),
        QRectF(6835,880,280,430),
        QRectF(7120,1170,1880,140),
        QRectF(8475,-90,525,80),
        QRectF(8275,-475,195,475),
        QRectF(8188,200,192,372),
        QRectF(6535,-473,195,670),
        QRectF(7405,-475,195,470),
        QRectF(6636,492,769,280),
        QRectF(6730,-90,385,375),
        QRectF(7410,490,770,85),
        QRectF(7605,-90,295,85),
        QRectF(7608,300,180,80),
        QRectF(7897,200,180,80)
};
QVector<QRectF> CheckCollides::knife=
    {
        QRectF(7410,400,195,90),
        QRectF(7795,400,390,90),
        QRectF(6730,-180,390,90),
        QRectF(7600,-180,390,90)
};
CheckCollides::CheckCollides()
{

}
bool CheckCollides::checkCollides1(QGraphicsItem* kirby, QGraphicsItem* background01, const QPointF& newPos)
{
    QRectF kirbyRect=kirby->boundingRect();
    kirbyRect.translate(newPos);
    for (const QRectF& rect : collides1)
    {
        if (kirbyRect.intersects(rect))
            return true;
    }
    if((newPos.x()>=40&&newPos.y()>=920&&newPos.x()<=870&&newPos.y()<=1080)||(newPos.x()>=690&&newPos.y()>=1020&&newPos.x()<=1043&&newPos.y()<=1600))
    {
        kirby->setPos(newPos);
        if(kirby->collidesWithItem(background01))
        {
            return true;
        }
    }
    return false;
}

bool CheckCollides::checkCollides2(QGraphicsItem* kirby, const QPointF& newPos)
{
    QRectF kirbyRect=kirby->boundingRect();
    kirbyRect.translate(newPos);
    for (const QRectF& rect : collides2)
    {
        if (kirbyRect.intersects(rect))
            return true;
    }
    return false;
}

bool CheckCollides::checkCollides3(QGraphicsItem* kirby,QGraphicsItem* background03, const QPointF& newPos)
{
    QRectF kirbyRect=kirby->boundingRect();
    kirbyRect.translate(newPos);
    for (const QRectF& rect : collides3)
    {
        if (kirbyRect.intersects(rect))
            return true;
    }
    if((newPos.x()>=6055&&newPos.y()>=-780&&newPos.x()<=6345&&newPos.y()<=-490)||(newPos.x()>=8570&&newPos.y()>=-780&&newPos.x()<=8955&&newPos.y()<=-390)||(newPos.x()>=8665&&newPos.y()>=-5&&newPos.x()<=8855&&newPos.y()<=190))
    {
        kirby->setPos(newPos);
        if(kirby->collidesWithItem(background03))
        {
            return true;
        }
    }
    return false;
}

bool CheckCollides::isOnSlope1(const QPointF& newPos,bool isPass1)
{
    if(!isPass1)
    {
        if(newPos.x()>=270&&newPos.x()<=590&&newPos.y()>=1310&&newPos.y()<=1450)
        {
            return true;
        }
        else if(newPos.x()>=350&&newPos.x()<=500&&newPos.y()>=825&&newPos.y()<=900)
        {
            return true;
        }
        else if(newPos.x()>=650&&newPos.x()<=800&&newPos.y()>=825&&newPos.y()<=900)
        {
            return true;
        }
        else if(newPos.x()>=720&&newPos.x()<=1015&&newPos.y()>=1045&&newPos.y()<=1325)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool CheckCollides::isOnSlope3(const QPointF& newPos,bool isPass2)
{
    if(isPass2)
    {
        if(newPos.x()>=8225&&newPos.x()<=8865&&newPos.y()>=540&&newPos.y()<=1115)
        {
            return true;
        }
        else if(newPos.x()>=8330&&newPos.x()<=8665&&newPos.y()>=105&&newPos.y()<=435)
        {
            return true;
        }
        else if(newPos.x()>=6005&&newPos.x()<=6635&&newPos.y()>=-140&&newPos.y()<=440)
        {
            return true;
        }
        else if(newPos.x()>=6175&&newPos.x()<=6535&&newPos.y()>=-570&&newPos.y()<=-240)
        {
            return true;
        }
        else if(newPos.x()>=7070&&newPos.x()<=7405&&newPos.y()>=-570&&newPos.y()<=-245)
        {
            return true;
        }
        else if(newPos.x()>=7940&&newPos.x()<=8275&&newPos.y()>=-570&&newPos.y()<=-245)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool CheckCollides::isOnGround1(QGraphicsItem* kirby,const QPointF& newPos,bool isPass1)
{
    if(!isPass1)
    {
        QRectF kirbyRect=kirby->boundingRect();
        kirbyRect.translate(newPos);
        for (const QRectF& rect : ground1)
        {
            if (kirbyRect.intersects(rect))
                return true;
        }
    }
    return false;
}

bool CheckCollides::isOnGround2(QGraphicsItem* kirby, const QPointF& newPos)
{
    QRectF kirbyRect=kirby->boundingRect();
    kirbyRect.translate(newPos);
    for (const QRectF& rect : ground2)
    {
        if (kirbyRect.intersects(rect))
            return true;
    }
    return false;
}

bool CheckCollides::isOnGround3(QGraphicsItem* kirby,const QPointF& newPos,bool isPass2)
{
    if(isPass2)
    {
        QRectF kirbyRect=kirby->boundingRect();
        kirbyRect.translate(newPos);
        for (const QRectF& rect : ground3)
        {
            if (kirbyRect.intersects(rect))
                return true;
        }
    }
    return false;
}

//单向平台
// bool CheckCollides::isOneWayPlatform(QGraphicsItem *kirby, const QPointF &newPos,const QPointF &oldPos)
// {
//     QVector<QRectF> oneWayPlatforms={
//         QRectF(8670,490,190,60),
//         QRectF(6056,-177,190,60)
//     };
//     QRectF kirbyRect=kirby->boundingRect();
//     kirbyRect.translate(newPos);
//     for (const QRectF& platform : oneWayPlatforms)
//     {
//         if(kirbyRect.intersects(platform))
//         {
//             if (oldPos.y()+kirbyRect.height()<=platform.y()+5&&(newPos.y()>oldPos.y()))
//             {
//                 return true;
//             }
//             return false;
//         }
//     }
//     return false;
// }//错误的
bool CheckCollides::isOneWayPlatform(QGraphicsItem *kirby, const QPointF &newPos, const QPointF &oldPos)
{
    QVector<QRectF> oneWayPlatforms = {
        QRectF(8670, 490, 190, 60),
        QRectF(6056, -190, 190, 60)
    };

    QSizeF kirbySize = kirby->boundingRect().size();
    QRectF kirbyRect(newPos, kirbySize); // 以 newPos 为左上角
    qreal oldBottom = oldPos.y() + kirbySize.height();
    qreal newBottom = newPos.y() + kirbySize.height();

    for (const QRectF& platform : oneWayPlatforms)
    {
        if (kirbyRect.intersects(platform))
        {
            if (oldBottom <= platform.top() + 5 && newBottom > platform.top())
            {
                return true; // 从下往上穿过平台
            }
            return false; // 从上面或者其他方向穿过，不算
        }
    }
    return false;
}
QRectF CheckCollides::getOneWayPlatform(QGraphicsItem *kirby, const QPointF &newPos,const QPointF &oldPos)
{
    QVector<QRectF> oneWayPlatforms={
        QRectF(8670,490,190,60),
        QRectF(6056,-190,190,60)
    };
    QRectF kirbyRect=kirby->boundingRect();
    kirbyRect.translate(newPos);
    for (const QRectF& platform : oneWayPlatforms)
    {
        if(kirbyRect.intersects(platform))
        {
            if (oldPos.y()+kirbyRect.height()<=platform.y()+5&&(newPos.y()>oldPos.y()))
            {
                return platform;
            }
        }
    }
    return QRectF();
}
bool CheckCollides::sticked(QGraphicsItem *kirby, const QPointF &newPos)
{
        QRectF kirbyRect=kirby->boundingRect();
        kirbyRect.translate(newPos);
        for (const QRectF& rect : knife)
        {
            if (kirbyRect.intersects(rect))
            return true;
        }
    return false;
}
