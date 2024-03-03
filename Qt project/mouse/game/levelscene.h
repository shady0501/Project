#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class LevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    PlayScene* play = NULL;

signals:
    void chooseLevelBack();
    void chooseNextPlay();
};

#endif // LEVELSCENE_H
