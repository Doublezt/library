#include "stdafx.h"
#include "QueryAuthorService.h"
#include <iostream>
#include <string>
using namespace std;

void QueryAuthorService()//��������servlet 
{
	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "����0���������� ����1����id�������� ����2������������ѯ����" << endl;
		cin >> choose;
		if (!cin)            //�����ɸ�дΪcin.fail() 
		{
			cout << endl;
			cout << "�����д�!����������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			choose = 1;
			continue;
		}
		switch (choose)
		{
			int choose2;
		case 0:return;
		case 1:
			choose2 = 1;
			while (choose2)
			{
				cout << endl;
				cout << "����������id�� ����0�������߲���������" << endl;
				cin >> choose2;
				if (!cin)            //�����ɸ�дΪcin.fail() 
				{
					cout << endl;
					cout << "�����д�!����������" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					choose2 = 1;
					continue;
				}
				if (choose2 == 0)
				{
					break;
				}
				list<Author> authorList= getAuthorById(choose2);
				if(authorList.size()==0)
				{
					cout << "�����ڸ�����id" << endl;
				}
				else
					showAuthorInfo(authorList);
			}
			break;
		case 2:
			choose2 = 1;
			while (choose2)
			{
				string authorName;
				cout << endl;
				cout << "�������������� ����0�������߲���������" << endl;
				cin >> authorName;
				if (!cin) {
					cout << endl;
					cout << "�����д�!����������" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					choose2 = 1;
					continue;
				}
				if (authorName=="0")
				{
					choose2 = 0;
					break;
				}
				list<Author> authorList = getAuthorByName(authorName);
				if (authorList.size()==0)
				{
					cout << endl;
					cout << "�����ڸ������Ķ���" << endl;
					continue;
				}
					showAuthorInfo(authorList);
			}
			break;
		default:
			cout << endl;
			cout << "����ȷ����ѡ�" << endl;
			break;
		}
	}
}