#pragma once
#include "Course.h"
using namespace std;

class Student
{
private:
	int id;
	string name;
	CourseNode* stuhead;

public:
	Student(Course, const char*);
	~Student();
	void Login();
	string GetName();
	void Display(Course);
	void SelectCourse();
	void DisselectCourse();
	void CheckSelection();
};