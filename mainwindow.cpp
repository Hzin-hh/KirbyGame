#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include"mypushbutton.h"
#include"playscene.h"
#include<QTimer>
#include<QSound>
#include<QDialog>
#include<QMessageBox>
#include"settingdialog.h"
#include<QLabel>
#include<QFont>
#include<QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //窗口
    ui->setupUi(this);
    QGraphicsScene *myScene = new QGraphicsScene;
    QWidget *myParent = nullptr;
    PlayScene *playScene = new PlayScene(myScene, myParent);

    setFixedSize(1000,800);
    setWindowIcon(QIcon(":/res/Kirby.png"));
    setWindowTitle("星之卡比");

    //音效
    QSound * backGroundSound=new QSound(":/res/MenuSong.wav",this);
    QSound * tapButtonSound=new QSound(":/res/TapButtonSound.wav",this);
    backGroundSound->setLoops(-1);
    backGroundSound->play();

    //按钮
    MyPushButton * playBtn=new MyPushButton(":/res/Menu_play2.png");
    playBtn->setParent(this);
    playBtn->move(this->width()*0.5-playBtn->width()*0.5,this->height()*0.5);

    MyPushButton * helpBtn=new MyPushButton(":/res/Menu_Help2.png");
    helpBtn->setParent(this);
    helpBtn->move(this->width()*0.5-helpBtn->width()*0.5,this->height()*0.6);

    MyPushButton * exitBtn=new MyPushButton(":/res/Menu_EXIT2.png");
    exitBtn->setParent(this);
    exitBtn->move(this->width()*0.5-exitBtn->width()*0.5,this->height()*0.7);

    MyPushButton * openmusicBtn=new MyPushButton(":/res/openmusic.png");
    openmusicBtn->setParent(this);
    openmusicBtn->move(this->width()*0.95,this->height()*0.05);

    MyPushButton * closemusicBtn=new MyPushButton(":/res/closemusic.png");
    closemusicBtn->setParent(this);
    closemusicBtn->move(this->width()*0.95, this->height()*0.05);
    closemusicBtn->hide();


    //点击菜单栏
    connect(ui->menu,&QMenu::triggered,[=](){
        QTimer::singleShot(500,this,[=](){
            int result= QMessageBox::question(this,"ques","是否退出",QMessageBox::Yes|QMessageBox::No);
            if(result==QMessageBox::Yes)
            {
                this->close();
            }
        });
    });


    //点击按钮
    //playBtn
    connect(playBtn,&MyPushButton::clicked,[=](){
        playBtn->zoom1();
        playBtn->zoom2();
        tapButtonSound->play();
        backGroundSound->stop();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            playScene->show();
            //音效
            QSound * gameSound=new QSound(":/res/GameSong.wav",this);
            gameSound->setLoops(-1);
            gameSound->play();
        });
    });

    //helpBtn
    connect(helpBtn,&MyPushButton::clicked,[=]()
            {
        helpBtn->zoom1();
        helpBtn->zoom2();
        tapButtonSound->play();
        QTimer::singleShot(200,this,[=](){
            QDialog * helpDialog=new QDialog(this);
            helpDialog->show();
            helpDialog->setWindowTitle("游戏操作介绍");
            helpDialog->setFixedSize(600,400);
            helpDialog->move(this->width()*0.5,this->height()*0.5);
            QLabel *label=new QLabel(helpDialog);
            label->setStyleSheet("font-family: 'Microsoft YaHei'; font-size: 16pt; font-weight: bold; color: red;");
            label->setAlignment(Qt::AlignHCenter);
            label->setText("游戏操作指南：\n\n"
                           "1. 方向键 ←/→ 移动角色\n"
                           "2. 方向键 ↑ 飞翔    ↓ 俯身\n"
                           "3. X键 跳跃\n"
                           "4. Z键 攻击\n"
                           "玩家初始拥有五条生命值\n"
                           "生命值耗尽游戏结束！"
                           );
            QVBoxLayout *layout = new QVBoxLayout(helpDialog);
            layout->addWidget(label);
            helpDialog->setLayout(layout);

        });

    });

    //exitBtn
    connect(exitBtn,&MyPushButton::clicked,[=]()
            {
                exitBtn->zoom1();
                exitBtn->zoom2();
                tapButtonSound->play();
                QTimer::singleShot(500,this,[=](){
                   int result= QMessageBox::question(this,"ques","是否退出",QMessageBox::Yes|QMessageBox::No);
                    if(result==QMessageBox::Yes)
                        {
                       this->close();
                    }
                });
            });

    //openmusicBtn
    connect(openmusicBtn,&MyPushButton::clicked,[=]()
            {
        openmusicBtn->hide();
        backGroundSound->stop();

        closemusicBtn->show();
    });

    //closemusicBtn
    connect(closemusicBtn,&MyPushButton::clicked,[=]()
            {
                closemusicBtn->hide();
                backGroundSound->play();
                openmusicBtn->show();
            });
}



void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/menubackround.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
MainWindow::~MainWindow()
{
    delete ui;
}
