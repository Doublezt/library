#include "stdafx.h"
#include "QueryBorrowRecordService.h"
#include "BookFunc.h"
#include "ReaderFunc.h"
void QueryBorrowRecordService()
{
	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "����0���������� ����1�����鼮id��ѯ���ļ�¼ ����2���ݶ���id��ѯ���ļ�¼" << endl;
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
			int bookId;
			bookId = 1;
			while (bookId)
			{
				int bookId;
				cout << endl;
				cout << "�������鼮id�� ����0���ؽ��ļ�¼��ѯ������" << endl;
				cin >> bookId;
				if (!cin)            //�����ɸ�дΪcin.fail() 
				{
					cout << endl;
					cout << "�����д�!����������" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					bookId = 1;
					continue;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if(bookId ==0)
				{
					break;
				}
				list<Book> bookList = getBookById(bookId);
				if(bookList.size() == 0 )
				{
					cout << endl;
					cout << "�����ڸ��鼮id!" << endl;
					continue;
				}
				list<BorrowRecord> borrowRecord = getRecordByBookId(bookId);
				if (borrowRecord.size() ==0)
				{
					cout << endl;
					cout << "���鼮��ǰû�б�����" << endl;
					continue;
				}
				showBorrowRecordInfo(borrowRecord);
			}
			break;
		case 2:
			int readerId;
			readerId = 1;
			while (readerId)
			{
				cout << endl;
				cout << "���������id�ţ�����0���ؽ��ļ�¼��ѯ������" << endl;
				cin >> readerId;
				if (!cin)            //�����ɸ�дΪcin.fail() 
				{
					cout << endl;
					cout << "�����д�!����������" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					readerId = 1;
					continue;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if(readerId == 0)
				{
					break;
				}
				list<Reader> readerList = getReaderById(readerId);
				if(readerList.size() ==0)
				{
					cout << endl;
					cout << "�����ڸö��ߣ�" << endl;
					continue;
				}
				list<BorrowRecord> borrowRecord = getRecordsByReaderId(readerId);
				if (borrowRecord.size() == 0)
				{
					cout << endl;
					cout << "�ö��ߵ�ǰû�н����鼮" << endl;
					continue;
				}
				showBorrowRecordInfo(borrowRecord);
			}
			break;
		default:
			cout << endl;
			cout << "����ȷ����ѡ�" << endl;
			break;
		}
	}
}
