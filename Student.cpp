#include "Student.h"

void Student::Login()
{
	cout << "请输入您的学号："; cin >> stuid;
	cout << "请输入您的姓名："; cin >> stuname;
}

void Student::Display(Course& course, Course& stucourse)
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
		stucourse.Display();
		break;
	case 2:
		course.Display();
		break;
	case 3:
		cout << endl;
		cout << setfill('*') << setw(40) << '*' << "已选课程"
			<< setfill('*') << setw(40) << '*' << setfill(' ') << endl;
		stucourse.Display();
		cout << endl;
		cout << setfill('*') << setw(40) << '*' << "所有课程"
			<< setfill('*') << setw(40) << '*' << setfill(' ') << endl;
		course.Display();
		break;
	default:
		cout << "请输入1~3的数字，其他数字无效。";
		goto inputChoice;
	}
}

void Student::SelectCourse(Course& course, Course& stucourse)
{
	bool x = 1;
	while (x)
	{
		CourseNode* currentCourseNode = course.m_head->next;
		CourseNode* temp = course.m_head;
		int input;
		bool flag = 1;
		cout << "请输入您想要选课的课程编号：（输入0可查看所有课程）";
	inputId:
		cin >> input;
		if (CheckInput(cin))
			goto inputId;
		if (!input)
		{
			course.Display();
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
			CourseNode* stuTemp = stucourse.m_head->next;			// 头节点后第一个元素
			CourseNode* newStuNode = currentCourseNode;
			stucourse.m_head->next = newStuNode;
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
		stucourse.WriteFile(stufile);
	}
}

void Student::DisselectCourse(Course& stucourse)
{
	bool x = 1;
	while (x)
	{
		CourseNode* currentNode = stucourse.m_head->next;
		CourseNode* temp = stucourse.m_head;
		int input;
		bool flag = 1;
		cout << "请输入您想要退选的课程编号：（输入0可查看所有您已选课程）";
	inputId:
		cin >> input;
		if (CheckInput(cin))
			goto inputId;
		if (!input)
		{
			stucourse.Display();
			cout << "现在请输入您想要退选的课程编号：";
			goto inputId;
		}
		while (currentNode != NULL)
		{
			if (currentNode->id == input)
			{
				flag = 0;
				cout << *currentNode << endl;
				break;
			}
			temp = currentNode;
			currentNode = currentNode->next;
		}
		if (flag)
		{
			cout << "\n未找到编号为" << input << "的这门课!" << endl;
			continue;
		}
		bool choice;
		cout << "您确定选择退选这门课吗？（1. 确定退选；0. 不退了）";
	inputChoice:
		cin >> choice;
		if (CheckInput(cin))
			goto inputChoice;
		if (choice)
		{
			temp->next = currentNode->next;
			delete currentNode;
			currentNode = temp;
		}
		cout << "还要继续退课吗？（0. 不了；1. 继续）" << endl;
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
		stucourse.WriteFile(stufile);
	}
}
