#pragma once
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

class Book                                                       //构建图书类类
{
	friend istream& operator>>(istream& in, Book& cp);		//提取运算符重载
	friend ostream& operator<<(ostream& out, Book& cp);		//插入运算符重载

public:
	bool Personnel_System();									//登录

	void B_Read_file();											//读取图书文件
	void B_Save_file();											//保存图书文件

	void B_clear();												//清理已有图书信息
	bool Book_add();											//添加图书信息
	bool Book_mod();											//修改图书信息
	bool Book_del();											//删除图书信息

	bool B_SetInto();										//设置图书信息
	bool B_If_match(char p[30]);
	void b_display();										//图书信息显示
	bool Book_search();
	void Deletenum();

	char b_num[15];					//编号
	char b_name[30];				//书名
	char author[20];				//作者
	char ISBN[30];				//ISBN
	int b_quantity;					//图书数量
	int b_sum = 0;											//图书数
	string key;													//管理员密码
	vector<Book> b_array;										//记录图书类
};
