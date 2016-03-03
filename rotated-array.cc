#include <iostream>
#include <fstream>

using namespace std;

void print(ostream & os,int data[],int length)
{
	for(int i = 0;i < length; ++ i)
		os << data[i] << " " ;
	os << endl;
}
void swap(int *var1,int *var2)
{
	int temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

//错误1:没有判断升排序，最小数在左边的情况
//错误2:没有判断start，end，mid对应的三个数相等的情况
int smallest(int data[],int length)
{
	if(data == NULL)
		throw runtime_error("Data must must be not null");
	int start = 0,end = length - 1;
	int mid;
	while(data[start] >= data[end])
	{
		if(start == end - 1)
		{
			return data[end];
		}
		mid = (end + start) / 2;
		if(data[start] == data[mid] && data[end] == data[mid])
		{
			for(int i = start;i < end;++ i)
				if(data[i] < data[mid])
					return data[i];
		}
		else
		{

			if(data[start] <= data[mid])
			{
				start = mid;
				continue;
			}
			else if(data[end] >= data[mid])
			{
				end = mid;
				continue;
			}

		}
		
	}
	return data[start];
}

int main()
{
	ifstream inf("input.txt");
	if(!inf)
	{
		cout << "open input file error" << endl;
		return -1;
	}
	ofstream ouf("output.txt");
	if(!ouf)
	{
		cout << "open output file error" << endl;
		return -1;
	}
	int temp;
	while(inf >> temp)
	{
		int *data = new int[temp];
		int num;
		for(int i  = 0;i < temp;i ++)
			inf >> *(data + i);
		// print(cout,data,temp);
		ouf << smallest(data,temp) << endl;
		delete [] data;
	}
	return 0;
}