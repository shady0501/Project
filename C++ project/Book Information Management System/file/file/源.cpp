/**
 *项目名称:图书管理系统
 *语言:C++
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

//界面初始化函数
void login_init()
{
	system("cls");
	cout << "\n>>>>>>>>>>欢迎进入图书管理系统<<<<<<<<<<" << endl
		<< "请输入您的登录方式" << endl
		<< "1——读者管理	2——图书管理 3——借阅管理 4--退出系统" << endl;
}

int main()                                //主函数
{
	Book xiangnan;
	Student duzhe;
	management mag;
	//若文件不存在，则新建文件
	//存放学生信息
	ofstream Student_Information("Student_Information.txt", ios::app);
	if (!Student_Information)
	{
		cerr << "文件\"flight information.dat\"无法打开!\n";
		exit(1);
	}
	Student_Information.close();

	ofstream Book_Information("Book_Information.txt", ios::app);   //存放图书信息
	if (!Book_Information)
	{
		cerr << "文件\"flight information.dat\"无法打开!\n";
		exit(1);
	}
	Book_Information.close();

	ofstream S_Information("S_Information.dat", ios::app);
	if (!S_Information)
	{
		cerr << "文件\"flight information.dat\"无法打开!\n";
		exit(1);
	}
	S_Information.close();

	int dlry;										//登陆人员
	while (1)
	{
		login_init();							//界面初始化
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
			cout << "输入错误，请重新选择!" << endl;
		}
	}
	return 0;
}