#include <iostream>
#include <string>
using namespace std;

namespace Mynamespace
{
	class math
	{
	public:
		math(int par_a, int par_b)
		{
			a = par_a;
			b = par_b;
		}
		int add(void)
		{
			return a + b;
		}
		int multiple(void)
		{
			return a * b;
		}
	private:
		int a;
		int b;

	};
}



void aaa()
{
	string str1 = "ABC";
	string str2("dfdf");
	string str3 = str1 + str2;
	cout << "str1 = " << str1 << "  str2 = " << str2 << "  str3 = " << str3 << endl;
	str2 += str2;
	str3 += "aff";
	cout << "str2 = " << str2 << "  str3 = " << str3 << endl;
	cout << "str1[1] = " << str1[1] << "  str1 == str2 ? " << (str1 == str2) << endl;
	string str = "ABC";
	cout << "str == str1 ? " << (str == str1) << endl;



}


