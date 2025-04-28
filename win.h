#ifndef WIN_H
#define WIN_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
#include<QSoundEffect>
#include "mypushbutton.h"

class Win : public QWidget
{
    Q_OBJECT
public:
    explicit Win(QWidget *parent = nullptr);
    QLabel *winLabel;
    void showWin();
    QSoundEffect* winSound = new QSoundEffect(this);
    MyPushButton* backButton = new MyPushButton(":/res/Menu_Back.png");
signals:
    void backClicked();
};

#endif // WIN_H
