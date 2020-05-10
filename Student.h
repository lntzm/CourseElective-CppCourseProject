#pragma once
#include "Course.h"
using namespace std;

class Student : public Course
{
private:
	string stuid;
	string stuname;
	CourseNode* m_stuhead;

public:
	Student();
	~Student();
	void WriteFile(const char* filename);
	void ReadFile(const char* filename);
	void Login();
	void Init();
	string GetName();
	void Display();
	void DisplayMore();
	void SelectCourse();
	void DisselectCourse();
	void CheckSelection();
};


