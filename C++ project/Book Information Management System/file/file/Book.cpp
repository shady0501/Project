#include<iostream>
#include<iomanip>
#include<fstream>
#include"Book.h"

//提取运算符重载
istream& operator>>(istream& in, Book& cp)
{
	in >> cp.b_num >> cp.b_name >> cp.author >> cp.ISBN >> cp.b_quantity;
	return in;
}

//插入运算符重载
ostream& operator<<(ostream& out, Book& cp)
{
	out << cp.b_num << ' ' << cp.b_name << ' ' << cp.author << ' ' << cp.ISBN << ' ' << cp.b_quantity << '\n';
	return out;
}

//图书管理系统 
bool Book::Personnel_System()
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
					<< "*****    1——添加图书信息					"
					<< "2——修改图书信息" << endl
					<< "*****	 3——删除图书信息					"
					<< "4——查询图书信息" << endl
					<< "*****    5——退出登录" << endl
					<< "你需要做什么？(1-5)" << endl;
				cin >> menu_options;
				switch (menu_options)
				{

				case 1:Book_add(); break;
				case 2:Book_mod(); break;
				case 3:Book_del(); break;
				case 4:Book_search(); break;
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
							B_Save_file();
						}
						cout << "操作成功";
					}
				}

				B_clear();
			}
		else
		{
			cout << "密码错误!" << endl;
			continue;
		}
	}
	return true;
}

//读取图书文件
void Book::B_Read_file()
{
	ifstream b_file;
	b_file.open("Book_Information.txt");
	if (!b_file.is_open())
	{
		cerr << "文件\"Book_Information.txt\"无法打开\n";
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

//保存图书文件
void Book::B_Save_file()
{
	ofstream b_file("Book_Information.txt");
	if (!b_file)
	{
		cerr << "文件\"Book_Information.txt\"无法打开!\n";
		exit(1);
	}
	int i = -1;
	while (++i < b_sum)
	{
		b_file << b_array[i];
	}
	b_file.close();
}

void Book::B_clear()                          //清理已有图书信息
{
	b_array.clear();
	b_sum = 0;
}

//添加图书信息
bool Book::Book_add()
{
	B_Read_file();
	Book _book;
	cout << "请进行信息录入。按“+”结束!\n";
	do
	{
		b_array.push_back(_book);
	} while (b_array[b_sum++].B_SetInto());
	b_sum--;
	b_array.pop_back();
	return true;
}

//修改图书信息
bool Book::Book_mod()
{
	char _b_num[30];
	B_Read_file();
	cout << "请输入您要修改的图书信息的图书号或书名:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "该图书的原信息为:\n";
			b_array[i].b_display();
			cout << "请输入正确信息！ \n";
			b_array[i].B_SetInto();
			b_sum++;							//保持总航线数不变
			return true;
		}
		if (i == b_sum)
		{
			cout << "抱歉!您要修改的信息不存在! " << endl;
			return false;
		}
		break;
	}
	B_Save_file();
}

bool Book::Book_del()                      //删除图书信息
{
	char _b_num[15];
	B_Read_file();
	cout << "请输入您要删除的图书信息的图书号:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "该图书的原信息为:\n";
			b_array[i].b_display();
			b_array[i].Deletenum();
			b_sum--;
			return true;
		}
		if (i == b_sum)
		{
			cout << "抱歉!您要删除的信息不存在! " << endl;
			return false;
		}
	}
	B_Save_file();
}

bool Book::B_SetInto()               //设置图书信息
{
	char temp[15];
	cout << "请输入图书号:(输入+退出)";
	cin >> temp;
	if (temp[0] == '+')
		return false;
	strcpy(b_num, temp);
	cout << "书名:";
	cin >> b_name;
	cout << "作者:";
	cin >> author;
	cout << "ISBN";
	cin >> ISBN;
	cout << "数量:";
	cin >> b_quantity;
	return true;
}

//判断图书号是否匹配
bool Book::B_If_match(char p[30])
{
	return (!strcmp(b_num, p) || !strcmp(b_name, p));
}

//显示函数
void Book::b_display()
{
	cout << setiosflags(ios::left) << setw(12) << b_num << "    " << setw(30) << b_name << "    " << setw(10) << author << endl
		<< setw(20) << ISBN << "    " << "剩余数量:" << setw(3) << b_quantity << endl;
}

//查询图书信息
bool Book::Book_search()
{
	char _b_num[30];
	B_Read_file();
	cout << "请输入您要查询的图书信息的图书号或书名:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "该图书的信息为:\n";
			b_array[i].b_display();
			return true;
		}
		if (i == b_sum)
		{
			cout << "抱歉!您要查询的信息不存在! " << endl;
			return false;
		}
		break;
	}
	B_Save_file();
}

void Book::Deletenum()
{
	int n;
	cout << "请输入删除的数量：";
	cin >> n;
	b_quantity -= n;
}