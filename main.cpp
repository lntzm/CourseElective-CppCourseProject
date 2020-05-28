#include "Course.h"
#include "Student.h"
using namespace std;

int main()
{
	while (1)
		Welcome();
	return 0;
}

void Welcome()
{
	const char* filename = "courses.txt";			// 课程文件命名
	Course course(filename);
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
	
	int choice;
	while (1)
	{
		cin >> choice;
		if (CheckInput(cin))
			continue;
		switch (choice)
		{
		case 1:
			system("cls");
			AdminMenu(course, filename);
			return;			// return是为了跳出while循环
		case 2:
			system("cls");
			StuMenu(course, filename);
			return;
		case 0: exit(0);
		default:
			cout << "请输入0~2，其他数字无效。" << endl;
			continue;
		}
	}
}

void AdminMenu(Course& course, const char* filename)
{
	while (1)
	{
		system("cls");
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
	inputChoice:				// 为方便下方switch中default的调用，使用goto
		cin >> choice;
		if (CheckInput(cin))
			goto inputChoice;
		switch (choice)
		{
		case 1:
			OperationMenu("管理员", "查看课程");
			course.Display(filename);
			cout << "回车或输入任意字符返回管理员主界面。" << endl;
			getchar();			// 等待输入字符
			getchar();
			break;
		case 2:
			OperationMenu("管理员", "添加课程");
			course.AddCourse(filename);
			break;
		case 3:
			OperationMenu("管理员", "查找课程");
			course.Find(filename);
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
			// switch外已经有一层while，再使用循环不方便break出循环，需要增加判断的变量
			goto inputChoice;			// 因此这里采用goto，且并没有降低可读性
		}
	}
}

void StuMenu(Course& course, const char* filename)
{
	system("cls");
	Student student;
	student.Login();						// 登录，获取学号与姓名
	string temp = student.stuid + ".txt";	// 该学生选课文件，以学号命名
	const char* stufile = temp.c_str();		// string 转 const char*
	Course stucourse(stufile);
	while (1)
	{
		cout << "\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁" << endl;
		cout << "\t\t\t▏                                            ▕" << endl;
		cout << "\t\t\t▏           " << right << setw(6) << student.stuname
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
	inputChoice:		// 下方有两处goto调用此处
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
				student.Display(course, stucourse, filename, stufile);
				cout << "\n还需要继续查看吗？(1. 继续；0. 返回学生主界面)";
				InputBool(x);
				system("cls");
			}
			break;
		}
		case 2:
			OperationMenu("学生", "查找课程");
			course.Find(filename);
			system("cls");
			break;
		case 3:
			OperationMenu("学生", "选课");
			student.SelectCourse(course, stucourse, filename, stufile);
			system("cls");
			break;
		case 4:
			OperationMenu("学生", "退课");
			student.UnselectCourse(stucourse, stufile);
			system("cls");
			break;
		case 0:
			return;
		default:
			cout << "请输入数字0~4，其他数字无效。" << endl;
			goto inputChoice;			// 同AdminMenu()，使用goto
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
