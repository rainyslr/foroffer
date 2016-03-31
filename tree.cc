#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector> 
#include <queue>
#include <stack>
using namespace std;

//如果两棵树所有节点的都只有右节点或者豆只有左节点，还是可以唯一确认这棵树到底是哪一种情况。
// 这两句话求出的是对应的指针变量的大小而非数组的大小，牢记

void print(ostream & os,int data[],int length)
{
	for(int i = 0;i < length; ++ i)
		os << data[i] << " " ;
	os << endl;
}

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



void BetterPreOrderCore(BinaryTreeNode* root,ostream& os)
{
	stack<BinaryTreeNode*> node_stack;
	BinaryTreeNode *node = root;
	while(!node_stack.empty() || node)
	{
		while(node)
		{
			os << node->m_nValue << " ";
			node_stack.push(node);
			node = node->m_pLeft;
		}
		if(!node_stack.empty())
		{
			node = node_stack.top();
			node_stack.pop();
			node = node->m_pRight;
		}
	}
}

void BetterInOrderCore(BinaryTreeNode* root,ostream& os)
{
	stack<BinaryTreeNode*> node_stack;
	BinaryTreeNode *node = root;
	while(!node_stack.empty() || node)
	{
		while(node)
		{
			node_stack.push(node);
			node = node->m_pLeft;
		}
		if(!node_stack.empty())
		{
			node = node_stack.top();
			os << node->m_nValue << " ";
			node_stack.pop();
			node = node->m_pRight;
		}
	}
}

// 其实思考的时候既然想到了无法区分右子树是否已经访问，为何不想到添加一个标志位呢
// 当从栈中弹出一个节点，如果该节点没有右子树则可以输出这个这个节点，且将其设置为last_visit；
// 如果弹出的节点的右子节点已经访问，说明右子树已经遍历结束，也可直接输出该节点
void BetterCPostOrderCore(BinaryTreeNode* root,ostream& os)
{
	stack<BinaryTreeNode*> node_stack;
	// stack<BinaryTreeNode*> last_visit_stack;
	BinaryTreeNode *node = root,*last_visit = NULL;
	while(node)
	{
		node_stack.push(node);
		node = node->m_pLeft;
	}
	while(!node_stack.empty())
	{
		node = node_stack.top();
		node_stack.pop();
		if(!node->m_pRight || node->m_pRight == last_visit)
		{
			last_visit = node;
			os << node->m_nValue << " ";
		}
		else
		{
			node_stack.push(node);
			node = node->m_pRight;
			while(node)
			{
				node_stack.push(node);
				node = node->m_pLeft;
			}
		}
	}
}


void PreOrderRecursiveCore(BinaryTreeNode* root,ostream& os)
{
	os << root->m_nValue << " ";
	if(root->m_pLeft)
		PreOrderRecursiveCore(root->m_pLeft,os);
	if(root->m_pRight)
		PreOrderRecursiveCore(root->m_pRight,os);
}

void InOrderRecursiveCore(BinaryTreeNode* root,ostream& os)
{
	if(root->m_pLeft)
		InOrderRecursiveCore(root->m_pLeft,os);
	os << root->m_nValue << " ";
	if(root->m_pRight)
		InOrderRecursiveCore(root->m_pRight,os);
}

void PostOrderRecursiveCore(BinaryTreeNode* root,ostream& os)
{
	if(root->m_pLeft)
		PostOrderRecursiveCore(root->m_pLeft,os);
	if(root->m_pRight)
		PostOrderRecursiveCore(root->m_pRight,os);
	os << root->m_nValue << " ";
}

string ConstructPreOrder(BinaryTreeNode* root)
{
	if(!root)
		throw runtime_error("root pointer is null");
	
	ostringstream order_stream;
	BetterPreOrderCore(root,order_stream);
	order_stream << '\n';
	return order_stream.str();

}

string ConstructInOrder(BinaryTreeNode* root)
{
	if(!root)
		throw runtime_error("root pointer is null");
	ostringstream order_stream;
	InOrderRecursiveCore(root,order_stream);
	order_stream << '\n';
	return order_stream.str();
}

string ConstructPostOrder(BinaryTreeNode* root)
{
	if(!root)
		throw runtime_error("root pointer is null");
	ostringstream order_stream;
	PostOrderRecursiveCore(root,order_stream);
	order_stream << '\n';
	return order_stream.str();
}

BinaryTreeNode* BetterConstructCore(int* start_pre,int* end_pre,int* start_in,int* end_in)
{
	BinaryTreeNode* root_node = AllocNode();
	int root_value = *start_pre;
	root_node->m_nValue = root_value;
	root_node->m_pLeft = NULL;
	root_node->m_pRight = NULL;
	if(start_pre == end_pre)
	{
		if(start_in == end_in && *start_pre == * start_in)
			return root_node;
		else
			throw runtime_error("order sequence error when just one node");
	}
	int *root_in_inorder = start_in;

	// 在中序遍历序列中找到先序序列中的根
	while(root_in_inorder <= end_in && (*root_in_inorder) != root_value)
	{
		root_in_inorder ++;
	}
	if(root_in_inorder > end_in || (*root_in_inorder) != root_value)
		throw runtime_error("order sequence error when more than one node");
	int left_length = root_in_inorder - start_in;
	int *left_end_pre = start_pre + left_length;
	if(left_length > 0)
	{
		
		root_node->m_pLeft = BetterConstructCore(start_pre + 1,left_end_pre,start_in,root_in_inorder - 1);
	}
	if(root_in_inorder < end_in)
	{
		root_node->m_pRight = BetterConstructCore(left_end_pre + 1,end_pre,root_in_inorder + 1,end_in);
	}
	return root_node;
}

BinaryTreeNode* Construct(int* preorder,int* inorder,int length)
{
	if(!preorder || !inorder || length <= 0)
		throw runtime_error("argument error in Construct()");
	// return ConstructCore(preorder,preorder + length - 1,inorder,inorder + length - 1);
	return BetterConstructCore(preorder,preorder + length - 1,inorder,inorder + length - 1);
}

void GetOrderSeq(istream& ins,int** pre_order,int** in_order)
{
	if(!pre_order && !in_order)
		throw runtime_error("argument error in GetOrderSeq()");
	int node_amout;
	ins >> node_amout;
	*pre_order = new int [node_amout];
	*in_order = new int [node_amout];
	if(!(*pre_order) || !(*in_order))
		throw runtime_error("alloc error for pre_order array and in_order array");
	for(int i = 0;i < node_amout;++ i)
		ins >> *((*pre_order) + i);
	for(int i = 0;i < node_amout;++ i)
		ins >> *((*in_order) + i);
}

void CreateTreeOrderSeq(const string& in_file,int tree_num,int*** pre_order,int*** in_order)
{
	//此时输入文件的格式应该如下；
// 	7 					//序列的数字数
// 8 6 5 7 10 9 11		//先序
// 5 6 7 8 9 10 11		//中序
	ifstream inf(in_file.c_str());
	if(!inf)
		throw runtime_error("open input file error");
	*pre_order = new int* [tree_num];
	*in_order = new int* [tree_num];
	for(int i = 0;i < tree_num;++ i)
		GetOrderSeq(inf,*pre_order + i,*in_order + i);
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
//题目为从上到下输出树，可以考虑是否输出换行（和面试官交流）
void PrintTreeWithoutEmptyNode(BinaryTreeNode* root)
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

void TestTreePrintFunc()
{
	BinaryTreeNode *node[5];
	for(int i = 0;i < 5;++ i)
	{
		node[i] = AllocNode();
		node[i]->m_nValue = i + 1;
	}
	node[0]->m_pLeft = node[1];
	node[0]->m_pRight = node[2];
	node[1]->m_pLeft = NULL;
	node[1]->m_pRight = node[3];
	node[2]->m_pLeft = node[4];
	node[2]->m_pRight = NULL;
	node[3]->m_pLeft = NULL;
	node[3]->m_pRight = NULL;
	node[4]->m_pLeft = NULL;
	node[4]->m_pRight = NULL;
	PrintTree(node[0]);
	ConstructInOrder(node[0]);
	ConstructPreOrder(node[0]);
	ConstructPostOrder(node[0]);
}

bool CompareSub(BinaryTreeNode* tree1,BinaryTreeNode* tree2)
{
	queue<BinaryTreeNode*> tree1_set,tree2_set;
	// cout << tree1_set.empty() << " " << tree1_set.empty() << endl;
	tree1_set.push(tree1);
	tree2_set.push(tree2);
	// cout << tree1_set.empty() << " " << tree1_set.empty() << endl;
	BinaryTreeNode *tree1_current,*tree2_current;
	while(!tree1_set.empty() && !tree2_set.empty())
	{
		tree1_current = tree1_set.front();
		tree2_current = tree2_set.front();
		tree1_set.pop();
		tree2_set.pop();
		if(tree1_current->m_nValue != tree2_current->m_nValue)
			return false;
		else
		{
			if(tree2_current->m_pLeft)
			{
				if(!tree1_current->m_pLeft)
					return false;
				else
				{
					tree1_set.push(tree1->m_pLeft);
					tree2_set.push(tree2->m_pLeft);
				}
				
			}
			else continue;
			if(tree2_current->m_pRight)
			{
				if(!tree1_current->m_pRight)
					return false;
				else
				{
					tree1_set.push(tree1->m_pRight);
					tree2_set.push(tree2->m_pRight);
				}				
			}
			else continue;
		}
	}
	return true;
}

bool CompareSubRecursively(BinaryTreeNode* tree1,BinaryTreeNode* tree2)
{
	if(!tree2)
		return true;
	if(!tree1)
		return false;
	if(tree1->m_nValue != tree2->m_nValue)
		return false;
	return CompareSubRecursively(tree1->m_pLeft,tree2->m_pLeft) & CompareSubRecursively(tree1->m_pRight,tree2->m_pRight);
}


bool JudgeSubtree(BinaryTreeNode* tree1,BinaryTreeNode* tree2)
{
	if(!tree2)
		return true;
	if(!tree1)
		return false;
	queue<BinaryTreeNode*> tree1_queue;
	tree1_queue.push(tree1);
	BinaryTreeNode* current_node = tree1;
	while(!tree1_queue.empty())
	{
		current_node = tree1_queue.front();
			tree1_queue.pop();
		if(CompareSub(current_node,tree2) == true)
		{
			return true;
		}
		else
		{
			if(current_node->m_pLeft)
				tree1_queue.push(current_node->m_pLeft);
			if(current_node->m_pRight)
				tree1_queue.push(current_node->m_pRight);
		}
	}
	return false;
}
bool JudgeSubtreeRecursively(BinaryTreeNode* tree1,BinaryTreeNode* tree2)
{
	if(!tree2)
		return true;
	if(!tree1)
		return false;
	bool result = false;
	if(tree1->m_nValue == tree2->m_nValue)
		result = CompareSubRecursively(tree1,tree2);
	if(!result && tree1->m_pLeft)
		result = JudgeSubtreeRecursively(tree1->m_pLeft,tree2);
	if(!result && tree1->m_pRight)
		result =JudgeSubtreeRecursively(tree1->m_pRight,tree2);
	return result;
}

void TestSizeofPointer()
{
	int *ptr,array[3];
	// 这句话求出的是对应的指针变量的大小而非数组的大小，牢记
	cout << sizeof(ptr) << endl;
	//即便指针变量已经指向一个数组，对其求sizeof得到的仍然是指针变量的大小
	ptr = array;
	cout << sizeof(ptr) << endl;
	cout << sizeof(array) << endl;
	//也就是所有指针的大小均为8字节
}

void MirrorTree(BinaryTreeNode* root)
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
			node_queue.push(current_node->m_pRight);
			node_queue.push(current_node->m_pLeft);
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



// 输入一棵树的后序遍历序列，判断是否为二叉搜索树
//二叉搜索树：左子树的节点都比根小，右子树的节点都比根大。
bool VerifySquenceOfBST(int sequence[],int length)
{
	if(!sequence || length <= 0)
		throw runtime_error("arg error");
	if(length == 1)
		return true;
	int root = sequence[length - 1];
	int i = 0;
	while(i < length - 1 && sequence[i] < root)
		++ i;
	if(i == length - 1)
		return VerifySquenceOfBST(sequence,length - 1);//右子树为空
	for(int j = i;j < length - 1;j ++)
	{
		if(sequence[j] <= root)
			return false;
	}
	if(i == 0)
		return VerifySquenceOfBST(sequence,length - 1);//左子树为空
	return VerifySquenceOfBST(sequence,i) && VerifySquenceOfBST(sequence + i,length - i - 1);
}

int main()
{
	// int *pre_order_set,*in_order_set;
	// CreateTreeOrderSeq("input.txt",1,&pre_order_set,&in_order_set);
	// int **pre_order_set,**in_order_set;
	// CreateTreeOrderSeq("input.txt",1,&pre_order_set,&in_order_set);
	// print(cout,*pre_order_set,7);
	// print(cout,*in_order_set,7);
	// // TestSizeofPointer();
	// print(cout,pre_order_set[1],3);
	// print(cout,in_order_set[1],3);
	// BinaryTreeNode* head = Construct(*pre_order_set,*in_order_set,7);
	// PrintTree(head);
	// PrintTreeWithoutEmptyNode(head);
	// MirrorTree(head);
	// BinaryTreeNode* head2 = Construct(pre_order_set[1],in_order_set[1],3);
	// PrintTree(head2);

	// BinaryTreeNode* head3 = Construct(pre_order_set[2],in_order_set[2],3);
	// PrintTree(head3);

	// cout << JudgeSubtree(head,head2) << endl;
	// cout << JudgeSubtree(head,head3) << endl;
	// cout << JudgeSubtreeRecursively(head,head2) << endl;
	// cout << JudgeSubtreeRecursively(head,head3) << endl;

	
	// cout << ConstructPreOrder(head);
	// cout << ConstructInOrder(head);
	// cout << ConstructPostOrder(head);
	// int seq1[] = {5,7,6,9,11,10,8};
	// int seq2[] = {7,4,6,5};
	// cout << VerifySquenceOfBST(seq1,7) << endl;
	// cout << VerifySquenceOfBST(seq2,4) << endl;

	// TestTreePrintFunc();
	BinaryTreeNode* root = CreateBinarySortingTree(cin);
	PrintTree(root);
  	return 0;
}