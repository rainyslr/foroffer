#include <iostream>
#include <math.h>

using namespace std;

int fun(int data[])
{
	double dis[3];
	for(int i = 1,j = 0;i < 7;i = i + 2,j++)
	{
		dis[j] = sqrt((data[i]-data[7]) * (data[i]-data[7]) + (data[i + 1]-data[8]) * (data[i + 1]-data[8]));
	}
	int result = 0;
	for(int i = 0;i < 3;++ i)
	{
		if(dis[i] <= data[0])
			result ++;
	}
	return result;
}
	
int main()
{
	int data[9];
	int result;
	while(1)
	{
		if(!(cin >> data[0]))
			break;
		for(int i = 1;i < 9;++ i)
			cin >> data[i];
		result = fun(data);
		cout << result << "x" << endl;
	}
	return 0;
}