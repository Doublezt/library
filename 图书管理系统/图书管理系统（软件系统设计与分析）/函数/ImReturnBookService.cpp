#include "stdafx.h"
#include "ReturnBookService.h"
#include <string.h>
using namespace std;
void ReturnBookService(int readerId)
{
	int choose =1;
	list<BorrowRecord> borRecordList = getRecordsByReaderId(readerId);
	list<BorrowRecord>::iterator i;
	while (choose)
	{
		
		cout << endl;
		cout << "����0�˳����鹦�� ����1���л������" << endl;
		cout << "����������ѡ��" << endl;
		int bookId;
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
		case 0:break;
		case 1:
			if (borRecordList.size() == 0)
			{
				cout << endl;
				cout << "��û��Ҫ�����鼮��" << endl;
				return;
			}
			cout << endl;
			cout << "������Ҫ���鼮��id�ţ�";
			cin >> bookId;
			if (!cin)            //�����ɸ�дΪcin.fail() 
			{
				cout << endl;
				cout << "�����д�!����������" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for (i = borRecordList.begin(); i != borRecordList.end(); i++)
			{
				if (bookId == i->bookId)
				{
					time_t now = time(NULL);
					list<Reader> rList = getReaderById(i->readerId);
					list<Reader>::iterator j;
					if (now > i->rationalTime)
					{
						cout << endl;
						cout << "�����ѳ���" << endl;
						j = rList.begin();
						j->fine += (now - i->rationalTime) / (24 * 3600);
					}
					BorrowHistory b;
					b.bookId = i->bookId;
					b.readerId = i->readerId;
					b.borrowTime = i->startTime;
					b.returnTime = now;
					addHistory(b);
					deleteRecord(i->id);
					break;
				}
			}
			if (i == borRecordList.end())
			{
				cout << endl;
				cout << "���ļ�¼��û�ж�ӦID���鼮��,����ʧ��" << endl;
			}
			break;
		default:cout << endl << "����ȷ����ѡ��" << endl;break;
		}
	

	}
	
}