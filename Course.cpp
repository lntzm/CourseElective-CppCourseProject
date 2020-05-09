#include "Course.h"

using namespace std;

CourseNode::CourseNode()
{
	next = NULL;
}
CourseNode::~CourseNode()
{
	//id = 0;
	//name = "";
	//property = "";
	//totaltime = 0;
	//classtime = 0;
	//labtime = 0;
	//credits = 0;
	//semester = "";
	next = NULL;
}

Course::Course(const char* filename)
{
	m_head = new CourseNode;
	m_head->next = NULL;
	ifstream ifs(filename);
	if (!ifs)				// 文件不存在
	{
		cout << "未发现课程文件！系统将自动创建" << filename << endl;
		WriteFile(filename);
		cout << filename << "创建成功!\n" << endl;
	}
	else
	{
		ReadFile(filename);
	}
}

Course::~Course()					//析构，释放申请的内存
{
	//CourseNode* p = m_head->next, * temp;
	//while (p != NULL)
	//{
	//	temp = p;
	//	p = p->next;
	//	delete temp;
	//}
	//delete m_head;
	//m_head = NULL;

	CourseNode* currentNode = m_head->next;
	while (currentNode != NULL)
	{
		CourseNode* temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	m_head->next = NULL;
	delete m_head;
	m_head = NULL;
}

void Course::WriteFile(const char* filename)
{
	CourseNode* p = m_head->next;
	ofstream ofs(filename);
	if (!ofs)
	{
		cout << "文件以输出流方式打开或创建失败，请检查。" << endl;
		system("pause");
		exit(0);
	}
	if (p == NULL)
		return;
	while (p != NULL)
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
	ifstream ifs(filename);
	if (!ifs)
	{
		cout << "文件以输入流方式打开失败，请检查。" << endl;
		system("pause");
		exit(0);
	}
	CourseNode* temp = m_head;
	while (ifs.peek() != EOF)		//判断是否读取到文件末尾了 采用这个peek函数而不采用ifs.eof()是防止文件为空时还进入循环
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
		temp = p;
	}
}

istream& operator >> (istream& input, CourseNode& node)
{
inputId:
	cout << "请输入课程编号："; input >> node.id;
	if (CheckInput(input))
		goto inputId;
	cout << "请输入课程名称："; input >> node.name;
	cout << "请输入课程性质："; input >> node.property;
inputTotaltime:
	cout << "请输入总学时："; input >> node.totaltime;
	if (CheckInput(input))
		goto inputTotaltime;
inputClasstime:
	cout << "请输入授课学时："; input >> node.classtime;
	if (CheckInput(input))
		goto inputClasstime;
inputLabtime:
	cout << "请输入实验或上机学时："; input >> node.labtime;
	if (CheckInput(input))
		goto inputLabtime;
inputCredits:
	cout << "请输入学分："; input >> node.credits;
	if (CheckInput(input))
		goto inputCredits;
	cout << "请输入开课学期："; input >> node.semester;
	return input;
}

ostream& operator << (ostream& output, CourseNode& node)
{
	cout << left << setw(10) << node.id << left << setw(20) << node.name
		<< left << setw(10) << node.property << left << setw(8) << node.totaltime
		<< left << setw(10) << node.classtime << left << setw(10) << node.labtime
		<< left << setw(6) << node.credits << left << setw(18) << node.semester;
	return output;
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
	return 0;
}

void Course::Display()
{
	DisplayTitle();
	CourseNode* currentNode = m_head->next;
	while (currentNode != NULL)
	{
		cout << *currentNode << endl;
		currentNode = currentNode->next;
	}
}

void Course::DisplayTitle()
{
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
		newNode->next = temp;
		cout << "还要继续添加吗？（0. 不添加了；1. 继续添加）" << endl;
	inputX1:
		cin >> x;
		if (CheckInput(cin))
			goto inputX1;
	}
	cout << "添加完成，是否保存到课程文件？（0. 不保存；1. 保存）\n提示：如果不保存，数据会丢失。" << endl;
inputX2:
	cin >> x;
	if (CheckInput(cin))
		goto inputX2;
	if (x)
	{
		WriteFile(filename);
	}
}

void Course::Find()
{
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
		cin >> choice;
		if (CheckInput(cin))			
			goto inputChoice;
		switch (choice)
		{
		case 0:
			return;
		case 1:
			goto findById;
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
	inputX:
		cin >> x;					// x为true时继续循环，false退出循环
		if (CheckInput(cin))
			goto inputX;

	}
	while (0)			// 确保正常情况程序跳过执行该语句，只有goto能够访问
	{
	findById:
		FindEditDelById(0, "");
	}
	
}

void Course::FindMenu(const char* optname)
{
	system("cls");
	cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▏当前位置：管理员>查找课程>" 
		<<setw(10)<< optname << "        ▕" << endl;
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
		if (!n)
			FindMenu("按课程编号");
		bool flag = 1;
		int input;
		CourseNode* currentNode = m_head->next, * temp = m_head;
		
		cout << "请输入要" << optname << "的课程编号：";
	inputInput:
		cin >> input;
		if (CheckInput(cin))
			goto inputInput;
		DisplayTitle();
		while (currentNode != NULL)
		{
			if (currentNode->id == input)
			{
				flag = 0;
				cout << *currentNode << endl;

				if (n == 1)			// 编辑课程
				{
					bool y;
					cout << "确认要编辑该课程吗？（0. 否；1. 确认编辑）";
				inputY1:
					cin >> y;
					if (CheckInput(cin))
						goto inputY1;
					if (y == true)
					{
						Edit(currentNode);
					}
					WriteFile(filename);
				}

				if (n == 2)			// 删除课程
				{
					bool y;
					cout << "确认要删除该课程吗？（0. 否；1. 确认删除）";
				inputY2:
					cin >> y;
					if (CheckInput(cin))
						goto inputY2;
					if (y == true)
					{
						temp->next = currentNode->next;
						delete currentNode;
						currentNode = temp;
					}
					WriteFile(filename);
				}
			}
			temp = currentNode;
			currentNode = currentNode->next;
		}
		if (flag)
		{
			cout << "\n未找到id为" << input << "的这门课!" << endl;
		}
		cout << "\n当前操作已完成，还需要继续" << optname
			<< "吗？（0. 返回；1. 继续" << optname << "）" << endl;
	inputX:
		cin >> x;
		if (CheckInput(cin))
			goto inputX;
	}
	
}

void Course::FindInInt(int choice, const char* optname)
{
	bool flag = 1;
	int input;
	CourseNode* currentNode = m_head->next, * temp = m_head;
	cout << "请输入要查找的"<<optname<<"：";
inputInput:
	cin >> input;
	if (CheckInput(cin))
		goto inputInput;
	DisplayTitle();
	while (currentNode != NULL)
	{
		switch (choice)
		{
		case 1:
			if (currentNode->id == input)
			{
				flag = 0;
				cout << *currentNode << endl;
			}
			temp = currentNode;
			currentNode = currentNode->next;
			break;

		case 4:
			if (currentNode->totaltime == input)
			{
				flag = 0;
				cout << *currentNode << endl;
			}
			temp = currentNode;
			currentNode = currentNode->next;
			break;

		case 5:
			if (currentNode->classtime == input)
			{
				flag = 0;
				cout << *currentNode << endl;
			}
			temp = currentNode;
			currentNode = currentNode->next;
			break;

		case 6:
			if (currentNode->labtime == input)
			{
				flag = 0;
				cout << *currentNode << endl;
			}
			temp = currentNode;
			currentNode = currentNode->next;
			break;
		}
	}
	if (flag)
	{
		cout << "\n未找到"<<optname<<"为" << input << "的这门课!" << endl;
	}
}

void Course::FindInFloat(int choice, const char* optname)
{
	bool flag = 1;
	float input;
	CourseNode* currentNode = m_head->next, * temp = m_head;
	cout << "请输入要查找的" << optname << "：";
inputInput:
	cin >> input;
	if (CheckInput(cin))
		goto inputInput;
	DisplayTitle();
	if (choice != 7)
		return;
	while (currentNode != NULL)
	{
		if (currentNode->credits == input)
		{
			flag = 0;
			cout << *currentNode << endl;
		}
		temp = currentNode;
		currentNode = currentNode->next;
	}
	if (flag)
	{
		cout << "\n未找到" << optname << "为" << input << "的这门课!" << endl;
	}
}

void Course::FindInString(int choice, const char* optname)
{
	bool flag = 1;
	string input;
	CourseNode* currentNode = m_head->next, * temp = m_head;
	cout << "请输入要查找的" << optname << "：";
	cin >> input;
	DisplayTitle();
	while (currentNode != NULL)
	{
		switch (choice)
		{
		case 2:
			if (currentNode->name == input)
			{
				flag = 0;
				cout << *currentNode << endl;
			}
			temp = currentNode;
			currentNode = currentNode->next;
			break;

		case 3:
			if (currentNode->property == input)
			{
				flag = 0;
				cout << *currentNode << endl;
			}
			temp = currentNode;
			currentNode = currentNode->next;
			break;

		case 8:
			if (currentNode->semester == input)
			{
				flag = 0;
				cout << *currentNode << endl;
			}
			temp = currentNode;
			currentNode = currentNode->next;
			break;
		}
	}
	if (flag)
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
		switch (choice)
		{
		case 0:
			return;

		case 1:
			EditMenu(currentNode->id, "课程编号");
		inputId:
			cout << "请输入课程编号："; cin >> currentNode->id;
			if (CheckInput(cin))
				goto inputId;
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
		inputTotaltime:
			cout << "请输入总学时："; cin >> currentNode->totaltime;
			if (CheckInput(cin))
				goto inputTotaltime;
			break;

		case 5:
			EditMenu(currentNode->id, "授课学时");
		inputClasstime:
			cout << "请输入授课学时："; cin >> currentNode->classtime;
			if (CheckInput(cin))
				goto inputClasstime;
			break;

		case 6:
			EditMenu(currentNode->id, "实验学时");
		inputLabtime:
			cout << "请输入实验或上机学时："; cin >> currentNode->labtime;
			if (CheckInput(cin))
				goto inputLabtime;
			break;

		case 7:
			EditMenu(currentNode->id, "学分");
		inputCredits:
			cout << "请输入学分："; cin >> currentNode->credits;
			if (CheckInput(cin))
				goto inputCredits;
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
	inputX:
		cin >> x;
		if (CheckInput(cin))
			goto inputX;
	}
}

void Course::EditMenu(int id, const char* optname)
{
	system("cls");
	cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▏当前位置：管理员>编辑课程>" << setw(9) << id << "<"
		<< setw(8) << optname << " ▕" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
}