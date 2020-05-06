#pragma once
#include "Course.h"
using namespace std;

class Student
{
private:
	int id;
	string name;
	int courseid;

public:
	Student();
	~Student();
	void SelectCourse();
	void DisselectCourse();
	void CheckSelection();
};