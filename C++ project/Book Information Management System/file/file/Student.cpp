#include<iostream>
#include<iomanip>
#include<fstream>
#include"Student.h"

//��ȡ���������
istream& operator>>(istream& in, Student& cp)
{
	in >> cp.s_num >> cp.s_name >> cp.tell >> cp.borrow_max >> cp.borrow_quantity;
	for (int i = 0; i < cp.borrow_quantity; i++)
	{
		in >> cp.borrow_books[i];

	}
	return in;
}

//�������������
ostream& operator<<(ostream& out, Student& cp)
{
	out << cp.s_num << ' ' << cp.s_name << ' ' << cp.tell << ' ' << cp.borrow_max << ' ' << cp.borrow_quantity << ' ';
	for (int i = 0; i < 10; i++)
	{
		out << cp.borrow_books[i] << ' ';

		if (i == 9)
		{
			out << '\n';
		}
	}
	return out;
}

bool Student::Personnel_System()             //���߹���ϵͳ 
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
					<< "*****  	  1�������ѧ����Ϣ					"
					<< "2�����޸�ѧ����Ϣ" << endl
					<< "*****    3����ɾ��ѧ����Ϣ					"
					<< "4������ѯѧ����Ϣ" << endl
					<< "*****    5�����˳���¼" << endl
					<< "����Ҫ��ʲô��(1-5)" << endl;

				cin >> menu_options;

				switch (menu_options)
				{
				case 1:Student_add(); break;
				case 2:Student_mod(); break;
				case 3:Student_del(); break;
				case 4:Student_search(); break;
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
							S_Save_file();
						}

						cout << "�����ɹ�";
					}
				}
				S_clear();

			}
		else
		{
			cout << "�������!" << endl;
			continue;
		}
	}
	return true;
}




//��ȡѧ���ļ�
void Student::S_Read_file()
{
	ifstream s_file;
	s_file.open("Student_Information.txt");
	if (!s_file.is_open())
	{
		cerr << "�ļ�\"Student_Information.txt\"�޷���\n";
		exit(1);
	}
	while (!s_file.eof())
	{
		Student stu;
		s_file >> stu;
		s_array.push_back(stu);
		s_sum++;
	}
	for (int i = 0; i < 4; ++i)
	{
		cout <<"i="<< s_array[i] << endl;
	}
	s_sum--;
	s_file.close();
}

void Student::S_Save_file()                    //����ѧ���ļ�
{
	ofstream s_file("Student_Information.txt");
	if (!s_file)
	{
		cerr << "�ļ�\"Student_Information.txt\"�޷���!\n";
		exit(1);
	}
	int i = -1;
	while (++i < s_sum)
	{
		s_file << s_array[i];
	}
	s_file.close();
}

bool Student::Student_add()             //���ѧ����Ϣ
{
	S_Read_file();
	Student _stu;
	cout << "�������Ϣ¼�롣����+������!\n";
	do
	{
		s_array.push_back(_stu);
	} while (s_array[s_sum++].S_SetInto());
	s_sum--;
	s_array.pop_back();
	return true;
}

bool Student::Student_mod()                 //�޸�ѧ����Ϣ
{
	char _s_num[15];
	S_Read_file();
	cout << "��������Ҫ�޸ĵ�ѧ����Ϣ��ѧ�Ż�����:";
	cin >> _s_num;
	int i = 0;
	for (; i < s_sum; i++)
	{
		if (s_array[i].S_If_match(_s_num))
		{
			cout << "��ͬѧ��ԭ��ϢΪ:\n";
			s_array[i].s_display();
			cout << "��������ȷ��Ϣ�� \n";
			s_array[i].S_SetInto();
			s_sum++;							//����ѧ����
			return true;
		}
		if (i == s_sum)
		{
			cout << "��Ǹ!��Ҫ�޸ĵ���Ϣ������! " << endl;
			return false;
		}
		break;
	}
	S_Save_file();
}

bool Student::Student_del()                  //ɾ��ѧ����Ϣ
{
	char _s_num[15];
	S_Read_file();
	cout << "��������Ҫɾ����ѧ����Ϣ��ѧ��:";
	cin >> _s_num;
	for (int i = 0; i < s_sum; i++)
	{
		if (s_array[i].S_If_match(_s_num))
		{
			cout << "��ͬѧ��ԭ��ϢΪ:\n";
			s_array[i].s_display();
			s_array[i].Deletenum();
			s_sum--;
			return true;
		}
		if (i == s_sum)
		{
			cout << "��Ǹ!��Ҫɾ������Ϣ������! " << endl;
			return false;
		}
	}
	S_Save_file();
}

//��ѯѧ����Ϣ
bool Student::Student_search()
{
	char _s_num[15];
	S_Read_file();
	cout << "��������Ҫ��ѯ��ѧ����Ϣ��ѧ�Ż�����:";
	cin >> _s_num;
	int i = 0;
	for (; i < 15; i++)//@#$
	{
		cout << "i=" << i << endl;
		if (s_array[i].S_If_match(_s_num))
		{
			cout << "��ͬѧ��ԭ��ϢΪ:\n";
			s_array[i].s_display();

			return true;
		}
		if (i == s_sum)
		{
			cout << "��Ǹ!��Ҫ��ѯ����Ϣ������! " << endl;
			return false;
		}
		//break;
	}
	S_Save_file();
}

void Student::S_clear()                 //��������ѧ����Ϣ
{
	s_array.clear();
	s_sum = 0;
}

//����ѧ����Ϣ
bool Student::S_SetInto()
{
	char temp[15];
	cout << "������ѧ��:(����+�˳�)";
	cin >> temp;
	if (temp[0] == '+')
	{
		return false;
	}
	strcpy(s_num, temp);
	cout << "ѧ������:";
	cin >> s_name;
	cout << "�绰����:";
	cin >> tell;
	do
	{
		cout << "����������(1-10):";
		cin >> borrow_max;
	} while (borrow_max <= 0 || borrow_max > 10);
	return true;
}

bool Student::S_If_match(char p[30])                //�ж�ѧ���Ƿ�ƥ��
{

	return (!strcmp(s_num, p) || !strcmp(s_name, p));
}
void Student::s_display()	//��ʾѧ����Ϣ									//��ʾ
{
	cout << setiosflags(ios::left) << "ѧ��:" << setw(12) << s_num << "    " << setw(10) << s_name << "    " << setw(25) << tell << endl
		<< "��������" << borrow_max << endl;
}



void Student::Deletenum()
{
	borrow_quantity -= 0;
}
