#include <iostream>
using namespace std;

int MaxFac(int m,int n)
{ 
	int k,p,t;
	t = m < n ? m:n;
	for(k=t; ;k--)
		if(m%k==0&&n%k==0) break;
	return k;
}

int func(int monter,int energy,int defense[])
{
	int result = energy;
	for(int i = 0;i < monter;++ i)
	{
		if(result >= defense[i])
			result += defense[i];
		else result += MaxFac(result, defense[i]);
	}
	return result;
}

int main()
{
	int monter,energy;
	int* defense;
	while(cin >> monter)
	{
		cin >> energy;
		defense = new int[monter];
		for(int i = 0;i < monter; ++ i)
			cin >> defense[i];
		cout << func(monter,energy,defense) << endl;
		delete defense;
	}
	return 0;
}
