#include "Student.h"

Student::Student(const char* stufile) : Course("courses.txt")
{
	Student::m_head = new CourseNode;
	m_head->next = NULL;
	ifstream ifs(stufile);
	if (!ifs)				// 文件不存在
	{
		cout << "未发现学生选课文件！系统将自动创建" << stufile << endl;
		Course::WriteFile(stufile);
		cout << stufile << "创建成功!\n" << endl;
	}
	else
	{
		Course::ReadFile(stufile);
	}
}

Student::~Student()
{

}

void Student::Login()
{

}

string Student::GetName()
{
	return "0";
}

void Student::Display()
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
	{
		Course::DisplayTitle();
		CourseNode* currentNode = Student::m_head->next;
		while (currentNode != NULL)
		{
			cout << *currentNode << endl;
			currentNode = currentNode->next;
		}
		break;
	}
	case 2:
		Course::Display();
		break;
	case 3:
	{
		cout << endl;
		cout << setfill('*') << setw(40) << '*' << "已选课程"
			<< setfill('*') << setw(40) << '*' << setfill(' ') << "\n\n";
		Course::DisplayTitle();
		CourseNode* currentNode = m_head->next;
		while (currentNode != NULL)
		{
			cout << *currentNode << endl;
			currentNode = currentNode->next;
		}
		cout << endl;
		cout << setfill('*') << setw(40) << '*' << "所有课程"
			<< setfill('*') << setw(40) << '*' << setfill(' ') << "\n\n";
		Course::Display();
		break;
	}
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
		CourseNode* temp = m_head->next;			// 头节点后第一个元素
		//CourseNode* newNode = new CourseNode;       // 创建新节点
		//cin >> *newNode;							// 输入数据，>>已被重载

		m_head->next = newNode;
		newNode->next = temp;
		cout << "还要继续添加选课吗？（0. 不添加了；1. 继续添加）" << endl;
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

void Student::DisselectCourse()
{

}

void Student::CheckSelection()
{

}
