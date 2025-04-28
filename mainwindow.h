#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include"playscene.h"
#include<QSound>
#include<QSoundEffect>
#include"gameover.h"
#include"win.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QDialog>
#include<QMessageBox>
#include"settingdialog.h"
#include<QLabel>
#include<QFont>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static QSoundEffect* gameSound;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    QStackedWidget * stackWidget;
    QGraphicsScene *myScene = new QGraphicsScene;
    PlayScene *playScene = new PlayScene(myScene, nullptr);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QPixmap background;
    QPixmap helpBackground;
    QWidget* menuPage;
    QWidget* helpPage;
};
#endif // MAINWINDOW_H
