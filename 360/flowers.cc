#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int FindNum(int** data)
{
	(*data) = new int[1000];
	for(int i = 1;i < 10;++ i)
	{
		for(int j = 0;j < 10;++ j)
		{
			for(int k = 0;k < 10;++ k)
			{
				int num = i * 100 + j * 10 + k;
				if(i * i * i + j * j * j + k * k * k == num)
				{
					data[0][num] = 1;
				}
			}
		}
	}
	return 0;
}

int main()
{
	int *data;
	FindNum(&data);
	int n,m,count;
	while(cin >> m >> n)
	{
		count  = 0;
		for(int i = m;i <= n;++ i)
			if(data[i])
			{
				count ++;
				cout << i << " ";
			}
		if(!count)
			cout << "no" << endl;
		else
			cout << endl;
	}
	delete data;
	return 0;
}