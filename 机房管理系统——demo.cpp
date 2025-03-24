#include<iostream>
#include<ctime>
#include<cstring>
#include<fstream>
#include<iomanip>

using namespace std;

class computer
{
private:
	int computer_id;//用于记录电脑编号

	char id[30] = "\0";//用于登记用户号

	char name[30] = "\0";//用于登记用户名

	time_t login_time =0;//登入时间

	char iferror[10] = "false";//用于记录电脑是否故障，是为true

	char ifuse[10] = "No";//用于记录电脑是否正在使用，是为Yes

	char* pointer=NULL;//用于接受动态内存分配生成的时间字符串，利于将来释放

public:

	computer* next = NULL;//使用链表将各电脑联系起来，为了方便调用，设定为public

	computer(int _computer_id,const char* _id, const char* _name);//构造函数

	int get_computer_id(void);//获取computer_id

	char* get_id(void);//获取id

	char* get_name(void);//获取name

	time_t get_login_time(void);//获取login_time

	char* get_time(void);//获取login_time对应的时间

	char* get_iferror(void);//获取iferror

	char* get_ifuse(void);//获取ifuse

	void change_login_time(time_t time);

	void change_iferror(const char* if_error);//修改链表中的iferror

	void change_ifuse(const char* if_use);//修改链表中的ifuse

	void change_id(const char* _id);//修改链表中的id

	void change_name(const char* _name);//修改链表中的name

	void delete_pointer(void);//由于析构函数无法显示调用，因此构造该函数

	~computer();//释放动态内存分配空间
};

class administratorsystem
{
private:

	char administrator_id[30];//用于登记管理员id

	char password[30];//登记输入的密码

	char check_code[30];//登记校验码（重置密码）

	int N;//记录需要创建电脑对象的个数

	computer* phead = NULL;//接受create函数传递回来的链表首地址

public:

	void administrator_record(char* object,const char*filename);//记录数据到不同的txt中，专门保存管理员的数据

	void computer_record(int _computer_id, const char* iferror, const char* ifuse, const char* _id, const char* _name, time_t time);//专门保存登录的管理员管理的电脑数据

	int detect(char* object, int sign);//用于检测id,密码等是否已经被占用

	void input_management(char* object,int sign);//限制输入次数,仅用于管理administratorsystem的数据

	void input_check(char* subject,int num);//检测是否按照规定输入

	void administrator_register(void);//用于注册管理员账号

	void administrator_login(void);//用于处理有关管理员登入的一系列操作

	void administrator_create(void);//利用文件里面的数据创建节点

	void computer_login(void);//电脑登入

	void computer_logout(void);//电脑登出

	void reset_password(void);//用于重置密码	

	void create(int num);//用于用户创建新节点

	void administrator_change_state(int computer_id, const char* state);//用于改变电脑状态

	void show_computer(void);//展示各电脑目前状态

	void help(int i);//菜单,i用来控制种类

	~administratorsystem();
};

void get_duration(time_t LoginTime);//获取用户总共使用时长

void introduction(void);//介绍

void ComputerLabManagementSystem(administratorsystem administrator);//总函数，涵盖整个功能 

int main()
{
	introduction();
	administratorsystem administrator;
	ComputerLabManagementSystem(administrator);
	return 0;
}

void get_duration(time_t LoginTime)
{
	long long int duration, day, hour, minute, second;
	time_t LogOutTime;
	time(&LogOutTime);
	duration = difftime(LogOutTime, LoginTime);//返回值为秒数。本来的返回类型为double，这里用long long int类型是为了能接受更长的时间。
	day = duration / 86400;//86400=60*60*24
	hour = (duration % 86400) / 3600;//3600=60*60
	minute = (duration % 3600) / 60;
	second = duration % 60;
	cout << day << "天" << hour << "小时" << minute << "分钟" << second << "秒"<<endl;
}

void introduction(void)
{
	cout << setw(75)<<"*****机房管理系统*****     ver.2.6"<<endl;
	cout << "感谢您选择本系统！" << endl;
	cout << "编写这个系统时尽量考虑到了用户交互的各种可能性，但可能会有疏忽，请尽量按照要求交互。如果在运行时出现bug欢迎反馈!" << endl;
	cout << "该程序解释权归主编所有（doge）"<<endl;
	cout << "希望您能有良好的使用体验！————刘主编"<<endl;
	system("pause");
	system("cls");
}

computer::computer(int _computer_id,const char* _id="\0", const char* _name="\0")
{
	strcpy_s(id, strlen(id)+1, _id);
	strcpy_s(name, strlen(name)+1, _name);
	computer_id = _computer_id;
}

int computer::get_computer_id(void)
{
	return computer_id;
}

char* computer::get_id(void)
{
	return id;
}

char* computer::get_name(void)
{
	return name;
}

time_t computer::get_login_time(void)
{
	return login_time;
}

char* computer::get_time(void)
{
	char* currenttime=new char[26];
	if (login_time == 0)
		time(&login_time);
	ctime_s(currenttime, 26, &login_time);
	pointer = currenttime;
	return currenttime;
}

char* computer::get_iferror(void)
{
	return iferror;
}

char* computer::get_ifuse(void)
{
	return ifuse;
}

void computer::change_login_time(time_t time)
{
	login_time = time;
}

void computer::change_iferror(const char* if_error)
{
	strcpy_s(iferror, strlen(if_error) + 1, if_error);
}

void computer::change_ifuse(const char* if_use)//修改链表中的ifuse
{
	strcpy_s(ifuse, strlen(if_use) + 1, if_use);
}

void computer::change_id(const char* _id)
{
	strcpy_s(id, strlen(_id) + 1, _id);
}

void computer::change_name(const char* _name)
{
	strcpy_s(name, strlen(_name) + 1, _name);
}

void computer::delete_pointer(void)
{
	delete[]pointer;
}

computer::~computer()
{
	if (pointer != NULL)
		delete[]pointer;
}

void administratorsystem::computer_record(int _computer_id, const char* if_error="false", const char* if_use="No", const char* _id = "\0", const char* _name = "\0", time_t time = 0)
{
	ofstream outfile(administrator_id, ios::app);
	if (!outfile)
	{
		cout << "打开文件" << administrator_id << "出错！程序退出……";
		system("pause");
		exit(0);
	}
	outfile << _computer_id << ' ' << if_error << ' ' << if_use << ' ' << _id << ' ' << _name << ' ' <<time<<' ' << endl;
	outfile.close();
}

void administratorsystem::administrator_record(char* object, const char* filename)//将数据记录到文件内
{
	ofstream outfile(filename, ios::app);
	if (!outfile)
	{
		cout << "打开文件"<<filename<<"出错！程序退出……";
		system("pause");
		exit(0);
	}
	outfile << object << ' ' << endl;
	outfile.close();
}

int administratorsystem::detect(char* object, int sign)//用于检验是否重复,不重复返回1,且object大小均为30字节。sign用于判断是id还是password还是check_code
{
	char object_txt[30] = "\0";
	ifstream infile("administrator id.txt");
	switch (sign)
	{
	case(1)://1为id
	{
		while (1)
		{
			char judge = '\0';
			infile.get(judge);
			if (judge == '\0')//这里单独放是考虑到第一次使用，文件为空文件.同时也可以判断是否已经到达末尾
			{
				infile.close();
				return 1;
			}
			else if (judge != '\n')
				infile.seekg(-1, ios::cur);//将光标移回去
			for (int j = 0; j < 30; j++)//这里使用j<30,不使用strlen函数是为了防止有一部分是object而导致判断错误
			{
				infile.get(object_txt[j]);
				if (object_txt[j] == ' ')
				{
					object_txt[j] = '\0';
					break;
				}
			}
			if (!strcmp(object, object_txt))//object已经出现过
			{
				infile.close();
				return 0;
			}
		}
		break;
	}
	case(2)://2为password
	{
		infile.close();
		ifstream infile("administrator password.txt");
		while (1)
		{
			char judge = '\0';
			infile.get(judge);
			if (judge == '\0')//这里单独放是考虑到第一次使用，文件为空文件。同时也可以判断是否已经到达末尾
			{
				infile.close();
				return 1;
			}
			else if (judge != '\n')
				infile.seekg(-1, ios::cur);//将光标移回去
			for (int j = 0; j < 30; j++)//这里使用j<30,不使用strlen函数是为了防止有一部分是object而导致判断错误
			{
				infile.get(object_txt[j]);
				if (object_txt[j] == ' ')
				{
					object_txt[j] = '\0';
					break;
				}
			}
			if (!strcmp(object, object_txt))//object已经出现过
			{
				infile.close();
				return 0;
			}
		}

		break;
	}
	case(3)://3为check_code
	{
		infile.close();
		ifstream infile("administrator check_code.txt");
		while (1)
		{
			char judge = '\0';
			infile.get(judge);
			if (judge == '\0')//这里单独放是考虑到第一次使用，文件为空文件。同时也可以判断是否已经到达末尾
			{
				infile.close();
				return 1;
			}
			else if (judge != '\n')
				infile.seekg(-1, ios::cur);//将光标移回去
			for (int j = 0; j < 30; j++)//这里使用j<30,不使用strlen函数是为了防止有一部分是object而导致判断错误
			{
				infile.get(object_txt[j]);
				if (object_txt[j] == ' ')
				{
					object_txt[j] = '\0';
					break;
				}
			}
			if (!strcmp(object, object_txt))//object已经出现过
			{
				infile.close();
				return 0;
			}
		}
		break;
	}
	}
}

void administratorsystem::input_management(char* object,int sign)//输入次数管理
{
	int j = 0;
	while (detect(object,sign))
	{
		if (j == 3)
		{
			cout << "尝试次数过多！系统退出……" << endl;
			system("pause");
			exit(0);
		}
		cout << "输入错误！请重试……" << endl;
		cin >> object;
		j++;
	}
}

void administratorsystem::input_check(char* subject,int num)//能够检测任意一个字符数组是否接受了超过自身大小的数据
{
	char* blank = new char[num];
	for (int i = 0; i < num; i++)
		blank[i] = '\0';//创建空白数组，便于将subject清空
	while (strlen(subject) == num)
	{
		cout << "超出字符限制，请重新输入！"<<endl;
		strcpy_s(subject, num+1, blank);//清空subject
		cin >> subject;//重新输入
	}
	delete[num]blank;//清除动态内存分配生成的数组
}

void administratorsystem::administrator_register(void)//用于注册并检查id是否已经被占用
{
	cout << "下面将创建一个管理员账号！" << endl;
	cout << "请输入id:(<30字符，接受汉字，一个汉字占两个字符。回车或空格以结束）" << '\n';
	cin >> administrator_id;
	input_check(administrator_id,30);
	while (!detect(administrator_id,1))
		cout << "该id已经被占用！重新输入……"<<'\n';
	cout << "请输入密码:(<30字符，不接受空格。空格或回车以结束)" << '\n';
	cin >> password;
	input_check(password,30);
	cout << "创建成功！"<<'\n';
	srand(time(NULL));//初始化随机数
	do
	{
		for (int i = 0; i < 4; i++)
		{
			int number = rand() % 10;
			check_code[i] = ('0' + number);
		}
	} while (!detect(check_code,3));//创建独一无二的校验码，用于之后重置账号密码
	cout << "您该账号对应的管理员校验码是:" << check_code << endl;
	cout << "该校验码只在这里出现，它可用于重置您账号的密码，请记住！（按回车继续……）" << endl;
	administrator_record(administrator_id,"administrator id.txt");
	administrator_record(password, "administrator password.txt");
	administrator_record(check_code, "administrator check_code.txt");
	system("pause");
	system("cls");
	help(1);
}

void administratorsystem::administrator_login(void)//用于处理有关管理员登入的操作
{
	cout << "请输入管理员id:";
	cin >> administrator_id;
	input_check(administrator_id,30);
	input_management(administrator_id,1);
	cout << "请输入密码:";
	cin >> password;
	input_check(password,30);
	input_management(password,2);
	cout << "登入成功！"<<endl;
	system("pause");
	system("cls");
	char sign;
	ifstream infile(administrator_id);
	if (!(infile>>sign))
	{
		infile.close();
		cout << "请输入您管理的电脑台数:";
		cin >> N;
		create(N);
	}
	else
	{
		infile.close();
		int sign;
		cout << "检测到您之前存在记录，是否加载？(是为1，否为0）:";
		cin >> sign;
		if (sign)
		{
			system("cls");
			administrator_create();
		}
		else
		{
			system("cls");
			cout << "请输入您管理的电脑台数:";
			cin >> N;
			ofstream outfile(administrator_id);
			outfile.close();//清空文件
			create(N);
		}
	}
	help(2);
}

void administratorsystem::computer_login(void)
{
	int computer_id;
	char _id[30] = "\0";
	char _name[30] = "\0";
	computer* p1 = NULL, * p2 = NULL;
	do
	{
		cout << "请输入登入的电脑编号:(输入0退出程序）";
		cin >> computer_id;
		if (computer_id == 0)
		{
			cout << "程序即将退出……" << endl;
			system("pause");
			exit(0);
		}
		while (computer_id > N || computer_id <= 0)
		{
			cout << "您输入的编号超出范围，请重试！ " << endl;
			cin >> computer_id;
		}
		computer* p3 = phead, * p4 = p3->next;
		for (int i = 1; i <= N; i++)
		{
			if (p3->get_computer_id() == computer_id)
			{
				if (!strcmp(p3->get_ifuse(), "Yes"))//当电脑被他人使用
				{
					cout << "该电脑正在被他人使用！\n使用者用户号为:" << p3->get_id() << "  " << "用户名为:" << p3->get_name() << " " << "登入时间为:" << p3->get_time() << endl;
					p3->delete_pointer();
					cout << "请重新输入编号……" << endl << endl;
					computer_id = 0;//这里充当sign的功能，其实就是从头重新执行一次
				}
				if (!strcmp(p3->get_iferror(), "true"))//当电脑故障
				{
					cout << "该电脑故障，无法使用！" << endl;
					cout << "请重新输入编号……" << endl << endl;
					computer_id = 0;
				}
				p1 = p3, p2 = p4;
				break;
			}
			p3 = p4;
			p4 = p3->next;
		}
	} while (computer_id == 0);
	cout << "输入用户号（30字符以内）:";
	cin >> _id;
	input_check(_id, 30);
	cout << "输入用户名（30字符以内）:";
	cin >> _name;
	input_check(_name, 30);
	p1->change_id(_id);
	p1->change_name(_name);
	p1->change_ifuse("Yes");
	time_t begin;
	time(&begin);
	p1->change_login_time(begin);
	cout << "登入成功！登入信息为：" << endl;
	cout << "电脑编号:" << p1->get_computer_id() << endl << "用户号:" << p1->get_id() << endl << "用户名:" << p1->get_name() << endl << "登入时间:" << p1->get_time();
	p1->delete_pointer();
	cout << "按回车键回到菜单……" << endl;
	p1 = phead, p2 = p1->next;//回到phead
	ofstream outfile0(administrator_id);
	outfile0.close();//这两行是为了覆盖原来文件里面的内容
	for (int i = 1; i <= N; i++)
	{
		computer_record(i, p1->get_iferror(), p1->get_ifuse(), p1->get_id(), p1->get_name(), p1->get_login_time());
		p1 = p2;
		if (p1 != NULL)
			p2 = p1->next;
	}
	ofstream outfile(administrator_id, ios::app);
	outfile << N;
	outfile.close();
	system("pause");
	system("cls");
	help(2);
}

void administratorsystem::computer_logout(void)
{
	int computer_id;
	int sign;
	char id[30] = "\0";
	char name[30] = "\0";
	computer* p1 = NULL, * p2 = NULL;
	do
	{
		cout << "请输入登出的电脑编号:(输入0退出程序）";
		cin >> computer_id;
		if (computer_id == 0)
		{
			cout << "程序即将退出……" << endl;
			system("pause");
			exit(0);
		}
		while (computer_id > N || computer_id <= 0)
		{
			cout << "您输入的编号超出范围，请重试！" << endl;
			cin >> computer_id;
		}
		computer* p3 = phead, * p4 = p3->next;
		for (int i = 1; i <= N; i++)
		{
			if (p3->get_computer_id() == computer_id)
			{
				sign = 0;
				if (!strcmp(p3->get_iferror(), "true"))//当电脑故障
				{
					cout << "该电脑故障！" << endl;
					cout << "请重新输入编号……" << endl << endl;
					computer_id = 0;
					sign = 1;
				}
				if (!strcmp(p3->get_ifuse(), "No") && sign==0)//没有人使用电脑,则无需登出
				{
					cout << "该电脑没有人使用！" << endl;
					cout << "请重新输入编号……" << endl << endl;
					computer_id = 0;//这里充当sign的功能，其实就是从头重新执行一次
				}
				
				p1 = p3, p2 = p4;
				break;
			}
			p3 = p4;
			p4 = p3->next;
		}
	} while (computer_id == 0);
	cout << "即将登出电脑" << p1->get_computer_id() << "!"<<endl;
	cout << "该电脑的使用者用户号是:" << p1->get_id() << " " << "用户名是:" << p1->get_name() << "登入时间为:" << p1->get_time()<<endl;
	p1->delete_pointer();
	cout << "是否登出？(是为1，否为0):";
	cin >> sign;
	while (sign != 1 && sign != 0)
	{
		cout << "您输入错误了！请输入1或0……";
		cin >> sign;
	}
	if (sign == 1)
	{
		char blank[30] = "\0";//清空id和name
		p1->change_id(blank);
		p1->change_name(blank);
		p1->change_ifuse("No");
		cout << "该用户已登出！使用电脑时长总计为:";
		get_duration(p1->get_login_time());
		p1->change_login_time(0);
		ofstream outfile(administrator_id);
		outfile.close();//清空文件，重新录入
		p1 = phead, p2 = p1->next;
		for (int i = 1; i <= N; i++)
		{
			computer_record(i, p1->get_iferror(), p1->get_ifuse(), p1->get_id(), p1->get_name(), p1->get_login_time());
			if (p2 != NULL)
			{
				p1 = p2;
				p2 = p1->next;
			}
		}
		ofstream outfile0(administrator_id, ios::app);
		outfile0 << N;
		outfile0.close();
		cout << "按回车键回到菜单……" << endl;
		system("pause");
		system("cls");
		help(2);
	}
	else
	{
		cout << "程序将返回菜单，回车键继续……"<<endl;
		system("pause");
		help(2);
	}
}

void administratorsystem::administrator_create(void)//这是根据文件里面的内容读取账号信息并重新创建出来
{
	fstream file(administrator_id, ios::app | ios::in);//打开后光标位于最后，也就是N之前
	if (!file)
	{
		cout << "文件打开失败，程序即将退出……";
		system("pause");
		exit(0);
	}
	file.seekg(-1, ios::end);//将光标移动到N前面
	file >> N;
	computer* p1 = new computer(1), * p2 = p1;
	phead = p1;
	for (int i = 2; i <= N; i++)
	{
		p1 = new computer(i,"\0", "\0");
		p2->next = p1;
		p2 = p1;
	}
	p1 = phead;//指针回到开头
	p2 = p1->next;
	file.seekg(0, ios::beg);//光标回到开头
	int point = 0;
	int line = 1;//确定行数，也就是确定id
	int round = 0;//用于控制循环
	char content[30]="\0";//暂存file输入内容
	char clearcontent[30] = "\0";//用于清除content内容
	for(int i=0;i<6*N;i++)//有N个链表待初始化，一个链表初始化6次，因此共6*N
	{
		switch (point % 6)//根据point值来确定file输入的数据类型
		{
		case(0)://类型为computer_id。由于已经初始化过，因此无需录入，而是借此移动指针
		{
			for (round = 0; round < 30; round++)
			{
				file.get(content[round]);
				if (content[round] == '\n')//消除\n带来的影响
				{
					content[round] = '\0';
					round--;
					continue;
				}
				if (content[round] == ' ')//当if成立，光标已经移动到了空格之后
				{
					content[round] = '\0';
					while (line != p1->get_computer_id())//移动指针
					{
						p1 = p2;
						p2 = p1->next;
					}
					strcpy_s(content, strlen(content) + 1, clearcontent);//清除内容
					point++;
					break;
				}
			}
		}
		case(1): //类型为if_error
		{
			for (round = 0; round < 30; round++)
			{
				file.get(content[round]);
				if (content[round] == ' ')
				{
					content[round] = '\0';
					p1->change_iferror(content);//利用函数修改iferror内容
					strcpy_s(content, strlen(content) + 1, clearcontent);//清除内容
					point++;
					break;
				}
			}
		}
		case(2)://类型为ifuse
		{
			for (round = 0; round < 30; round++)
			{
				file.get(content[round]);
				if (content[round] == ' ')
				{
					content[round] = '\0';
					p1->change_ifuse(content);//利用函数修改ifuse内容
					strcpy_s(content, strlen(content) + 1, clearcontent);//清除内容
					point++;
					break;
				}
			}
		}
		case(3)://类型为id
		{
			for (round = 0; round < 30; round++)
			{
				file.get(content[round]);
				if (content[round] == ' ')
				{
					content[round] = '\0';
					p1->change_id(content);//利用函数修改id
					strcpy_s(content, strlen(content) + 1, clearcontent);//清空content
					point++;
					break;
				}
			}
		}
		case(4)://类型为name
		{
			for (round = 0; round < 30; round++)
			{
				file.get(content[round]);
				if (content[round] == ' ')
				{
					content[round] = '\0';
					p1->change_name(content);
					strcpy_s(content, strlen(content) + 1, clearcontent);
					point++;
					break;
				}
			}
		}
		case(5)://类型为time
			
			for (round = 0; round < 30; round++)
			{
				file.get(content[round]);
				if (content[round] == ' ')
				{
					content[round] = '\0';
					time_t time=0;
					for (int j = 0; j <= round-1; j++)//将content里面保存的数字从字符类型变为time_t类型
						time = time * 10 + (content[j] - '0');
					p1->change_login_time(time);
					strcpy_s(content, strlen(content) + 1, clearcontent);
					point++;
					line++;
					break;
				}
			}
		}
	}
	cout << "数据载入成功！载入的数据为:" << endl<<endl;
	show_computer();
}

void administratorsystem::reset_password(void)//用于重置密码
{
	int line = 0;//控制行数
	char id_txt[30] = "\0";
	char password_txt[30] = "\0";
	int j = 0;
	cout << "请输入管理员校验码:(不接受空格,输入零退出程序）";
	cin >> check_code;
	if (check_code == 0)
	{
		cout << "程序即将退出……" << endl;
		exit(0);
	}
	input_management(check_code,3);
	cout << "请输入需要重置密码的id:（不接受空格）";
	cin >> administrator_id;
	input_management(administrator_id,1);
	cout << "请输入重置后的密码:";
	cin >> password;
	//这里想法是创建另外一个文件，将不修改的直接“复制”过去，修改的再另外输入。最后再把内容重新覆写到原文件中
	fstream file0("administrator id.txt", ios::in | ios::app);//光标在文件末尾
	file0.seekg(0);//将光标移动到开头
	do
	{
		for (int i = 0; i < 30; i++)
		{
			file0.get(id_txt[i]);
			if (id_txt[i] == ' ')
			{
				id_txt[i] = '\0';
				break;
			}
		}
		line++;
	} while (!strcmp(administrator_id,id_txt));
	//程序运行到这里，光标移动到了需要修改密码的id,我们真正要的是line以确定它对应密码所在行
	file0.close();
	fstream file1("administrator password.txt",ios::in|ios::app);
	file1.seekg(0);
	fstream file2("administrator reset_password.txt", ios::in | ios::app);
	file2.seekg(0);
	while (line != 1)//在没有到需要修改的那一行，直接把内容复制过去
	{
		for (int j = 0; j < 30; j++)
		{
			file1.get(password_txt[j]);
			if (password_txt[j] == '\n')
				continue;
			file2 << password_txt[j];
			if (password_txt[j] == ' ')
			{
				file2 << '\n';
				line--;
				break;
			}
		}
	}//到这里，光标到需要修改的密码前
	file1.ignore(100);//先把原密码文件光标跳转到下一行
	for (int k = 0; k < 30; k++)
	{
		file2 << password[k];
		if (password[k] == ' ')
		{
			file2 << '\n';
			break;
		}
	}//输入修改的密码
	while (!file1.eof())
	{
		for (int l = 0; l < 30; l++)
		{
			file1.get(password_txt[l]);
			if (password_txt[l] == '\n')
				continue;
			file2 << password_txt[l];
			if (file1.eof())
			{
				file2 << '\n';
				file1.close();
				file2.close();
				break;
			}
		}
	}
	cout << "密码修改成功!新密码为:"<<password<<endl;
	cout << "按回车键返回菜单……"<<endl;
	system("pause");
	system("cls");
	help(2);
}

void administratorsystem::create(int num)//创建节点
{
	if (phead != NULL)
		delete[]phead;
	computer* head = NULL, * p1=NULL, * p2=NULL;
	p1 = new computer(1);
	head = p1;
	p2 = p1;
	computer_record(1);
	for (int i = 2; i <= num; i++)//定义i来控制循环创建节点个数
	{
		p1 = new computer(i);
		p2->next = p1;
		p2 = p1;
		computer_record(i);
	}
	ofstream outfile(administrator_id, ios::app);
	outfile << num;
	outfile.close();
	cout << "您管理的" << num << "台电脑已经生成！" << endl;
	phead = head;
}

void administratorsystem::administrator_change_state(int computer_id,const char* state)//实现对电脑状态的改变
{
	computer* p1 = NULL, * p2 = NULL;
	do
	{
		computer* p3 = phead;
		computer* p4 = phead->next;
		for (int i = 0; i < N; i++)
		{
			while (p3->get_computer_id() != computer_id)
			{
				p3 = p4;
				p4 = p3->next;
			}
			//运行到这里，p1指向的就是想要修改的电脑的链表
			if (!strcmp(p3->get_ifuse(), "Yes"))//如果想要设定故障，但这个时候有人使用
			{
				cout << "该电脑有人正在使用！\n使用者用户号为:" << p3->get_id() << " " << "用户名为:" << p3->get_name()<<" "<<"登入时间为:"<<p3->get_time() << endl;
				p3->delete_pointer();
				cout << "请重新输入编号……"<<endl;
				computer_id = 0;
			}
			if (computer_id != 0)
			{
				p3->change_iferror(state);
				break;
			}
		}
		p1 = p3;
		p2 = p4;
	} while (computer_id == 0);
	ofstream outfile(administrator_id);
	for (int j = 1; j <= N; j++)
	{
		if (p1 != phead)
		{
			p1 = phead;
			p2 = p1->next;
		}
		computer_record(j, p1->get_iferror(), p1->get_ifuse(), p1->get_id(), p1->get_name());
		p1 = p2;
		p2 = p1->next;
	}
	outfile.seekp(0, ios::end);
	outfile << N;
	outfile.close();
	cout << "状态修改成功！已保存！" << endl;
	system("pause");
	system("cls");
	help(2);
}

void ComputerLabManagementSystem(administratorsystem administrator)
{
	char check = '\0';
	ifstream infile("administrator id.txt");
	infile >> check;
	if (!check)
	{
		infile.close();
		cout << "检测到这是您第一次使用该系统，下面将先为您注册一个账户！" << endl<<endl;
		administrator.administrator_register();
	}
		administrator.help(1);
}

void administratorsystem::show_computer(void)
{
	cout << "====================================机房状态====================================="<<endl;
	cout << "==========电脑编号==========状态=========用户号========用户名========登入时间=======" << endl;
	computer* p1 = phead, * p2 = p1->next;
	for (int i = 0; i < N; i++)
	{
		cout <<"          "<<"电脑"<< p1->get_computer_id()<<"       "<<"||";
		if (!strcmp(p1->get_iferror(), "true"))//iferror为true,也就是电脑有故障
			cout << "[故障]" <<"||"<< endl << endl;
		else if (!strcmp(p1->get_ifuse(), "Yes"))//电脑没有故障并且正在被使用
		{
			cout << "[使用]" << "||" << "       " << p1->get_id() << "       " << p1->get_name() << "       " << p1->get_time() << endl << endl;
			p1->delete_pointer();
		}
		else//电脑无故障且没有被使用
			cout << "[空闲]"<<"||" << endl << endl;
		p1 = p2;
		if(p1!=NULL)
			p2 = p1->next;
	}
	cout << "完毕！回车键返回菜单……" << endl;
	system("pause");
	help(2);
}

void administratorsystem::help(int i)
{
	int selection=0;
	do
	{
		if (i == 1)//这是未登录时候的菜单
		{
			cout << "-------------------------------------菜单-------------------------------------" << endl;
			cout << "-----------------------------------1.登录-------------------------------------" << endl;
			cout << "-----------------------------------2.注册-------------------------------------" << endl;
			cout << "-----------------------------------3.修改密码---------------------------------" << endl;
			cout << "-----------------------------------4.退出系统---------------------------------" << endl;
				cout << "输入数字以选择服务:";
			cin >> selection;
			switch (selection)
			{
			case(1):
			{
				system("cls");
				administrator_login();
				break;
			}
			case(2):
			{
				system("cls");
				administrator_register();
				break;
			}
			case(3):
			{
				system("cls");
				reset_password();
				break;
			}
			case(4):
			{
				cout << "感谢您的使用！按回车键退出程序……"<<endl;
				system("pause");
				exit(0);
			}
			default:
			{
				cout << "输入无效数字，请重试！" << endl;
				system("pause");
				system("cls");
			}
			}
		}
	}while (selection!=0);

	do
	{
		if (i == 2)//这是登录进去之后的菜单
		{
			cout << "-------------------------------------菜单-------------------------------------" << endl;
			cout << "-----------------------------------1.电脑登入---------------------------------" << endl;
			cout << "-----------------------------------2.电脑登出---------------------------------" << endl;
			cout << "-----------------------------------3.设置故障---------------------------------" << endl;
			cout << "-----------------------------------4.解除故障---------------------------------" << endl;
			cout << "-----------------------------------5.查看机房状态-----------------------------" << endl;
			cout << "-----------------------------------6.退出系统---------------------------------" << endl;
			cout << "输入数字以选择服务:";
			cin >> selection;
			cout << endl;
			switch (selection)
			{
			case(1):
			{
				computer_login();
				break;
			}
			case(2):
			{
				computer_logout();
				break;
			}
			case(3):
			{
				int _id;
				cout << "请输入故障的电脑编号:";
				cin >> _id;
				while (_id > N || _id <= 0)
				{
					cout << "您输入的编号超出范围，请重试！";
					cin >> _id;
				}
				administrator_change_state(_id, "true");
			}
			case(4):
			{
				int _id;
				cout << "请输入修复的电脑编号:";
				cin >> _id;
				while (_id > N || _id <= 0)
				{
					cout << "您输入的编号超出范围，请重试！";
					cin >> _id;
				}
				administrator_change_state(_id, "false");
			}
			case(5):
			{
				show_computer();
				break;
			}
			case(6):
			{
				cout << "感谢您的使用！按回车键退出程序……"<<endl;
				system("pause");
				exit(0);
			}
			default:
			{
				cout << "输入无效数字，请重试！" << endl;
				system("pause");
				system("cls");
				help(2);
			}
			}
		}
	} while (selection != 0);
}

administratorsystem::~administratorsystem()
{
	delete[]phead;
} 
