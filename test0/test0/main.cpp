
//C++��׼Ҫ��ϵͳ�ṩ��ͷ�ļ���������չ��.h����string��string.h�ȡ�

#include "cstdio"		
#include <opencv2\opencv.hpp>
#include <iostream>   // ���������������
//#include "string.cpp"
using namespace std;  // ʹ�ñ�׼�����ռ�




//���������ڵ�һ�α�����֮ǰ������������Ķ���

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



/*		��		*/
class Score 
{
	public:
		//��ʽ����
		void setScore(int m, int f)
		{
			mid_exam = m;
			fin_exam = f;
		}
		void showScore()
		{
			cout << "���гɼ�: " << mid_exam << endl;
			cout << "��ĩ�ɼ���" << fin_exam << endl;
		}
		int a, b;
	private:

		int mid_exam;
		int fin_exam;
};

//�����������ֻ������Ա������ԭ�ͣ�����Ա�����Ķ���д������ⲿ�����ֳ�Ա���������ⶨ���һ����ʽ�ǣ�
//����ֵ���� ����::��Ա������(������) { ������ }


class MyClass
{
	public:
		//���캯�� ��Ҫ����Ϊ�������ռ䣬���г�ʼ��
		MyClass(int a, int b)
		{
			cout << "���캯��ʹ����..." << endl;
			max = a;
			min = b;
		}
		//�������� û�в����ͷ���ֵ  
		//ͨ�����ڳ�������ʱ��һЩ�����������ͷŷ����������ڴ�ռ��
		//��������������ڽ���ʱ�����������ᱻ�Զ����� (һ��Ϊ�ֲ�������
		~MyClass()
		{
			cout << "��������ʹ����..." << endl;
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

	////��ӡ
	//cout << "Enter two numbers: " << endl;

	////����
	////������� >> ���������հ׷���Ȼ��������������������Ӧ��ֵ
	//cin >> x >> y;

	//int sum = add(x, y);
	//cout << "The sum is : " << sum << '\n';


	int a = 3, b = 5, c = 7;
	double x = 10.334, y = 8.9003;
	cout << add(a, b) << endl;
	cout << add(x, y) << endl;
	cout << add(a, b, c) << endl;



	//���ϣ���ھֲ���������������ʹ��ͬ����ȫ�ֱ����������ڸñ���ǰ���ϡ�::��
	//��ʱ::value����ȫ�ֱ���value����::����Ϊ�������ʶ����
	int value;  //����ֲ�����value
	value = 100;
	::value = 1000;
	cout << "local value : " << value << endl;
	cout << "global value : " << ::value << endl;


	//ǿ������ת��
	int i = 10;
	x = double(i);

	//new��delete�����
	int* p;
	p = new int(99);	//����ռ�
	p[0] = 1;
	delete p;			//�ͷſռ�

	//���ã�reference��  �ֳƱ���
	int& j = i;
	cout << "i = " << i << "\r\n" << "j = " << j << endl;
	cout << "i�ĵ�ַΪ " << &i << endl;
	cout << "j�ĵ�ַΪ " << &j << endl;
	//i��j��ֵ��ͬ����ַҲ��ͬ


	index(2) = 100;             //�ȼ��ڽ�a[2]��ֵ��Ϊ100;
	cout << "index(2) = " << index(2) << endl;


	//ʵ����
	Score class_one;

	class_one.a = 10;

	//�ڶ������ʱ�����������ָ��˶����ָ�����������ʴ˶���ĳ�Աʱ�������á�.������������Ӧ��ʹ�á�->����������
	//Score* sc;
	//sc ->setScore(12, 13);

	Score myScore;  // ���� Score ���һ������

	myScore.setScore(85, 90);  // �������к���ĩ�ɼ�
	myScore.showScore();       // ��ʾ��Щ�ɼ�


	MyClass class1(12,14);
	class1.print_ab();


	//��û�ж��幹�캯�����࣬�乫�����ݳ�Ա�����ó�ʼֵ�б���г�ʼ����
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



//class ���� 
//{
//	public��
//		�������ݳ�Ա��
//		���г�Ա������
//	protected:
//		�������ݳ�Ա��
//		������Ա������
//	private:
//		˽�����ݳ�Ա��
//		˽�г�Ա������
//};





