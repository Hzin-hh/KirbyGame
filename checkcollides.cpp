#include "checkcollides.h"

CheckCollides::CheckCollides()
{

}
bool CheckCollides::checkCollides1(QGraphicsItem* kirby, QGraphicsItem* background01, const QPointF& newPos, bool isPass1)
{
    if(!isPass1)
    {
        QRectF kirbyRect=kirby->boundingRect();
        kirbyRect.translate(newPos);
        QRectF left(7,7,30,1593);
        QRectF up(7,7,1040,90);
        QRectF right(1020,7,15,1590);
        QRectF ground1_01(20,1510,1040,90);
        QRectF ground1_02(640,1370,146,230);
        QRectF ground1_03(750,1370,305,230);
        QRectF ground2_01(45,960,135,50);
        QRectF ground2_02(250,960,140,50);
        QRectF ground2_03(550,890,100,205);
        QRectF ground2_04(830,960,40,50);
        QRectF square1_01(190,750,120,120);
        QRectF square1_02(470,680,120,120);
        QRectF square1_03(750,610,120,120);
        QRectF square2_01(190,540,190,50);
        QRectF square2_02(400,470,190,50);
        QRectF square2_03(605,400,190,50);
        QRectF square2_04(815,330,190,50);
        if (kirbyRect.intersects(ground1_01) ||
            kirbyRect.intersects(ground1_02) ||
            kirbyRect.intersects(ground1_03) ||
            kirbyRect.intersects(left)||
            kirbyRect.intersects(up)||
            kirbyRect.intersects(right)||
            kirbyRect.intersects(ground2_01)||
            kirbyRect.intersects(ground2_02)||
            kirbyRect.intersects(ground2_03)||
            kirbyRect.intersects(ground2_04)||
            kirbyRect.intersects(square1_01)||
            kirbyRect.intersects(square1_02)||
            kirbyRect.intersects(square1_03)||
            kirbyRect.intersects(square2_01)||
            kirbyRect.intersects(square2_02)||
            kirbyRect.intersects(square2_03)||
            kirbyRect.intersects(square2_04)
            )
        {
            return true;
        }
        if((newPos.x()>=40&&newPos.y()>=920&&newPos.x()<=870&&newPos.y()<=1080)||(newPos.x()>=690&&newPos.y()>=1020))
        {
            kirby->setPos(newPos);
            if(kirby->collidesWithItem(background01))
            {
                return true;
            }
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
        QRectF ground1_01(20,1510,1040,90);
        QRectF ground1_02(640,1370,146,230);
        QRectF ground1_03(750,1370,305,230);
        QRectF ground2_01(45,960,135,50);
        QRectF ground2_02(250,960,140,50);
        QRectF ground2_03(550,890,100,205);
        QRectF ground2_04(820,950,40,50);
        QRectF square1_01(190,750,120,1);
        QRectF square1_02(470,680,120,1);
        QRectF square1_03(750,610,120,1);
        QRectF square2_01(190,540,190,1);
        QRectF square2_02(400,470,190,1);
        QRectF square2_03(605,400,190,1);
        QRectF square2_04(815,330,190,1);
        if (kirbyRect.intersects(ground1_01) ||
            kirbyRect.intersects(ground1_02) ||
            kirbyRect.intersects(ground1_03) ||
            kirbyRect.intersects(ground2_01)||
            kirbyRect.intersects(ground2_02)||
            kirbyRect.intersects(ground2_03)||
            kirbyRect.intersects(ground2_04)||
            kirbyRect.intersects(square1_01)||
            kirbyRect.intersects(square1_02)||
            kirbyRect.intersects(square1_03)||
            kirbyRect.intersects(square2_01)||
            kirbyRect.intersects(square2_02)||
            kirbyRect.intersects(square2_03)||
            kirbyRect.intersects(square2_04))
        {
            return true;
        }
    }
    return false;
}
