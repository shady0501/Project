/**
 *��Ŀ����:ͼ�����ϵͳ
 *����:C++
 **/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include"Book.h"
#include"Management.h"
#include"Student.h"

using namespace std;

//�����ʼ������
void login_init()
{
	system("cls");
	cout << "\n>>>>>>>>>>��ӭ����ͼ�����ϵͳ<<<<<<<<<<" << endl
		<< "���������ĵ�¼��ʽ" << endl
		<< "1�������߹���	2����ͼ����� 3�������Ĺ��� 4--�˳�ϵͳ" << endl;
}

int main()                                //������
{
	Book xiangnan;
	Student duzhe;
	management mag;
	//���ļ������ڣ����½��ļ�
	//���ѧ����Ϣ
	ofstream Student_Information("Student_Information.txt", ios::app);
	if (!Student_Information)
	{
		cerr << "�ļ�\"flight information.dat\"�޷���!\n";
		exit(1);
	}
	Student_Information.close();

	ofstream Book_Information("Book_Information.txt", ios::app);   //���ͼ����Ϣ
	if (!Book_Information)
	{
		cerr << "�ļ�\"flight information.dat\"�޷���!\n";
		exit(1);
	}
	Book_Information.close();

	ofstream S_Information("S_Information.dat", ios::app);
	if (!S_Information)
	{
		cerr << "�ļ�\"flight information.dat\"�޷���!\n";
		exit(1);
	}
	S_Information.close();

	int dlry;										//��½��Ա
	while (1)
	{
		login_init();							//�����ʼ��
		cin >> dlry;
		if (dlry == 1)
		{
			duzhe.Personnel_System();
		}
		else if (dlry == 2)
		{

			xiangnan.Personnel_System();

		}
		else if (dlry == 3)
		{

			mag.Student_System();

		}
		else if (dlry == 4)
		{
			return 0;
		}
		else
		{
			cout << "�������������ѡ��!" << endl;
		}
	}
	return 0;
}