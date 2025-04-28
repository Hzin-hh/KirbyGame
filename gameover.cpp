#include "gameover.h"
#include<QSound>

GameOver::GameOver(QWidget *parent)
    : QWidget{parent}
{
    QSound * tapButtonSound=new QSound(":/res/TapButtonSound.wav",this);
    this->setWindowTitle("GameOver!");
    this->setFixedSize(1000, 800);
    QPixmap lose(":/res/loseScreen.png");
    QPixmap scaledLose = lose.scaled(1000, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    loseLabel = new QLabel(this);
    loseLabel->setPixmap(scaledLose);
    loseLabel->setGeometry(0, 0, this->width(), this->height());
    gameOverSound->setSource(QUrl("qrc:/res/loseSong.wav"));
    backButton->move(this->width()*0.5-backButton->width()*0.5,this->height()*0.6);
    backButton->setParent(this);
    connect(backButton,&MyPushButton::clicked,this,&GameOver::backClicked);
    connect(backButton,&MyPushButton::clicked,[=](){
        backButton->zoom1();
        backButton->zoom2();
        tapButtonSound->play();
    });
}

void GameOver::showGameOver()
{
    this->show();
    gameOverSound->play();
}
