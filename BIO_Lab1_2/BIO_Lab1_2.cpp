// BIO_Lab1_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int NumberOfPattern(char* dnk, char* pattern, int n)
{
	int tmp = 0;	// число вхождений
	for (int i = 0; i < strlen(dnk); i++)
	{
		// сравнивает strlen(pattern) символов dnk с pattern 
		if (strncmp((dnk + i), pattern, n) == 0)
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
		char dnk[80];
		char strlength[5];
		fin.getline(dnk, 80);	// считать строку ( не больше 30 символов)
		fin.getline(strlength, 5);	// считать 2 строку (5 символов)
		fin.close();
		cout << dnk << endl;
		cout << strlength << endl;
		int n = atoi(strlength);	// перевод 2-й строки в int

		char *pattern = new char[80];
		vector<int> count(80);
		char** resPattern = new char*[80];
		for (int i = 0; i < 80; i++)
		{
			resPattern[i] = new char[80];
		}
		char** tmpStr = new char*[80];
		for (int i = 0; i < 80; i++)
		{
			tmpStr[i] = new char[80];
		}
		for (int i = 0; i < strlen(dnk) - (n - 1); i++)
		{
			int temp = 0;
			strncpy_s(pattern, 80, (dnk + i), n);
			temp = NumberOfPattern(dnk, pattern, n);
			count[i] = temp;
			strcpy_s(resPattern[i], 80, pattern);
		}
		int max = 0;
		for (int i = 0; i < count.size(); i++)
		{
			if (count[i] > max)
				max = count[i];
		}
		char* srav = new char[1];
		int t = 0;
		int res = 0;
		for (int i = 0; i < strlen(dnk) - (n - 1); i++)
		{
			if (count[i] == max)
			{
				res = count[i];
				// заносим в tmpstr resPattern[i] (чаще всего встречающийся кусок)
				tmpStr[t] = resPattern[i];
				t++;
			}
		}
		for (int i = 0; i < t; i++)
		{
			int k = 0;
			for (int j = 0; j < i; j++)
			{
				if (strcmp(tmpStr[i], tmpStr[j]) == 0)
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
