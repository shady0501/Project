#ifndef XXXXX_H
#define XXXXX_H
#include <QWidget>

class XXXXX:public QWidget
{
public:
    XXXXX(QWidget*);
    void setButtonState(QWidget*, const QString&, int, int);
    void gravity();
    void keyPressEvent(QKeyEvent*);
    void paintEvent(QPaintEvent*);
    void setWall();

private:
    int position[22][27];
    int X;
    int Y;
    int v;
    int direction;
};

#endif // XXXXX_H
