#include <iostream>
// #include "helper.h"
using namespace std;

void print(ostream & os,int data[],int length)
{
	for(int i = 0;i < length; ++ i)
		os << data[i] << " " ;
	os << endl;
}

void print(ostream & os,int data[],int length,int pos)
{
	cout << "position is:" << pos << ",";
	for(int i = 0;i < length; ++ i)
		os << data[i] << " " ;
	os << endl;
}


//所有排序都是升序排序
void SelectionSorter(int* data,int length)
{
	if(!data || length <= 0)
		throw runtime_error("arg error");
	int processing_index = 0,min_index;
	int temp;
	for(;processing_index < length;++ processing_index)
	{
		min_index = processing_index;
		for(int j = processing_index + 1;j < length;++ j)
		{
			if(data[j] < data[min_index])
			{
				min_index = j;
			}
		}
		if(min_index != processing_index)
		{
			temp = data[processing_index];
			data[processing_index] = data[min_index];
			data[min_index] = temp;
		}
	}
}

// 二路选择排序
void TwoEleSelectionSorter(int *data,int length)
{
	if(!data || length <= 0)
		throw runtime_error("arg error");
	int min,max,temp,i,j;
	for(i = 0;i < length / 2; ++ i)
	{
		min = max = i;
		for(j = i + 1;j < length - i; ++j)
		{
			if(data[j] > data[max])
				max = j;
			if(data[j] < data[min])
				min = j;
		}
		if(min != i)
		{
			temp = data[i];
			data[i] = data[min];
			data[min] = temp;
		}
		if(max != i)
		{
			temp = data[length - i - 1];
			data[length - i - 1] = data[max];
			data[max] = temp;
		}
		print(cout,data,10);
	}
}

/** 
 * 已知H[s…m]除了H[s] 外均满足堆的定义 
 * 调整H[s],使其成为大顶堆.即将对第s个结点为根的子树筛选,  
 * 
 * @param H是待调整的堆数组 
 * @param s是待调整的数组元素的位置 
 * @param length是数组的长度 
 * 
 */  
void HeapAdjust(int H[],int s, int length)  
{  
    int tmp  = H[s];  
    int child = 2*s+1; //左孩子结点的位置。(i+1 为当前调整结点的右孩子结点的位置)  
    while (child < length) {  
        if(child+1 <length && H[child]<H[child+1]) { // 如果右孩子大于左孩子(找到比当前待调整结点大的孩子结点)  
            ++child ;  
        }  
        if(H[s]<H[child]) {  // 如果较大的子结点大于父结点  
            H[s] = H[child]; // 那么把较大的子结点往上移动，替换它的父结点  
            s = child;       // 重新设置s ,即待调整的下一个结点的位置  
            child = 2*s+1;  
        }  else {            // 如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出  
             break;  
        }  
        H[s] = tmp;         // 当前待调整的结点放到比其大的孩子结点位置上  
    }  
    print(cout,H,length);  
}  
  
  
/** 
 * 初始堆进行调整 
 * 将H[0..length-1]建成堆 
 * 调整完之后第一个元素是序列的最小的元素 
 */  
void BuildingHeap(int H[], int length)  
{   
    //最后一个有孩子的节点的位置 i=  (length -1) / 2  
    for (int i = (length -1) / 2 ; i >= 0; --i)  
        HeapAdjust(H,i,length);  
}  
/** 
 * 堆排序算法 
 */  
void HeapSort(int H[],int length)  
{  
    //初始堆  
    BuildingHeap(H, length);  
    //从最后一个元素开始对序列进行调整  ，当最后一个元素与堆顶交换并调整后，最大元素就落到了数组的最后边，也就是所谓的出堆
    for (int i = length - 1; i > 0; --i)  
    {  
        //交换堆顶元素H[0]和堆中最后一个元素  
        int temp = H[i]; H[i] = H[0]; H[0] = temp;  
        //每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整  
        HeapAdjust(H,0,i);  
  }  
}   

void BubbleSorter(int* data,int length)
{
	if(!data || length <= 0)
		throw runtime_error("arg error");
	int temp,compare_times;
	for(int round = 1;round < length;++ round)
	{
		compare_times = length - round;
		for(int i = 0;i < compare_times;++ i)
		{
			if(data[i] > data[i + 1])
			{
				temp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = temp;
			}

		}	
	}
}

void BubbleSorter1(int* data,int length)
{
	if(!data || length <= 0)
		throw runtime_error("arg error");
	int i = length - 1;
	int temp;
	while(i > 0)
	{
		int pos = 0;
		for(int j = 0;j < i;++ j)
		{
			if(data[j] > data[j + 1])
			{
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
				pos = j;
			}

		}
		i = pos;
	}
}

void BubbleSorter2(int* data,int length)
{
	if(!data || length <= 0)
		throw runtime_error("arg error");
	int low = 0,high = length - 1;
	int temp;
	while(low < high)
	{
		for(int j = low;j < high;++ j)
		{
			if(data[j] > data[j + 1])
			{
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
		high --;
		for(int j = high;j > low;-- j)
		{
			if(data[j] < data[j - 1])
			{
				temp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = temp;
			}
		}
		low ++;
	}
}

void swap(int* num1,int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
	return;
}

int PartionSingle(int data[],int length,int start,int end)
{
	//从左边开始，最右边的数是哨兵，small纪录最近一个比哨兵小的元素应该存放的位置（当该索引值与
	// 当前访问索引i相等，则说明前面的数都是比哨兵小的数，无需交换
	// 否则需要将最近找到的比哨兵小的数挪至small
	if(data == NULL || length < 0 || start < 0 || end >= length || start > length)
		return -1;
	int small  = start - 1;
	for(int i = start;i < end; ++ i)
	{
		if(data[i] < data[end])
		{
			++ small;
			if(small != i)
			{
				swap(data + small,data + i);
			}
		}
	}
	++ small;
	swap(data + small,end + data);
	return small;
}

int Partition(int data[],int low,int high)
{
	// 两边开始进行坐标移动
	int key = data[low];
	while(low < high)
	{
		while(data[high] >= key && high > low)
			high --;
		swap(data + high,data + low);
		// print(cout,data,10);
		while(data[low] <= key && high > low)
			low ++;
		swap(data + high,data + low);
		// print(cout,data,10);
	}
	return low;
}


void QuickSorter(int* data,int low,int high)
{
	if(low < high)
	{
		int index = Partition(data,low,high);
		QuickSorter(data,low,index - 1);
		QuickSorter(data,index + 1,high);
	}
}

//直接插入排序
void StraightInSertionSorter(int data[],int length)
{
	if(!data || length <= 0)
		throw runtime_error("arg error");
	int key,previous_index;
	for(int i = 1;i < length;++ i)
	{
		key = data[i];
		int j;
		for(j = i - 1;data[j] > key && j >= 0;-- j)
			data[j + 1] = data[j];
		data[j + 1] = key;
	}
	return;
}

 void BinaryInsertSorter(int data[],int length)
 {
 	if(!data || length <= 0)
		throw runtime_error("arg error");
	int key,left,right,mid,next_index;
	for(int i = 1;i < length;++ i)
	{
		key = data[i];
		left = 0;
		right = i -1;
		while(left <= right)
		{
			mid = (left + right) / 2;
			if(data[mid] < key)
				left = mid + 1;
			else if(data[mid] > key)
				right = mid - 1;
			else{
				next_index = mid;
				while(data[next_index] == key)
					next_index ++;
				goto move;
			}
		}
		next_index = left;
	move:
		int j;
		for(j = i - 1;j >=next_index;-- j)
			data[j + 1] = data[j];
		data[j + 1] = key;
	}

 }

void BinaryRoadInsertSorter(int data[],int length)
{
	int *temp = new int [length];
	temp[0] = data[0];
	int small,big;
	small = big = 0;
	for(int i = 1;i < length;++ i)
	{
		if(data[i] < temp[small])
		{
			small = (small - 1 + length) % length;
			temp[small] = data[i];
		}
		else if(data[i] > temp[big])
		{
			big = (big + 1 + length) % length;
			temp[big] = data[i];
		}
		else
		{
			int insert_index = (big + 1 + length) % length;
			while(temp[(insert_index - 1 + length) % length] > temp[insert_index])
			{
				temp[insert_index] = temp[(insert_index - 1 + length) % length];
				insert_index = (insert_index - 1 + length) % length;
			}
			insert_index = (insert_index + 1 + length) % length;
			temp[insert_index] = data[i];
		}

	}
	for(int i = 0;i < length;++ i)
	{
		data[i] = temp[(small + i + length) % length];
	}
}

void ShellInsertSort(int data[],int length,int dk)
{
	//以dk对数组元素分组，对每一组数进行有序插入
	//直接插入排序的时候，previous_index比i小1，此处变为小dk
	// 和直接插入排序类似，只是逻辑上相邻的两个元素物理上相邻dk
	int key;
	for(int i = dk;i < length;)
	{
		key = data[i];
		int previous_index = i - dk;
		while(data[previous_index] > key && previous_index >= 0)
		{
			data[previous_index + dk] = data[previous_index];
			previous_index -= dk;
		}
		data[previous_index + dk] = key;
		print(cout,data,length,i);
		i += 1;
	}
}

void ShellSorter(int data[],int length)
{
	if(!data || length <= 0)
		throw runtime_error("arg error");
	int dk = length / 2;
	while(dk)
	{
		cout << "start when dk is:" << dk << endl;
		ShellInsertSort(data,length,dk);
		dk /= 2;
		
	}
}


void Merge(int sourceArr[],int tempArr[], int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j=midIndex+1, k = startIndex;
    while(i!=midIndex+1 && j!=endIndex+1)
    {
        if(sourceArr[i] >= sourceArr[j])
            tempArr[k++] = sourceArr[j++];
        else
            tempArr[k++] = sourceArr[i++];
    }
    while(i != midIndex+1)
        tempArr[k++] = sourceArr[i++];
    while(j != endIndex+1)
        tempArr[k++] = sourceArr[j++];
    for(i=startIndex; i<=endIndex; i++)
        sourceArr[i] = tempArr[i];
}

//内部使用递归，二路归并算法
void BinaryMergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
	//其实这个才更像希尔排序，但是希尔排序中每一组的元素是间隔dk，而这边是紧挨着的若干个元素
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = (startIndex + endIndex) / 2;
        BinaryMergeSort(sourceArr, tempArr, startIndex, midIndex);
        BinaryMergeSort(sourceArr, tempArr, midIndex+1, endIndex);
        Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
    }
}

//内部使用递归，从小增量开始归并
void MergeSort(int sourceArr[], int tempArr[],int length)
{
	int len = 2,step = 1;
	while(step < length)
	{
		// cout << "len:" << len << endl;
		
		int i = 0;
		//实际上就是数组中剩余没处理的数数目超过len，
		while(i + len < length)
		{
			Merge(sourceArr,tempArr,i,i + step - 1,i + len - 1);
			i += len;
			
		}
		if(i + step < length)//剩下的数据长度大于step又小于len，所以还是需要合并
		{
			Merge(sourceArr,tempArr,i,i + step - 1,length- 1);
		}
		len *= 2;
		step = len / 2;
	}
}

int main()
{
	// ArrayData **data = ReadIntArrays("input.txt",1);
	// cout << data[0] << endl;
	int a[] = {1,4, 7,2,9,3,5};
	int a1[] = {1,4, 7,2,9,3,5};
	int a3[] = {49,38,65,97,76,13,27,49,55,4};
	int a4[] = {5,2,6,1};
	// SelectionSorter(a,7);
	// BubbleSorter(a1,7);
	// SelectionSorter(a,7);
	// print(cout,a,7);
	// BinaryInsertSorter(a,7);
	// print(cout,a,7);
	// print(cout,a1,7);
	print(cout,a3,10);
	// ShellSorter(a3,10);
	// StraightInSertionSorter(a3,10);
	// TwoEleSelectionSorter(a3,10);
	// HeapSort(a3,10);
	// BubbleSorter1(a3,10);
	// BubbleSorter2(a3,10);
	// QuickSorter(a3,0,9);
	int b[10] = {0};  
    MergeSort(a3, b, 10); 
 //    print(cout,b,10);    
	print(cout,a3,10);
	// MyMergeSort(a4,4);
}