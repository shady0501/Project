#ifndef MOUSE_H
#define MOUSE_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QImage>
#include <QPainter>

class Mouse : public QObject
{
    Q_OBJECT
public:
    explicit Mouse(QObject *parent = nullptr,int Row=0,int Col=0);
    explicit Mouse(QPoint StartPos,QObject *parent = nullptr);

    int mRow,mCol;//地图位置
    QPoint mPos;//画图位置
    QImage img;

    void Move(int dRow,int dCol);
    void Paint(QPainter *p,QPoint Pos);

signals:

};

#endif // MOUSE_H
