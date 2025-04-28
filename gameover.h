#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
#include<QSoundEffect>
#include"mypushbutton.h"

class GameOver : public QWidget
{
    Q_OBJECT
public:
    explicit GameOver(QWidget *parent = nullptr);
    QLabel *loseLabel;
    void showGameOver();
    QSoundEffect* gameOverSound = new QSoundEffect(this);
    MyPushButton* backButton = new MyPushButton(":/res/Menu_Back.png");
signals:
    void backClicked();
};

#endif // GAMEOVER_H
