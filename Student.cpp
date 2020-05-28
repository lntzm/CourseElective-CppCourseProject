#include "Student.h"

void Student::Login()
{
	cout << "请输入您的学号："; cin >> stuid;
	cout << "请输入您的姓名："; cin >> stuname;
}

void Student::Display(Course& course, Course& stucourse, const char* filename, const char* stufile)
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
		stucourse.Display(stufile);			// 显示学生选课文件
		break;
	case 2:
		course.Display(filename);			// 显示课程文件
		break;
	case 3:
		cout << endl;
		cout << setfill('*') << setw(40) << '*' << "已选课程"
			<< setfill('*') << setw(40) << '*' << setfill(' ') << endl;
		stucourse.Display(stufile);
		cout << endl;
		cout << setfill('*') << setw(40) << '*' << "所有课程"
			<< setfill('*') << setw(40) << '*' << setfill(' ') << endl;
		course.Display(filename);
		break;
	default:
		cout << "请输入1~3的数字，其他数字无效。";
		goto inputChoice;
	}
}

void Student::SelectCourse(Course& course, Course& stucourse, const char* filename, const char* stufile)
{
	//stucourse.ReadFile(stufile);				// 读取文件，刷新链表
	bool x = 1;
	while (x)
	{
		int input;
		bool flag = 1;						// 标志位
		cout << "请输入您想要选课的课程编号：（输入0可查看所有课程）";
		InputInt(cin, input);
		if (!input)
		{
			course.Display(filename);		// 显示所有课程
			cout << "现在请输入您想要选课的课程编号：";
			InputInt(cin, input);
		}
		CourseNode* currentCourseNode = course.m_head->next;
		CourseNode* temp = course.m_head;
		while (currentCourseNode != NULL)
		{
			if (currentCourseNode->id == input)			// 找到此课程，输出
			{
				flag = 0;
				cout << *currentCourseNode << endl;
				break;							// break，currentNode指向当前课程
			}
			temp = currentCourseNode;
			currentCourseNode = currentCourseNode->next;	// 否则指向下一个
		}
		if (flag)						// 遍历完成，未找到
		{
			cout << "\n未找到编号为" << input << "的这门课!" << endl;
			continue;
		}
		bool choice;
		cout << "您确定选择这门课吗？（1. 确定；0. 放弃）";
		InputBool(choice);
		if (choice)
		{
			CourseNode* stuTemp = stucourse.m_head->next;		// 头节点后第一个元素
			CourseNode* newStuNode = currentCourseNode;			// CourseNode复制到newStuNode
			stucourse.m_head->next = newStuNode;
			newStuNode->next = stuTemp;
		}
		cout << "还要继续选课吗？（0. 不了；1. 继续）";
		InputBool(x);
	}
	cout << "操作完成，是否保存？（0. 不保存；1. 保存）";
	InputBool(x);
	if (x)
	{
		string temp = stuid + ".txt";
		const char* stufile = temp.c_str();
		stucourse.WriteFile(stufile);
	}
}

void Student::UnselectCourse(Course& stucourse, const char* stufile)
{
	bool x = 1;
	while (x)
	{
		int input;
		bool flag = 1;
		cout << "请输入您想要退选的课程编号：（输入0可查看所有您已选课程）";
		InputInt(cin, input);
		if (!input)
		{
			stucourse.Display(stufile);
			cout << "现在请输入您想要退选的课程编号：";
			InputInt(cin, input);
		}
		CourseNode* currentNode = stucourse.m_head->next;
		CourseNode* temp = stucourse.m_head;
		while (currentNode != NULL)
		{
			if (currentNode->id == input)		// 找到此课程输出，并break
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
		InputBool(choice);
		if (choice)
		{
			temp->next = currentNode->next;
			delete currentNode;					// 删除这一节点
			currentNode = temp;
		}
		cout << "还要继续退课吗？（0. 不了；1. 继续）";
		InputBool(x);
	}
	cout << "操作完成，是否保存？（0. 不保存；1. 保存）";
	InputBool(x);
	if (x)
	{
		string temp = stuid + ".txt";
		const char* stufile = temp.c_str();
		stucourse.WriteFile(stufile);
	}
}
