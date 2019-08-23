#include "stdafx.h"
#include "QueryBooksByAuthorService.h"
#include "string"
#include "showInfo.h"

void QueryBooksByAuthorService()
{
	 int choose;
	 choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "����0���������� ����1��������id��ѯ�鼮" << endl;
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
				cin >> authorId;
				if (!cin)            //�����ɸ�дΪcin.fail() 
				{
					cout << endl;
					cout << "�����д�!����������" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					authorId = 1;
					continue;
				}
				if(authorId == 0)
				{
					break;
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
