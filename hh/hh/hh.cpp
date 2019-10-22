#include "stdafx.h"
#include<iostream>
#include<fstream>
#include <algorithm> 
#include<vector>
#include<string>
using namespace std;
typedef long long ll;
typedef struct {
	string word;
	int num;
	char c;
	double pinlv;
}words;
vector<words> v;//容量
ofstream result("secondfunction.txt");

class myFile {
private:
	int character;
	int word;
	int line;
	int letter;
	string filename;
public:
	myFile();
	myFile(string s);
	void get_character();
	void get_word();
	void get_mostword();
	void get_line();
	//void get_letter();
	void get_all();
	int get_characters() { get_character(); return character; }
	int get_words() { get_word(); return word; }
	int get_lines() { get_line(); return line; }
	//int get_letters() { get_letter(); return letter; }
};
char temp;
bool digit(char a) { if (a >= '0'&&a <= '9')return true; else return false; }//是否数字
bool dic_word(const string &a, const string &b) { return a < b; }//字典序
bool set_word(const words &a, const words &b) { if (a.num == b.num)return a.word < b.word; else return a.num > b.num; }//单词排序
bool myword(char a) { if ((a >= 'a'&&a <= 'z') || (a >= 'A'&&a <= 'Z') || (a >= '0'&&a <= '9'))return true; else return false; }//单词检测
bool Delimiter(char a) { if (a > 122 || a < 48)return true; else if (a < 65 && a>57)return true; else return false; }
// 空白字符检测 
bool ch(char a) { if (a == ' ' || a == '\t' || a == '\n')return true; else return false; }
//void getletter()
//{
//	words
//	for()
//}
myFile::myFile()
{
	character = 0;
	word = 0;
	line = 0;
}
myFile::myFile(string s)
{
	filename = s;
	character = 0;
	word = 0;
	line = 0;
}
void myFile::get_character()
{
	ifstream file(filename);
	if (!file)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	file >> noskipws;// 记录所有字符 
	while (file >> temp)character++;
	file.close();
}
void myFile::get_line()
{
	ifstream file(filename);
	if (!file)
	{
		cerr << "open error!" << endl;
		exit(1);
	}

	int ef = 0; //记录每行中非空白字符个数
	file >> noskipws;// 记录所有字符 

	while (file >> temp)
	{
		if (!ch(temp))ef++; // 空白符之间字符数量 
		if (temp == '\n'&&ef > 0) { line++; ef = 0; }// 判断是否为有效行
	}
	if (ef > 0) { line++; ef = 0; }
}
void myFile::get_word()
{
	ifstream file(filename);
	if (!file)
	{
		cerr << "open error!" << endl;
		exit(1);
	}

	file >> noskipws;// 记录所有字符 

	vector<string>::iterator fir, las;
	vector<words>::iterator wit;
	vector<string>tempstr; // 单词容器，存文件所有单词
	string _word; //  string 临时变量
	words w;  //  words 临时变量
	int flag = 1, wordlen = 0;

	while (file >> temp)
	{
		if (Delimiter(temp))// 判断是否是分隔符
		{
			if (flag = 1 && wordlen > 3)
			{
				transform(_word.begin(), _word.end(), _word.begin(), ::tolower);// 转换为小写 
				word++;
				//存储单词 
				tempstr.push_back(_word);
			}
			wordlen = 0; flag = 1; _word.clear();
		}
		if (myword(temp)) // 单词 
		{
			wordlen++;
			if (wordlen < 3)
				if (!digit(temp) && flag == 1)
				{
					char s[2] = { temp,0 };
					_word += temp;
				}
				else flag = 0;
				if (wordlen >= 3 && flag == 1) { char s[2] = { temp,0 }; _word += temp; }
		}
	}
	//记录最后一个单词 
	if (flag = 1 && wordlen > 3)
	{
		transform(_word.begin(), _word.end(), _word.begin(), ::tolower);// 转换为小写 
		word++;
		//存储单词 
		tempstr.push_back(_word);
	}

	sort(tempstr.begin(), tempstr.end(), dic_word); //将所有单词字典排序，方便后续统计

	for (las = tempstr.begin(), fir = tempstr.begin() + 1; fir != tempstr.end(); fir++)
	{
		if (*fir != *las)
		{
			w.word = *las;
			w.num = fir - las;
			v.push_back(w);
			las = fir;
		}
	}
	//记录最后一个单词
	w.word = *las;
	w.num = fir - las;
	v.push_back(w);
	file.close();
}
void myFile::get_mostword()//排序
{
	sort(v.begin(), v.end(), set_word);  //将单词按符合要求进行排序

	if (v.size() <= 10)
		for (int i = 0; i < v.size(); i++)
			result << "<" << v[i].word << ">: " << v[i].num << endl;//<<"word frequency: " << (float)v[i].num / word << endl;
	else
		for (int i = 0; i < 10; i++)
			result << "<" << v[i].word << ">: " << v[i].num << endl;//<<"word frequency: " << (float)v[i].num / word << endl;

	result.close();

}

void myFile::get_all()
{
	get_character();
	get_word();
	result << "characters: " << character << endl;
	result << "words: " << word << endl;
	result << "lines: " << line << endl;
	get_mostword();
}
int main(int argc, char** argv)
{
	char* name = argv[1];
	myFile infile(name);
	infile.get_all();
	cout << "输出文件为secondfunction.txt" << endl;
	return 0;
}