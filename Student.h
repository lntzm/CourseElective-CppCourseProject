#pragma once
#include "Course.h"
using namespace std;

class Student : public Course
{
private:
	int stuid;
	string stuname;
	CourseNode* m_head;

public:
	Student(const char* stufile);
	~Student();
	void Login();
	string GetName();
	void Display();
	void SelectCourse();
	void DisselectCourse();
	void CheckSelection();
};


