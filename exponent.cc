#include <iostream>
#include <fstream>
#include <string>

#define COMPARE_PRECISION 0.000000001
using namespace std;

//由于精度原因，不能用等号判断两个小数是否相等
//按位与的优先级小于关系判断符

double SimpleExponet(double base,unsigned int abs_exponent);
double AbsExponent(double base,unsigned int abs_exponent);
double EvenExponet(double base,unsigned int even_exponet);
bool equal(double arg1,double arg2);

double Exponent(double base,int exponent)
{
	if(equal(base,0) == true)
	{
		if(exponent == 0)
			throw runtime_error("base is zeroand exponent is negative");
		else if(exponent == 0)
		{
			return 1;
		}
		else return 0;
	}
	else if(equal(exponent,1) == true)
		return 1;
	else
	{
		if(exponent < 0)
		{
			return 1 / AbsExponent(base,-exponent);
		}
		else return AbsExponent(base,exponent);
	}
}

// double SimpleExponet(double base,unsigned int abs_exponent)
// {
// 	double result = 1;
// 	for(int i = 0;i < abs_exponent;++ i)
// 			result *= base;
// 	return result;
// }
// double AbsExponent(double base,unsigned int abs_exponent)
// {
// 	if(abs_exponent % 2 == 0)
// 		return EvenExponet(base,abs_exponent);
// 	else
// 		return EvenExponet(base,abs_exponent)*base;
// }

// double EvenExponet(double base,unsigned int even_exponent)
// {
// 	if(even_exponent == 1)
// 		return base;
// 	else 
// 	{
// 	 	double temp = EvenExponet(base,even_exponent >> 1);
// 	 	return temp * temp;
// 	}
// }

double AbsExponent(double base,unsigned int abs_exponent)
{
	if(abs_exponent == 0)
		return 1;
	else if(abs_exponent == 1)
		return 1;
	double result = AbsExponent(base,abs_exponent >> 1);
	result *= result;
	if((abs_exponent &0x1) == 0)
		return result;
	else
		return result * base;
}

bool equal(double arg1,double arg2)
{
	if(arg1 - arg2 < COMPARE_PRECISION && arg2 - arg1 < COMPARE_PRECISION)//这个地方要用与，因为如果相等两个结果都是零
		return true;
	else return false;
}

int main()
{
	cout << Exponent(0,6) << endl;
	cout << Exponent(-1,4) << endl;
	cout << Exponent(10,-3) << endl;
	double var = 0;
	return 0;
}