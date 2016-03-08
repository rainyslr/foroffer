#include <iostream>
#include <fstream>
#include <string>

//错误点：按位与的优先级低于比较运算符
//错误点：未考虑DeleteNode函数中被删除节点地址为空的情况
//优点：有考虑调用函数时传入实參不是链表中节点的情况，面试的时候所有不确定的地方要记得跟面试官讨论
using namespace std;

void swap(int *var1,int *var2)
{
	int temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

void print(ostream & os,int data[],int length)
{
	for(int i = 0;i < length; ++ i)
		os << data[i] << " " ;
	os << endl;
}

// void sort(int num[],int length)
// {
// 	if(!num || length <= 0)
// 		throw runtime_error("argument wrong");
// 	int left_index = 0,right_index = length - 1;
// 	while(left_index <right_index)
// 	{
// 		while((num[left_index] & 0x1) == 1 && left_index < right_index)
// 		{
// 			left_index ++;
// 		}
// 		while((num[right_index] & 0x1) == 0 && left_index < right_index)
// 		{
// 			right_index --;
// 		}
// 		swap(num + left_index,num + right_index);
// 	}

// }

void sort(int num[],int length)
{
	if(!num || length <= 0)
		throw runtime_error("argument wrong");
	int left_index = 0,right_index = length - 1;
	while(left_index <=right_index)
	{
		while((num[left_index] & 0x1) == 1 && left_index < right_index)
		{
			left_index ++;
		}
		if((num[left_index] & 0x1) == 1)
			return;
		while((num[right_index] & 0x1) == 0 && left_index < right_index)
		{
			right_index --;
		}
		if((num[right_index] & 0x1) == 0)
			return;
		swap(num + left_index,num + right_index);
	}

}

int main()
{
	int data[] = {2};
	int data2[] = {9,5,7,5,9};
	int data3[] = {8,9,5,7,5,1};
	int data4[] = {2,6,4,6,12};
	int data5[] = {1,3,5,2,4,6,12};
	int data6[] = {2,4,6,12,1,3,5};
	sort(data,1);
	print(cout,data,1);
	sort(data2,5);
	print(cout,data2,5);
	sort(data3,6);
	print(cout,data3,6);
	sort(data4,5);
	print(cout,data4,5);
	sort(data5,7);
	print(cout,data5,7);
	sort(data6,7);
	print(cout,data6,7);


}