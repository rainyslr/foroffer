#include <stack>
#include <iostream>
using namespace std;
bool ISPopOrder(const int* pPush,const int* pPop,int nLength)
{
	if(!pPush || !pPop || nLength <= 0)
		throw runtime_error("argument error");
	// bool bPossible true;
	stack<int> data;
	int count = 0;
	for(int i = 0;i < nLength;++ i)
	{
		while(data.empty() || data.top() != pPop[i])
		{
			if(count == nLength)
				return false;
			else
			{
				data.push(pPush[count]);
				count ++;
			}
		}
		data.pop();
	}
	return true;
}

int main()
{
	int push[] = {1,2,3,4,5};
	int pop1[] = {4,5,3,1,2};
	int pop2[] = {4,3,5,1,2};
	int pop3[] = {4,5,3,2,1};
	cout << ISPopOrder(push,pop1,5) << endl;
	cout << ISPopOrder(push,pop2,5) << endl;
	cout << ISPopOrder(push,pop3,5) << endl;
	return 0;

}