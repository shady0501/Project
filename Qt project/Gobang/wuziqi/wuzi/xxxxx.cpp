#include "xxxxx.h"
#include <QKeyEvent>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include <QDebug>

XXXXX::XXXXX(QWidget* w)
{
    this->setWindowTitle("XXXXX");
    setButtonState(w, "back", 680, 560);

    for(int i=0;i<22;i++)
    {
        for(int j=0;j<27;j++)
        {
            position[i][j] = 0;
        }
    }

    X = 20;
    Y = 1;
    v = 0;
    position[X][Y] = 1;
    direction = 1;
}

void XXXXX::setButtonState
(QWidget* w, const QString& btnName, int x, int y)
{
    QPushButton* btn = new QPushButton;
    btn->setParent(this);
    btn->setText(btnName);
    btn->move(x,y);
    btn->setStyleSheet("QPushButton { background-image: "
                       "url(:/initial/resources/selectButton.png); }");
    btn->show();

    connect(btn,&QPushButton::clicked,this,[=]{
        this->close();
        w->show();
    });
}

void XXXXX::gravity()
{

}

void XXXXX::keyPressEvent(QKeyEvent* event)
{
    int previousX = X;
    int previousY = Y;

    position[X][Y] = 0;

    if(event->key() == Qt::Key_W && X > 5)
    {
        X -= 4;
        qDebug()<<QString("(%1,%2)").arg(X).arg(Y);
    }
    else if(event->key() == Qt::Key_S && X < 22)
    {
        X += 4;
        qDebug()<<QString("(%1,%2)").arg(X).arg(Y);
    }
    else if(event->key() == Qt::Key_A && Y > 1)
    {
        direction = 2;
        Y--;
        qDebug()<<QString("(%1,%2)").arg(X).arg(Y);
    }
    else if(event->key() == Qt::Key_D && Y < 25)
    {
        direction = 1;
        Y++;
        qDebug()<<QString("(%1,%2)").arg(X).arg(Y);
    }

    if(position[X][Y] == 2 || X<0 || X>22 || Y<0 || Y>25)
    {
        X = previousX;
        Y = previousY;
    }

    position[X][Y] = 1;
    repaint();
}

void XXXXX::paintEvent(QPaintEvent*)
{
    setWall();

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/initial/resources/002.png");
    pix=pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    QString str = "";
    for(int i=0;i<22;i++)
    {
        for(int j=0;j<27;j++)
        {
            if(i==21 || i==0 || j==0 || j==26 || position[i][j]==2)
                str = ":/res/WALL.png";
            else
                str = ":/res/PATH.png";

            QImage img(str);
            painter.drawImage(QRect(j*img.width(),i*img.height(),
                                    img.width(),img.height()),img);

            if(position[i][j] == 1 && direction ==1)
            {
                qDebug()<<QString("(%1,%2)").arg(X).arg(Y);
                str = ":/res/right.png";
            }
            if(position[i][j] == 1 && direction ==2)
                str = ":/res/left.png";

            QImage ima(str);
            painter.drawImage(QRect(j*ima.width(),i*ima.height(),
                                    ima.width(),ima.height()),ima);
        }
    }
}

void XXXXX::setWall()
{
    for(int i = 1; i<4; ++i)
        position[17][i] = 2;
}
