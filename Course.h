#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class CourseNode
{
	friend ostream& operator << (ostream&, CourseNode& node);           // 重载<<
	friend istream& operator >> (istream&, CourseNode& node);	        // 重载>>
	friend class Course;
	friend class Student;												// 两个友元类，方便调用
protected:
	int id;				// 课程编号
	string name;		// 课程名称
	string property;	// 课程性质
	int totaltime;		// 总学时
	int classtime;		// 授课学时
	int labtime;		// 实验或上机学时
	float credits;		// 学分
	string semester;	// 开课学期
	CourseNode* next;	// 用于链表，指向下一节点
public:
	CourseNode();
	~CourseNode();		// 构造与析构
};

class Course
{
	friend class Student;
protected:
	CourseNode* m_head;						// 链表头
public:
	Course(const char*);
	~Course();
	void Display();							// 查看课程
	void DisplayTitle();
	void AddCourse(const char*);			// 添加课程
	void WriteFile(const char*);			// 链表写入文件
	void ReadFile(const char*);				// 读取文件中的信息建立链表
	void Find();							// 查找课程，选择查找方式
	void FindMenu(const char*);
	void FindEditDelById(int, const char*); // 查、改、删
	void FindInInt(int, const char*);
	void FindInFloat(int, const char*);
	void FindInString(int, const char*);
	void Edit(CourseNode*);					// 编辑课程
	void EditMenu(int, const char*);
};

bool CheckInput(istream&);					// 检查输入是否合法，否则清空缓冲区