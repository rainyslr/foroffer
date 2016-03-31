#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void  ResolveString(istream& is,ostream& os)
{
	int str_num,bit_size;
	is >> str_num >> bit_size;
	if(str_num <= 0 || bit_size <= 0)
		throw runtime_error("str_num error or bit_size error");
	string str;
	char *out_str = new char [bit_size + 1];
	for(int i =  0;i < str_num;++ i)
	{
		memset(out_str,'0',bit_size);
		out_str[bit_size] = 0;
		is >> str;
		int str_len = str.size();
		int rest_bit = str_len;
		const char* pos = str.c_str();
		while(rest_bit >= bit_size)
		{
			memcpy(out_str, pos,bit_size);
			os << out_str << ",";
			pos += bit_size;
			rest_bit -= bit_size;

		}
		memset(out_str,'0',bit_size);
		out_str[bit_size] = 0;
		memcpy(out_str,pos,rest_bit);
		os << out_str << ",";
	}
}

void  TransformString(istream& is,ostream& os)
{
	string line;
	getline(is,line);
	const char* pos = line.c_str();
	char number[500];
	memset(number,0,500);
	int copy_pos = 0;
	while(*pos)
	{
		switch(*pos)
		{
			case 'y':
				number[copy_pos ++ ] = '1';
				pos += 2;
				break;
			case 'e':
				number[copy_pos ++ ] = '2';
				pos += 2;
				break;
			case 's':
				pos ++;
				if(*pos == 'a')
				{
					number[copy_pos ++ ] = '3';
					pos += 2;
				}
				else
				{
					number[copy_pos ++ ] = '4';
					pos ++;
				}
				break;
			case 'w':
				number[copy_pos ++ ] = '5';
				pos ++;
				break;
			case 'l':
				number[copy_pos ++ ] = '6';
				pos ++;
				break;
			case 'q':
				number[copy_pos ++ ] = '7';
				pos ++;
				break;
			case 'b':
				number[copy_pos ++ ] = '8';
				pos ++;
				break;
			case 'j':
				number[copy_pos ++ ] = '9';
				pos ++;
				break;		
			default:
				throw runtime_error("input character error");		
		}

	}
	os << number;
}

void RandStr(istream& is,ostream& os)
{
	string str;
	is >> str;
	char ch;
	int count[257] = {0};
	const char* pos = str.c_str();
	while(*pos)
	{
		count[*pos] ++;
		pos ++;
	}
	for(int i = 0;i < 257;++ i)
	{
		if(count[i])
		{
			ch = i;
			os << ch;
		}
	}
}


int main()
{
	ifstream inf("input.txt");
	if(!inf)
	{
		throw runtime_error("open input file error");
	}
	ofstream ouf("output.txt");
	if(!ouf)
	{
		throw runtime_error("open input file error");
	}
	// ResolveString(inf,ouf);
	// TransformString(inf,ouf);
	RandStr(inf,ouf);
	int i = -1 /10;
	cout << i;
	
}