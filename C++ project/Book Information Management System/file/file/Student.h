#pragma once
//����������
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

class Student
{
	friend istream& operator>>(istream& in, Student& cp);		//��ȡ���������
	friend ostream& operator<<(ostream& out, Student& cp);		//�������������

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

	bool Personnel_System();									//������Ա��¼
	bool Student_System();										//ѧ����¼

	void S_Read_file();											//��ȡѧ���ļ�
	void S_Save_file();											//����ѧ���ļ�

	bool Student_add();											//���ѧ����Ϣ
	bool Student_mod();											//�޸�ѧ����Ϣ
	bool Student_del();											//ɾ��ѧ����Ϣ
	bool Student_search();
	void S_clear();												//��������ѧ����Ϣ

	bool S_SetInto();											//����ѧ����Ϣ
	bool S_If_match(char p[30]);								//�ж�ѧ���Ƿ�ƥ��
	void s_display();											//��ʾѧ����Ϣ

	void Deletenum();

	int s_sum = 0;												//ѧ����
	string key;													//����Ա����
	vector<Student> s_array;									//��¼ѧ����

	char s_num[15];						//���߱��
	char s_name[10];					//����
	char tell[30];					//�绰���� 
	int borrow_max;						//����������
	int borrow_quantity;				//��������
	char borrow_books[10][30];			//����ͼ��

private:

};