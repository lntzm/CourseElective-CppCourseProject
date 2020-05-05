#include "Admin.h"
using namespace std;

bool Admin::AddCourse(Course course)
{
	CourseNode* temp = course.m_head->next;
	CourseNode* newNode = new CourseNode;
	if (newNode == NULL)
		return false;
	cin >> newNode;
	

}