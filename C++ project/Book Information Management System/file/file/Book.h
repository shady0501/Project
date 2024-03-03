#pragma once
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

class Book                                                       //����ͼ������
{
	friend istream& operator>>(istream& in, Book& cp);		//��ȡ���������
	friend ostream& operator<<(ostream& out, Book& cp);		//�������������

public:
	bool Personnel_System();									//��¼

	void B_Read_file();											//��ȡͼ���ļ�
	void B_Save_file();											//����ͼ���ļ�

	void B_clear();												//��������ͼ����Ϣ
	bool Book_add();											//���ͼ����Ϣ
	bool Book_mod();											//�޸�ͼ����Ϣ
	bool Book_del();											//ɾ��ͼ����Ϣ

	bool B_SetInto();										//����ͼ����Ϣ
	bool B_If_match(char p[30]);
	void b_display();										//ͼ����Ϣ��ʾ
	bool Book_search();
	void Deletenum();

	char b_num[15];					//���
	char b_name[30];				//����
	char author[20];				//����
	char ISBN[30];				//ISBN
	int b_quantity;					//ͼ������
	int b_sum = 0;											//ͼ����
	string key;													//����Ա����
	vector<Book> b_array;										//��¼ͼ����
};
