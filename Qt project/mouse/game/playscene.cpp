#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QFont>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QApplication>
#include <QPropertyAnimation>
#include <QAbstractButton>
#include <QSound>
#include <QMovie>
#include "levelscene.h"
#include "mybutton.h"

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{
    //this->setWindowTitle("");
}

PlayScene::PlayScene(int num)
{
    this->levelnum = num;
    this->MapFile = PlayScene::getMapfile();
    qDebug()<<"mapfile="<<getMapfile();

    mMap=new Map(MapFile,this);

    mPainter=new QPainter(this);
    mMouse=new Mouse(this,1,1);

    this->setFixedSize(1500,1000);
    this->setWindowIcon(QPixmap(":/res/app.png"));
    this->setWindowTitle("关卡");

    QTime::currentTime();

    mTimer = new QTimer(this);
    mTimer->start(10);
    connect(mTimer,&QTimer::timeout,[this](){this->update();updateGame(); });//定时调用更新

    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    QMenu* start = bar->addMenu("Start");
    QAction* quit = start->addAction("Quit");

    connect (quit, &QAction::triggered, [=]{
        this->close();
    });

    //返回按钮
    MyButton* backBtn = new MyButton(":/res/back1.png",":/res/back2.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn, &MyButton::clicked,[=]{
        qDebug()<<"back";

        QTimer::singleShot(100,this,[=](){
            emit this->choosePlayBack();
        });
    });

    QLabel* label = new QLabel;
    label->setParent(this);

    QFont font;
    font.setFamily("Arial");
    font.setBold(true);
    font.setWeight(1000);
    font.setPointSize(30);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::red); // 设置为红色
    label->setPalette(palette);

    QString str = "level : " + QString::number(this->levelnum);
    label->setFont(font);
    label->setText(str);

    label->setGeometry(50,this->height()-100,500,50);

}

void PlayScene::paintEvent(QPaintEvent *)
{
    mPainter->begin(this);

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/003.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    mMap->Paint(mPainter);

    mMouse->Paint(mPainter,QPoint(0,0));

    mPainter->end();

}

QString PlayScene::getMapfile(){
    char level=levelnum+'0';
    QString Mapfile="./Map/level";
    Mapfile+=level;
    Mapfile+=".txt";
    qDebug()<<"PlayScene::getMapfile="<<Mapfile;
    return Mapfile;
}

void PlayScene::keyPressEvent(QKeyEvent* event)
{
        switch(event->key())
        {
        case Qt::Key_W:
        {
            //判断是否碰撞
            Collision(-1,0);
            break;
        }
        case Qt::Key_Up:
        {
            //判断是否碰撞
            Collision(-1,0);
            break;
        }
        case Qt::Key_S:
        case Qt::Key_Down:
        {
            Collision(1,0);
            break;
        }
        case Qt::Key_A:
        case Qt::Key_Left:
        {
            Collision(0,-1);
            break;
        }
        case Qt::Key_D:
        case Qt::Key_Right:
        {
            Collision(0,1);
            break;
        }
        }
}

void PlayScene::Collision(int dRow,int dCol){
    //下一位置
    int nRow=mMouse->mRow+dRow;
    int nCol=mMouse->mCol+dCol;

    if(mMap->mPArr[nRow][nCol]==Wall){
        return ;
    }

    mMouse->Move(dRow,dCol);
}

void PlayScene::updateGame()
{
    qDebug()<<mMouse->mCol<<","<<mMouse->mRow<<endl;
        if(mMouse->mCol==mMap->FlagCol&&mMouse->mRow==mMap->FlagRow)
        {
            // 创建窗口
            QWidget window;
            window.setWindowTitle("WIN");
            window.resize(400, 400);

            // 创建QLabel用于显示动画
            QLabel label(&window);
            label.setGeometry(0, 0, 500, 500);

            QMovie *movie = new QMovie(":/res/yh.gif");
            label.setMovie(movie);
            movie->start();
            movie->setSpeed(100);
            window.show();

           QString message="游戏已获胜！";
           QMessageBox msgBox;
           msgBox.setWindowTitle("提示");
           msgBox.setText(message);


           msgBox.addButton("返回关卡选择", QMessageBox::YesRole);
           //msgBox.addButton("开始下一关", QMessageBox::NoRole);

           connect(&msgBox, &QMessageBox::buttonClicked, this, [=](QAbstractButton *button){
               QMessageBox *msgBox = qobject_cast<QMessageBox*>(sender());
                  if (msgBox)
                  {
                      if (QMessageBox::YesRole == msgBox->buttonRole(button))
                      {
                          // 返回关卡选择窗口
                           emit this->choosePlayBack();
                           msgBox->close();
                      }
                      else if (QMessageBox::NoRole== msgBox->buttonRole(button))
                      {
                          // 开始下一关
                          emit this->chooseNextPlay();
                          msgBox->close();
                      }
                  }
           });
                    msgBox.exec();
               }
}
