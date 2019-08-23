
#include"stdafx.h"
#include<list>
#include"Structs.h"
#include"AuthorFunc.h"
#include"showInfo.h"
#include <iostream>
#include <string>
#include"DealFault.h"
using namespace std;

void QueryAuthorService() {

	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "�����룺" << endl;
		cout << "0:���������� " << endl;
		cout << "1:����id��������" << endl;
		cout << "2:������������ѯ����" << endl;
		choose = GetIntFromCin();//����choose
		switch (choose)
		{
			int choose2;
		case 0:
			return;
		case 1:
			choose2 = 1;
			while (choose2)
			{
				cout << endl;
				cout << "����������id��(��1��ʼ�������� ����0�������߲���������" << endl;
				choose2 = GetIntFromCin();
				if (choose2 == -1) {
					cout << "���벻��Ҫ��" << endl;
					continue;
				}

				if (choose2 == 0)
				{
					break;
				}
				list<Author> authorList = getAuthorById(choose2);
				if (authorList.size() == 0)
				{
					cout << "�����ڸ�����id" << endl;
				}
				else
					showAuthorInfo(authorList, true);
			}
			break;
		case 2:
			choose2 = 1;
			while (choose2)
			{
				string authorName;
				string key;//����ѡ���Ƿ��˰�����������
				cout << endl << "���Ƿ�Ҫ�˳����ң� ����0�������߲��������棬��������������" << endl;
				getline(cin, key);
				if (key == "0")
					break;
				//����������
				cout << endl << "������������" << endl;
				getline(cin, authorName);
				list<Author> authorList = getAuthorByName(authorName);
				if (authorList.size() == 0)
				{
					cout << endl;
					cout << "�����ڸ������Ķ���" << endl;
					continue;
				}
				showAuthorInfo(authorList, 1);
			}
			break;
		default:
			cout << endl;
			cout << "����ȷ����ѡ�" << endl;
			break;
		}
	}

}


void QueryBooksByAuthorService()
{
	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "�����룺" << endl;
		cout << "0����������" << endl;
		cout << "1��������id��ѯ�鼮" << endl;
		choose = GetIntFromCin();
		switch (choose)
		{
		case 0:return;
		case 1:
			int authorId;
			authorId = 1;
			while (authorId)
			{
				cout << endl;
				cout << "����������id ����0�������߲�ѯ����������" << endl;
				authorId = GetIntFromCin();
				if (authorId == 0)
				{
					break;
				}
				if (authorId == -1) {
					cout << "���벻��Ҫ��" << endl;
					continue;
				}

				list<Book> bookList = getBooksByAuthor(authorId);
				if (bookList.size() == 0)
				{
					cout << endl;
					cout << "�����ڸ�����id��" << endl;
					continue;
				}
				showBooksInfo(bookList);
			}
			break;
		default:
			cout << endl;
			cout << "����ȷ����ѡ�" << endl;
			continue;
		}
	}
}
