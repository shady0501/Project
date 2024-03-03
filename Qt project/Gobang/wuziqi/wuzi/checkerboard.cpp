#include "checkerboard.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QIcon>

checkerboard::checkerboard(QWidget* w, const QString& name)
{
    qDebug()<<"checkerboard:"+name;
    this->setWindowTitle(name);
    this->setWindowIcon(QIcon(":/initial/resources/002.png"));
    setButtonState(w,"返回",650,550);
    setButtonState(w,"悔棋",650,450);

    for(int i = 0; i < 19; ++i)
    {
        for(int j = 0; j < 19; ++j)
        {
            board[i][j]=0;
            white[i][j]=0;
            black[i][j]=0;
        }
    }

    X = 9;
    Y = 9;
    doubleCounter = 0;
    doubleLastPlayer = 2;
    doubleLastX = 0;
    doubleLastY = 0;
    soloLastPlayer = 2;
    soloX = 0;
    soloY = 0;
    step = false;
    flag = false;
    Qname = name;
    theLastWindow = w;
}

void checkerboard::setButtonState
(QWidget* w, const QString& btnName, int x, int y)
{
    QPushButton* btn = new QPushButton;
    btn->setParent(this);
    btn->setText(btnName);
    btn->move(x,y);
    btn->setStyleSheet("QPushButton { background-image: "
                       "url(:/initial/resources/selectButton.png); }");
    btn->show();

    if(btnName == "返回")
    {
        connect(btn,&QPushButton::clicked,this,[=]{
            this->close();
            w->show();
        });
    }

    if(btnName == "悔棋")
    {
        qDebug()<<white[9][8];
        qDebug()<<black[9][9];
        connect(btn,&QPushButton::clicked,this,[=]{
            back();
        });
    }
}

void checkerboard::mousePressEvent(QMouseEvent* event)
{
    if(Qname == "五子棋——人机对战")
    {
        QString str = QString("x=%1, y=%2").arg(event->x()).arg(event->y());
        qDebug()<<str;
        int mouseX = (event->y()-112+12.5)/25;
        int mouseY = (event->x()-116+12.5)/25;

        if(mouseX>=0 && mouseX<19 && mouseY>=0 && mouseY<19 &&
           soloLastPlayer ==2 && board[mouseX][mouseY]==0)
        {
            board[mouseX][mouseY]=1;
            soloLastPlayer = 1;
            soloX = mouseX;
            soloY = mouseY;
            step = false;

            win();

            if(soloLastPlayer == 1 && step == false)
            {
                AI();
            }

            win();
        }

        repaint();
    }
}

void checkerboard::AI()
{
    soloLastPlayer = 2;

    AIcheck4();

    if(step == false)
        AIplay();

    if(step == false)
        AIcheck3();

    if(step == false)
        AIstart();

}

void checkerboard::AIstart()
{
    qDebug()<<QString("AIstart start");

    if(board[soloX-1][soloY-1] == 0)
    {
        board[soloX-1][soloY-1] = 2;
        qDebug()<<QString("start——0");
        step = true;
    }
    else if(board[soloX+1][soloY] == 0)
    {
        board[soloX+1][soloY] = 2;
        qDebug()<<QString("start——1");
        step = true;
    }
    else if(board[soloX][soloY-1] == 0)
    {
        board[soloX][soloY-1] = 2;
        qDebug()<<QString("start——2");
        step = true;
    }
    else if(board[soloX-1][soloY] == 0)
    {
        board[soloX-1][soloY] = 2;
        qDebug()<<QString("start——3");
        step = true;
    }
    else if(board[soloX+1][soloY+1] == 0)
    {
        board[soloX+1][soloY+1] = 2;
        qDebug()<<QString("start——4");
        step = true;
    }
    else if(board[soloX][soloY+1] == 0)
    {
        board[soloX][soloY+1] = 2;
        qDebug()<<QString("start——5");
        step = true;
    }
    else if(board[soloX+1][soloY-1] == 0)
    {
        board[soloX+1][soloY-1] = 2;
        qDebug()<<QString("start——6");
        step = true;
    }
    else if(board[soloX-1][soloY+1] == 0)
    {
        board[soloX-1][soloY+1] = 2;
        qDebug()<<QString("start——7");
        step = true;
    }

    qDebug()<<QString("AIstart end");
}

void checkerboard::AIplay()
{
    qDebug()<<QString("AIplay start");

    int sum[4] = {0};
    int blank[4][2] = {{0}};

    for(int i=0; i<19; ++i)
    {
        for(int j=0; j<19; ++j)
        {
            //qDebug()<<QString("进入for循环");
            if(board[i][j]==2)
            {
                sum[0]++;
                qDebug()<<QString("sum0 = %1)").arg(sum[0]);
                blank[0][0] = i;
                blank[0][1] = j+1;
            }
            else
            {
                sum[0] = 0;
                blank[0][0] = 0;
                blank[0][1] = 0;
            }

            if(board[j][i]==2)
            {
                sum[1]++;
                qDebug()<<QString("sum1 = %1)").arg(sum[1]);
                blank[1][0] = j+1;
                blank[1][1] = i;
            }
            else
            {
                sum[1] = 0;
                blank[1][0] = 0;
                blank[1][1] = 0;
            }

            for(int k=0; i>3&&i<15 && j<3&&j<15 && k<5; ++k)
            {
                if(i+k<19 && j+k<19 && board[i+k][j+k] == 2)
                {
                    sum[2]++;
                    qDebug()<<QString("sum2 = %1)").arg(sum[2]);
                    blank[2][0] = i+k+1;
                    blank[2][1] = j+k+1;
                }
                else
                {
                    sum[2] = 0;
                    blank[2][0] = 0;
                    blank[2][1] = 0;
                }

                if(j-k>=0 && board[i+k][j-k] == 2)
                {
                    sum[3]++;
                    qDebug()<<QString("sum3 = %1)").arg(sum[3]);
                    blank[3][0] = i+k+1;
                    blank[3][1] = j-k-1;
                }
                else
                {
                    sum[3] = 0;
                    blank[3][0] = 0;
                    blank[3][1] = 0;
                }
            }

            for(int k=0; sum[k] == 4 && k<5; ++k)
            {
                if(board[blank[k][0]][blank[k][1]]==0)
                {
                    board[blank[k][0]][blank[k][1]]=2;
                    qDebug()<<QString("sum%1=4").arg(k);
                    step = true;
                    return;
                }
                else
                {
                    if(blank[0][1]-5>=0 && board[blank[0][0]][blank[0][1]-5]==0)
                    {
                        board[blank[0][0]][blank[0][1]-5]=2;
                        step =true;
                        return;
                    }
                    else if(blank[1][0]-5>=0 && board[blank[1][0]-5][blank[1][1]]==0)
                    {
                        board[blank[1][0]-5][blank[1][1]]=2;
                        step =true;
                        return;
                    }
                    else if(blank[2][0]-5>=0 && blank[2][1]-5>=0
                            && board[blank[2][0]-5][blank[2][1]-5]==0)
                    {
                        board[blank[2][0]-5][blank[2][1]-5]=2;
                        step =true;
                        return;
                    }
                    else if(blank[3][0]-5>=0 && blank[3][1]+5<19
                            && board[blank[3][0]-5][blank[3][1]+5]==0)
                    {
                        board[blank[3][0]-5][blank[3][1]+5]=2;
                        step =true;
                        return;
                    }
                }
            }

            for(int k=0; sum[k] == 3 && k<5; ++k)
            {
                qDebug()<<QString("sum%1 = 3").arg(k);

                if(blank[0][1]-5>=0 && board[blank[0][0]][blank[0][1]]==0
                        && board[blank[0][0]][blank[0][1]-5]==0)
                {
                    board[blank[0][0]][blank[0][1]]=2;
                    step =true;
                    return;
                }
                else if(blank[1][0]-5>=0 && board[blank[1][0]][blank[1][1]]==0
                        && board[blank[1][0]-5][blank[1][1]]==0)
                {
                    board[blank[1][0]][blank[1][1]]=2;
                    step =true;
                    return;
                }
                else if(blank[2][0]-5>=0 && blank[2][1]-5>=0
                        && board[blank[2][0]][blank[2][1]]==0
                        && board[blank[2][0]-5][blank[2][1]-5]==0)
                {
                    board[blank[2][0]][blank[2][1]]=2;
                    step =true;
                    return;
                }
                else if(blank[3][0]-5>=0 && blank[3][1]+5<19
                        && board[blank[3][0]][blank[3][1]]==0
                        && board[blank[3][0]-5][blank[3][1]+5]==0)
                {
                    board[blank[3][0]][blank[3][1]]=2;
                    step =true;
                    return;
                }
            }
        }
    }

    qDebug()<<QString("AIplay end");
}

int checkerboard::AIcheck4()
{
    qDebug()<<QString("AIcheck4 start");

    int counter[4] = {0};
    int number[4][2] = {{0}};

    for(int i=0;i<7;++i)
    {
        if(soloY+3-i>=0 && soloY+3-i<19 && board[soloX][soloY+3-i]==1)
        {
            ++counter[0];
            number[0][0] = soloX;
            number[0][1] = soloY+3-i-1;
        }
        else
        {
            counter[0] = 0;
            number[0][0] = 0;
            number[0][1] = 0;
        }

        if(soloX+3-i>=0 && soloX+3-i<19 && board[soloX+3-i][soloY]==1)
        {
            ++counter[1];
            number[1][0] = soloX+3-i-1;
            number[1][1] = soloY;
        }
        else
        {
            counter[1] = 0;
            number[1][0] = 0;
            number[1][1] = 0;
        }

        if(soloX+3-i>=0 && soloX+3-i<19 &&
           soloY+3-i>=0 && soloY+3-i<19 && board[soloX+3-i][soloY+3-i]==1)
        {
            ++counter[2];
            number[2][0] = soloX+3-i-1;
            number[2][1] = soloY+3-i-1;
        }
        else
        {
            counter[2] = 0;
            number[2][0] = 0;
            number[2][1] = 0;
        }

        if(soloX+3-i>=0 && soloX+3-i<19 &&
           soloY-3+i>=0 && soloY-3+i<19 && board[soloX+3-i][soloY-3+i]==1)
        {
            ++counter[3];
            number[3][0] = soloX+3-i-1;
            number[3][1] = soloY-3+i+1;
        }
        else
        {
            counter[3] = 0;
            number[3][0] = 0;
            number[3][1] = 0;
        }

        for(int j=0; j<5; ++j)
        {
            if(counter[j]==4)
            {
                if(number[j][0]>=0 && number[j][0]<19 && number[j][1]>=0 &&
                   number[j][1]<19 && board[number[j][0]][number[j][1]] == 0)
                {
                    board[number[j][0]][number[j][1]] = 2;
                    step = true;
                    qDebug()<<1;
                    return 1;
                }
                else if(j == 0)
                {
                    board[number[j][0]][number[j][1]+5] = 2;
                    step = true;
                    qDebug()<<2;
                    return 1;
                }
                else if(j == 1)
                {
                    board[number[j][0]+5][number[j][1]] = 2;
                    step = true;
                    qDebug()<<3;
                    return 1;
                }
                else if(j == 2)
                {
                    board[number[j][0]+5][number[j][1]+5] = 2;
                    step = true;
                    qDebug()<<4;
                    return 1;
                }
                else if(j == 3)
                {
                    board[number[j][0]+5][number[j][1]-5] = 2;
                    step = true;
                    qDebug()<<5;
                    return 1;
                }
            }
        }
        qDebug()<<7;
    }
    qDebug()<<8;

    qDebug()<<QString("return 0");
    qDebug()<<QString("AIcheck4 end");
    return 0;
}

void checkerboard::AIcheck3()
{
    qDebug()<<QString("AIcheck3 start");

    int number[4][2] = {{0}};
    int counter[4] = {0};

    for(int i=0; i<5; ++i)
    {
        if(board[soloX][soloY-2+i]==1)
        {
            ++counter[0];
            number[0][0] = soloX;
            number[0][1] = soloY-2+i+1;
            qDebug()<<QString("counter0=%1,number0=%2,number1=%3").arg(counter[0]).arg(number[0][0]).arg(number[0][1]);
        }
        else
        {
            counter[0] = 0;
            number[0][0] = 0;
            number[0][1] = 0;
        }

        if(board[soloX-2+i][soloY]==1)
        {
            ++counter[1];
            number[1][0] = soloX-2+i+1;
            number[1][1] = soloY;
        }
        else
        {
            counter[1] = 0;
            number[1][0] = 0;
            number[1][1] = 0;
        }

        if(board[soloX-2+i][soloY-2+i]==1)
        {
            ++counter[2];
            number[2][0] = soloX-2+i+1;
            number[2][1] = soloY-2+i+1;
        }
        else
        {
            counter[2] = 0;
            number[2][0] = 0;
            number[2][1] = 0;
        }

        if(board[soloX+2-i][soloY-2+i]==1)
        {
            ++counter[3];
            number[3][0] = soloX+2-i-1;
            number[3][1] = soloY-2+i+1;
        }
        else
        {
            counter[3] = 0;
            number[3][0] = 0;
            number[3][1] = 0;
        }

        for(int j=0;j<4;++j)
        {
            if(counter[j]==3 && number[j][0]>=0 && number[j][0]<19 && number[j][1]>=0
               && number[j][1]<19 && board[number[j][0]][number[j][1]] == 0)
            {
                qDebug()<<QString("连3——%1 == 4").arg(j);

                if(j==0 && board[number[j][0]][number[j][1]-4] != 2)
                {
                   if(number[j][1]-5>=0 && board[number[j][0]][number[j][1]-5] != 1)
                   {
                       board[number[j][0]][number[j][1]] = 2;
                       qDebug()<<QString("连3——0 0");
                       step = true;
                       return;
                   }
                   else
                   {
                       board[number[j][0]][number[j][1]-4] = 2;
                       qDebug()<<QString("连3——0 1");
                       step = true;
                       return;
                   }
                }
                else if(j==1 && board[number[j][0]-4][number[j][1]] != 2)
                {
                    if(number[j][0]-5>=0 && board[number[j][0]-5][number[j][1]] != 1)
                    {
                        board[number[j][0]][number[j][1]] = 2;
                        qDebug()<<QString("连3——1 0");
                        step = true;
                        return;
                    }
                    else
                    {
                        board[number[j][0]-4][number[j][1]] = 2;
                        qDebug()<<QString("连3——1 1");
                        step = true;
                        return;
                    }
                }
                else if(j==2 && board[number[j][0]-4][number[j][1]-4] != 2)
                {
                    if(number[j][0]-5>=0 && number[j][1]-5>=0  &&
                            board[number[j][0]-5][number[j][1]-5] != 1)
                    {
                        board[number[j][0]][number[j][1]] = 2;
                        qDebug()<<QString("连3——2 0");
                        step = true;
                        return;
                    }
                    else
                    {
                        board[number[j][0]-4][number[j][1]-4] = 2;
                        qDebug()<<QString("连3——2 1");
                        step = true;
                        return;
                    }
                }
                else if(j==3 && board[number[j][0]-4][number[j][1]+4] != 2 )
                {
                    if(number[j][0]-5>=0 && number[j][1]+5<19&&
                            board[number[j][0]-5][number[j][1]+5] != 1)
                    {
                        board[number[j][0]][number[j][1]] = 2;
                        qDebug()<<QString("连3——3 0");
                        step = true;
                        return;
                    }
                    else
                    {
                        board[number[j][0]-4][number[j][1]+4] = 2;
                        qDebug()<<QString("连3——3 1");
                        step = true;
                        return;
                    }
                }
            }
        }
    }


    qDebug()<<QString("AIcheck3 end");
}

void checkerboard::keyPressEvent(QKeyEvent *event)
{
    if(Qname == "五子棋——双人对战")
    {
        if(((event->key() == Qt::Key_W && doubleLastPlayer == 2) ||
            (event->key() == Qt::Key_I && doubleLastPlayer == 1)) && X > 0)
        {
            X--;
            repaint();
        }
        else if(((event->key() == Qt::Key_S && doubleLastPlayer == 2) ||
                 (event->key() == Qt::Key_K && doubleLastPlayer == 1)) && X < 18)
        {
            X++;
            repaint();
        }
        else if(((event->key() == Qt::Key_A && doubleLastPlayer == 2) ||
                 (event->key() == Qt::Key_J && doubleLastPlayer == 1)) && Y > 0)
        {
            Y--;
            repaint();
        }
        else if(((event->key() == Qt::Key_D && doubleLastPlayer == 2) ||
                 (event->key() == Qt::Key_L && doubleLastPlayer == 1)) && Y < 18)
        {
            Y++;
            repaint();
        }
        else if(event->key() == Qt::Key_F && board[X][Y] == 0 && doubleLastPlayer == 2)
        {
            doubleCounter++;
            board[X][Y] = 1;
            black[X][Y] = doubleCounter;
            doubleLastPlayer = 1;
            doubleLastX = X;
            doubleLastY = Y;
            flag = true;
            repaint();
        }
        else if(event->key() == Qt::Key_H && board[X][Y] == 0 && doubleLastPlayer == 1)
        {
            doubleCounter++;
            board[X][Y] = 2;
            white[X][Y] = doubleCounter;
            doubleLastPlayer = 2;
            doubleLastX = X;
            doubleLastY = Y;
            flag = true;
            repaint();
        }

        win();
    }
}

void checkerboard::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/initial/resources/002.png");
    pix=pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    QString str = "";
    for(int i=0;i<19;i++)
    {
        for(int j=0;j<19;j++)
        {
            str = boardPaint(i,j);

            QImage img(str);
            painter.drawImage(QRect(100+j*img.width(),105+i*img.height(),
                                    img.width(),img.height()),img);

            if(Qname == "五子棋——双人对战")
            {
                QImage ima(":/initial/resources/0.png");
                painter.drawImage(QRect(100+Y*img.width(),105+X*img.height(),
                                        img.width(),img.height()),ima);

                if(flag)
                {
                    QImage imag(":/initial/resources/0.png");
                    painter.drawImage(QRect(100+doubleLastY*img.width(),105+doubleLastX*img.height(),
                                            img.width(),img.height()),imag);
                }
            }
        }
    }

}

QString checkerboard::boardPaint(int i,int j)
{
    if(board[i][j]==0)
    {
        if(i==0 && j==0)
            return (":/initial/resources/board0.png");
        else if(i==0 && j==18)
            return (":/initial/resources/board2.png");
        else if(i==18 && j==18)
            return (":/initial/resources/board4.png");
        else if(i==18 && j==0)
            return (":/initial/resources/board6.png");
        else if(i==0)
            return (":/initial/resources/board1.png");
        else if(j==18)
            return (":/initial/resources/board3.png");
        else if(i==18)
            return (":/initial/resources/board5.png");
        else if(j==0)
            return (":/initial/resources/board7.png");
        else if((i==3&&j==3) || (i==3&&j==9) || (i==3&&j==15)
                ||(i==9&&j==3) ||(i==9&&j==9) ||(i==9&&j==15)
                ||(i==15&&j==3)||(i==15&&j==9)||(i==15&&j==15))
            return (":/initial/resources/01board.png");
        else
            return (":/initial/resources/0board.png");
    }
    else if(board[i][j]==1)
        return (":/initial/resources/black.png");
    else if(board[i][j]==2)
        return (":/initial/resources/white.png");

    return ("");
}

bool checkerboard::ifwin(int number)
{
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;

    for(int i=0;i<19;++i)
    {
        for(int j=0;j<19;++j)
        {
            if(board[i][j]==number)
                counter1++;
            else
                counter1 = 0;

            if(board[j][i]==number)
                counter2++;
            else
                counter2 = 0;

            for(int k=0; k<5; ++k)
            {
                if(i+k<19 && j+k<19 && board[i+k][j+k] == number)
                    counter3++;
                else
                    counter3 = 0;

                if(j-k>=0 && board[i+k][j-k] == number)
                    counter4++;
                else
                    counter4 = 0;
            }

            if(counter1 == 5 || counter2 == 5 || counter3 == 5|| counter4 == 5)
                return true;
        }
    }

    return false;
}

void checkerboard::win()
{
    if(ifwin(1) || ifwin(2))
    {
        QString message;

        if(ifwin(1))
        {
            message="黑方已获胜！";
        }
        else if(ifwin(2))
        {
            message="白方已获胜！";
        }

        setMessageBoxState(message);
    }
}

void checkerboard::setMessageBoxState(QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText(message);

    QPushButton* btn1 = msgBox.addButton("返回",QMessageBox::YesRole);
    connect(btn1,&QPushButton::clicked,this,[=]{
        this->close();
        theLastWindow->show();
    });

    QPushButton* btn2 = msgBox.addButton("再来一局",QMessageBox::NoRole);
    connect(btn2,&QPushButton::clicked,this,[=]{
        for(int i=0; i<19; ++i)
        {
            for(int j=0; j<19; ++j)
            {
                board[i][j] = 0;
                white[i][j]=0;
                black[i][j]=0;
            }
        }

        X = 9;
        Y = 9;
        doubleCounter = 0;
        doubleLastPlayer = 2;
        doubleLastX = 0;
        doubleLastY = 0;
        soloLastPlayer = 2;
        soloX = 0;
        soloY = 0;
        step = false;
        flag = false;


        repaint();
    });

    msgBox.exec();
}

void checkerboard::back()
{
    //int num=0;

    for(int i=18;i>=0;--i)
    {
        for(int j=18;j>=0;--j)
        {
            if(doubleLastPlayer == 1 && black[i][j]==doubleCounter)
            {
                doubleLastPlayer = 2;
                doubleCounter--;

                QPainter painter(this);

                QString str = boardPaint(i,j);
                QImage img(str);
                painter.drawImage(QRect(100+j*img.width(),105+i*img.height(),
                                        img.width(),img.height()),img);

                repaint();

                return;
            }

            if(doubleLastPlayer == 2 && white[i][j]==doubleCounter)
            {
                doubleLastPlayer = 1;
                doubleCounter--;

                QPainter painter(this);

                QString str = boardPaint(i,j);
                QImage img(str);
                painter.drawImage(QRect(100+j*img.width(),105+i*img.height(),
                                        img.width(),img.height()),img);

                repaint();

                return;
            }
        }
    }
}
