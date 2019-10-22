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
vector<words> v;//����
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
bool digit(char a) { if (a >= '0'&&a <= '9')return true; else return false; }//�Ƿ�����
bool dic_word(const string &a, const string &b) { return a < b; }//�ֵ���
bool set_word(const words &a, const words &b) { if (a.num == b.num)return a.word < b.word; else return a.num > b.num; }//��������
bool myword(char a) { if ((a >= 'a'&&a <= 'z') || (a >= 'A'&&a <= 'Z') || (a >= '0'&&a <= '9'))return true; else return false; }//���ʼ��
bool Delimiter(char a) { if (a > 122 || a < 48)return true; else if (a < 65 && a>57)return true; else return false; }
// �հ��ַ���� 
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
	file >> noskipws;// ��¼�����ַ� 
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

	int ef = 0; //��¼ÿ���зǿհ��ַ�����
	file >> noskipws;// ��¼�����ַ� 

	while (file >> temp)
	{
		if (!ch(temp))ef++; // �հ׷�֮���ַ����� 
		if (temp == '\n'&&ef > 0) { line++; ef = 0; }// �ж��Ƿ�Ϊ��Ч��
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

	file >> noskipws;// ��¼�����ַ� 

	vector<string>::iterator fir, las;
	vector<words>::iterator wit;
	vector<string>tempstr; // �������������ļ����е���
	string _word; //  string ��ʱ����
	words w;  //  words ��ʱ����
	int flag = 1, wordlen = 0;

	while (file >> temp)
	{
		if (Delimiter(temp))// �ж��Ƿ��Ƿָ���
		{
			if (flag = 1 && wordlen > 3)
			{
				transform(_word.begin(), _word.end(), _word.begin(), ::tolower);// ת��ΪСд 
				word++;
				//�洢���� 
				tempstr.push_back(_word);
			}
			wordlen = 0; flag = 1; _word.clear();
		}
		if (myword(temp)) // ���� 
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
	//��¼���һ������ 
	if (flag = 1 && wordlen > 3)
	{
		transform(_word.begin(), _word.end(), _word.begin(), ::tolower);// ת��ΪСд 
		word++;
		//�洢���� 
		tempstr.push_back(_word);
	}

	sort(tempstr.begin(), tempstr.end(), dic_word); //�����е����ֵ����򣬷������ͳ��

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
	//��¼���һ������
	w.word = *las;
	w.num = fir - las;
	v.push_back(w);
	file.close();
}
void myFile::get_mostword()//����
{
	sort(v.begin(), v.end(), set_word);  //�����ʰ�����Ҫ���������

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
	cout << "����ļ�Ϊsecondfunction.txt" << endl;
	return 0;
}