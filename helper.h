#include <string>
using namespace std;
struct ArrayData
{
	ArrayData(int* num_array,int length);
	friend std::ostream & operator << (std::ostream & os, const ArrayData & array_data);
	friend std::istream & operator >> (std::istream & is, ArrayData & array_data);
	int* m_data;
	int m_length;
};

std::ostream & operator << (std::ostream & os, const ArrayData & array_data)
{
	for(int i = 0;i < array_data.m_length; ++ i)
		os << array_data.m_data[i] << " " ;
	os << endl;
	return os;
}

std::istream & operator >> (std::istream & ins,ArrayData & array_data)
{

//此时输入文件中数组的格式应该如下；	
// 	7 					//数组大小
// 8 6 5 7 10 9 11		//数组元素
ins >> array_data.m_length;
array_data.m_data = new int [array_data.m_length];
for(int i = 0;i < array_data.m_length;++ i)
	ins >> array_data.m_data[i];
return ins;

}


ArrayData **ReadIntArrays(const string& in_file,int array_amout)
{
	ifstream inf(in_file.c_str());
	if(!inf)
		throw runtime_error("open input file error");
	ArrayData **data = new ArrayData[array_amout];
	for(int i = 0;i < array_amout;++ i)
	{
		inf >> *(data[i]);
	}
	return data;
}


