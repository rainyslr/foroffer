#include <iostream>
#include <fstream>
using namespace std;

void print(ostream & os,int data[],int length)
{
	for(int i = 0;i < length; ++ i)
		os << data[i] << " " ;
	os << endl;
}

void PrintMattrix(int **numbers,int rows,int colums)
{
	cout << "rows:" << rows << " ,colums:" << colums << endl;
	for(int i = 0;i < rows;++ i)
	{
		for(int j = 0;j < colums;++ j)
			cout << numbers[i][j] << " ";
		cout << endl;
	}
	cout << endl;

}

void GetMattrix(int ***numbers,int* rows,int* colums)
{
	ifstream inf("input.txt");
	if(!inf)
	{
		cout << "open input file error" << endl;
		return ;
	}
	inf >> *rows >> *colums;
	*numbers =  new int* [*rows];
	for(int i  = 0;i < *rows;i ++)
	{
		(*numbers)[i] = new int[*colums];
		for(int j  = 0;j < *colums;j ++)
			inf >> (*numbers)[i][j];	
	}
	return ;
}

void PrintMatrixClockwisely(int **numbers,int rows,int colums)
{
	if(!numbers || !(*numbers))
		throw runtime_error("pointer error");
	if(!colums || !rows)
		throw runtime_error("pointer error");
	int top = 0,bottom = rows - 1,left = 0,right = colums - 1;
	while(left <= right && top <= bottom)
	{
		for(int i = left;i <= right;++ i)
			cout << numbers[top][i] << " ";
		top ++;
		for(int j = top;j <= bottom;++ j)
			cout << numbers[j][right] << " ";
		right --;
		for(int i = right;i >= left;-- i)
			cout << numbers[bottom][i] << " ";
		bottom --;
		for(int j = bottom;j >= top;-- j)
			cout << numbers[j][left] << " ";
		left ++;

	}
}

int main()
{
	int **numbers;
	int rows,colums;
	GetMattrix(&numbers,&rows,&colums);
	PrintMattrix(numbers,rows,colums);
	PrintMatrixClockwisely(numbers,rows,colums);
}
