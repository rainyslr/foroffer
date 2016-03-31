#include <cstdio>  
#include <memory.h>  
#include <queue>  
#include <iostream>
  
using namespace std;  
  
#define EMPTY    0  
  
struct data_type  
{  
    int state[4];  
    int step;  
};  
  
int capacity[4], targetState[4];  
  
bool visited[100][100][100][100];  
  
bool ATState(data_type current)  
{  
    for (int i = 0; i < 4; i++)  
    {  
        if (current.state[i] != targetState[i])  
        {  
            return false;  
        }  
    }  
    return true;  
}  
  
void PWater(int destination, int source, data_type &cup)  
{  
    //目标杯子能装的水
    int waterYield = capacity[destination] - cup.state[destination];  
    if (cup.state[source] >= waterYield)  
    {  
        cup.state[destination] += waterYield;  
        cup.state[source] -= waterYield;  
    }  
    else  
    {  
        cup.state[destination] += cup.state[source];  
        cup.state[source] = 0;  
    }  
}  
  
int Fun(void)  
{  
    int i, j, k;  
    data_type initial;  
    queue<data_type> toExpandState;  
  
    memset(visited, false, sizeof(visited));  
    initial.state[0] = capacity[0];  
    initial.state[1] = initial.state[2] = initial.state[3] =0;  
    initial.step = 0;  
    toExpandState.push(initial);  
    visited[initial.state[0]][0][0][0] = true;  
  
    while (!toExpandState.empty())  
    {  
        data_type node = toExpandState.front();  
        toExpandState.pop();  
        if (ATState(node))  
        {  
            return node.step;  
        }  
        for (i = 0; i < 4; i++)  
        {  
            for (j = 1; j < 4; j++)  
            {  
                k = (i+j)%4;  
                if (node.state[i] != EMPTY && node.state[k] < capacity[k])  
                {  
                    data_type newNode = node;  
                    // 将水倒到第k个杯子里
                    PWater(k, i, newNode);  
                    newNode.step = node.step + 1;  
                    if (!visited[newNode.state[0]][newNode.state[1]][newNode.state[2]][newNode.state[3]])  
                    {  
                        visited[newNode.state[0]][newNode.state[1]][newNode.state[2]][newNode.state[3]] = true;  
                        toExpandState.push(newNode);  
                    }  
                }  
            }  
        }  
    }  
    return -1;  
}  
  
int main(void)  
{  
	capacity[0] = 10;
    capacity[1] = 6;
    capacity[2] = 5;
    capacity[3] = 4;
	while(cin >> targetState[0] >> targetState[1] >> targetState[2] >> targetState[3])
		cout << Fun() << endl;
    return 0;  
} 