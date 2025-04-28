#include "win.h"
#include<QTimer>
#include<QSound>
Win::Win(QWidget *parent)
    : QWidget{parent}
{
    QSound * tapButtonSound=new QSound(":/res/TapButtonSound.wav",this);
    this->setWindowTitle("WIN!");
    this->setFixedSize(1000, 800);
    QPixmap win(":/res/winScreen.png");
    QPixmap scaledWin = win.scaled(1000, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    winLabel = new QLabel(this);
    winLabel->setPixmap(scaledWin);
    winLabel->setGeometry(0, 0, this->width(), this->height());
    winSound->setSource(QUrl("qrc:/res/winSong.wav"));
    backButton->move(this->width()*0.5-backButton->width()*0.5,this->height()*0.8);
    backButton->setParent(this);
    backButton->hide();
    connect(backButton,&MyPushButton::clicked,this,&Win::backClicked);
    connect(backButton,&MyPushButton::clicked,[=](){
        backButton->zoom1();
        backButton->zoom2();
        tapButtonSound->play();
    });
}

void Win::showWin()
{
    this->show();
    winSound->play();
    QTimer::singleShot(2000,this,[this]{
        backButton->show();
    });
}
