#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <map>

using namespace std;

class a{
	int x;
};

int S(char* s,int len)
{
	cout << "str:" << s << endl;
	int start = 0;
	int count = 0;
	int sum = 0;
	for(int i = 0;i < len;++ i)
	{
		if(start)
		{
			if(s[i] == '.')
				count ++;
			else
			{
				sum += count - 1;
				count = 0;
				start = 0;

			}
		}
		else
		{
			if(s[i] == '.')
			{
				start = 1;
				count = 1;
			}

		}
	}
	if(count)
		sum += count - 1;
	return sum;
}

int BetterS(char* s,int len)
{
	int sum = 0;
	for(int i = 0;i < len;++ i)
	{
		if(s[i] == '.' && s[i + 1] == '.')
			sum ++;
	}
	return sum;
}
 
void fun(istream& is,int len,int times)
{
	char* str;
	str = new char[len + 1];
	is >> str;

	int index;char tempchar;
	for(int i = 0;i < times;++ i)
	{
		is >> index;
		is >> tempchar;
		str[index - 1] = tempchar;
		// cout << S(str,len) << endl;
		cout << S(str,len) << endl;
	}
}



int main()
{
	int len,times;
	char* str;
	ifstream inf("input.txt");
	if(!inf)
		throw runtime_error("open fail");
	while(inf >> len >> times)
	{
		fun(inf,len,times);

	}
		

}

