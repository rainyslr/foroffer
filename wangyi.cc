#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

/*******************************************************************************
// 按照关联度和输入顺序输出n个书目列表。输入以n代表结束
输入
2 5 7
4 8
15 20      
5 3 
3 8 
2 9 11
n
输出
2 5 7
5 3 
3 8 
4 8
15 20 
2 9 11
*******************************************************************************/

void PrintBookList(ostream& ous,vector< std::vector<string> >&book_list);
void PrintItem(const string& word,map<string,vector<int> >&related,int amout)
{
	map<string,vector<int> >::iterator iter = related.find(word);
	if(iter == related.end())
		cout << "cant find the word" << endl;
	else
	{
		cout << iter->first << ":";
		for(int i = 0;i < amout;++ i)
			cout << (iter->second)[i] << " ";
		cout << endl;
	}
}

void PrintRealte(ostream& ous,map<string,vector<int> >&related,int amout = 6)
{
	ous << "related table:" << endl;
	map<string,vector<int> >::iterator iter = related.begin();
	for(;iter != related.end();++ iter)
	{
		ous << iter->first << "\t\t:";
		for(int i = 0;i < amout;++ i)
			ous << (iter->second)[i] << "\t";
		ous << endl;
	}
	ous << endl;
}

void Print(ostream& ous,map<int,string>&list)
{
	map<int,string>::iterator iter = list.begin();
	for(;iter != list.end();++ iter)
		ous << iter->second << endl;
	ous << endl;
}
//如果related定义为map<string,int* >，不知道为什么最后得到的关系表总是随机的
void ReadList(istream& ins,map<int,string>&list,vector< std::vector<string> >&book_list,map<string,vector<int> >&related)
{
	int user_amout = 0;
	string line,word;
	map<string,vector<int> >::iterator realated_iter ;


	for(int i = 0;;++ i)
	{
		getline(ins, line);
		if(line == "n")
			break;
		list[i] = line;
		istringstream ins(line);
		std::vector<string> usr_words;
		while(ins >> word)
		{
			usr_words.push_back(word);
			
		}
		book_list.push_back(usr_words);
		user_amout ++;
	}

	for(int j = 0;j < user_amout;++ j)
	{
		int amout = book_list[j].size();
		for(int i = 0;i < amout;++ i)
		{
			word = book_list[j][i];
			realated_iter = related.find(word);

			if(realated_iter == related.end())
			{
				std::vector<int> vec(user_amout,0);
				vec[j] = 1;
				related[word] = vec;
			}
			else
			{
				(realated_iter->second)[j] = 1;//表明用户i有这个单词
			}
			
		}

	}
	
}


void PrintBookList(ostream& ous,vector< std::vector<string> >&book_list)
{
	ous << "book table:" << endl;
	vector< std::vector<string> >::iterator iter = book_list.begin();
	for(;iter != book_list.end();++ iter)
	{
		int amout = iter->size();
		for(int i = 0;i < amout;++ i)
			ous << (*iter)[i] << " ";
		ous << endl;
	}
	ous << endl;
}

void SortList(ostream& ous,map<int,string>&list,vector< std::vector<string> >&book_list,map<string,vector<int> >&related)
{
	map<int,string>::iterator current = list.begin();
	std::vector<string>::iterator w_iter;
	int usr_ind;
	int min_next;
	int usr_amout = list.size();
	string related_word;
	while(1)
	{
		ous << current->second << endl;
		//find next usr list
		usr_ind = current->first;
		list.erase(current);
		if(list.empty())
			break;

		std::vector<string> words = book_list[usr_ind];
		min_next = usr_amout;
		for(w_iter = words.begin();w_iter != words.end();++ w_iter)
		{
			related[*w_iter][usr_ind] = 0;//在关联数据表中删除其纪录
			for(int i = 0;i < usr_amout;++ i)
			{
				if(related[*w_iter][i])
				{
					if(i < min_next)
						min_next = i;
					break;
				}
			}
				
		}

		if(min_next == usr_amout)
		{
			//没有关联数据
			current = list.begin();
		}
		else
		{
			current = list.find(min_next);
		}

	}
}

int main()
{
	ifstream inf("input.txt");
	ofstream ouf("output.txt");
	map<int,string> list;
	vector< std::vector<string> > book_list;
	map<string, vector<int> > related;
	ReadList(inf,list,book_list,related);
	PrintBookList(ouf,book_list);
	// Print(ouf,list);
	PrintRealte(ouf,related,list.size());
	SortList(ouf,list,book_list,related);
	return 0;
}




