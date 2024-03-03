#pragma once
//构建读者类
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

class Student
{
	friend istream& operator>>(istream& in, Student& cp);		//提取运算符重载
	friend ostream& operator<<(ostream& out, Student& cp);		//插入运算符重载

public:
	Student()
	{
		memset(s_num, 0, sizeof(s_num));
		memset(s_name, 0, sizeof(s_name));
		memset(tell, 0, sizeof(tell, 0, sizeof(tell)));
		borrow_max = 0;
		borrow_quantity = 0;
		memset(borrow_books, 0, sizeof(borrow_books));
	}

	bool Personnel_System();									//工作人员登录
	bool Student_System();										//学生登录

	void S_Read_file();											//读取学生文件
	void S_Save_file();											//保存学生文件

	bool Student_add();											//添加学生信息
	bool Student_mod();											//修改学生信息
	bool Student_del();											//删除学生信息
	bool Student_search();
	void S_clear();												//清理已有学生信息

	bool S_SetInto();											//设置学生信息
	bool S_If_match(char p[30]);								//判断学号是否匹配
	void s_display();											//显示学生信息

	void Deletenum();

	int s_sum = 0;												//学生数
	string key;													//管理员密码
	vector<Student> s_array;									//记录学生类

	char s_num[15];						//读者编号
	char s_name[10];					//姓名
	char tell[30];					//电话号码 
	int borrow_max;						//最大借阅数量
	int borrow_quantity;				//借阅数量
	char borrow_books[10][30];			//借阅图书

private:

};