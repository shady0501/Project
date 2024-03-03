#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QAbstractButton>
#include "map.h"
#include "mouse.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int);

    void paintEvent(QPaintEvent*);
    virtual void keyPressEvent(QKeyEvent*);

    //void setMapPicture(const QString&);

    Mouse *mMouse;

    QTimer *mTimer;//游戏计时器
    int levelnum;
    Map *mMap;
    QPainter *mPainter;
    QString MapFile;
    QString getMapfile();

    void Collision(int dRow,int dCol);
    void updateGame();

signals:
    void choosePlayBack();
    void chooseNextPlay();

};

#endif // PLAYSCENE_H
