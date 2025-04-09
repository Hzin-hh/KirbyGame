#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
#include "mainwindow.h"

class GameOver : public QWidget
{
    Q_OBJECT
public:
    explicit GameOver(QWidget *parent = nullptr);
    QLabel *loseLabel;
    void showGameOver();

private:
    MainWindow *parentMainWindow = nullptr;
signals:
    void gameOverFinished();
};

#endif // GAMEOVER_H
