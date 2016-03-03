#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int judge(const char* data)
{
	if(data == NULL)
		throw runtime_error("data pointer is null");
	int length = strlen(data);
	if(length <= 0)
		throw runtime_error("data length error");
	int result = 0;
	for(int i = 0;i < length;++ i)
	{
		result = result*26 + (data[i] - 'A' + 1);
	}
	return result;
}

int main()
{
	cout << judge("AC") << endl;
	//cout << i <<endl;
	return 0;
}