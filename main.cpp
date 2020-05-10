#include "Course.h"
#include "Student.h"
using namespace std;

void Welcome();
void AdminMenu(const char*);
void StuMenu(const char*);
void OperationMenu(const char*, const char*);


int main()
{
	while (1)
		Welcome();
	return 0;
}

void Welcome()
{
	system("cls");
	cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▏           欢迎使用学生选修课程系统         ▕" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▏▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▕" << endl;
	cout << "\t\t\t▏请选择登录用户：                            ▕" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▏           1. 教师（管理员）登录            ▕" << endl;
	cout << "\t\t\t▏           2. 学生登录                      ▕" << endl;
	cout << "\t\t\t▏           0. 退出系统                      ▕" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
	
	const char* filename = "courses.txt";
	int choice;
inputChoice:
	cin >> choice;
	if (CheckInput(cin))
		goto inputChoice;
	switch (choice)
	{
	case 1:
		system("cls");
		AdminMenu(filename);
		break;
	case 2:
		system("cls");
		StuMenu(filename);
		break;
	case 0: exit(0);
	default:
		cout << "请输入0~2，其他数字无效。" << endl;
		goto inputChoice;
	}
}

void AdminMenu(const char* filename)
{
	while (1)
	{
		system("cls");
		Course course(filename);
		
		cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▏           管理员用户，欢迎您！             ▕" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▏▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▕" << endl;
		cout << "\t\t\t▏请选择下列操作：                            ▕" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▏           1. 查看课程                      ▕" << endl;
		cout << "\t\t\t▏           2. 添加课程                      ▕" << endl;
		cout << "\t\t\t▏           3. 查找课程                      ▕" << endl;
		cout << "\t\t\t▏           4. 编辑课程                      ▕" << endl;
		cout << "\t\t\t▏           5. 删除课程                      ▕" << endl;
		cout << "\t\t\t▏           0. 退出登录                      ▕" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
			
		int choice;
	inputChoice:
		cin >> choice;
		if (CheckInput(cin))
			goto inputChoice;
		switch (choice)
		{
		case 1:
			OperationMenu("管理员", "查看课程");
			course.Display();
			cout << "回车或输入任意字符返回管理员主界面。" << endl;
			getchar();
			getchar();
			break;
		case 2:
			OperationMenu("管理员", "添加课程");
			course.AddCourse(filename);
			break;
		case 3:
			OperationMenu("管理员", "查找课程");
			course.Find();
			break;
		case 4:
			OperationMenu("管理员", "编辑课程");
			course.FindEditDelById(1, filename);
			break;
		case 5:
			OperationMenu("管理员", "删除课程");
			course.FindEditDelById(2, filename);
			break;
		case 0:
			return;
		default:
			cout << "请输入数字0~5，其他数字无效。" << endl;
			goto inputChoice;
		}
	}
}

void StuMenu(const char* filename)
{
	Student student;
	student.Login();
	student.Init();
	string name = student.GetName();
	while (1)
	{
		system("cls");
		Course course(filename);

		cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▏           " << right << setw(6) << name
			<< "同学，欢迎您！             ▕" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▏▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▕" << endl;
		cout << "\t\t\t▏请选择下列操作：                            ▕" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▏           1. 查看课程                      ▕" << endl;
		cout << "\t\t\t▏           2. 查找课程                      ▕" << endl;
		cout << "\t\t\t▏           3. 选课                          ▕" << endl;
		cout << "\t\t\t▏           4. 退课                          ▕" << endl;
		cout << "\t\t\t▏           0. 退出登录                      ▕" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;

		int choice;
	inputChoice:
		cin >> choice;
		if (CheckInput(cin))
			goto inputChoice;
		switch (choice)
		{
		case 1:
		{
			bool x = 1;
			while (x)
			{
				OperationMenu("学生", "查看课程");
				student.DisplayMore();
				cout << "\n还需要继续查看吗？(1. 继续；0. 返回学生主界面)";
			inputX:
				cin >> x;
				if (CheckInput(cin))
					goto inputX;
			}
			break;
		}
		case 2:
			OperationMenu("学生", "查找课程");
			course.Find();
			break;
		case 3:
			OperationMenu("学生", "选课");
			student.SelectCourse();
			break;
		case 4:
			OperationMenu("学生", "退课");
			student.DisselectCourse();
			break;
		case 0:
			return;
		default:
			cout << "请输入数字0~4，其他数字无效。" << endl;
			goto inputChoice;
		}
	}
}

void OperationMenu(const char* usr, const char* optname)
{
	system("cls");
	cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▏当前位置：" << left << setw(6) << usr << ">"
		<< left << setw(8) << optname << "                   ▕" << endl;
	cout << "\t\t\t▏                                            ▕" << endl;
	cout << "\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
}



