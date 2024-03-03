#include<iostream>
#include<iomanip>
#include<fstream>
#include"Book.h"

//��ȡ���������
istream& operator>>(istream& in, Book& cp)
{
	in >> cp.b_num >> cp.b_name >> cp.author >> cp.ISBN >> cp.b_quantity;
	return in;
}

//�������������
ostream& operator<<(ostream& out, Book& cp)
{
	out << cp.b_num << ' ' << cp.b_name << ' ' << cp.author << ' ' << cp.ISBN << ' ' << cp.b_quantity << '\n';
	return out;
}

//ͼ�����ϵͳ 
bool Book::Personnel_System()
{
	while (1)
	{
		int menu_options;

		cout << "�������¼����:";
		cin >> key;
		if (key == "123456")											//��¼����
			while (1)
			{
				cout << endl
					<< "*****  	 ���˵�:								          **********" << endl
					<< "*****    ������Ա		              	" << endl
					<< "*****    1�������ͼ����Ϣ					"
					<< "2�����޸�ͼ����Ϣ" << endl
					<< "*****	 3����ɾ��ͼ����Ϣ					"
					<< "4������ѯͼ����Ϣ" << endl
					<< "*****    5�����˳���¼" << endl
					<< "����Ҫ��ʲô��(1-5)" << endl;
				cin >> menu_options;
				switch (menu_options)
				{

				case 1:Book_add(); break;
				case 2:Book_mod(); break;
				case 3:Book_del(); break;
				case 4:Book_search(); break;
				case 5:return false;
				default:cout << "�������,������ѡ��" << endl; break;
				}
				if (!(menu_options == 4))
				{
					cout << "�Ƿ�ȷ�ϣ�        ��ȷ��/(Y/y)��    ��ȡ��/(N/n)��" << endl;
					char yn;
					do
					{
						cin >> yn;
					} while (!(yn == 'Y' || yn == 'y' || yn == 'N' || yn == 'n'));


					if (yn == 'Y' || yn == 'y')
					{

						if (menu_options == 1 || menu_options == 2 || menu_options == 3)
						{
							B_Save_file();
						}
						cout << "�����ɹ�";
					}
				}

				B_clear();
			}
		else
		{
			cout << "�������!" << endl;
			continue;
		}
	}
	return true;
}

//��ȡͼ���ļ�
void Book::B_Read_file()
{
	ifstream b_file;
	b_file.open("Book_Information.txt");
	if (!b_file.is_open())
	{
		cerr << "�ļ�\"Book_Information.txt\"�޷���\n";
		exit(1);
	}
	while (!b_file.eof())
	{
		Book _book;
		b_file >> _book;
		b_array.push_back(_book);
		b_sum++;
	};
	b_sum--;
	b_file.close();
}

//����ͼ���ļ�
void Book::B_Save_file()
{
	ofstream b_file("Book_Information.txt");
	if (!b_file)
	{
		cerr << "�ļ�\"Book_Information.txt\"�޷���!\n";
		exit(1);
	}
	int i = -1;
	while (++i < b_sum)
	{
		b_file << b_array[i];
	}
	b_file.close();
}

void Book::B_clear()                          //��������ͼ����Ϣ
{
	b_array.clear();
	b_sum = 0;
}

//���ͼ����Ϣ
bool Book::Book_add()
{
	B_Read_file();
	Book _book;
	cout << "�������Ϣ¼�롣����+������!\n";
	do
	{
		b_array.push_back(_book);
	} while (b_array[b_sum++].B_SetInto());
	b_sum--;
	b_array.pop_back();
	return true;
}

//�޸�ͼ����Ϣ
bool Book::Book_mod()
{
	char _b_num[30];
	B_Read_file();
	cout << "��������Ҫ�޸ĵ�ͼ����Ϣ��ͼ��Ż�����:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "��ͼ���ԭ��ϢΪ:\n";
			b_array[i].b_display();
			cout << "��������ȷ��Ϣ�� \n";
			b_array[i].B_SetInto();
			b_sum++;							//�����ܺ���������
			return true;
		}
		if (i == b_sum)
		{
			cout << "��Ǹ!��Ҫ�޸ĵ���Ϣ������! " << endl;
			return false;
		}
		break;
	}
	B_Save_file();
}

bool Book::Book_del()                      //ɾ��ͼ����Ϣ
{
	char _b_num[15];
	B_Read_file();
	cout << "��������Ҫɾ����ͼ����Ϣ��ͼ���:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "��ͼ���ԭ��ϢΪ:\n";
			b_array[i].b_display();
			b_array[i].Deletenum();
			b_sum--;
			return true;
		}
		if (i == b_sum)
		{
			cout << "��Ǹ!��Ҫɾ������Ϣ������! " << endl;
			return false;
		}
	}
	B_Save_file();
}

bool Book::B_SetInto()               //����ͼ����Ϣ
{
	char temp[15];
	cout << "������ͼ���:(����+�˳�)";
	cin >> temp;
	if (temp[0] == '+')
		return false;
	strcpy(b_num, temp);
	cout << "����:";
	cin >> b_name;
	cout << "����:";
	cin >> author;
	cout << "ISBN";
	cin >> ISBN;
	cout << "����:";
	cin >> b_quantity;
	return true;
}

//�ж�ͼ����Ƿ�ƥ��
bool Book::B_If_match(char p[30])
{
	return (!strcmp(b_num, p) || !strcmp(b_name, p));
}

//��ʾ����
void Book::b_display()
{
	cout << setiosflags(ios::left) << setw(12) << b_num << "    " << setw(30) << b_name << "    " << setw(10) << author << endl
		<< setw(20) << ISBN << "    " << "ʣ������:" << setw(3) << b_quantity << endl;
}

//��ѯͼ����Ϣ
bool Book::Book_search()
{
	char _b_num[30];
	B_Read_file();
	cout << "��������Ҫ��ѯ��ͼ����Ϣ��ͼ��Ż�����:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "��ͼ�����ϢΪ:\n";
			b_array[i].b_display();
			return true;
		}
		if (i == b_sum)
		{
			cout << "��Ǹ!��Ҫ��ѯ����Ϣ������! " << endl;
			return false;
		}
		break;
	}
	B_Save_file();
}

void Book::Deletenum()
{
	int n;
	cout << "������ɾ����������";
	cin >> n;
	b_quantity -= n;
}