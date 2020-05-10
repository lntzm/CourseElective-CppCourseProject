#include "Student.h"

Student::Student() : Course("courses.txt")
{
	m_stuhead = new CourseNode;
	m_stuhead->next = NULL;
}

Student::~Student()
{
	CourseNode* currentNode = m_stuhead->next;
	while (currentNode != NULL)
	{
		CourseNode* temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	m_stuhead->next = NULL;
	delete m_stuhead;
	m_stuhead = NULL;
}

void Student::WriteFile(const char* filename)
{
	CourseNode* p = m_stuhead->next;
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
	cout << "成功写入" << filename << "！" << endl;
	ofs.close();
}

void Student::ReadFile(const char* filename)
{
	ifstream ifs(filename);
	if (!ifs)
	{
		cout << "文件以输入流方式打开失败，请检查。" << endl;
		system("pause");
		exit(0);
	}
	CourseNode* temp = m_stuhead;
	while (ifs.peek() != EOF)		//判断是否读取到文件末尾了 采用这个peek函数而不采用ifs.eof()是防止文件为空时还进入循环
	{
		CourseNode* p = new CourseNode;
		ifs >> p->id >> ws
			>> p->name >> ws
			>> p->property >> ws
			>> p->totaltime >> ws
			>> p->classtime >> ws
			>> p->labtime >> ws
			>> p->credits >> ws
			>> p->semester >> ws;

		temp->next = p;
		p->next = NULL;
		temp = p;
	}
}

void Student::Login()
{
	cout << "请输入您的学号："; cin >> stuid;
	cout << "请输入您的姓名："; cin >> stuname;
}

void Student::Init()
{
	string temp = stuid + ".txt";
	const char* stufile = temp.c_str();
	ifstream ifs(stufile);
	if (!ifs)				// 文件不存在
	{
		cout << "未发现学生选课文件！系统将自动创建" << stufile << endl;
		WriteFile(stufile);
		cout << stufile << "创建成功!\n" << endl;
	}
	else
	{
		ReadFile(stufile);
	}
}

string Student::GetName()
{
	return stuname;
}

void Student::Display()
{
	Course::DisplayTitle();
	CourseNode* currentNode = m_stuhead->next;
	while (currentNode != NULL)
	{
		cout << *currentNode << endl;
		currentNode = currentNode->next;
	}
}

void Student::DisplayMore()
{
	int choice;
	cout << "请选择查看方式：(1. 查看已选课程；2. 查看所有课程；3. 一起查看)";
inputChoice:
	cin >> choice;
	if (CheckInput(cin))
		goto inputChoice;
	switch (choice)
	{
	case 1:
		Display();
		break;
	case 2:
		Course::Display();
		break;
	case 3:
		cout << endl;
		cout << setfill('*') << setw(40) << '*' << "已选课程"
			<< setfill('*') << setw(40) << '*' << setfill(' ') << endl;
		Display();
		cout << endl;
		cout << setfill('*') << setw(40) << '*' << "所有课程"
			<< setfill('*') << setw(40) << '*' << setfill(' ') << endl;
		Course::Display();
		break;
	default:
		cout << "请输入1~3的数字，其他数字无效。";
		goto inputChoice;
	}
}

void Student::SelectCourse()
{
	bool x = 1;
	while (x)
	{
		CourseNode* currentCourseNode = Course::m_head->next;
		CourseNode* temp = Course::m_head;
		int input;
		bool flag = 1;
		cout << "请输入您想要选课的课程编号：（输入0可查看所有课程）";
	inputId:
		cin >> input;
		if (CheckInput(cin))
			goto inputId;
		if (!input)
		{
			Course::Display();
			cout << "现在请输入您想要选课的课程编号：";
			goto inputId;
		}
		while (currentCourseNode != NULL)
		{
			if (currentCourseNode->id == input)
			{
				flag = 0;
				cout << *currentCourseNode << endl;
				break;
			}
			temp = currentCourseNode;
			currentCourseNode = currentCourseNode->next;
		}
		if (flag)
		{
			cout << "\n未找到编号为" << input << "的这门课!" << endl;
			continue;
		}
		bool choice;
		cout << "您确定选择这门课吗？（1. 确定；0. 放弃）";
	inputChoice:
		cin >> choice;
		if (CheckInput(cin))
			goto inputChoice;
		if (choice)
		{
			CourseNode* stuTemp = m_stuhead->next;			// 头节点后第一个元素
			CourseNode* newStuNode = currentCourseNode;
			m_stuhead->next = newStuNode;
			newStuNode->next = stuTemp;
		}
		cout << "还要继续选课吗？（0. 不了；1. 继续）" << endl;
	inputX1:
		cin >> x;
		if (CheckInput(cin))
			goto inputX1;
	}
	cout << "操作完成，是否保存？（0. 不保存；1. 保存）" << endl;
inputX2:
	cin >> x;
	if (CheckInput(cin))
		goto inputX2;
	if (x)
	{
		string temp = stuid + ".txt";
		const char* stufile = temp.c_str();
		WriteFile(stufile);
	}
}

void Student::DisselectCourse()
{

}

void Student::CheckSelection()
{

}

