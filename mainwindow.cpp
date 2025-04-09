#include "mainwindow.h"
#include "ui_mainwindow.h"

QSound* MainWindow::gameSound=nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QStackWidget
    stackWidget=new QStackedWidget(this);
    setCentralWidget(stackWidget);

    // ========== 创建主菜单界面 ==========
    menuPage = new QWidget();
    QVBoxLayout *menuLayout = new QVBoxLayout(menuPage);
    menuPage->setLayout(menuLayout);
    background.load(":/res/menubackround.png");
    helpBackground.load(":/res/helpMenu.png");

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
    playBtn->setParent(menuPage);
    playBtn->move(this->width()*0.5-playBtn->width()*0.5,this->height()*0.5);

    MyPushButton * helpBtn=new MyPushButton(":/res/Menu_Help2.png");
    helpBtn->setParent(menuPage);
    helpBtn->move(this->width()*0.5-helpBtn->width()*0.5,this->height()*0.6);

    MyPushButton * exitBtn=new MyPushButton(":/res/Menu_EXIT2.png");
    exitBtn->setParent(menuPage);
    exitBtn->move(this->width()*0.5-exitBtn->width()*0.5,this->height()*0.7);

    MyPushButton * openmusicBtn=new MyPushButton(":/res/openmusic.png");
    openmusicBtn->setParent(this);
    openmusicBtn->move(this->width()*0.95,this->height()*0.05);

    MyPushButton * closemusicBtn=new MyPushButton(":/res/closemusic.png");
    closemusicBtn->setParent(this);
    closemusicBtn->move(this->width()*0.95, this->height()*0.05);
    closemusicBtn->hide();


    // ========== 创建帮助界面 ==========
    helpPage = new QWidget();
    QVBoxLayout *helpLayout = new QVBoxLayout(helpPage);
    helpPage->setLayout(helpLayout);
    MyPushButton * backBtn=new MyPushButton(":/res/Menu_Back.png");
    backBtn->setParent(helpPage);
    backBtn->move(this->width()*0.5-exitBtn->width()*0.5,this->height()*0.85);

    stackWidget->addWidget(menuPage);
    stackWidget->addWidget(helpPage);

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
            gameSound=new QSound(":/res/GameSong.wav",this);
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
                    stackWidget->setCurrentIndex(1);
                });
            });

    //exitBtn
    connect(exitBtn,&MyPushButton::clicked,[=]()
            {
                exitBtn->zoom1();
                exitBtn->zoom2();
                tapButtonSound->play();
                QTimer::singleShot(500,this,[=](){
                    int result= QMessageBox::question(this,"退出","是否退出",QMessageBox::Yes|QMessageBox::No);
                    if(result==QMessageBox::Yes)
                    {
                        this->close();
                    }
                });
            });

    //backBtn
    connect(backBtn,&MyPushButton::clicked,[=](){
        backBtn->zoom1();
        backBtn->zoom2();
        tapButtonSound->play();
        QTimer::singleShot(500,this,[=](){
            stackWidget->setCurrentIndex(0);
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
    if(stackWidget->currentIndex()==0)
        painter.drawPixmap(0,0,this->width(),this->height(),background);
    else
    {
        painter.drawPixmap(0,0,this->width(),this->height(),helpBackground);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
