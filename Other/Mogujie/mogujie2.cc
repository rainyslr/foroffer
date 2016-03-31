#include <iostream>
#include <vector> 
#include <map>
#include <string.h>

#define MAX_LEG_AMOUT 100001
#define MAX_LEG_LEN 100001
#define MAX_LEG_PAY 201

using namespace std;

int max_len = 0;
int min_len = MAX_LEG_LEN;
int min_pay = MAX_LEG_PAY;
int max_pay = 0;

int leg_len[MAX_LEG_AMOUT] = {0};
int leg_pay[MAX_LEG_AMOUT] = {0};
int len_count[MAX_LEG_LEN] = {0};
int pay_statics[MAX_LEG_PAY][MAX_LEG_LEN] = {0};//纪录某一个pay，某一个len的腿的数目

//找出pay和len的边界值
void PreProcess()
{
	for(int len = 0;len < MAX_LEG_LEN;++ len)
	{
		if(len_count[len])
		{
			min_len = len;
			break;
		}
	}

	for(int len = MAX_LEG_LEN - 1;len > 0;-- len)
	{
		if(len_count[len])
		{
			max_len = len;
			break;
		}
	}

	for(int pay = 0;pay < MAX_LEG_PAY;++ pay)
	{
		for(int len = 0;len < MAX_LEG_LEN;++ len)
			if(pay_statics[pay][len])
			{
				min_pay = pay;
				goto end1;
			}
	}
end1:
	for(int pay = MAX_LEG_PAY - 1;pay > 0;-- pay)
	{
		for(int len = 0;len < MAX_LEG_LEN;++ len)
			if(pay_statics[pay][len])
			{
				max_pay = pay;
				return;
			}
	}
}

// 移除掉amout条长度比up_len小的腿所需代价
int MinCost(int up_len,int amout)
{
	if(up_len == min_len || amout <= 0)
		return 0;//没有可移除的腿
	int rm = amout;
	int cost = 0;
	while(rm)
	{
		for(int pay = min_pay;pay <= max_pay;++ pay)
			for(int len = min_len;len <  up_len;++ len)
				if(pay_statics[pay][len])
				{
					if(pay_statics[pay][len] < rm)
					{
						cost += pay * pay_statics[pay][len];
						rm -=  pay_statics[pay][len];
					}
					else
					{
						cost += pay * rm;
						return cost;
					}

				}

	}
	return cost;
}

int main()
{
	int nleg;
	while(cin >> nleg)
	{
		memset(len_count,0,sizeof(len_count));
		memset(leg_len,0,sizeof(leg_len));
		memset(leg_pay,0,sizeof(leg_pay));
		memset(pay_statics,0,sizeof(pay_statics));
		for(int i = 0;i < nleg;++ i)
		{
			cin >> leg_len[i];
			len_count[leg_len[i]] ++;
		}	
		for(int i = 0;i < nleg;++ i)
		{
			cin >> leg_pay[i];
			pay_statics[leg_pay[i]][leg_len[i]] ++;
		}

		PreProcess();
		int min_cost = 20000000;

		for(int len = max_len;len >= min_len; -- len)
		{
			//len为剩下桌腿组合中最大的长度
			if(!len_count[len])
				continue;	
			int cost = 0;
			int longer_rm = 0;
			//移除掉比len长的腿
			for(int longer = len + 1;longer <= max_len;++ longer)
			{
				longer_rm += len_count[longer];
				for(int pay = min_pay;pay <= max_pay;++ pay)
					cost += pay * pay_statics[pay][longer];
			}
			//移除掉比len短的腿若干条使得个数上符合要求,移除短腿个数为len_count[len] - 1；
			int smaller_need_rm = nleg - longer_rm - 2*len_count[len] + 1;
			int rm_smaller_cost = MinCost(len,smaller_need_rm);
			cost += rm_smaller_cost;
			// cout << "when longest len is :"<< len <<"cost:" << cost << endl;
			if(cost < min_cost)
				min_cost = cost;
		}
		cout << min_cost << endl;
	}
	return 0;
}

