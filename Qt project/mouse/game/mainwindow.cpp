#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSound>
#include "mybutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗口模式
    setFixedSize(1500,1000);

    setWindowIcon(QIcon(":/res/app.png"));

    setWindowTitle("老鼠走迷宫");

    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //音效
    QSound* startSound = new QSound(":/res/playsound.wav",this);
    startSound->setLoops(-1);
    startSound->play();

    //开始按钮
    MyButton* startBtn = new MyButton(":/res/start1.png",":/res/start2.png");
    startBtn->setParent(this);
    startBtn->move(1100,this->height()*0.7);

    level = new LevelScene;

    connect(level,&LevelScene::chooseLevelBack,[=]{
        this->setGeometry(level->geometry());
        level->hide();
        this->show();
    });

    connect (startBtn,&MyButton::clicked,[=]()
    {
        qDebug()<<"点击开始";
        //开始音效
        startSound->setLoops(-1);
        startSound->play();

        QTimer::singleShot(100,this,[=]{
            //设置场景位置
            level->setGeometry(this->geometry());
            //选择关卡
            this->hide();
            level->show();
        });

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    //加入背景图
    QPainter painter(this);

    QPixmap pix;

    pix.load(":/res/start.png");
    pix=pix.scaled(pix.width()*10,pix.height()*30);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //背景图上加入文字
    pix.load(":/res/fontStart.png");
    pix=pix.scaled(pix.width()*1,pix.height()*2.5);
    painter.drawPixmap(200,20,pix);


}

