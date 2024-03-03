#include<iostream>
#include<iomanip>
#include<fstream>
#include"Student.h"

//提取运算符重载
istream& operator>>(istream& in, Student& cp)
{
	in >> cp.s_num >> cp.s_name >> cp.tell >> cp.borrow_max >> cp.borrow_quantity;
	for (int i = 0; i < cp.borrow_quantity; i++)
	{
		in >> cp.borrow_books[i];

	}
	return in;
}

//插入运算符重载
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

bool Student::Personnel_System()             //读者管理系统 
{
	while (1)
	{
		int menu_options;

		cout << "请输入登录密码:";
		cin >> key;
		if (key == "123456")											//登录密码
			while (1)
			{
				cout << endl
					<< "*****  	 主菜单:								          **********" << endl
					<< "*****    工作人员		              	" << endl
					<< "*****  	  1——添加学生信息					"
					<< "2——修改学生信息" << endl
					<< "*****    3——删除学生信息					"
					<< "4——查询学生信息" << endl
					<< "*****    5——退出登录" << endl
					<< "你需要做什么？(1-5)" << endl;

				cin >> menu_options;

				switch (menu_options)
				{
				case 1:Student_add(); break;
				case 2:Student_mod(); break;
				case 3:Student_del(); break;
				case 4:Student_search(); break;
				case 5:return false;
				default:cout << "输入错误,请重新选择" << endl; break;
				}

				if (!(menu_options == 4))
				{
					cout << "是否确认？        《确认/(Y/y)》    《取消/(N/n)》" << endl;
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

						cout << "操作成功";
					}
				}
				S_clear();

			}
		else
		{
			cout << "密码错误!" << endl;
			continue;
		}
	}
	return true;
}




//读取学生文件
void Student::S_Read_file()
{
	ifstream s_file;
	s_file.open("Student_Information.txt");
	if (!s_file.is_open())
	{
		cerr << "文件\"Student_Information.txt\"无法打开\n";
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

void Student::S_Save_file()                    //保存学生文件
{
	ofstream s_file("Student_Information.txt");
	if (!s_file)
	{
		cerr << "文件\"Student_Information.txt\"无法打开!\n";
		exit(1);
	}
	int i = -1;
	while (++i < s_sum)
	{
		s_file << s_array[i];
	}
	s_file.close();
}

bool Student::Student_add()             //添加学生信息
{
	S_Read_file();
	Student _stu;
	cout << "请进行信息录入。按“+”结束!\n";
	do
	{
		s_array.push_back(_stu);
	} while (s_array[s_sum++].S_SetInto());
	s_sum--;
	s_array.pop_back();
	return true;
}

bool Student::Student_mod()                 //修改学生信息
{
	char _s_num[15];
	S_Read_file();
	cout << "请输入您要修改的学生信息的学号或名字:";
	cin >> _s_num;
	int i = 0;
	for (; i < s_sum; i++)
	{
		if (s_array[i].S_If_match(_s_num))
		{
			cout << "该同学的原信息为:\n";
			s_array[i].s_display();
			cout << "请输入正确信息！ \n";
			s_array[i].S_SetInto();
			s_sum++;							//保持学生数
			return true;
		}
		if (i == s_sum)
		{
			cout << "抱歉!您要修改的信息不存在! " << endl;
			return false;
		}
		break;
	}
	S_Save_file();
}

bool Student::Student_del()                  //删除学生信息
{
	char _s_num[15];
	S_Read_file();
	cout << "请输入您要删除的学生信息的学号:";
	cin >> _s_num;
	for (int i = 0; i < s_sum; i++)
	{
		if (s_array[i].S_If_match(_s_num))
		{
			cout << "该同学的原信息为:\n";
			s_array[i].s_display();
			s_array[i].Deletenum();
			s_sum--;
			return true;
		}
		if (i == s_sum)
		{
			cout << "抱歉!您要删除的信息不存在! " << endl;
			return false;
		}
	}
	S_Save_file();
}

//查询学生信息
bool Student::Student_search()
{
	char _s_num[15];
	S_Read_file();
	cout << "请输入您要查询的学生信息的学号或名字:";
	cin >> _s_num;
	int i = 0;
	for (; i < 15; i++)//@#$
	{
		cout << "i=" << i << endl;
		if (s_array[i].S_If_match(_s_num))
		{
			cout << "该同学的原信息为:\n";
			s_array[i].s_display();

			return true;
		}
		if (i == s_sum)
		{
			cout << "抱歉!您要查询的信息不存在! " << endl;
			return false;
		}
		//break;
	}
	S_Save_file();
}

void Student::S_clear()                 //清理已有学生信息
{
	s_array.clear();
	s_sum = 0;
}

//设置学生信息
bool Student::S_SetInto()
{
	char temp[15];
	cout << "请输入学号:(输入+退出)";
	cin >> temp;
	if (temp[0] == '+')
	{
		return false;
	}
	strcpy(s_num, temp);
	cout << "学生姓名:";
	cin >> s_name;
	cout << "电话号码:";
	cin >> tell;
	do
	{
		cout << "最大借阅数量(1-10):";
		cin >> borrow_max;
	} while (borrow_max <= 0 || borrow_max > 10);
	return true;
}

bool Student::S_If_match(char p[30])                //判断学号是否匹配
{

	return (!strcmp(s_num, p) || !strcmp(s_name, p));
}
void Student::s_display()	//显示学生信息									//显示
{
	cout << setiosflags(ios::left) << "学号:" << setw(12) << s_num << "    " << setw(10) << s_name << "    " << setw(25) << tell << endl
		<< "最大借阅量" << borrow_max << endl;
}



void Student::Deletenum()
{
	borrow_quantity -= 0;
}
