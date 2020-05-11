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
private:
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
	CourseNode();		// 构造函数
	~CourseNode();		// 析构函数
};

class Course
{
	friend class Student;					// 声明友元类
private:
	CourseNode* m_head;						// 链表头
public:
	Course(const char*);					// 构造函数
	~Course();								// 析构函数
	void Display(const char*);				// 查看课程
	void DisplayTitle();					// 显示表头标题
	void AddCourse(const char*);			// 添加课程
	void WriteFile(const char*);			// 链表写入文件
	void ReadFile(const char*);				// 读取文件中的信息建立链表
	void Find(const char*);					// 查找课程，选择查找方式
	void FindMenu(const char*);				// 查找时的菜单，显示当前位置
	void FindEditDelById(int, const char*); // 查、改、删
	void FindInInt(int, const char*);		// 查询方式为整型时的查询
	void FindInFloat(int, const char*);		// 查询方式为浮点型时的查询
	void FindInString(int, const char*);	// 查询方式为字符串时的查询
	void Edit(CourseNode*);					// 编辑课程
	void EditMenu(int, const char*);		// 查找时的菜单，显示当前位置
};

// 以下函数在Student.cpp和main中都可能有调用，实现一些小功能，减少代码冗余，提高利用率
bool CheckInput(istream&);					// 检查输入是否合法，否则清空缓冲区
void InputBool(bool&);						// 输入bool型变量
void InputInt(istream&, int&);				// 输入整型变量

// 以下函数在main.cpp中被调用，在此声明，为一些显示界面
void Welcome();								// 主界面
void AdminMenu(Course&, const char*);		// 管理员界面
void StuMenu(Course&, const char*);			// 学生界面
void OperationMenu(const char*, const char*);	// 操作菜单，显示当前位置