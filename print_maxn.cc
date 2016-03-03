#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ofstream ouf;

//犯错：忽略了输入为零的情况

void FindSize()
{
	cout << "sizeof(char):" << sizeof(char) << std::endl;
	cout << "sizeof(short int):" << sizeof(short) << std::endl;
	cout << "sizeof(int):" << sizeof(int) << std::endl;
	cout << "sizeof(long int):" << sizeof(long int) << std::endl;
	cout << "sizeof(long long int):" << sizeof(long long int) << std::endl;
	cout << "sizeof(float):" << sizeof(float) << std::endl;
	cout << "sizeof(double):" << sizeof(double) << std::endl;
	cout << "sizeof(long double):" << sizeof(long double) << std::endl;
}

void print_with_prefix(ostream & os,char num[])
{

	os<< num << endl;
}

void print_without_prefix(ostream & os,char num[])
{
	int index = 0;
	while(num[index] == '0')
		++ index;
	os<< num + index << endl;
}

int Increase(int n,char num[])
{
	int index = n - 1;
	int carry = 1;
	while(carry && index >= 0)
	{
		int temp = num[index] + carry - '0';
		num[index] = temp % 10 + '0';
		carry = temp / 10;
		index --;
	}
	return !carry;
}

void func(int n)
{
	if(n <= 0)
		throw runtime_error("digit capacity shuld be positive");
	char *num = new char[n + 1];
	if(num == NULL)
		throw runtime_error("cant alloc space");
	memset(num,'0',n);
	num[n] = 0;
	ofstream ouf("output.txt");
	if(!ouf)
	{
		cout << "open output file error" << endl;
		return ;
	}
	while(Increase(n,num) != 0)
	{
		//print_with_prefix(ouf,num);
		print_without_prefix(ouf,num);
	}

}

void PrintMaxNRecursively(char num[],int length,int index)
{

	if(index == length - 1)
		print_without_prefix(ouf,num);
	else
	{
		for(int j = 0;j < 10;++ j)
		{
			num[index + 1] = '0' + j;
			PrintMaxNRecursively(num,length,index + 1);
		}
		
	}
}

void PrintMaxN(int n)
{

	if(n <= 0)
		throw runtime_error("digit capacity shuld be positive");
	char *num = new char[n + 1];
	if(num == NULL)
		throw runtime_error("cant alloc space");

	num[n] = 0;
	for(int i = 0;i < 10;i ++)
	{
		num[0] = '0' + i;
		PrintMaxNRecursively(num,n,0);
	}
}



int main()
{
	ouf.open("output.txt");
	if(!ouf)
	{
		cout << "open output file error" << endl;
		return -1;
	}
	//func(2);
	PrintMaxN(0);
	return 0;
}