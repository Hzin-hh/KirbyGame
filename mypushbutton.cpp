#include "mypushbutton.h"
#include<QPixmap>
#include<QPropertyAnimation>

 //MyPushButton::MyPushButton(QPushButton *parent)
//     : QWidget{parent}
// {}

MyPushButton::MyPushButton(QString sendimg)
{
    QPixmap pix;
    pix.load(sendimg);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoom1()
{
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}


void MyPushButton::zoom2()
{
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
