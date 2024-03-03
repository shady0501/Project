#include<iostream>
#include<vector>
#include<string>
#include<windows.h>

using namespace std;

//void color(int x)                             //����������ɫ 
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
    int a[15][15];                              //�������� 
    qipan();
    void paint1();
    void play();
    void setRules();
    int AI();                                    //AI 
    int player(int, int, int);                     //��� 
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

int qipan::max1(int a1[4])    //�����ֵ
{
    int temp = a1[0];
    for (int i = 1; i < 4; i++)
        if (a1[i] > temp)
            temp = a1[i];
    return temp;
}

int qipan::get1(int a1[4])//����ڼ������
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

void qipan::paint1()//������
{
    cout << "  ";
    for (int i = 0; i < 15; i++)//��������������      //������������   
    {                   
        if (i <= 9)
            cout << " " << i;                          //����С��9ʱ�ȿո��ٳ������� 
        else
            cout << i << "";                           //���ִ���9ʱ���ո�������� 
    }
    cout << endl;

    for (int i = 0; i < 15; i++)
    {
        if (i <= 9)                //�����̺�������     
            cout << i << "  ";
        else
            cout << i << " ";

        for (int j = 0; j < 15; j++)
        {
            if (a[i][j] == 0)
            {
                color(7);
                cout << "x" << " ";            //����������ÿ�������x���Ż�������� 
            }
            else if (a[i][j] == 1)//1Ϊ�췽
            {
                color(7,12);         //��ʾ��ɫ����
                cout << "��";
            }
            else if (a[i][j] == 2)//2Ϊ������AI��
            {
                color(7,1);         //��ʾ��ɫ����
                cout << "��";
            }
        }
        cout << endl;
    }
}
int qipan::player(int x1, int y1, int z)         //������� 
{
    if (x1 > 14 || y1 > 14 || a[x1][y1] != 0)//��Ч����
    {
        cout << "������Ч";
        return 1;
    }
    a[x1][y1] = z;                        //zΪ1�����췽����ң�

    int total = 0;//�������Ӻ����Ƿ�����5������
    for (int i = y1 - 1; i >= 0; i--)// (x1,i)λ���к췽����
    {
        if (a[x1][i] == z)               
            total++;
        else
            break;
    }
    for (int i = y1 + 1; i < 15; i++)// (x1,i)λ���к췽����
    {
        if (a[x1][i] == z)
            total++;
        else
            break;
    }
    if (total >= 4)//�ж��Ƿ��ʤ
        return 5;                                    //��ʤ

    total = 0;//�������������Ƿ�����5������
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
        return 5;                                      //��ʤ

    total = 0;//�����������ϵ����µ�б���Ƿ�����5������
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
        return 5;                                      //��ʤ

    total = 0;//�����������µ����ϵ�б���Ƿ�����5������
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
        return 5;                                    //��ʤ

    return 2;                                    //������Ч����δ��ʤ
}
int qipan::AI()
{
    //211--305�ж�AI�Ƿ��ʤ
    for (int i = 0; i < 15; i++)//����ÿһ��
    {
        for (int j = 0; j < 15; j++)//����ÿһ��
        {
            int total1 = 0;
            int total2 = 0;
            int total3 = 0;
            int total4 = 0;

            if (a[i][j] != 0)//����i��j)λ���������ӣ�ֱ�Ӽ�����һѭ�����ж���һλ��
                continue;

            for (int a1 = 1; a1 < 5; a1++)                     //�ж�ˮƽ��
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
            for (int a1 = 1; a1 < 5; a1++)                        //�ж���ֱ����
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
            for (int a1 = 1; a1 < 5; a1++)                         //�ж���б��
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
            for (int a1 = 1; a1 < 5; a1++)                          //�ж���б��
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
                // cout<<"Al�ѻ�ʤ";
                return -1;
            }
        }
    }

    for (int i = 0; i < 15; i++)                         //�ж϶����Ƿ��д������ӵ����
    {
        for (int j = 0; j < 15; j++)
        {
            int total1 = 0;//�췽������������
            int total2 = 0;//    ����
            int total3 = 0;//
            int total4 = 0;//

            if (a[i][j] == 1 || a[i][j] == 2)//���(i,j)λ��������ֱ����һ��ѭ��
                continue;

            for (int a1 = 1; a1 < 5; a1++)//�жϺ췽����������
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

            for (int a1 = 1; a1 < 5; a1++)//�жϺ췽����������
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

            for (int a1 = 1; a1 < 5; a1++)//�жϺ췽����������б��������
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

            for (int a1 = 1; a1 < 5; a1++)//�жϺ췽����������б��������
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
            int tp1 = get1(a1);//�������ߺ췽�������

            if (temp == 3)//����һ����������������ʱ
            {
                if (tp1 == 1)//�����Ϻ췽�������
                {
                    int a1;
                    int tpx1 = 0;

                    for (a1 = 1; a1 <= 3; a1++)
                    {
                        // tpx1=0;
                        if (j - a1 < 0)//j <= 3ʱ
                            break;
                        if (a[i][j - a1] == 1)//�ж�(i,j)λ��ͬһ������м����췽����
                            tpx1++;           //a1Ϊ(i,j)���ĺ췽������Ŀ
                        else
                            break;
                    }
                    if (tpx1 == 3)//3���췽����ȫ��(i,j)����� a1 = 3
                    {
                        if (j - a1 == 0)
                        {
                        }
                        else if (j - a1 - 1 >= 0)
                        {
                            if (a[i][j - a1 - 1] == 0)//�����췽�����������
                            {
                                a[i][j] = 2;//AI�������췽�����Ҳ����
                                return 0;
                            }
                        }
                    }
                    else if (tpx1 == 2)//2���췽������(i,j)���
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 1)//1���췽������(i,j)���
                    {
                        a[i][j] = 2;
                        return 0;
                    }
                    else if (tpx1 == 0)//�޺췽������(i,j)���
                    {
                        if (j + a1 == 14)//a1=0��j=14
                        {
                        }
                        else if (j + a1 < 14)//a1 = 0, j < 14
                        {
                            if (a[i][j + a1 + 1] == 0)//�����ڸ�ɶ��
                            {
                                a[i][j] = 2;
                                cout << "i=" << i << "j=" << j << endl;
                                return 0;
                            }
                        }
                    }
                }
                else if (tp1 == 2)//�����Ϻ췽�������
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
                else if (tp1 == 3)//б���Ϻ췽�������
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
                else if (tp1 == 4)//б���Ϻ췽�������
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

    //�췽��������вʱ
    int t1 = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)//��������
        {
            if (a[i][j] == 2)
                t1++;
        }
    }
    if (t1 == 0)
    {
        a[7][7] = 2;//AI��һ�����ڣ�7��7��λ��
        return 0;
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)//��������
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
                //cout<<"Al�ѻ�ʤ";
                return -1;
            }
            if (temp > s)//��ʱs = 0
            {
                s = temp;
                s1[0] = i;
                s1[1] = j;
            }
        }
    }
    s = 0;                   //��ʼ��
    a[s1[0]][s1[1]] = 2;
    s1[0] = -1;
    s1[1] = -1;

    return 0;
}
void qipan::play()
{ 
    while (1)      //��ѭ��
    {
        int x1, y1;
        int temp = AI();
        paint1();
        cout << endl;

        if (temp == -1)                          //�ж�AI�Ƿ��ʤ
        {
            cout << "Al�ѻ�ʤ";
            Sleep(2000);
            return;
        }

        cout << "Al�Ѿ�����" << endl;
        cout << "��췽����" << endl;

        cin >> x1 >> y1;                          //�췽����ң�����
        temp = player(x1, y1, 1);
        cout << endl;

        if (temp == 1)                           //�жϺ췽����ң������Ƿ���Ч
        {
            while (temp == 1) 
            {
                paint1();
                cout << "�췽������Ч������������";
                cin >> x1 >> y1;
                temp = player(x1, y1, 1);
                cout << endl;
            }
        }

        if (temp == 5)                           //�жϺ췽����ң��Ƿ��ʤ
        {
            paint1();
            cout << "��ϲ�췽��ʤ" << endl;
            Sleep(2000);
            return;
        }

        paint1();                          //��δ��ʤ��������������
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
    cout << "����5���ڶ������¹���" << endl;
    cout << "    1.���Ϊ�췽��AIΪ����" << endl;
    cout << "    2.���������������Ӷ�ָ��λ�ú췽����" << endl;
    cout << endl;
    Sleep(5000);
    color(7, 0);
}