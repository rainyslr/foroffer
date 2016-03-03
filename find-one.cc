#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int FindOne(int var)
{
	int result = 0;
	while(var)
	{
		var = var & (var - 1);
		result ++;
	}
	return result;
}

int main()
{
	cout << FindOne(-4) << endl;
	return 0;
}