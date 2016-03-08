#include <stdio.h>

//面试宝典中说这个求值顺序是从右到左。但是在我的mac上还是输出的0和1，而且编译的时候warning：不确定求值顺序
int main()
{
	int i = 0;
	printf("%d,%d\n",i,++i);
}