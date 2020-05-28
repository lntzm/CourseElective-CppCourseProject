#include "Course.h"

using namespace std;

CourseNode::CourseNode()
{
	next = NULL;
}

CourseNode::~CourseNode()
{
	next = NULL;
}

Course::Course(const char* filename)
{
	ifstream ifs(filename);
	if (!ifs)						// 文件不存在，创建文件
	{
		m_head = new CourseNode;
		m_head->next = NULL;			// 申请内存，初始化链表
		cout << "未发现"<<filename<<"！系统将自动创建此文件" << endl;
		WriteFile(filename);
		cout << filename << "创建成功!\n" << endl;
	}
	else						   // 文件存在，读取文件
		ReadFile(filename);
}

Course::~Course()					// 析构，释放申请的内存
{
	CourseNode* currentNode = m_head->next;
	while (currentNode != NULL)		// 删除所有节点
	{
		CourseNode* temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	m_head->next = NULL;
	delete m_head;
	m_head = NULL;					// 链表头置NULL
}

void Course::WriteFile(const char* filename)
{
	CourseNode* p = m_head->next;
	ofstream ofs(filename);
	if (!ofs)						// 可写打开失败，退出程序
	{
		cout << "文件以输出流方式打开或创建失败，请检查。" << endl;
		system("pause");
		exit(0);
	}
	if (p == NULL)					// p==NULL，为空文件，此时为创建文件，无需写入
		return;
	while (p != NULL)				// 链表写入文件
	{
		ofs << p->id << '\t' << p->name << '\t' << p->property << '\t'
			<< p->totaltime << '\t' << p->classtime << '\t' << p->labtime << '\t'
			<< p->credits << '\t' << p->semester << '\t' << endl;
		p = p->next;
	}
	cout << "成功写入" << filename <<"！"<< endl;
	ofs.close();
}

void Course::ReadFile(const char* filename)	
{
	m_head = new CourseNode;
	m_head->next = NULL;			// 申请内存，初始化链表
	ifstream ifs(filename);
	if (!ifs)
	{
		cout << "文件以输入流方式打开失败，请检查。" << endl;
		system("pause");
		exit(0);
	}
	CourseNode* temp = m_head;
	while (ifs.peek() != EOF)		// 没有到文件末尾时。采用peek()而非ifs.eof()，防止文件为空时进入循环
	{
		CourseNode* p = new CourseNode;
		ifs >> p->id >> ws
			>> p->name >> ws
			>> p->property >> ws
			>> p->totaltime >> ws
			>> p->classtime	>> ws
			>> p->labtime >> ws
		    >> p->credits >> ws
			>> p->semester >> ws;

		temp->next = p;
		p->next = NULL;
		temp = p;				// 指向下一节点
	}
	ifs.close();
}

istream& operator >> (istream& input, CourseNode& node)		// 重载，用于输入CourseNode类，语法糖
{
	cout << "请输入课程编号："; InputInt(input, node.id);
	cout << "请输入课程名称："; input >> node.name;
	cout << "请输入课程性质："; input >> node.property;
	cout << "请输入总学时："; InputInt(input,node.totaltime);
	cout << "请输入授课学时："; InputInt(input, node.classtime);
	cout << "请输入实验或上机学时："; InputInt(input, node.labtime);
	cout << "请输入学分：";
	while (1)
	{
		input >> node.credits;
		if (!CheckInput(input)) break;
	}
	cout << "请输入开课学期："; input >> node.semester;
	return input;
}

ostream& operator << (ostream& output, CourseNode& node)	// 重载，用于输出CourseNode类，语法糖
{
	cout << left << setw(10) << node.id << left << setw(20) << node.name
		<< left << setw(10) << node.property << left << setw(8) << node.totaltime
		<< left << setw(10) << node.classtime << left << setw(10) << node.labtime
		<< left << setw(6) << node.credits << left << setw(18) << node.semester;
	return output;
}

void Course::Display(const char* filename)
{
	ReadFile(filename);				// 读取文件，更新状态
	DisplayTitle();
	CourseNode* currentNode = m_head->next;
	while (currentNode != NULL)		// 遍历链表，输出
	{
		cout << *currentNode << endl;	// <<已被重载
		currentNode = currentNode->next;
	}
	cout << endl;
}

void Course::DisplayTitle()			// 输出表头标题
{
	cout << endl;
	cout << left << setw(10) << "课程编号" << left << setw(20) << "课程名称"
		<< left << setw(10) << "课程性质" << left << setw(8) << "总学时"
		<< left << setw(10) << "授课学时" << left << setw(10) << "实验学时"
		<< left << setw(6) << "学分" << left << setw(18) << "开课学期" << endl;
	cout << setfill('-') << setw(89) << '-' << endl;
	cout << setfill(' ');
}

void Course::AddCourse(const char* filename)
{
	bool x = 1;
	while (x)
	{
		CourseNode* temp = m_head->next;			// 头节点后第一个元素
		CourseNode* newNode = new CourseNode;       // 创建新节点
		cin >> *newNode;							// 输入数据，>>已被重载
		m_head->next = newNode;
		newNode->next = temp;						// 将newNode插在链表的头
		cout << "还要继续添加吗？（0. 不添加了；1. 继续添加）" << endl;
		InputBool(x);								// x为true时继续循环，false退出循环
	}
	cout << "添加完成，是否保存？（0. 不保存；1. 保存）" << endl;
	InputBool(x);									// 是否写入文件，即保存数据
	if (x)
		WriteFile(filename);
}

void Course::Find(const char* filename)
{
	ReadFile(filename);					// 读取文件，更新状态
	int choice;
	bool x = 1;
	while (x)
	{
		cout << "请选择查找方式：" << endl;
		cout << "1. 按课程编号\t 2. 按课程名称\n"
			 << "3. 按课程性质\t 4. 按总学时  \n"
			 << "5. 按授课学时\t 6. 按实验学时\n"
			 << "7. 按学分    \t 8.按开课学期\n"
			 << "0. 不查找了，返回" << endl;
	inputChoice:
		cin >> choice;					// 选择查找方式
		if (CheckInput(cin))			
			goto inputChoice;
		switch (choice)
		{
		case 0:
			return;
		case 1:
			FindEditDelById(0, "");
			// break是对swtich，continue是对while
			continue;					// 跳过下方输出语句，继续循环
		case 2:
			FindMenu("按课程名称");
			FindInString(choice, "课程名称");
			break;
		case 3:
			FindMenu("按课程性质");
			FindInString(choice, "课程性质");
			break;
		case 4:
			FindMenu("按总学时");
			FindInInt(choice, "总学时");
			break;
		case 5:
			FindMenu("按授课学时");
			FindInInt(choice, "授课学时");
			break;
		case 6:
			FindMenu("按实验学时");
			FindInInt(choice, "实验学时");
			break;
		case 7:
			FindMenu("按学分");
			FindInFloat(choice, "学分");
			break;
		case 8:
			FindMenu("按开课学期");
			FindInString(choice, "开课学期");
			break;
		default:
			cout << "输入有误，请输入0~8的数字。" << endl;
			cin.clear();
			cin.ignore(1024, '\n');		// 清除缓冲区
			goto inputChoice;			// 重新输入
		}
		cout << "\n查找完毕，还需要继续查找吗？（0. 返回；1. 继续查找）" << endl;
		InputBool(x);				// x为true时继续循环，false退出循环
	}
}

void Course::FindMenu(const char* optname)
{
	system("cls");
	cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▏当前位置：用户>查找课程>" 
		<<setw(10)<< optname << "          ▕" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
}

void Course::FindEditDelById(int n, const char* filename)
{
	bool x = 1;
	const char* optname;
	switch (n)
	{
	case 0: optname = "查找"; break; 
	case 1: optname = "编辑"; break; 
	case 2: optname = "删除"; break; 
	default: optname = "";
	}
	while (x)
	{
		if (!n)			// n == 0，查找模式
			FindMenu("按课程编号");
		int input;
		cout << "请输入要" << optname << "的课程编号：（输入0查看所有课程）";
		InputInt(cin, input);
		if (!input)
		{
			Display(filename);
			cout << "现在请输入要" << optname << "的课程编号：";
			InputInt(cin, input);
		}
		bool flag = 1;		// 标志位，判断是否找到了数据
		CourseNode* currentNode = m_head->next, * temp = m_head;
		DisplayTitle();
		while (currentNode != NULL)		// 遍历链表
		{
			if (currentNode->id == input)	// 找到对应课程
			{
				flag = 0;
				cout << *currentNode << endl;
				if (n == 1)			// 编辑课程
				{
					bool y;
					cout << "\n确认要编辑该课程吗？（0. 否；1. 确认编辑）";
					InputBool(y);
					if (y)
					{
						Edit(currentNode);
						WriteFile(filename);
					}
				}

				if (n == 2)			// 删除课程
				{
					bool y;
					cout << "\n确认要删除该课程吗？（0. 否；1. 确认删除）";
					InputBool(y);
					if (y)
					{
						temp->next = currentNode->next;
						delete currentNode;
						currentNode = temp;
					}
					WriteFile(filename);
				}
			}
			temp = currentNode;
			currentNode = currentNode->next;		// 指向下一个节点
		}
		if (flag)									// 遍历完没找到
			cout << "\n未找到编号为" << input << "的这门课!" << endl;
		if (!n)										// 查找模式
			cout << "\n查找完毕，还需要继续按课程编号进行查找吗？"
			<< "（0. 返回选择查找方式；1. 继续查找课程编号）" << endl;
		else										// 编辑、删除模式
		cout << "\n当前操作已完成，还需要继续" << optname
			<< "吗？（0. 返回；1. 继续" << optname << "）" << endl;
		InputBool(x);				// true继续循环，false退出循环
	}
}

void Course::FindInInt(int choice, const char* optname)
{
	bool flag = 1;
	int input;
	CourseNode* currentNode = m_head->next, * temp = m_head;
	cout << "请输入要查找的"<<optname<<"：";
	InputInt(cin, input);
	DisplayTitle();
	int method;
	while (currentNode != NULL)		// 遍历链表查找
	{
		switch (choice)
		{
		case 1: method = currentNode->id; break;
		case 4: method = currentNode->totaltime; break;
		case 5: method = currentNode->classtime; break;
		case 6: method = currentNode->labtime; break;
		}
		if (method == input)	// 找到则输出
		{
			flag = 0;
			cout << *currentNode << endl;
		}
		temp = currentNode;
		currentNode = currentNode->next;
	}
	if (flag)					// 遍历完成，未找到
		cout << "\n未找到"<<optname<<"为" << input << "的这门课!" << endl;
}

void Course::FindInFloat(int choice, const char* optname)
{
	bool flag = 1;
	float input;
	CourseNode* currentNode = m_head->next, * temp = m_head;
	cout << "请输入要查找的" << optname << "：";
	while (1)
	{
		cin >> input;
		if (!CheckInput(cin)) break;
	}
	DisplayTitle();
	if (choice != 7)		// float类型只有学分，校验choice是否为7，不是则return
		return;
	while (currentNode != NULL)					// 遍历链表查找
	{
		if (currentNode->credits == input)		// 找到则输出
		{
			flag = 0;
			cout << *currentNode << endl;
		}
		temp = currentNode;
		currentNode = currentNode->next;
	}
	if (flag)									// 遍历完成，未找到
		cout << "\n未找到" << optname << "为" << input << "的这门课!" << endl;
}

void Course::FindInString(int choice, const char* optname)
{
	bool flag = 1;
	string input;
	CourseNode* currentNode = m_head->next, * temp = m_head;
	cout << "请输入要查找的" << optname << "：";
	cin >> input;
	DisplayTitle();
	string method;
	while (currentNode != NULL)
	{
		switch (choice)
		{
		case 2: method = currentNode->name; break;
		case 3: method = currentNode->property; break;
		case 8: method = currentNode->semester; break;
		}
		if (method == input)		// 找到则输出
		{ 
 			flag = 0;
			cout << *currentNode << endl;
		}
		temp = currentNode;
		currentNode = currentNode->next;
	}
	if (flag)								// 遍历完成，未找到
	{
		cout << "未找到" << optname << "为" << input << "的这门课!" << endl;
	}
}

void Course::Edit(CourseNode* currentNode)
{
	bool x = 1;
	string temp;
	int choice;
	while (x)
	{
		cout << "请选择要编辑的内容：" << endl;
		cout << "1. 课程编号\t 2. 课程名称\n"
			<< "3. 课程性质\t 4. 总学时  \n"
			<< "5. 授课学时\t 6. 实验学时\n"
			<< "7. 学分    \t 8.开课学期\n"
			<< "0. 取消编辑，返回" << endl;
	inputChoice:
		cin >> choice;
		if (CheckInput(cin))
			goto inputChoice;
		// 将要编辑的内容写入currentNode
		switch (choice)
		{
		case 0:
			return;

		case 1:
			EditMenu(currentNode->id, "课程编号");
			cout << "请输入课程编号："; InputInt(cin,currentNode->id);
			break;

		case 2:
			EditMenu(currentNode->id, "课程名称");
			cout << "请输入课程名称："; cin >> currentNode->name;
			break;

		case 3:
			EditMenu(currentNode->id, "课程性质");
			cout << "请输入课程性质："; cin >> currentNode->property;
			break;

		case 4:
			EditMenu(currentNode->id, "总学时");
			cout << "请输入总学时："; InputInt(cin, currentNode->totaltime);
			break;

		case 5:
			EditMenu(currentNode->id, "授课学时");
			cout << "请输入授课学时："; InputInt(cin, currentNode->classtime);
			break;

		case 6:
			EditMenu(currentNode->id, "实验学时");
			cout << "请输入实验或上机学时："; InputInt(cin, currentNode->labtime);
			break;

		case 7:
			EditMenu(currentNode->id, "学分");
			cout << "请输入学分："; 
			while (1)
			{
				cin >> currentNode->credits;
				if (!CheckInput(cin)) break;
			}
			break;

		case 8:
			EditMenu(currentNode->id, "开课学期");
			cout << "请输入开课学期："; cin >> currentNode->semester;
			break;

		default:
			cout << "输入有误，请输入0~8的数字。" << endl;
			cin.clear();
			cin.ignore(1024, '\n');		// 清除缓冲区
			goto inputChoice;			// 重新输入
		}
		cout << "\n已完成当前项的编辑，还需要编辑其他项吗？（0. 不需要；1. 需要）" << endl;
		InputBool(x);
	}
}

void Course::EditMenu(int id, const char* optname)
{
	system("cls");
	cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▏当前位置：管理员>编辑课程>" << setw(9) << id << ">"
		<< setw(8) << optname << "▕" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
}

bool CheckInput(istream& input)
{
	if (!input.good())		// 类型不对则清除缓冲区，否则cin无法输入，进入死循环
	{
		input.clear();
		input.ignore(1024, '\n');		// 将输入的回车前或1024个字符缓冲区清除
		// input.sync();				// VS2019编译器cin.sync()无法清除缓冲区
		cout << "输入字符不合法，请重试。" << endl;
		return 1;
	}
	return 0;				// 输入正确，返回false
}

void InputBool(bool& x)
{
	while (1)
	{
		cin >> x;
		if (!CheckInput(cin))		// 检查输入数据的类型是否正确，否则重新输入
			break;
	}
}

void InputInt(istream& input, int& x)
{
	// 为方便重载>>时调用此函数，传参intream&
	while (1)
	{
		input >> x;
		if (!CheckInput(cin))		// 检查输入数据的类型是否正确，否则重新输入
			break;
	}
}
