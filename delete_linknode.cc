#include <iostream>
#include <fstream>
#include <string>

//错误点：未考虑删除节点为头节点的情况,只要删除节点，一定要考虑这个问题
//错误点：未考虑DeleteNode函数中被删除节点地址为空的情况
//优点：有考虑调用函数时传入实參不是链表中节点的情况，面试的时候所有不确定的地方要记得跟面试官讨论
using namespace std;

struct ListNode
{
	int m_nValue;
	ListNode *m_pNext;	
};

void Print(ListNode **pListHead)
{
	if(pListHead == NULL)
		throw runtime_error("invalid pointer");
	else if((*pListHead) == NULL)
	{
		cout << "link is null" << endl;
		return;
	}
	ListNode *current = (*pListHead);
	while(current->m_pNext != NULL)
	{
		cout << current->m_nValue << " ";
		current = current->m_pNext;
	}
	cout << current->m_nValue << endl;
	return;
}



ListNode* CreateLink(istream& inf)
{
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


void Init(ListNode* link_array[],int number)
{
	ifstream inf("input.txt");
	if(!inf)
	{
		throw runtime_error("open input file error" );
	}
	for(int i = 0;i < number;++ i)
		link_array[i] = CreateLink(inf);
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
	else if(*pListHead == pToBeDeleted)
	{
		delete pToBeDeleted;
		*pListHead = NULL;
	}
	else
	{
		memcpy(pToBeDeleted,pToBeDeleted->m_pNext,sizeof(ListNode));
		delete pToBeDeleted->m_pNext;
	}
}

void DeleteLastNthNode(ListNode **pListHead,int k)
{
	if(pListHead == NULL || !(*pListHead) || k <= 0)
		throw runtime_error("wrong argument in DeleteLastNthNode()");
	ListNode *p_first = *pListHead,*p_second = *pListHead;
	for(int i = 0;i < k - 1;++i)
	{
		if(p_first->m_pNext == NULL)
		{
			throw runtime_error("k is larger than the length of the link");
		}
		p_first = p_first->m_pNext; 
	}
	if(!p_first->m_pNext)
	{
		//the deleted node is the head;
		*pListHead = p_second->m_pNext;
		delete p_second;
		return;
	}
	p_first = p_first->m_pNext; 
	while(p_first->m_pNext)
	{
		p_first = p_first->m_pNext; 
		p_second = p_second->m_pNext; 
	}	
	ListNode *p_deleted = p_second->m_pNext;
	p_second->m_pNext = p_deleted->m_pNext;
	delete p_deleted;
}

ListNode* GetNodeAddress(ListNode **pListHead,int serch_key)
{
	if(pListHead == NULL || (*pListHead) == NULL)
		throw runtime_error("wrong pointer in link");
	ListNode* temp = *pListHead;
	while(temp->m_nValue != serch_key &&  temp->m_pNext != NULL)
			temp = temp->m_pNext;
	if(temp->m_nValue != serch_key)
		return NULL;
	return temp;
}

ListNode* Reverse(ListNode* add_node)
{
	if(!(add_node->m_pNext))
	{
		add_node->m_pNext = add_node;
		return add_node;
	}
	else
	{
		ListNode* ret_node = Reverse(add_node->m_pNext);
		add_node->m_pNext->m_pNext = add_node;
		return ret_node;
	}
}


ListNode* ReverseLinkRecursively(ListNode** pListHead)
{
	if(pListHead == NULL || (*pListHead) == NULL)
		throw runtime_error("wrong pointer in ReverseLink()");
	ListNode* new_head = Reverse(*pListHead);
	(*pListHead)->m_pNext = NULL;
	return new_head;
}

ListNode* ReverseLink(ListNode** pListHead)
{
	if(pListHead == NULL || (*pListHead) == NULL)
		throw runtime_error("wrong pointer in ReverseLink()");
	ListNode *p_current = *pListHead,*p_before = NULL,*p_ahead;
	// while(p_current->m_pNext)
	while(p_current->m_pNext)
	{
		p_ahead = p_current->m_pNext;
		p_current->m_pNext = p_before;
		p_before = p_current;
		p_current = p_ahead;
	}
	p_current->m_pNext = p_before;
	return p_ahead;
}

ListNode* MergeTwoSortedLink(ListNode **pListHead1,ListNode **pListHead2)
{
	if(!pListHead1 || !pListHead2)
		throw runtime_error("wrong pointer in MergeTwoSortedLink");
	else if(!(*pListHead1))
		return *pListHead2;
	else if(!(*pListHead2))
		return *pListHead1;
	ListNode *head,*p_link1,*p_link2,*p_current;
	if((*pListHead1)->m_nValue <= (*pListHead2)->m_nValue)
	{
		head = *pListHead1;
		p_link1 = head->m_pNext;
		p_link2 = *pListHead2;
	}
	else
	{
		head = *pListHead2;
		p_link2 = head->m_pNext;
		p_link1 = *pListHead1;
	}
	p_current = head;
	while(p_link1 && p_link2)
	{
		if(p_link1->m_nValue <= p_link2->m_nValue)
		{
			p_current->m_pNext = p_link1;
			p_link1 = p_link1->m_pNext;
		}
		else
		{
			p_current->m_pNext = p_link2;
			p_link2 = p_link2->m_pNext;
		}
		p_current = p_current->m_pNext;
	}
	if(p_link1)
	{
		p_current->m_pNext = p_link1;
	}
	else if(p_link2)
		p_current->m_pNext = p_link2;
	return head;
}



int main()
{
	// ListNode *head_node = CreateLink();
	// Print(&head_node);
	// ListNode* delete_address = GetNodeAddress(&head_node,2);
	// if(delete_address != NULL)
	// 	DeleteNode(&head_node,delete_address);
	// DeleteLastNthNode(&head_node,5);
	// Print(&head_node);
	// DeleteLastNthNode(&head_node,1);
	// Print(&head_node);
	// DeleteLastNthNode(&head_node,4);
	// Print(&head_node);
	// ListNode *new_head = ReverseLink(&head_node);
	// ListNode *new_head = ReverseLinkRecursively(&head_node);
	// Print(&new_head);
	ListNode* array[6];
	Init(array,6);
	ListNode* head = MergeTwoSortedLink(array,array + 1);
	Print(&head);

	// ListNode* null_link = NULL;
	// head = MergeTwoSortedLink(array,&null_link);
	// Print(&head);
	// head = MergeTwoSortedLink(&null_link,array);
	// Print(&head);
	// head = MergeTwoSortedLink(&null_link,&null_link);
	// Print(&head);

	head = MergeTwoSortedLink(array + 2,array + 3);
	Print(&head);

	return 0;
}

