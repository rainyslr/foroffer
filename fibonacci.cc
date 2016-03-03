#include <iostream>
#include <fstream>

using namespace std;

//犯错：定义变量的时候要用long int ，否则溢出
long long int fibonacci(int var)
{
	if(var < 0)
		throw runtime_error("Data must must be not null");
	if(var == 0 || var == 1)
		return 1;
	long int p1 = 1,p2 = 1;
	int index = 2;
	long int result;
	while(index < var)
	{
		result = p1 + p2;
		p2 = p1;
		p1 = result;
		++ index;
	}
	result = p1 + p2;
	return result;
}

int main()
{
	int i = fibonacci(5);
	cout << fibonacci(0) << endl;
	cout << fibonacci(1) << endl;
	cout << fibonacci(2) << endl;
	cout << fibonacci(50) << endl;
	cout << fibonacci(100) << endl;
	//cout << i <<endl;
	return 0;
}