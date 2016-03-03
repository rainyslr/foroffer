#include <iostream>
#include <fstream>
#include <string>

//错误点：未考虑删除节点为头节点的情况
//错误点：未考虑DeleteNode函数中被删除节点地址为空的情况
using namespace std;

struct ListNode
{
	int m_nValue;
	ListNode *m_pNext;	
};

void Print(ListNode **pListHead)
{
	if(pListHead == NULL || (*pListHead) == NULL)
		throw runtime_error("invalid pointer");
	ListNode *current = (*pListHead);
	while(current->m_pNext != NULL)
	{
		cout << current->m_nValue << " ";
		current = current->m_pNext;
	}
	cout << current->m_nValue << endl;
	return;
}

ListNode* CreateLink()
{
	ifstream inf("input.txt");
	if(!inf)
	{
		throw runtime_error("open input file error" );
	}
	int node_amout;
	inf >> node_amout;
	if(node_amout <= 0)
		throw runtime_error("node_amout shuold be positive");
	ListNode *head_node,*node = new ListNode;
	if(node == NULL)
			throw runtime_error("fail to alloc space for the head node");
	inf >> node->m_nValue;
	node->m_pNext = NULL;
	head_node = node;
	for(int i = 1;i < node_amout;++ i)
	{
		node->m_pNext = new ListNode;
		if(node->m_pNext == NULL)
			throw runtime_error("fail to alloc space for the new node");
		node = node->m_pNext;
		inf >> node->m_nValue;
		node->m_pNext = NULL;
		
	}
	return head_node;
}

void DeleteNode(ListNode **pListHead,ListNode *pToBeDeleted)
{
	if(pListHead == NULL || (*pListHead) == NULL || !pToBeDeleted)
		throw runtime_error("wrong pointer int link");
	if(pToBeDeleted->m_pNext == NULL)
	{
		ListNode* previous = *pListHead;
		while(previous->m_pNext != pToBeDeleted)
			previous = previous->m_pNext;
		previous->m_pNext = NULL;
	}
	else
	{
		memcpy(pToBeDeleted,pToBeDeleted->m_pNext,sizeof(ListNode));
		delete pToBeDeleted->m_pNext;
	}
}

ListNode* GetNodeAddress(ListNode **pListHead,int serch_key)
{
	if(pListHead == NULL || (*pListHead) == NULL)
		throw runtime_error("wrong pointer int link");
	ListNode* temp = *pListHead;
	while(temp->m_nValue != serch_key &&  temp->m_pNext != NULL)
			temp = temp->m_pNext;
	if(temp->m_nValue != serch_key)
		return NULL;
	return temp;
}

int main()
{
	ListNode *head_node = CreateLink();
	Print(&head_node);
	ListNode* delete_address = GetNodeAddress(&head_node,5);
	if(delete_address != NULL)
		DeleteNode(&head_node,delete_address);
	Print(&head_node);
	return 0;
}

