#include <iostream>
#include <string>

using namespace std;

void TestStr()
{
	// p1的指向不能改变；
	// char* const p1 = "hellpo";
	// p2指向的值不能改变
	const char * p2 = "cell";
	char str[3];
	memset(str,0,3);
	str[0] = 's';
	// p2[2] = 'l';//这一句是错的.p2所指向的值不能改变
	// p1[2] = 'l';这一句编译能通过，但是运行的时候报错。因为实际上是将一个常量字符串付给了一个可更改其指向值的指针
	// p1 =str;这句诗错的，p1的值不能变化，它是一个const变量。
	
	cout << str;
	p2 = str;
	// p2[1] = 'l';虽然p2实际指向一个可变的数组，但是它自身的类型决定了其指向的值不能改变
	cout << p2;
}

int Min(int i,int j,int k)
{
	int min = i < j ? i : j;
	if(min > k)
		min = k;;
	return min;
}

// 字符串编辑距离
int Distance(const string& str1,const string& str2)
{
	int len1 = str1.size() + 1;
	int len2 = str2.size() + 1;

	int **row;
	row = new int* [len2];
	for(int i = 0;i < len2; ++ i)
	{
		row[i] = new int[len1];
	}
	
	for(int i = 0;i < len2; ++ i)
		row[i][0] = i;
	for(int i = 1;i < len1; ++ i)
		row[0][i] = i;
	int last_dis;
	for(int i = 1;i < len2; ++ i)
	{
		for(int j = 1;j < len1;++ j)
		{
			if(str2[i - 1] == str1[j - 1])
				last_dis = 0;
			else last_dis = 1;
			row[i][j] = Min(row[i - 1][j] + 1,row[i][j - 1] + 1,row[i - 1][j - 1] + last_dis);
		}
	}

	int result = row[len2 -1][len1 - 1];
	for(int i = 0;i < len2; ++ i)
	{
		for(int j = 0;j < len1;++ j)
		{
			cout  << row[i][j] << "\t";
		}
		cout << endl;
		delete row[i];
	}
	delete row;
	return result;
}


int main()
{
	// TestStr();
	string str1("failing");
	string str2("sailn");
	Distance(str1,str2);
	// cout << "result:" << Distance(str1,str2);
	return 0;
}