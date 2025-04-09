#include "gameover.h"
#include <QDebug>

GameOver::GameOver(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("GameOver");
    this->setFixedSize(1000, 800);
    QPixmap lose(":/res/loseScreen.png");
    QPixmap scaledLose = lose.scaled(1000, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    loseLabel = new QLabel(this);
    loseLabel->setPixmap(scaledLose);
    loseLabel->setGeometry(0, 0, this->width(), this->height());

}

void GameOver::showGameOver()
{
    this->show();
}
