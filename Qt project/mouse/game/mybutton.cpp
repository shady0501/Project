#include "mybutton.h"
#include<QDebug>
#include<QPropertyAnimation>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

MyButton::MyButton (QString normalImg, QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);

    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());

    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyButton::mousePressEvent(QMouseEvent* e)
{
    if(pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);

        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());

        this->setStyleSheet("QPushButton{border:0px;}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    return QPushButton::mousePressEvent(e);
}

void MyButton::mouseReleaseEvent(QMouseEvent* e)
{
    if(pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);

        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());

        this->setStyleSheet("QPushButton{border:0px;}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    return QPushButton::mouseReleaseEvent(e);
}
