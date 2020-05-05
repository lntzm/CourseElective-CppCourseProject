#pragma once
#include <iostream>
#include <string>
#include "Course.h"
using namespace std;

class Admin
{
	friend ostream& operator << (ostream&, CourseNode& node);                      //ÉùÃ÷ÖØÔØ¡°<<¡±
	friend istream& operator >> (istream&, CourseNode& node);
public:
	bool AddCourse(Course);
	void EditCourse();
	void DeleteCourse();
	
};