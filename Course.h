#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class CourseNode
{
	friend ostream& operator << (ostream&, CourseNode& node);          // 重载<<
	friend istream& operator >> (istream&, CourseNode& node);	       // 重载>>
	friend class Course;
	friend class Student;
protected:
	int id;				// 课程编号
	string name;		// 课程名称
	string property;	// 课程性质
	int totaltime;		// 总学时
	int classtime;		// 授课学时
	int labtime;		// 实验或上机学时
	float credits;		// 学分
	string semester;	// 开课学期
	CourseNode* next;
public:
	CourseNode();
	~CourseNode();
};

class Course
{
	friend class Student;
protected:
	CourseNode* m_head;
public:
	Course(const char*);
	~Course();
	void Display();
	void DisplayTitle();
	void AddCourse(const char*);
	void WriteFile(const char*);			// 链表写入文件
	void ReadFile(const char*);				// 读取文件中的信息建立链表
	void Find();
	void FindMenu(const char*);
	void FindEditDelById(int, const char*);
	void FindInInt(int, const char*);
	void FindInFloat(int, const char*);
	void FindInString(int, const char*);
	void Edit(CourseNode*);
	void EditMenu(int, const char*);
};

bool CheckInput(istream&);