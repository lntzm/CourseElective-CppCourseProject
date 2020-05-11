#pragma once
#include "Course.h"
using namespace std;

class Student					// 为Course的友元类
{
public:
	string stuid;				// 学号
	string stuname;				// 姓名
	void Login();
	void Display(Course&, Course&);			// 学生界面的显示课程
	void SelectCourse(Course&, Course&);	// 选课
	void DisselectCourse(Course&);			// 退课
};


