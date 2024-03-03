#include "levelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "mybutton.h"

LevelScene::LevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1500,1000);
    this->setWindowIcon(QPixmap(":/res/app.png"));
    this->setWindowTitle("选择关卡");

    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    QMenu* start = bar->addMenu("Start");
    QAction* quit = start->addAction("Quit");

    connect (quit, &QAction::triggered, [=]{
        this->close();
    });

    MyButton* backBtn = new MyButton(":/res/back1.png",":/res/back2.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn, &MyButton::clicked,[=]{
        qDebug()<<"back";

        QTimer::singleShot(100,this,[=](){
            emit this->chooseLevelBack();
        });
    });

    //创建关卡按钮
    MyButton *menuBtn[5];
    for(int i=0;i<5;++i)
    {
        menuBtn[i] = new MyButton(":/res/selectButton.png");
        menuBtn[i]->setParent(this);
        menuBtn[i]->move(200+i%3 *500, 400 +i/3 *300);

        connect(menuBtn[i],&MyButton::clicked,[=](){
            this->hide();

            //进入游戏场景
            play = new PlayScene(i+1);
            play->show();

            //设置场景位置
            play->setGeometry(this->geometry());

            connect(play,&PlayScene::choosePlayBack,[=]{
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });

            connect(play,&PlayScene::chooseNextPlay,[=]{
                delete play;
                play = NULL;
                emit menuBtn[i+1]->clicked();
            });
        });

        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn[i]->width(),menuBtn[i]->height());

        QFont font;
        font.setBold(true);
        font.setPointSize(20);
        label->setFont(font);

        label->setText(QString::number(i+1));
        label->move(200+i%3 *500, 400 +i/3 *300);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

void LevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/levelscene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/fontSelect.png");
    pix=pix.scaled(pix.width()*1,pix.height()*3);
    painter.drawPixmap(450,30,pix);
}
