#include "Course.h"
using namespace std;

Course::Course(const char* filename)
{
	m_head = new CourseNode;
	m_head->next = NULL;
	ifstream ifs(filename);
	if (!ifs)				// 文件不存在
	{
		cout << "未发现课程文件！系统将自动创建" << filename << endl;
		WriteFile(filename);
		cout << filename << "创建成功!\n\n" << endl;
	}
}

Course::~Course()					//析构，释放申请的内存
{
	CourseNode* p = m_head->next, * temp;
	while (p != NULL)
	{
		temp = p;
		p = p->next;
		delete temp;
	}
	delete m_head;
	m_head = NULL;
}

void Course::WriteFile(const char* filename)
{
	CourseNode* p = m_head->next;
	ofstream ofs(filename);
	if (!ofs)
	{
		cout << "文件以输出流方式打开或创建失败，请检查。" << endl;
		system("pause");
		exit(0);
	}
	while (p != NULL)
	{
		ofs << p->id << '\t' << p->name << '\t' << p->property << '\t'
			<< p->totaltime << '\t' << p->classtime << '\t' << p->labtime << '\t'
			<< p->credits << '\t' << p->semester << '\t' << endl;
		p = p->next;
	}
	ofs.close();
}

void Course::ReadFile(const char* filename)	
{
	ifstream ifs(filename);
	if (!ifs)
	{
		cout << "文件以输入流方式打开失败，请检查。" << endl;
		system("pause");
		exit(0);
	}
	CourseNode* temp = m_head;
	while (ifs.peek() != EOF)		//判断是否读取到文件末尾了 采用这个peek函数而不采用ifs.eof()是防止文件为空时还进入循环
	{
		CourseNode* p = new CourseNode;
		ifs >> p->id >> ws
			>> p->name >> ws
			>> p->property >> ws
			>> p->totaltime >> ws
			>> p->labtime >> ws
		    >> p->credits >> ws
			>> p->semester >> ws;

		temp->next = p;
		p->next = NULL;
		temp = p;
	}
}

istream& operator >> (istream& input, CourseNode& node)
{
	a1:
	cout << "请输入课程编号："; input >> node.id;
	if (CheckInput(input))
		goto a1;
	cout << "请输入课程名称："; input >> node.name;
	cout << "请输入课程性质："; input >> node.property;
	a2:
	cout << "请输入总学时："; input >> node.totaltime;
	if (CheckInput(input))
		goto a2;
	a3:
	cout << "请输入授课学时："; input >> node.classtime;
	if (CheckInput(input))
		goto a3;
	a4:
	cout << "请输入实验或上机学时："; input >> node.labtime;
	if (CheckInput(input))
		goto a4;
	a5:
	cout << "请输入学分："; input >> node.credits;
	if (CheckInput(input))
		goto a5;
	cout << "请输入开课学期："; input >> node.semester;
	return input;
}

bool CheckInput(istream& input)
{
	if (!input.good())
	{
		input.clear();
		input.sync();
		cout<<"输入数据不合法，请重新输入";
		return true;
	}
	return false;
}
