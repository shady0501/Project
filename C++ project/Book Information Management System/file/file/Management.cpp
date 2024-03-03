#include<iostream>
#include<iomanip>
#include<fstream>
#include"Management.h"

istream& operator>>(istream& in, management& cp)
{
	in >> cp.book >> cp.stu >> cp.da >> cp.a;
	return in;
}

//�������������
ostream& operator<<(ostream& out, management& cp)
{
	out << cp.book << ' ' << cp.stu << ' ' << cp.da << ' ' << cp.a << '\n';
	return out;
}

//ѧ����¼
bool management::Student_System()
{
	while (1)
	{
		Student cp;
		bool key = s_login(cp);

		while (key)
		{
			int menu_options;

			cout << "*****	 ���˵�:								             **********" << endl
				<< "*****	 ѧ��:							" << endl
				<< "*****	 1��������ͼ��" << endl
				<< "*****	 2�����黹ͼ��" << endl
				<< "*****	 3������ѧ�Ų�ѯ�鼮��Ϣ" << endl
				<< "*****    4������ͼ��" << endl
				<< "*****    5�����˳���¼" << endl
				<< "����Ҫ��ʲô?��ѡ��1-5��" << endl;
			cin >> menu_options;
			switch (menu_options)
			{
			case 1:borrow_book(cp); break;
			case 2:return_book(cp); break;
			case 3:c_search(); break;
			case 4:reduce_book(cp); break;
			case 5:return false;
			}
			if (menu_options == 1 || menu_options == 2)
			{
				cout << "�Ƿ�ȷ�ϣ�        ��ȷ��/(Y/y)��    ��ȡ��/(N/n)��" << endl;
				char yn;
				do
				{
					cin >> yn;
				} while (!(yn == 'Y' || yn == 'y' || yn == 'N' || yn == 'n'));
				if (yn == 'Y' || yn == 'y')
				{
					cout << "�����ɹ���" << endl;
					S_Save_file();
					B_Save_file();
				}
			}
			S_clear();
			B_clear();
		}
		cout << "δ�ҵ�������Ϣ��" << endl;
	}
	return true;
}

//��ȡͼ���ļ�
void management::c_Read_file()
{
	ifstream c_file;
	c_file.open("S_Information.txt");
	if (!c_file.is_open())
	{
		cerr << "�ļ�\"S_Information.txt\"�޷���\n";
		exit(1);
	}
	while (!c_file.eof())
	{
		management _book;
		c_file >> _book;
		c_array.push_back(_book);
		c_sum++;
	};
	c_sum--;
	c_file.close();
}

//����ͼ���ļ�
void management::c_Save_file()
{
	ofstream c_file("S_Information.txt");
	if (!c_file)
	{
		cerr << "�ļ�\"S_Information.txt\"�޷���!\n";
		exit(1);
	}
	int i = -1;
	while (++i < c_sum)
	{
		c_file << c_array[i];
	}
	c_file.close();
}

//ѧ��ƾѧ�ŵ�¼
bool management::s_login(Student& cp)
{
	char _s_num[15];
	S_Read_file();
	cout << "����������ѧ��:";
	cin >> _s_num;
	for (int i = 0; i < s_sum; i++)
	{
		if (s_array[i].S_If_match(_s_num))
		{
			cp = s_array[i];
			cout << "��ӭ��," << cp.s_name << "ͬѧ��" << endl;
			S_clear();
			return true;
		}
	}
	S_clear();
	return false;
}

//����ͼ����Ϣ
bool management::c_SetInto()
{
	char temp[15];
	cout << "�������鼮���:(����+�˳�)";
	cin >> temp;
	if (temp[0] == '+')
		return false;
	strcpy(book, temp);
	cout << "���߱��:";
	cin >> stu;
	cout << "����:";
	cin >> da;
	cout << "0��1��";
	cin >> a;

	return true;
}

bool management::c_add()
{
	c_Read_file();
	management _book;
	cout << "�������Ϣ¼�롣����+������!\n";
	do
	{
		c_array.push_back(_book);
	} while (c_array[c_sum++].c_SetInto());
	c_sum--;
	c_array.pop_back();
	return true;
}

bool management::c_If_match(char p[30])         //�ж�ͼ����Ƿ�ƥ��
{
	return (!strcmp(book, p));
}

void management::c_display()                  //��ʾ����
{
	cout << setiosflags(ios::left) << setw(12) << book << "    " << setw(30) << stu << "    " << setw(10) << da << endl
		<< setw(20) << a << endl;
}

bool management::c_search()                   //��ѯ������Ϣ
{
	char _s_num[15];
	c_Read_file();
	cout << "��������Ҫ����鼮���:";
	cin >> _s_num;
	int i = 0;
	for (; i < c_sum; i++)
	{
		if (c_array[i].c_If_match(_s_num))
		{
			cout << "���ļ�¼:\n";
			c_array[i].c_display();
			return true;
		}
		if (i == c_sum)
		{
			cout << "��Ǹ!��Ҫ�޸ĵ���Ϣ������! " << endl;
			return false;
		}
		break;
	}
	c_Save_file();
}

bool management::borrow_book(Student& cp)                //����
{
	S_Read_file();
	B_Read_file();
	c_Read_file();
	char _b_num[30];
	cout << "���������ͼ���ͼ��Ż�����:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "��ͼ�����ϢΪ:\n";
			b_array[i].b_display();
			b_array[i].b_quantity--;

			c_add();
			c_Save_file();
			if (cp.borrow_quantity > cp.borrow_max - 1)
			{
				cout << "��Ǹ�����Ѵ����������ޣ�" << endl;
				return false;
			}
			strcpy(cp.borrow_books[cp.borrow_quantity++], b_array[i].b_name);
			for (int j = 0; j < s_sum; j++)
			{
				if (s_array[j].S_If_match(cp.s_num))
				{
					s_array[j] = cp;
					return true;
				}
			}
		}
		if (i == b_sum - 1)
		{
			cout << "��Ǹ!������ͼ��δ��¼! " << endl;
			return false;
		}
	}

}

bool management::return_book(Student& cp)            //����
{
	S_Read_file();
	B_Read_file();
	char _b_num[30];
	cout << "�������뻹ͼ���ͼ��Ż�����:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "��ͼ�����ϢΪ:\n";
			b_array[i].b_display();
			b_array[i].b_quantity++;

			c_add();

			c_Save_file();

			for (int k = 0; k < cp.borrow_quantity; k++)
			{
				if (!strcmp(cp.borrow_books[k], b_array[i].b_name))
				{
					for (int m = k; m < cp.borrow_quantity - 1; m++)
					{
						strcpy(cp.borrow_books[m], cp.borrow_books[m + 1]);
					}
					strcpy(cp.borrow_books[--cp.borrow_quantity], "");
					//					cp.borrow_quantity--;
					break;
				}
			}
			for (int j = 0; j < s_sum; j++)
			{

				if (s_array[j].S_If_match(cp.s_num))
				{
					s_array[j] = cp;
					return true;
				}
			}
		}
		if (i == b_sum)
		{
			cout << "��Ǹ!���뻹��ͼ��δ��¼! " << endl;
			return false;
		}
	}
}

bool management::reduce_book(Student& cp)          //�� 
{
	S_Read_file();
	B_Read_file();
	char _b_num[30];
	cout << "��������ͼ���ͼ��Ż�����:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "��ͼ�����ϢΪ:\n";
			b_array[i].b_display();
			cout << "�Ƿ�ȷ�ϣ�        ��ȷ��/(Y/y)��    ��ȡ��/(N/n)��" << endl;
			char yn;
			do
			{
				cin >> yn;
			} while (!(yn == 'Y' || yn == 'y' || yn == 'N' || yn == 'n'));
			if (yn == 'Y' || yn == 'y')
			{
				S_Save_file();
				cout << "�뽻��1000Ԫ��Ϊ�⳥" << endl;
			}

			cout << "�����ɹ�" << endl;
		}

		c_add();

		c_Save_file();
		for (int k = 0; k < cp.borrow_quantity; k++)
		{
			if (!strcmp(cp.borrow_books[k], b_array[i].b_name))
			{
				for (int m = k; m < cp.borrow_quantity - 1; m++)
				{
					strcpy(cp.borrow_books[m], cp.borrow_books[m + 1]);
				}
				strcpy(cp.borrow_books[--cp.borrow_quantity], "");
				//					cp.borrow_quantity--;
				break;
			}
		}
		for (int j = 0; j < s_sum; j++)
		{

			if (s_array[j].S_If_match(cp.s_num))
			{
				s_array[j] = cp;
				return true;
			}
		}
		if (i == b_sum)
		{
			cout << "��Ǹ!��δ��ñ��鼮! " << endl;
			return false;
		}
	}
}

