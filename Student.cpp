#include "Student.h"

Student::Student(Course course, const char* filename)
{
	stuhead = new CourseNode;
	stuhead->next = NULL;
	ifstream ifs(filename);
	if (!ifs)				// 文件不存在
	{
		cout << "未发现课程文件！系统将自动创建" << filename << endl;
		course.WriteFile(filename);
		cout << filename << "创建成功!\n" << endl;
	}
	else
	{
		course.ReadFile(filename);
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

void Student::Display(Course course)
{
	course.DisplayTitle();
	CourseNode* currentNode = course.m_head->next;
	while (currentNode != NULL)
	{
		cout << *currentNode << endl;
		currentNode = currentNode->next;
	}

	cout << "\n输入任意字符返回管理员主界面。" << endl;
	getchar();
	getchar();
}
void Student::SelectCourse()
{

}

void Student::DisselectCourse()
{

}

void Student::CheckSelection()
{

}
