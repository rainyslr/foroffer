#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <map>

using namespace std;

class Hen
{
public:
	int n;
	Hen()
	{
		n = 100;
		cout << "Hen:" << n << endl;
	}
	Hen(int i):n(i){
		cout << "Hen:" << n << endl;
	}
	~Hen()
	{
		cout << "Distroy Hen:" << n << endl;
	}
};

class Hen1
{
public:
	int n;
	Hen1()
	{
		n = 100;
		cout << "Hen1:" << n << endl;
	}
	Hen1(int i):n(i){
		cout << "Hen1:" << n << endl;
	}
	~Hen1()
	{
		cout << "Distroy Hen1:" << n << endl;
	}
};

class Hen2
{
public:
	int n;
	Hen2()
	{
		n = 100;
		cout << "Hen2:" << n << endl;
	}
	Hen2(int i):n(i){
		cout << "Hen2:" << n << endl;
	}
	~Hen2()
	{
		cout << "Distroy Hen2:" << n << endl;
	}
};

class Egg:public Hen,public Hen2,public Hen1
{
public:
	int m;
	Hen hen;
	Hen1 hen1;
	Hen2 hen2;
	Egg(int i):Hen2(i),Hen1(i),hen1(i*2),hen2(2*i),hen(i*2){
		m = i;
		cout << "Egg:" << m << endl;
	}
	Egg();
	~Egg()
	{
		cout << "Distroy Egg:" << m << endl;
	}
	
};

int main()
{
	Egg egg(10);
}