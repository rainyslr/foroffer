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

int partion(int data[],int length,int start,int end)
{
	//从左边开始，最右边的数是哨兵，small纪录最近一个比哨兵小的元素应该存放的位置（当该索引值与
	// 当前访问索引i相等，则说明前面的数都是比哨兵小的数，无需交换
	// 否则需要将最近找到的比哨兵小的数挪至small
	if(data == NULL || length < 0 || start < 0 || end >= length || start > length)
		return -1;
	int small  = start - 1;
	for(int i = start;i < end; ++ i)
	{
		if(data[i] < data[end])
		{
			++ small;
			if(small != i)
			{
				swap(data + small,data + i);
			}
		}
	}
	++ small;
	swap(data + small,end + data);
	return small;
}

bool fast_sort(int data[],int length,int start,int end)
{
	if(data == NULL || length < 0 || start < 0 || end >= length || start > length)
		return false;
	if(start == end)
		return true;
	int index = partion(data,length,start,end);
	if(index == -1)
		return false;
	if(index > start)
		fast_sort(data,length,start,index - 1);
	if(index < end)
		fast_sort(data,length,index + 1,end);
	return true;
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
		fast_sort(data,temp,0,temp - 1);
		print(ouf,data,temp);
		delete [] data;
	}
	return 0;
	
}