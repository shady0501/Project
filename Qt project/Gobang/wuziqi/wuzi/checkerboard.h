#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H
#include <QWidget>

class checkerboard:public QWidget//棋盘类
{
public:
    checkerboard(QWidget*, const QString& = NULL);
    void setButtonState(QWidget*, const QString& = NULL, int = 0, int = 0);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent*);
    void paintEvent(QPaintEvent*);
    QString boardPaint(int, int);
    void AI();
    void AIstart();
    void AIplay();
    int AIcheck4();
    void AIcheck3();
    bool ifwin(int);
    void win();
    void setMessageBoxState(QString);
    void back();//悔棋

private:
    int board[19][19];
    int white[19][19];
    int black[19][19];
    int doubleCounter;
    int X;
    int Y;
    int doubleLastPlayer;
    int doubleLastX;
    int doubleLastY;
    int soloLastPlayer;
    int soloX;
    int soloY;
    bool step;
    bool flag;
    QString Qname;
    QWidget* theLastWindow;
};

#endif // CHECKERBOARD_H
