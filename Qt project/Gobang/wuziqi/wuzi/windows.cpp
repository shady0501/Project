#include "windows.h"
#include "mainwindow.h"
#include "checkerboard.h"
#include "xxxxx.h"
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QWidget>
#include <QIcon>

Windows::Windows(QWidget* w,const QString& name,const QString& filePath)
{
    Qname = name;
    this->setWindowTitle(name);
    this->setWindowIcon(QIcon(filePath));

    if(Qname == "五子棋")
    {
        setButtonStatus(this,"人机对战",300,300);

        setButtonStatus(this,"双人对战",300,400);
    }
    else if(Qname == "XXXXX")
    {
        setButtonStatus(this,"第一关",300,200);
        setButtonStatus(this,"第二关",300,300);
        setButtonStatus(this,"第三关",300,400);
    }

    QPushButton* btn = new QPushButton();
    btn->setParent(this);
    btn->setText("返回");
    btn->move(300,500);
    btn->setStyleSheet("QPushButton { background-image: url(:/initial/resources/selectButton.png); }");
    btn->show();
    //this->resize(500,600);
    connect(btn,&QPushButton::clicked,this,[=]{
        this->close();
        w->show();
    });
}

void Windows::setButtonStatus
(QWidget* w, const QString& btnName, int x, int y)
{
    QPushButton* btn = new QPushButton(w);
    btn->setText(btnName);
    btn->move(x,y);
    btn->setStyleSheet("QPushButton { background-image: url(:/initial/resources/selectButton.png); }");
    btn->show();

    if(Qname=="五子棋")
    {
        connect(btn,&QPushButton::clicked,this,[=]{
            w->hide();
            checkerboard* board = new checkerboard(w,"五子棋——" + btnName);
            board->show();
            qDebug()<<"五子棋————"+btnName;
            board->setGeometry(w->geometry());
        });
    }
    else if(Qname=="XXXXX")
    {
        connect(btn,&QPushButton::clicked,this,[=]{
            w->hide();
            XXXXX* xxx = new XXXXX(w);
            xxx->show();
            qDebug()<<"xxx————"+btnName;
            xxx->setGeometry(w->geometry());
        });
    }
}

void Windows::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;

    if(Qname=="五子棋")
        pix.load(":/initial/resources/001.png");
    else if(Qname=="XXXXX")
        pix.load(":/initial/resources/002.png");
    pix=pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
