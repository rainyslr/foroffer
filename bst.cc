#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector> 
#include <queue>
#include <stack>
using namespace std;

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

BinaryTreeNode* AllocNode(void)
{
	BinaryTreeNode *node = new BinaryTreeNode;
		if(!node)
			throw runtime_error("fail to alloc space for a new node");
	return node;
}

void PrintTree(BinaryTreeNode* root)
{
	if(!root)
	{
		cout << "empty tree" << endl;
	}
	queue<BinaryTreeNode*> node_queue;
	node_queue.push(root);
	int deep = 0,node_count = 0,null_node_count = 0;
	while(!node_queue.empty())
	{
		BinaryTreeNode* current_node = node_queue.front();
		if(current_node)
		{
			node_queue.push(current_node->m_pLeft);
			node_queue.push(current_node->m_pRight);
			cout << current_node->m_nValue << " ";
		}
		else
		{
			node_queue.push(NULL);
			node_queue.push(NULL);
			cout << "NULL ";
			null_node_count ++;
		} 
		node_count ++;
		if(node_count == (0x1 << deep))
		{
			if(null_node_count == node_count)
				break;//本层节点全为空节点
			node_count = 0;
			null_node_count = 0;
			deep ++;
			cout << endl;
		}
		node_queue.pop();
	}
	cout << endl;
}

// 根据输入的无序序列构造二叉排序树
BinaryTreeNode* CreateBinarySortingTree(istream& is)
{
	int num;
	BinaryTreeNode* root;
	if(is >> num)
	{
		root = AllocNode();
		root->m_nValue = num;
		root->m_pLeft = NULL;
		root->m_pRight = NULL;
	}
	else return NULL;
	BinaryTreeNode* cur;
	while(is >> num)
	{
		BinaryTreeNode* node = AllocNode();
		node->m_pLeft = NULL;
		node->m_pRight = NULL;
		node->m_nValue = num;
		cur = root;
		while(cur)
		{
			if(cur->m_nValue > num)
			{
				if(cur->m_pLeft)
					cur = cur->m_pLeft;
				else
				{
					cur->m_pLeft = node;
					cur = NULL;
				}
			}
			else
			{
				if(cur->m_pRight)
					cur = cur->m_pRight;
				else
				{
					cur->m_pRight = node;
					cur = NULL;
				}
			}
		}
	}
	return root;
}



int main()
{
	BinaryTreeNode* root = CreateBinarySortingTree(cin);
	PrintTree(root);
  	return 0;
}