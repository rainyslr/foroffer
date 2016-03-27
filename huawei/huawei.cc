#include <iostream>
#include <fstream>
#include <string>

#define MAX_SIZE 100

using namespace std;

int Max(int i,int j,int k)
{
	int max = i > j ? i : j;
	if(max < k)
		max = k;
	return max;
}

// 垒积木，动态规划
void Block(istream& is)
{
	int amout;
	int hash[MAX_SIZE][MAX_SIZE][MAX_SIZE];//记录各种尺寸的积木的数量
	int result[MAX_SIZE][MAX_SIZE][MAX_SIZE];
	int length,width,high;
	
	while(is >> amout)
	{
		memset(hash,0,sizeof(hash));
		memset(result,0,sizeof(hash));
		for(int i = 0;i < amout;++ i)
		{
			is >> length >> width >> high;
			hash[length][width][high] ++;
		}
		int max = 0;
		for(int i = 1;i < MAX_SIZE;++ i)
		{
			for(int j = 1;j < MAX_SIZE;++ j)
			{
				for(int k = 1;k < MAX_SIZE;++ k)
				{

					result[i][j][k] = Max(result[i - 1][j][k],result[i][j - 1][k],result[i][j][k - 1]) + hash[i][j][k];
					if(result[i][j][k] > max)
						max = result[i][j][k];
				}
			}
		}
		cout << max << endl;

	}

}

/*******************************************************************************/
// 用快排思想查找第n大的数

void swap(int* i,int *j)
{
	int temp = *i;
	*i = *j;
	*j = temp;
}

int Getindex(int low,int high,int data[])
{
	if(low == high)
		return low;
	int left = low,right = high;
	while(left < right)
	{
		while(data[left] > data[right] && left < right)
			++ left;
		swap(data + left,data + right);
		while(data[left] > data[right] && left < right)
			-- right;
		swap(data + left,data + right);
	}
	return left;
}


int FindNMax(int low,int high,int index,int data[])
{
	int key = Getindex(low,high,data);
	if(key == index)
		return data[key];
	else if(key < index)
	{
		if(key == high)
			throw runtime_error("error");
		return FindNMax(key + 1,high,index,data);
	}
	else 
	{
		if(key == low)
			throw runtime_error("error");
		return FindNMax(low,key - 1,index,data);
	}
}

/*******************************************************************************/

int main()
{
	// ifstream inf("input.txt");
	// Block(inf);
	int data[] = {5,2,4,3,1};

	cout << FindNMax(0,4,3,data) << endl;

	return 0;
}


