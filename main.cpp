#include "Course.h"
#include "Student.h"
#include "Admin.h"
#include <iomanip>
using namespace std;

void Welcome(Course, const char*);
void AdminMenu(Course, const char*);
void AdminOperationMenu(const char*); 


int main()
{
	const char* filename = "courses.txt";
	Course course(filename);
	while (1)
		Welcome(course, filename);
	cout << "here?" << endl;
	return 0;
}

void Welcome(Course course, const char* filename)
{
	cout << "\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
	cout << "\t\t▏                                            ▕" << endl;
	cout << "\t\t▏           欢迎使用学生选修课程系统         ▕" << endl;
	cout << "\t\t▏                                            ▕" << endl;
	cout << "\t\t▏▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▕" << endl;
	cout << "\t\t▏请选择登录用户：                            ▕" << endl;
	cout << "\t\t▏                                            ▕" << endl;
	cout << "\t\t▏           1. 教师（管理员）登录            ▕" << endl;
	cout << "\t\t▏           2. 学生登录                      ▕" << endl;
	cout << "\t\t▏           0. 退出系统                      ▕" << endl;
	cout << "\t\t▏                                            ▕" << endl;
	cout << "\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
	
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		system("cls");
		AdminMenu(course, filename);
		break;
	}
	case 2:
	{
		system("cls");
		break;
	}
	case 0: exit(0);
	}
}

void AdminMenu(Course course, const char* filename)
{
	while (1)
	{
		system("cls");
		cout << "\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
		cout << "\t\t▏                                            ▕" << endl;
		cout << "\t\t▏           管理员用户，欢迎您！             ▕" << endl;
		cout << "\t\t▏                                            ▕" << endl;
		cout << "\t\t▏▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▕" << endl;
		cout << "\t\t▏请选择下列操作：                            ▕" << endl;
		cout << "\t\t▏                                            ▕" << endl;
		cout << "\t\t▏           1. 添加课程                      ▕" << endl;
		cout << "\t\t▏           2. 查找课程                      ▕" << endl;
		cout << "\t\t▏           3. 编辑课程                      ▕" << endl;
		cout << "\t\t▏           4. 删除课程                      ▕" << endl;
		cout << "\t\t▏           0. 退出登录                      ▕" << endl;
		cout << "\t\t▏                                            ▕" << endl;
		cout << "\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			AdminOperationMenu("添加课程");
			course.AddCourse(filename);
			break;
		case 2:
			AdminOperationMenu("查找课程");
			break;
		case 3:
			AdminOperationMenu("编辑课程");
			break;
		case 4:
			AdminOperationMenu("删除课程");
			break;
		case 0:
			cout << "before ~" << endl;
			return;
		}
	}
}

void AdminOperationMenu(const char optname[9])
{
	system("cls");
	cout << "\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
	cout << "\t\t▏                                            ▕" << endl;
	cout << "\t\t▏您选择的是："<<optname<<"                        ▕" << endl;
	cout << "\t\t▏                                            ▕" << endl;
	cout << "\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
}



