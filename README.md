# CourseElective-CppCourseProject
This is a cpp course project of EE. 电信学院C++课程设计


## 1.1 程序的总体设计
该项目的程序文件由三个cpp文件以及两个h头文件构成，三个cpp文件分别为两个类文件Course.cpp与Student.cpp，以及一个主程序main.cpp。h头文件用于对主程序中的一些函数、类中的成员函数与成员变量等进行声明，分别为Course.h与Student.h。
该项目的程序结构分为三个类与一个主程序及相关函数。三个类分别为：CourseNode类，用于存放课程编号、课程名称等课程信息；Course类，以链表的方式操作CourseNode类，实现管理员用户对课程的增、删、查、改；Student类，存放学生信息并通过调用Course类的一些方法操作CourseNode类，实现学生用户的选课、退课等操作。主程序中定义了程序的入口，以及有关显示界面、选择与跳转界面的若干函数。
 
图1 该项目的类图
这三个类的类图如图1所示。Course类与Student类均是CourseNode类的友元类，它们可以访问CourseNode类的成员变量，从而获取课程信息；Student类也是Course类的友元类，它可以访问并调用Course类中的一些方法，再封装为自己的成员函数，通过操作不同的Course类对象，完成学生用户的操作。这里，我们选择将Student类定义为Course类的友元类，而不是继承Course类，这是因为如果选择继承Student类，重写父类中的成员函数会导致大量代码重复，这样的设计既不美观优雅，也降低了代码的可读性。我们在主程序的相关函数中新建这些类的对象，调用类的方法，从而完成整个流程，实现学生选修课程系统。
## 1.2 数据结构
程序中采用CourseNode类实现有关课程信息数据的封装，将所有有关课程信息的数据定义为CourseNode类的成员变量，并将另外两个类设置为该类的友元类，实现对数据的访问与操作。
由于课程总数量未知，我们在程序中采用线性链表这一数据结构进行管理，实现灵活的内存管理。链表的结构如图2所示。
 
图2 线性链表结构示意图
在图2中，链表可由头指针m_head唯一确定，而中间每一个结点的指针域next都会指向下一个结点，链表最后一个结点的指针域为空，表示链表的结束。假设p是指向线性表中第i个结点的指针，则p -> next是指向第i + 1个结点的指针，因此，数据通过这种方式链接在了一起。
## 1.3 函数原型声明的说明
### 1.3.1 CourseNode类
(1) 构造函数 CourseNode()
输入参数：无
功能描述：
	指针域置空值。
(2) 析构函数 ~Course()
功能描述：
	指针域置空值。
(3) 友元函数 istream& operator >> (istream& input, CourseNode& node)
输入参数：
	istream& input	>> 的左操作数
	CourseNode& node	>> 的右操作数
输出参数：
	istream& input	>> 的左操作数
返回值：
	istream& input	>> 的左操作数
功能描述：
	重载 >> 操作符，用于输入CourseNode类信息。
(4) 友元函数 ostream& operator << (ostream& output, CourseNode& node)
输入参数：
	ostream& output	>> 的左操作数
	CourseNode& node	>> 的右操作数
输出参数：
	ostream& output	>> 的左操作数
返回值：
	ostream& output	>> 的左操作数
功能描述：
	重载 << 操作符，用于输出CourseNode类信息。
### 1.3.2 Course类
(1) 构造函数 Course(const char* filename)
输入参数：
	const char* filename	保存课程信息的文件名
功能描述：
	创建文件或读取文件信息，建立链表。
(2) 析构函数 ~Course()
功能描述：
	清空链表，释放内存。
(3) void WriteFile(const char* filename)
输入参数：
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	将链表写入文件。
(4) void ReadFile(const char* filename)
输入参数：
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	读取文件信息，建立或更新链表。
(5) void Display(const char* filename)
输入参数：
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	查看课程，将课程信息输出到屏幕。
(6) void DisplayTitle()
输入参数：无
输出参数：无
返回值：无
功能描述：
	显示课程信息的表头。
(7) void AddCourse(const char* filename)
输入参数：
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	向链表中添加新的课程，并写入文件。
(8) void Find(const char* filename)
输入参数：
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	选择查找方式，进行查找链表中某一数据。
(9) void FindMenu(const char* optname)
输入参数：
	const char* optname	选择的查找方式的名称
输出参数：无
返回值：无
功能描述：
	在屏幕上显示当前位置菜单与查找方式。
(10) void FindEditDelById(int n, const char* filename)
输入参数：
	int n	确定当前操作为查找、编辑或删除
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	按课程编号查找课程，并根据需要选择编辑或删除操作。
(11) void FindInInt(int choice, const char* filename)
输入参数：
	int choice	确定当前查找方式
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	查找方式为整型（总学时、授课学时、实验或上机学时），查询课程信息。
(12) void FindInFloat(int choice, const char* optname)
输入参数：
	int choice	确定当前查找方式
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	查找方式为浮点型（学分），查询课程信息。
(13) void FindInString(int choice, const char* filename)	
输入参数：
	int choice	确定当前查找方式
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	查找方式为字符串（课程名称、课程性质、开课学期）的课程信息。
(14) void Edit(CourseNode* currentNode)
输入参数：
	CourseNode * currentNode	类指针，用于指向链表当前结点
输出参数：无
返回值：无
功能描述：
	对特定结点的课程信息进行修改编辑。
(15) void EditMenu(int id, const char* optname)
输入参数：
	int id	当前待编辑的课程编号
	const char* optname	当前编辑的课程信息项
输出参数：无
返回值：无
功能描述：
	在屏幕上显示当前编辑的课程编号与课程信息项。
### 1.3.3 Student类
(1) void Login()
输入参数：无
输出参数：无
返回值：无
功能描述：
	学生用户登录，获取学号与姓名。
(2) void Display(Course& course, Course& stucourse, 
const char* filename, const char* stufile)
输入参数：
	Course& course	Course(filename)对象的引用
	Course& stucourse	Course(stufile)对象的引用
	const char* filename	保存课程信息的文件名（所有课程）
	const char* stufile	保存学生选课信息的文件名
输出参数：无
返回值：无
功能描述：
	学生用户查看所有课程或已选课程。
(3) void SelectCourse(Course& course, Course& stucourse,
 		 const char* filename, const char* stufile)
输入参数：
	Course& course	Course(filename)对象的引用
	Course& stucourse	Course(stufile)对象的引用
	const char* filename	保存课程信息的文件名（所有课程）
	const char* stufile	保存学生选课信息的文件名
输出参数：
	Course& stucourse	Course(stufile)对象的引用
返回值：无
功能描述：
	学生用户进行选课操作。
(4) void UnselectCourse(Course& stucourse, const char* stufile)
输入参数：
	Course& stucourse	Course(stufile)对象的引用
	const char* stufile	保存学生选课信息的文件名
输出参数：
	Course& stucourse	Course(stufile)对象的引用
返回值：无
功能描述：
	学生用户进行退课操作。
### 1.3.4 主程序模块
(1) bool CheckInput(istream& input)
输入参数：
	istream& input	输入流对象的引用
输出参数：
	istream& input	输入流对象的引用
返回值：
	1或0，无变量名	不同条件直接返回true或false
功能描述：
	检查输入流数据是否合法，类型是否一致，否则清空缓冲区。
(2) void InputBool(bool& x)
输入参数：
	bool& x	布尔型变量x的引用
输出参数：
	bool& x	布尔型变量x的引用
返回值：
功能描述：
	输入布尔类变量，不合法时重新输入。
(3) void InputInt(istream& input, int& x)
输入参数：
	istream& input	输入流对象的引用
	bool& x	布尔型变量x的引用
输出参数：
	bool& x	布尔型变量x的引用
返回值：
功能描述：
	输入整型变量，不合法时重新输入。
(4) void Welcome()
输入参数：无
输出参数：无
返回值：无
功能描述：
	欢迎界面，选择用户登录，创建Course对象。
(5) void AdminMenu(Course& course, const char* filename)
输入参数：
	Course& course	Course(filename)对象的引用
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	管理员界面，选择操作类型，调用Course类的方法进行操作。
(6) void StuMenu(Course& course, const char* filename)
输入参数：
	Course& course	Course(filename)对象的引用
	const char* filename	保存课程信息的文件名
输出参数：无
返回值：无
功能描述：
	学生界面，选择操作类型，创建Student对象，调用Student类的方法。
(7) void OperationMenu(const char* usr, const char* optname)
输入参数：
	const char* usr	用户名名称
	const char* optname	当前操作的名称
输出参数：无
返回值：无
功能描述：
	显示当前位置菜单。
(8) int main()
功能描述：
   主函数，程序入口。
