#pragma once
#include "Course.h"
using namespace std;

class Student					// 为Course的友元类
{
public:
	string stuid;				// 学号
	string stuname;				// 姓名
	void Login();				// 登录，获取学号与姓名
	void Display(Course&, Course&, const char*, const char*);		// 学生界面的显示课程
	void SelectCourse(Course&, Course&, const char*, const char*);	// 选课
	void UnselectCourse(Course&, const char*);			// 退课
};


