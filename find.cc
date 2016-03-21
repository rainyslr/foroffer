#include <iostream>
using namespace std;

template <typename T>
int BinarySearch(T* array,const int size,const T& key)
{
	int low = 0,high = size;
	int mid;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(array[mid] == key)
			return mid;
		else if(array[mid] < key)
		{
			low = mid + 1;
		}
		else if(array[mid] > key)
		{
			high = mid - 1;
		}
	}
		return -1;
}

template <typename T>
int BinarySearchRecursively(T* array,const int low,const int high,const T& key)
{
	if(low > high)
		return -1;
	int mid = (high + low) / 2;
	if(array[mid] == key)
		return mid;
	else if(array[mid] < key)
		return BinarySearchRecursively(array,mid + 1,high,key);
	else if(array[mid] > key)
		return BinarySearchRecursively(array,low,mid - 1,key);
}

void TestBinarySearch()
{
	int data[] = {1,2,4,5,5,9};
	cout << "search 9:" << BinarySearchRecursively(data,0,6,9) << endl;
	cout << "search 2:" << BinarySearchRecursively(data,0,6,2) << endl;
	cout << "search 3:" << BinarySearchRecursively(data,0,6,3) << endl;
	cout << "search 9:" << BinarySearch(data,6,9) << endl;
	cout << "search 2:" << BinarySearch(data,6,2) << endl;
	cout << "search 3:" << BinarySearch(data,6,3) << endl;

}

int main()
{
	TestBinarySearch();
	return 0;
}