#pragma once
#include "Course.h"
using namespace std;

class Student
{
public:
	string stuid;
	string stuname;
	void Login();
	void Display(Course&, Course&);
	void SelectCourse(Course&, Course&);
	void DisselectCourse(Course&);
};


