
//C++标准要求系统提供的头文件不包括扩展名.h，如string，string.h等。

#include "cstdio"		
#include <opencv2\opencv.hpp>
#include <iostream>   // 包含输入输出流库
//#include "string.cpp"
using namespace std;  // 使用标准命名空间




//内联函数在第一次被调用之前必须进行完整的定义

inline double circle(double r)  
{
	double PI = 3.14;
	return PI * r * r;
}

int		add		(int x, int y);
double	add		(double x, double y);
int		add		(int x, int y, int z);
int&	index	(int i);
void	aaa		();



int		value;



/*		类		*/
class Score 
{
	public:
		//隐式声明
		void setScore(int m, int f)
		{
			mid_exam = m;
			fin_exam = f;
		}
		void showScore()
		{
			cout << "期中成绩: " << mid_exam << endl;
			cout << "期末成绩：" << fin_exam << endl;
		}
		int a, b;
	private:

		int mid_exam;
		int fin_exam;
};

//在类的声明中只给出成员函数的原型，而成员函数的定义写在类的外部。这种成员函数在类外定义的一般形式是：
//返回值类型 类名::成员函数名(参数表) { 函数体 }


class MyClass
{
	public:
		//构造函数 主要用于为对象分配空间，进行初始化
		MyClass(int a, int b)
		{
			cout << "构造函数使用中..." << endl;
			max = a;
			min = b;
		}
		//析构函数 没有参数和返回值  
		//通常用于撤销对象时的一些清理任务，如释放分配给对象的内存空间等
		//当对象的生命周期结束时，析构函数会被自动调用 (一般为局部变量）
		~MyClass()
		{
			cout << "析构函数使用中..." << endl;
		}
		void print_ab()
		{
			cout << "max = " << max << endl;
			cout << "min = " << min << endl;
		}
	
	private:
		int max, min;
	
};


class A {
public:
	char name[10];
	int no;
};



int main()
{
	//int x, y;

	////打印
	//cout << "Enter two numbers: " << endl;

	////输入
	////运算符“ >> ”将跳过空白符，然后读入后面与变量类型相对应的值
	//cin >> x >> y;

	//int sum = add(x, y);
	//cout << "The sum is : " << sum << '\n';


	int a = 3, b = 5, c = 7;
	double x = 10.334, y = 8.9003;
	cout << add(a, b) << endl;
	cout << add(x, y) << endl;
	cout << add(a, b, c) << endl;



	//如果希望在局部变量的作用域内使用同名的全局变量，可以在该变量前加上“::”
	//此时::value代表全局变量value，“::”称为作用域标识符。
	int value;  //定义局部变量value
	value = 100;
	::value = 1000;
	cout << "local value : " << value << endl;
	cout << "global value : " << ::value << endl;


	//强制类型转换
	int i = 10;
	x = double(i);

	//new和delete运算符
	int* p;
	p = new int(99);	//分配空间
	p[0] = 1;
	delete p;			//释放空间

	//引用（reference）  又称别名
	int& j = i;
	cout << "i = " << i << "\r\n" << "j = " << j << endl;
	cout << "i的地址为 " << &i << endl;
	cout << "j的地址为 " << &j << endl;
	//i和j的值相同，地址也相同


	index(2) = 100;             //等价于将a[2]的值赋为100;
	cout << "index(2) = " << index(2) << endl;


	//实例化
	Score class_one;

	class_one.a = 10;

	//在定义对象时，若定义的是指向此对象的指针变量，则访问此对象的成员时，不能用“.”操作符，而应该使用“->“操作符。
	//Score* sc;
	//sc ->setScore(12, 13);

	Score myScore;  // 创建 Score 类的一个对象

	myScore.setScore(85, 90);  // 设置期中和期末成绩
	myScore.showScore();       // 显示这些成绩


	MyClass class1(12,14);
	class1.print_ab();


	//对没有定义构造函数的类，其公有数据成员可以用初始值列表进行初始化。
	A asd = { "chen", 23 };
	cout << asd.name << asd.no << endl;

	aaa();

	return 0;
}


int a[] = { 1, 3, 5, 7, 9 };

int& index(int i)
{
	return a[i];
}


int add(int x, int y)
{
	return x + y;
}

double add(double x, double y)
{
	return x - y;
}

int add(int x, int y, int z)
{
	return x + y + z;
}



//class 类名 
//{
//	public：
//		公有数据成员；
//		公有成员函数；
//	protected:
//		保护数据成员；
//		保护成员函数；
//	private:
//		私有数据成员；
//		私有成员函数；
//};





