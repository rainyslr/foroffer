#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double Sum(int start,int length)
{
	double sum = start;
	double ele = start;
	for(int i = 1;i < length;++ i)
	{
		ele = sqrt(ele);
		sum += ele;
	}
	return sum;
}

int main()
{
	int n,m;
	
	cout.setf(std::ios_base::fixed);
	cout.setf(std::ios_base::showpoint);
	cout.precision(2); 
	while(cin >> n >> m)
	{
		cout << Sum(n,m) << endl;
	}
	return 0;
}