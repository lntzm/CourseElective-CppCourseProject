#include <iomanip>
#include "Course.h"

using namespace std;

CourseNode::CourseNode()
{
	next = NULL;
}
CourseNode::~CourseNode()
{
	//id = 0;
	//name = "";
	//property = "";
	//totaltime = 0;
	//classtime = 0;
	//labtime = 0;
	//credits = 0;
	//semester = "";
	next = NULL;
}

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
	else
	{
		ReadFile(filename);
	}
}

// main里函数传参，不能析构
Course::~Course()					//析构，释放申请的内存
{
	//CourseNode* p = m_head->next, * temp;
	//while (p != NULL)
	//{
	//	temp = p;
	//	p = p->next;
	//	delete temp;
	//}
	//delete m_head;
	//m_head = NULL;

	//CourseNode* currentNode = m_head->next;
	//while (currentNode != NULL)
	//{
	//	CourseNode* temp = currentNode->next;
	//	delete currentNode;
	//	currentNode = temp;
	//}
	//m_head->next = NULL;
	//delete m_head;
	//m_head = NULL;
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
	cout << "成功写入" << filename << endl;
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
			>> p->classtime	>> ws
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
	cout << "请输入课程编号："; input >> node.id;
	CheckInput(input);
	cout << "请输入课程名称："; input >> node.name;
	cout << "请输入课程性质："; input >> node.property;
	cout << "请输入总学时："; input >> node.totaltime;
	CheckInput(input);
	cout << "请输入授课学时："; input >> node.classtime;
	CheckInput(input);
	cout << "请输入实验或上机学时："; input >> node.labtime;
	CheckInput(input);
	cout << "请输入学分："; input >> node.credits;
	CheckInput(input);
	cout << "请输入开课学期："; input >> node.semester;
	return input;
}

ostream& operator << (ostream& output, CourseNode& node)
{
	cout << left << setw(10) << node.id << left << setw(15) << node.name
		<< left << setw(4) << node.property << left << setw(4) << node.totaltime
		<< left << setw(4) << node.classtime << left << setw(4) << node.labtime
		<< left << setw(4) << node.credits << left << setw(15) << node.semester << endl;
	return output;
}

void CheckInput(istream& input)
{
	if (!input.good())
	{
		input.clear();
		input.sync();
		throw 1;
	}
}

void Course::AddCourse(const char* filename)
{
	bool x = 1;
	while (x)
	{
		CourseNode* temp = m_head->next;			// 头节点后第一个元素
		CourseNode* newNode = new CourseNode;       // 创建新节点
		gettinginput:
		try 
		{
			cin >> *newNode;
		}
		catch (int)
		{
			cout << "输入数据不合法，请重新输入" << endl;
			goto gettinginput;
		}
		m_head->next = newNode;
		newNode->next = temp;
		cout << "还要继续添加吗？（0. 不添加了；1. 继续添加）" << endl;
		cin >> x;
	}
	cout << "添加完成，是否保存到课程文件？（0. 不保存；1. 保存）\n提示：如果不保存，重启应用数据会丢失。" << endl;
	cin >> x;
	if (x)
	{
		WriteFile(filename);
	}
	else
	{
		return;
	}

}

void Course::Display()
{
	cout << left << setw(10) << "课程编号" << left << setw(15) << "课程名称"
		<< left << setw(4) << "课程性质" << left << setw(4) << "总学时"
		<< left << setw(4) << "授课学时" << left << setw(4) << "实验学时"
		<< left << setw(4) << "学分" << left << setw(15) << "开课学期\n" << endl;
	cout << setfill('-') << setw(60) << endl;

}
