#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setButtonState(this,"五子棋",300,300,"五子棋");
    setButtonState(this,"XXXXX",300,400,"XXXXX");
    setButtonState(this,"退出",300,500);
    this->setWindowState(this,"初始界面",":/initial/resources/003.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWindowState
(QWidget* w,const QString& str,const QString& str2)
{
    w->setWindowTitle(str);
    w->setWindowIcon(QIcon(str2));

}

void MainWindow::setButtonState
(QWidget* w, const QString& btnName, int x, int y,const QString& windowName)
{
    QPushButton* btn = new QPushButton(w);
    btn->show();
    btn->setText(btnName);
    btn->move(x,y);
    btn->setStyleSheet("QPushButton { background-image: url(:/initial/resources/selectButton.png); }");

    if(btnName=="退出")
    {
        connect(btn,&QPushButton::clicked,w,&QWidget::close);
    }
    else
    {
        connect(btn,&QPushButton::clicked,w,[=]{
            w->hide();
            Windows* w2 = new Windows(w,windowName);
            w2->setGeometry(this->geometry());
            w2->show();
        });
    }
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/initial/resources/003.png");
    pix=pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
