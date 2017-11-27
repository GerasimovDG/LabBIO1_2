// BIO_Lab1_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int NumberOfPattern(string dnk0, string pattern0, int n)
{
	int tmp = 0;	// число вхождений
	for (int i = 0; i < dnk0.size(); i++)
	{
		string strdnk = dnk0.substr(i, n);
		// сравнивает n символов dnk с pattern 
		if (strdnk == pattern0)
			tmp++;
	}
	return tmp;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{
		string dnk;
		string strlength;
		getline(fin, dnk, '\n');	// считываем 1 строку
		getline(fin, strlength, '\n');	// считываем 2 строку
		fin.close();
		cout << dnk << endl;
		cout << strlength << endl;
		if (dnk.empty() || strlength.empty())
		{	// если одна из строк пустая - выход
			return 0;
		}
		int n = atoi(strlength.c_str());// перевод 2-й строки в int

		string pattern;
		vector<int> count;
		vector<string> resPattern;
		vector<string> tmpStr;

		for (int i = 0; i < dnk.size() - (n - 1); i++)
		{
			int temp = 0;
			pattern.insert(0, dnk, i, n);	// заносим часть днк в pattern
			temp = NumberOfPattern(dnk, pattern, n);	//считаем число повторений
			count.insert(count.end(), temp);	// заносим это число в count
			resPattern.insert(resPattern.end(), pattern);	// добавляем сам pattern в resPattern
			pattern.clear();	// pattern зануляем
		}
		int max = 0;
		for (int i = 0; i < count.size(); i++)
		{
			if (count[i] > max)
				max = count[i];
		}
		int t = 0;
		int res = 0;
		for (int i = 0; i < dnk.size() - (n - 1); i++)
		{
			if (count[i] == max)
			{
				res = count[i];
				// заносим в tmpstr resPattern[i] (чаще всего встречающийся кусок)
				tmpStr.insert(tmpStr.end(), resPattern[i]);
				t++;
			}
		}
		for (int i = 0; i < t; i++)
		{
			int k = 0;
			for (int j = 0; j < i; j++)
			{
				if (tmpStr[i] == tmpStr[j])
				{	// если строки совпали, увеличиваем счетчик
					k++;
				}
			}
			if (k == 0)	// если совпадений не было
			{			// печатаем
				cout << tmpStr[i] << endl;
				fout << tmpStr[i] << endl;
			}
		}
		fout.close();
	}
	return 0;
}
