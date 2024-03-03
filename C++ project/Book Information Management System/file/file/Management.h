#pragma once
#include<iostream>
#include<fstream>
#include"Book.h"
#include"Student.h"

using namespace std;

class management :public Student, public Book
{
	friend istream& operator>>(istream& in, management& cp);
	friend ostream& operator<<(ostream& out, management& cp);

public:
	bool Student_System();

	void c_Read_file();
	void c_Save_file();

	bool s_login(Student& cp);
	bool c_SetInto();
	bool c_add();
	bool c_If_match(char p[30]);
	void c_display();
	bool c_search();

	bool borrow_book(Student& cp);
	bool return_book(Student& cp);
	bool reduce_book(Student& cp);

	string key;
	int a;//��ǽ��Ϊ0����Ϊ1 
	int c_sum = 0;
	char book[30];//�鼮��� 
	char stu[30];//ѧ����� 
	char da[30];//���� 

	vector<management> c_array;//��Ϣ�� 
};