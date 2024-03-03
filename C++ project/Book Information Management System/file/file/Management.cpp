#include<iostream>
#include<iomanip>
#include<fstream>
#include"Management.h"

istream& operator>>(istream& in, management& cp)
{
	in >> cp.book >> cp.stu >> cp.da >> cp.a;
	return in;
}

//插入运算符重载
ostream& operator<<(ostream& out, management& cp)
{
	out << cp.book << ' ' << cp.stu << ' ' << cp.da << ' ' << cp.a << '\n';
	return out;
}

//学生登录
bool management::Student_System()
{
	while (1)
	{
		Student cp;
		bool key = s_login(cp);

		while (key)
		{
			int menu_options;

			cout << "*****	 主菜单:								             **********" << endl
				<< "*****	 学生:							" << endl
				<< "*****	 1——借阅图书" << endl
				<< "*****	 2——归还图书" << endl
				<< "*****	 3——按学号查询书籍信息" << endl
				<< "*****    4——损坏图书" << endl
				<< "*****    5——退出登录" << endl
				<< "你需要做什么?（选择1-5）" << endl;
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
				cout << "是否确认？        《确认/(Y/y)》    《取消/(N/n)》" << endl;
				char yn;
				do
				{
					cin >> yn;
				} while (!(yn == 'Y' || yn == 'y' || yn == 'N' || yn == 'n'));
				if (yn == 'Y' || yn == 'y')
				{
					cout << "操作成功！" << endl;
					S_Save_file();
					B_Save_file();
				}
			}
			S_clear();
			B_clear();
		}
		cout << "未找到您的信息！" << endl;
	}
	return true;
}

//读取图书文件
void management::c_Read_file()
{
	ifstream c_file;
	c_file.open("S_Information.txt");
	if (!c_file.is_open())
	{
		cerr << "文件\"S_Information.txt\"无法打开\n";
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

//保存图书文件
void management::c_Save_file()
{
	ofstream c_file("S_Information.txt");
	if (!c_file)
	{
		cerr << "文件\"S_Information.txt\"无法打开!\n";
		exit(1);
	}
	int i = -1;
	while (++i < c_sum)
	{
		c_file << c_array[i];
	}
	c_file.close();
}

//学生凭学号登录
bool management::s_login(Student& cp)
{
	char _s_num[15];
	S_Read_file();
	cout << "请输入您的学号:";
	cin >> _s_num;
	for (int i = 0; i < s_sum; i++)
	{
		if (s_array[i].S_If_match(_s_num))
		{
			cp = s_array[i];
			cout << "欢迎您," << cp.s_name << "同学！" << endl;
			S_clear();
			return true;
		}
	}
	S_clear();
	return false;
}

//设置图书信息
bool management::c_SetInto()
{
	char temp[15];
	cout << "请输入书籍编号:(输入+退出)";
	cin >> temp;
	if (temp[0] == '+')
		return false;
	strcpy(book, temp);
	cout << "读者编号:";
	cin >> stu;
	cout << "日期:";
	cin >> da;
	cout << "0借1还";
	cin >> a;

	return true;
}

bool management::c_add()
{
	c_Read_file();
	management _book;
	cout << "请进行信息录入。按“+”结束!\n";
	do
	{
		c_array.push_back(_book);
	} while (c_array[c_sum++].c_SetInto());
	c_sum--;
	c_array.pop_back();
	return true;
}

bool management::c_If_match(char p[30])         //判断图书号是否匹配
{
	return (!strcmp(book, p));
}

void management::c_display()                  //显示函数
{
	cout << setiosflags(ios::left) << setw(12) << book << "    " << setw(30) << stu << "    " << setw(10) << da << endl
		<< setw(20) << a << endl;
}

bool management::c_search()                   //查询借阅信息
{
	char _s_num[15];
	c_Read_file();
	cout << "请输入您要查的书籍编号:";
	cin >> _s_num;
	int i = 0;
	for (; i < c_sum; i++)
	{
		if (c_array[i].c_If_match(_s_num))
		{
			cout << "借阅记录:\n";
			c_array[i].c_display();
			return true;
		}
		if (i == c_sum)
		{
			cout << "抱歉!您要修改的信息不存在! " << endl;
			return false;
		}
		break;
	}
	c_Save_file();
}

bool management::borrow_book(Student& cp)                //借书
{
	S_Read_file();
	B_Read_file();
	c_Read_file();
	char _b_num[30];
	cout << "请输入想借图书的图书号或书名:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "该图书的信息为:\n";
			b_array[i].b_display();
			b_array[i].b_quantity--;

			c_add();
			c_Save_file();
			if (cp.borrow_quantity > cp.borrow_max - 1)
			{
				cout << "抱歉，您已达借书最大上限！" << endl;
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
			cout << "抱歉!您想借的图书未收录! " << endl;
			return false;
		}
	}

}

bool management::return_book(Student& cp)            //还书
{
	S_Read_file();
	B_Read_file();
	char _b_num[30];
	cout << "请输入想还图书的图书号或书名:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "该图书的信息为:\n";
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
			cout << "抱歉!您想还的图书未收录! " << endl;
			return false;
		}
	}
}

bool management::reduce_book(Student& cp)          //损坏 
{
	S_Read_file();
	B_Read_file();
	char _b_num[30];
	cout << "请输入损坏图书的图书号或书名:";
	cin >> _b_num;
	for (int i = 0; i < b_sum; i++)
	{
		if (b_array[i].B_If_match(_b_num))
		{
			cout << "该图书的信息为:\n";
			b_array[i].b_display();
			cout << "是否确认？        《确认/(Y/y)》    《取消/(N/n)》" << endl;
			char yn;
			do
			{
				cin >> yn;
			} while (!(yn == 'Y' || yn == 'y' || yn == 'N' || yn == 'n'));
			if (yn == 'Y' || yn == 'y')
			{
				S_Save_file();
				cout << "请交还1000元作为赔偿" << endl;
			}

			cout << "操作成功" << endl;
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
			cout << "抱歉!您未借该本书籍! " << endl;
			return false;
		}
	}
}

