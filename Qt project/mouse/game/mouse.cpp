#include "mouse.h"

Mouse::Mouse(QObject *parent,int Row,int Col) : QObject(parent)
{
    mRow=Row;
    mCol=Col;
    img=QImage(":/icon/BABA.png");

    //显示位置
    mPos=QPoint(mCol,mRow)*img.width();

}

Mouse::Mouse(QPoint StartPos,QObject *parent) : QObject(parent){
    mRow=StartPos.y();
    mCol=StartPos.x();
    img=QImage(":/icon/BABA.png");

    //显示位置
    mPos=QPoint(mCol,mRow)*img.width();
}


void Mouse::Move(int dRow,int dCol){
    //更新地图位置
    mRow+=dRow;
    mCol+=dCol;
    //更新打印位置
    mPos=QPoint(mCol,mRow)*img.width();
}

void Mouse::Paint(QPainter *p,QPoint Pos){
    p->drawImage(mPos+Pos,img);
}

