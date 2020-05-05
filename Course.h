#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct CourseNode
{
	int id;				// 课程编号
	string name;		// 课程名称
	string property;	// 课程性质
	int totaltime;		// 总学时
	int classtime;		// 授课学时
	int labtime;		// 实验或上机学时
	float credits;		// 学分
	string semester;	// 开课学期
	CourseNode* next;
};

class Course
{
	friend class Admin;
	friend class Student;
	friend ostream& operator << (ostream&, CourseNode& node);                      //声明重载“<<”
	friend istream& operator >> (istream&, CourseNode& node);                      //声明重载“>>”
private:
	CourseNode* m_head;

public:
	Course(const char*);
	~Course();
	void FindById(int);
	void FindInInt(int);
	void FindInFloat(float);
	void FindInString(string);
	void WriteFile(const char*);			// 链表写入文件
	void ReadFile(const char*)				// 读取文件中的信息建立链表

};
