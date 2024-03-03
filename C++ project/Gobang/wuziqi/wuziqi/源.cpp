#include<iostream>
#include<vector>
#include<string>
#include<windows.h>

using namespace std;

//void color(int x)                             //定义棋子颜色 
//{
//    if (x >= 0 & x <= 15)
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
//    else
//    {
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
//    }
//}

void color(int ForgC, int BackC = 0)
{
    if (ForgC >= 0 && ForgC <= 15)
    {
        WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    }
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);   
}

class qipan
{
public:
    int a[15][15];                              //棋盘数组 
    qipan();
    void paint1();
    void play();
    void setRules();
    int AI();                                    //AI 
    int player(int, int, int);                     //玩家 
    int max1(int a1[4]);
    int get1(int a1[4]);
    int s;
    int s1[2];
};

qipan::qipan()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
            a[i][j] = 0;
    }
    s = 0;
    s1[0] = -1;
    s1[1] = -1;
}

int qipan::max1(int a1[4])    //求最大值
{
    int temp = a1[0];
    for (int i = 1; i < 4; i++)
        if (a1[i] > temp)
            temp = a1[i];
    return temp;
}

int qipan::get1(int a1[4])//求出第几项最大
{
    int temp = a1[0];
    int tp1 = 1;
    for (int i = 1; i < 4; i++)
        if (a1[i] > temp)
        {
            temp = a1[i];
            tp1 = i + 1;
        }
    return tp1;
}

void qipan::paint1()//画棋盘
{
    cout << "  ";
    for (int i = 0; i < 15; i++)//画棋盘纵坐标标号      //棋盘上纵坐标   
    {                   
        if (i <= 9)
            cout << " " << i;                          //数字小于9时先空格再出现数字 
        else
            cout << i << "";                           //数字大于9时不空格出现数字 
    }
    cout << endl;

    for (int i = 0; i < 15; i++)
    {
        if (i <= 9)                //画棋盘横坐标标号     
            cout << i << "  ";
        else
            cout << i << " ";

        for (int j = 0; j < 15; j++)
        {
            if (a[i][j] == 0)
            {
                color(7);
                cout << "x" << " ";            //对于数组中每个量输出x，优化棋盘外观 
            }
            else if (a[i][j] == 1)//1为红方
            {
                color(7,12);         //显示红色棋子
                cout << "红";
            }
            else if (a[i][j] == 2)//2为蓝方（AI）
            {
                color(7,1);         //显示蓝色棋子
                cout << "蓝";
            }
        }
        cout << endl;
    }
}
int qipan::player(int x1, int y1, int z)         //玩家下棋 
{
    if (x1 > 14 || y1 > 14 || a[x1][y1] != 0)//无效落子
    {
        cout << "落子无效";
        return 1;
    }
    a[x1][y1] = z;                        //z为1，即红方（玩家）

    int total = 0;//遍历落子横行是否满足5个棋子
    for (int i = y1 - 1; i >= 0; i--)// (x1,i)位置有红方棋子
    {
        if (a[x1][i] == z)               
            total++;
        else
            break;
    }
    for (int i = y1 + 1; i < 15; i++)// (x1,i)位置有红方棋子
    {
        if (a[x1][i] == z)
            total++;
        else
            break;
    }
    if (total >= 4)//判断是否获胜
        return 5;                                    //获胜

    total = 0;//遍历落子竖行是否满足5个棋子
    for (int i = x1 - 1; i >= 0; i--) {
        if (a[i][y1] == z)
            total++;
        else
            break;
    }
    for (int i = x1 + 1; i < 15; i++)
    {
        if (a[i][y1] == z)
            total++;
        else
            break;
    }
    if (total >= 4)
        return 5;                                      //获胜

    total = 0;//遍历落子左上到右下的斜行是否满足5个棋子
    for (int i = 1; i < 5; i++)
    {
        if (x1 - i < 0 || y1 - i < 0)
            break;
        if (a[x1 - i][y1 - i] == z)
            total++;
        else
            break;
    }
    for (int i = 1; i < 5; i++) {
        if (x1 + i >= 15 || y1 + i >= 15)
            break;
        if (a[x1 + i][y1 + i] == z)
            total++;
        else
            break;
    }
    if (total >= 4)
        return 5;                                      //获胜

    total = 0;//遍历落子左下到右上的斜行是否满足5个棋子
    for (int i = 1; i < 5; i++)
    {
        if (x1 - i < 0 || y1 + i >= 15)
            break;
        if (a[x1 - i][y1 + i] == z)
            total++;
        else
            break;
    }
    for (int i = 1; i < 5; i++)
    {
        if (x1 + i >= 15 || y1 - i < 0)
            break;
        if (a[x1 + i][y1 - i] == z)
            total++;
        else
            break;
    }
    if (total >= 4)
        return 5;                                    //获胜

    return 2;                                    //落子有效，但未获胜
}
int qipan::AI()
{
    //211--305判断AI是否获胜
    for (int i = 0; i < 15; i++)//遍历每一行
    {
        for (int j = 0; j < 15; j++)//遍历每一列
        {
            int total1 = 0;
            int total2 = 0;
            int total3 = 0;
            int total4 = 0;

            if (a[i][j] != 0)//若（i，j)位置已有棋子，直接继续下一循环，判断下一位置
                continue;

            for (int a1 = 1; a1 < 5; a1++)                     //判断水平线
            {
                if (j - a1 < 0)
                    break;
                if (a[i][j - a1] == 2)
                    total1++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (j + a1 >= 14)
                    break;
                if (a[i][j + a1] == 2)
                    total1++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)                        //判断竖直部分
            {
                if (i - a1 < 0)
                    break;
                if (a[i - a1][j] == 2)
                    total2++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15)
                    break;
                if (a[i + a1][j] == 2)
                    total2++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)                         //判断左斜线
            {
                if (i - a1 < 0 || j - a1 < 0)
                    break;
                if (a[i - a1][i - a1] == 2)
                    total3++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15 || j + a1 >= 15)
                    break;
                if (a[i + a1][j + a1] == 2)

                    total3++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)                          //判断右斜线
            {
                if (i - a1 < 0 || j + a1 >= 15)
                    break;
                if (a[i - a1][j + a1] == 2)
                    total4++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15 || j - a1 < 0)
                    break;
                if (a[i + a1][j - a1] == 2)
                    total4++;
                else
                    break;
            }

            int a1[4] = { total1,total2,total3,total4 };
            int temp = max1(a1);
            if (temp >= 4) {
                a[i][j] = 2;
                // cout<<"Al已获胜";
                return -1;
            }
        }
    }

    for (int i = 0; i < 15; i++)                         //判断对手是否有大于三子的情况
    {
        for (int j = 0; j < 15; j++)
        {
            int total1 = 0;//红方横行棋子总数
            int total2 = 0;//    纵行
            int total3 = 0;//
            int total4 = 0;//

            if (a[i][j] == 1 || a[i][j] == 2)//如果(i,j)位置有棋子直接下一次循环
                continue;

            for (int a1 = 1; a1 < 5; a1++)//判断红方横行棋子数
            {
                if (j - a1 < 0)
                    break;
                if (a[i][j - a1] == 1)
                    total1++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (j + a1 >= 15)
                    break;
                if (a[i][j + a1] == 1)
                    total1++;
                else
                    break;
            }

            for (int a1 = 1; a1 < 5; a1++)//判断红方纵行棋子数
            {
                if (i - a1 < 0)
                    break;
                if (a[i - a1][j] == 1)
                    total2++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15)
                    break;
                if (a[i + a1][j] == 1)
                    total2++;
                else
                    break;
            }

            for (int a1 = 1; a1 < 5; a1++)//判断红方左上至右下斜线棋子数
            {
                if (i - a1 < 0 || j - a1 < 0)
                    break;
                if (a[i - a1][j - a1] == 1)
                    total3++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15 || j + a1 >= 15)
                    break;
                if (a[i + a1][j + a1] == 1)
                    total3++;
                else
                    break;
            }

            for (int a1 = 1; a1 < 5; a1++)//判断红方左下至右上斜线棋子数
            {
                if (i - a1 < 0 || j + a1 >= 15)
                    break;
                if (a[i - a1][j + a1] == 1)
                    total4++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15 || j - a1 < 0)
                    break;
                if (a[i + a1][j - a1] == 1)
                    total4++;
                else
                    break;
            }

            int a1[4] = { total1,total2,total3,total4 };
            int temp = max1(a1);
            int tp1 = get1(a1);//找哪条线红方棋子最多

            if (temp == 3)//最多的一条线上有三个棋子时
            {
                if (tp1 == 1)//横线上红方棋子最多
                {
                    int a1;
                    int tpx1 = 0;

                    for (a1 = 1; a1 <= 3; a1++)
                    {
                        // tpx1=0;
                        if (j - a1 < 0)//j <= 3时
                            break;
                        if (a[i][j - a1] == 1)//判断(i,j)位置同一行左侧有几个红方棋子
                            tpx1++;           //a1为(i,j)左侧的红方棋子数目
                        else
                            break;
                    }
                    if (tpx1 == 3)//3个红方棋子全在(i,j)左侧且 a1 = 3
                    {
                        if (j - a1 == 0)
                        {
                        }
                        else if (j - a1 - 1 >= 0)
                        {
                            if (a[i][j - a1 - 1] == 0)//三个红方棋子左侧无子
                            {
                                a[i][j] = 2;//AI在三个红方棋子右侧堵人
                                return 0;
                            }
                        }
                    }
                    else if (tpx1 == 2)//2个红方棋子在(i,j)左侧
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 1)//1个红方棋子在(i,j)左侧
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 0)//无红方棋子在(i,j)左侧
                    {
                        if (j + a1 == 14)//a1=0，j=14
                        {
                        }
                        else if (j + a1 < 14)//a1 = 0, j < 14
                        {
                            if (a[i][j + a1 + 1] == 0)//这是在干啥？
                            {
                                a[i][j] = 2;
                                cout << "i=" << i << "j=" << j << endl;
                                return 0;
                            }
                        }
                    }
                }
                else if (tp1 == 2)//竖线上红方棋子最多
                {
                    int a1;
                    int tpx1 = 0;
                    for (a1 = 1; a1 <= 3; a1++)
                    {
                        // tpx1=0;
                        if (i - a1 < 0)
                            break;
                        if (a[i - a1][j] == 1)
                            tpx1++;
                        else
                            break;
                    }
                    if (tpx1 == 3)
                    {
                        if (i - a1 == 0)
                        {
                        }
                        else if (i - a1 - 1 >= 0)
                        {
                            if (a[i - a1 - 1][j] == 0)
                            {
                                a[i][j] = 2;
                                return 0;
                            }
                        }
                    }
                    else if (tpx1 == 2)
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 1)
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 0)
                    {
                        if (i + a1 == 14)
                        {
                        }
                        else if (i + a1 < 14)
                        {
                            if (a[i + a1 + 1][j] == 0)
                            {
                                a[i][j] = 2;
                                cout << "i=" << i << "j=" << j << endl;
                                return 0;
                            }
                        }
                    }
                }
                else if (tp1 == 3)//斜线上红方棋子最多
                {
                    int a1;
                    int tpx1 = 0;
                    for (a1 = 1; a1 <= 3; a1++)
                    {
                        // tpx1=0;
                        if (i - a1 < 0 || j - a1 < 0)
                            break;
                        if (a[i - a1][j - a1] == 1)
                            tpx1++;
                        else
                            break;
                    }
                    if (tpx1 == 3)
                    {
                        if (i - a1 == 0 || j - a1 == 0)
                        {
                        }
                        else if (i - a1 - 1 >= 0 and j - a1 - 1 >= 0)
                        {
                            if (a[i - a1 - 1][j - a1 - 1] == 0)
                            {
                                a[i][j] = 2;
                                return 0;
                            }
                        }
                    }
                    else if (tpx1 == 2)
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 1)
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 0)
                    {
                        if (i + a1 == 14 || j + a1 == 14)
                        {
                        }
                        else if (i + a1 < 14 and j + a1 < 14)
                        {
                            if (a[i + a1 + 1][j + a1 + 1] == 0)
                            {
                                a[i][j] = 2;
                                cout << "i=" << i << "j=" << j << endl;
                                return 0;
                            }
                        }
                    }
                }
                else if (tp1 == 4)//斜线上红方棋子最多
                {
                    int a1;
                    int tpx1 = 0;
                    for (a1 = 1; a1 <= 3; a1++)
                    {
                        // tpx1=0;
                        if (i - a1 < 0 || j + a1 > 14)
                            break;
                        if (a[i - a1][j + a1] == 1)
                            tpx1++;
                        else
                            break;
                    }
                    if (tpx1 == 3)
                    {
                        if (i - a1 == 0 || j + a1 == 14)
                        {
                        }
                        else if (i - a1 - 1 >= 0 and j + a1 + 1 <= 14)
                        {
                            if (a[i - a1 - 1][j + a1 + 1] == 0)
                            {
                                a[i][j] = 2;
                                return 0;
                            }
                        }
                    }
                    else if (tpx1 == 2)
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 1)
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 0)
                    {
                        if (i + a1 == 14 || j - a1 == 0)
                        {
                        }
                        else if (i + a1 < 14 && j - a1 > 0)
                        {
                            if (a[i + a1 + 1][j - a1 - 1] == 0)
                            {
                                a[i][j] = 2;
                                return 0;
                            }
                        }
                    }
                }
            }
            else if (temp == 4 || temp == 5)
            {
                a[i][j] = 2;
                return 0;
            }
        }
    }

    //红方棋子无威胁时
    int t1 = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)//遍历棋盘
        {
            if (a[i][j] == 2)
                t1++;
        }
    }
    if (t1 == 0)
    {
        a[7][7] = 2;//AI第一步下在（7，7）位置
        return 0;
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)//遍历棋盘
        {
            int total1 = 0;
            int total2 = 0;
            int total3 = 0;
            int total4 = 0;

            if (a[i][j] != 0)
                continue;

            for (int a1 = 1; a1 < 5; a1++)
            {
                if (j - a1 < 0)
                    break;
                if (a[i][j - a1] == 2)
                    total1++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (j + a1 >= 15)
                    break;
                if (a[i][j + a1] == 2)
                    total1++;
                else
                    break;
            }

            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i - a1 < 0)
                    break;
                if (a[i - a1][j] == 2)
                    total2++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15)
                    break;
                if (a[i + a1][j] == 2)
                    total2++;
                else
                    break;
            }

            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i - a1 < 0 || j - a1 < 0)
                    break;
                if (a[i - a1][j - a1] == 2)
                    total3++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15 || j + a1 >= 15)
                    break;
                if (a[i + a1][j + a1] == 2)
                    total3++;
                else
                    break;
            }

            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i - a1 < 0 || j + a1 >= 15)
                    break;
                if (a[i - a1][j + a1] == 2)
                    total4++;
                else
                    break;
            }
            for (int a1 = 1; a1 < 5; a1++)
            {
                if (i + a1 >= 15 || j - a1 < 0)
                    break;
                if (a[i + a1][j - a1] == 2)
                    total4++;
                else
                    break;
            }

            int a1[4] = { total1,total2,total3,total4 };
            int temp = max1(a1);
            if (temp >= 4)
            {
                a[i][j] = 2;
                //cout<<"Al已获胜";
                return -1;
            }
            if (temp > s)//此时s = 0
            {
                s = temp;
                s1[0] = i;
                s1[1] = j;
            }
        }
    }
    s = 0;                   //初始化
    a[s1[0]][s1[1]] = 2;
    s1[0] = -1;
    s1[1] = -1;

    return 0;
}
void qipan::play()
{ 
    while (1)      //死循环
    {
        int x1, y1;
        int temp = AI();
        paint1();
        cout << endl;

        if (temp == -1)                          //判断AI是否获胜
        {
            cout << "Al已获胜";
            Sleep(2000);
            return;
        }

        cout << "Al已经落子" << endl;
        cout << "请红方落子" << endl;

        cin >> x1 >> y1;                          //红方（玩家）落子
        temp = player(x1, y1, 1);
        cout << endl;

        if (temp == 1)                           //判断红方（玩家）落子是否有效
        {
            while (temp == 1) 
            {
                paint1();
                cout << "红方落子无效，请重新落子";
                cin >> x1 >> y1;
                temp = player(x1, y1, 1);
                cout << endl;
            }
        }

        if (temp == 5)                           //判断红方（玩家）是否获胜
        {
            paint1();
            cout << "恭喜红方获胜" << endl;
            Sleep(2000);
            return;
        }

        paint1();                          //均未获胜，绘制现在棋盘
        cout << endl;
    }
}

int main()
{
    //qipan a;
    //a.setRules();
    //a.paint1();
    //a.play();
    cout << 5 / 2;
}

void qipan::setRules()
{
    color(4,15);
    cout << "请在5秒内读完如下规则：" << endl;
    cout << "    1.玩家为红方，AI为蓝方" << endl;
    cout << "    2.输入行数、列数从而指定位置红方下棋" << endl;
    cout << endl;
    Sleep(5000);
    color(7, 0);
}