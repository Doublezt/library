

#include"stdafx.h"
//���ļ�¼�ͽ�����ʷ����
#include<iostream>
#include"BorrowHistoryFunc.h"
#include"BookFunc.h"
#include "ReaderFunc.h"
#include"showInfo.h"
#include <list>
#include "Structs.h"
#include "BorrowRecordFunc.h"
#include"DealFault.h"

using namespace std;


void QueryBorrowHistoryService() {

	list<BorrowHistory> borrowHistoryList;

	int bookId;
	int readerId;
	int choice;

	for (;;) {
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "������ѡ�����id��ѯ�������id��ѯ" << endl;
		cout << endl;
		cout << "1.��ѯ���߽�����ʷ" << endl;
		cout << "2.��ѯĳ����Ľ�����ʷ" << endl;
		cout << "3.��ѯ���н�����ʷ" << endl;
		while (1)
		{
			cout << endl;
			cout << "�������ѯ��ʽ��";
			//cin >> choice;
			/*��������Լ�д��int����������ע�͵���
			�������������chooseֱ�ӵ��ں����ķ���ֵ��
			����������ݲ�����Ҫ��ͷ���-1�����򷵻��������*/

			choice = GetIntFromCin();
			break;
		}
		while (choice != 2 && choice != 1 && choice != 3) {
			while (1)
			{
				cout << endl;
				cout << "��ֻ������1��2��3������������:";
				choice = GetIntFromCin();
				break;
			}
		}

		if (choice == 1) {
			while (1)
			{
				cout << endl;
				cout << "��������ߵ�id��";
				readerId = GetIntFromCin();
				if (readerId < 0) {
					cout << endl;
					cout << "��������ݸ�ʽ����" << endl;
					continue;
				}
				break;
			}

			if (getReaderById(readerId).empty()) {
				cout << endl;
				cout << "�޶�Ӧ��ID�Ķ���" << endl;
				return;
			}
			borrowHistoryList = getHistoryByReaderId(readerId, 1);
			if (borrowHistoryList.empty()) {
				cout << endl;
				cout << "��ѯ������ʷΪ��" << endl;
				return;
			}
			showBorHistoryInfo(borrowHistoryList, 1);
		}
		else if(choice == 2){
			while (1)
			{
				cout << endl;
				cout << "���������id��";
				bookId = GetIntFromCin();
				if (bookId < 0) {
					cout << endl;
					cout << "��������ݸ�ʽ����" << endl;
					continue;
				}
				break;
			}
			if (getBookById(bookId).empty()) {
				cout << endl;
				cout << "�޶�Ӧ��ID����" << endl;
				return;
			}
			borrowHistoryList = getHistoryByBooksId(bookId, 1);
			if (borrowHistoryList.empty()) {
				cout << endl;
				cout << "��ѯ������ʷΪ��" << endl;
				return;
			}
			showBorHistoryInfo(borrowHistoryList, 1);
		}
		else {
			list<BorrowHistory> his = getAllHistory(0);
			showBorHistoryInfo(his, true);
		}
		return;
	}
}



void QueryRecord() {

	int select;
	while (1) {
		cout << "����Ҫ�鿴���м�¼���ǰ��շ�ҳ�鿴��¼?" << endl;
		cout << "1.�鿴���м�¼" << endl;
		cout << "2.���շ�ҳ�鿴��¼" << endl;
		cout << "������ѡ�";
		select = GetIntFromCin();
		switch (select)
		{
		case 1:break;
		case 2:break;
		default:
			cout << "ֻ������1��2��" << endl;
			continue;
		}
		break;
	}

	int i = 1;
	int start = 1;
	list<BorrowRecord> Recordlist;
	switch (select)
	{
	case 1:
		Recordlist = getRecords(1);
		showBorRecordInfo(Recordlist,true);
		break;
	case 2:
		while (1) {
			Recordlist.clear();
			Recordlist = getRecords(start, 5);//ÿҳչʾ5����
			if (Recordlist.empty()) {
				cout << "�Ѿ������¼ĩβҳ��" << endl;
				break;
			}

			cout << endl << endl << "��" << i << "ҳ��¼��Ϣ������ʾ��" << endl;
			showBorRecordInfo(Recordlist,true);
			start = start + 5;
			i++;
			while (1) {
				cout << endl << "���Ƿ�Ҫ�鿴�����¼����������1����������0" << endl;

				cout << "������ѡ�";
				select = GetIntFromCin();
				switch (select)
				{
				case 1:break;
				case 2:break;
				default:
					cout << "ֻ������1��2��" << endl;
					continue;
				}
				break;
			}
			switch (select)
			{
			case 1:continue;//����չʾ��Ϣ
			case 2:break;
			}
			break;
		}
		break;
	}

}


void QueryBorrowRecordService() {
	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "�����룺" << endl;
		cout << "0:����������" << endl;
		cout << "1:�����鼮id��ѯ���ļ�¼" << endl;
		cout << "2:���ݶ���id��ѯ���ļ�¼" << endl;
		cout << "3.��ѯ���н��ļ�¼" << endl;
		choose = GetIntFromCin();
		switch (choose)
		{
		case 0:
			return;
		case 1:
			int bookId;
			bookId = 1;
			while (bookId)
			{
				int bookId;
				cout << endl;
				cout << "�������鼮id�� ����0���ؽ��ļ�¼��ѯ������" << endl;
				bookId = GetIntFromCin();
				if (bookId == 0)
				{
					break;
				}
				if (bookId == -1) {
					cout << "���벻��Ҫ��" << endl;
					continue;
				}

				list<Book> bookList = getBookById(bookId);
				if (bookList.size() == 0)
				{
					cout << endl;
					cout << "�����ڸ��鼮id!" << endl;
					continue;
				}
				list<BorrowRecord> borrowRecord = getRecordByBookId(bookId);
				if (borrowRecord.size() == 0)
				{
					cout << endl;
					cout << "���鼮��ǰû�б�����" << endl;
					continue;
				}
				showBorRecordInfo(borrowRecord, true);
			}
			break;
		case 2:
			int readerId;
			readerId = 1;
			while (readerId)
			{
				cout << endl;
				cout << "���������id�ţ�����0���ؽ��ļ�¼��ѯ������" << endl;
				readerId = GetIntFromCin();
				if (readerId == 0)
				{
					break;
				}
				if (readerId == -1) {
					cout << "���벻��Ҫ��" << endl;
					continue;
				}

				list<Reader> readerList = getReaderById(readerId);
				if (readerList.size() == 0)
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
				showBorRecordInfo(borrowRecord, true);
			}
			break;
		case 3:
			QueryRecord();
			break;
		default:
			cout << endl;
			cout << "����ȷ����ѡ�" << endl;
			break;
		}
	}

}

void QueryExtendedBookService() {

	list<BorrowRecord> recordList;//���ݶ���id�������id��ѯ�����б�
	list<BorrowRecord> extendedRecordList;//���ڼ�¼���б�
	int bookId;
	int readerId;
	int choice;

	for (;;) {
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "��ѡ�����id��ѯ�������id��ѯ" << endl;
		cout << endl;
		cout << "1.��ѯ���߽�����ʷ" << endl;
		cout << "2.��ѯĳ����Ľ�����ʷ" << endl;
		while (1)
		{
			cout << endl;
			cout << "�������ѯ��ʽ��";
			choice = GetIntFromCin();
			break;
		}

		//�ж�������Ƿ�Ϊ0��1
		while (choice != 2 && choice != 1)
		{
			while (1)
			{
				cout << endl;
				cout << "��ֻ������1��2������������:";
				choice = GetIntFromCin();
				break;
			}
		}

		time_t now = time(NULL);//�����Ƚ��Ƿ�����

								//���ݶ���id��ѯ
		if (choice == 1) {
			while (1)
			{
				cout << endl;
				cout << "��������ߵ�id��";
				readerId = GetIntFromCin();
				if (readerId < 0) {
					cout << endl;
					cout << "������鼮��ʽ����" << endl;
					continue;
				}
				break;
			}

			if (getReaderById(readerId).empty()) {
				cout << endl;
				cout << "�޶�Ӧ��ID�Ķ���" << endl;
				return;
			}
			recordList = getRecordsByReaderId(readerId);
			if (recordList.empty()) {
				cout << endl;
				cout << "��¼Ϊ��" << endl;
				return;
			}
			for (list<BorrowRecord>::iterator it = recordList.begin(); it != recordList.end(); it++) {
				if ((*it).rationalTime < now) {
					extendedRecordList.push_back(*it);
				}
			}
			if (extendedRecordList.empty()) {
				cout << endl;
				cout << "��ѯ�ĳ��ڽ��ļ�¼Ϊ��" << endl;
				return;
			}
			showBorRecordInfo(extendedRecordList, true);
		}

		else {
			while (1)
			{
				cout << endl;
				cout << "���������id��";
				bookId = GetIntFromCin();
				if (bookId < 0) {
					cout << endl;
					cout << "�������ݸ�ʽ����" << endl;
					continue;
				}
				break;
			}

			if (getBookById(bookId).empty()) {
				cout << endl;
				cout << "�޶�Ӧ��ID����" << endl;
				return;
			}
			recordList = getRecordByBookId(bookId);
			if (recordList.empty())
			{
				cout << endl;
				cout << "��¼Ϊ��" << endl;
				return;
			}
			for (list<BorrowRecord>::iterator it = recordList.begin(); it != recordList.end(); it++) {
				if ((*it).rationalTime < now) {
					extendedRecordList.push_back(*it);
				}
			}
			if (extendedRecordList.empty()) {
				cout << endl;
				cout << "��ѯ�ĳ��ڽ��ļ�¼Ϊ�գ�" << endl;
				return;
			}
			showBorRecordInfo(extendedRecordList, true);
		}
		return;
	}
}

// ɾ�����ļ�¼(ֻ���ڵ��Գ���, �������ﲻ���е���)
void DeleteBorrowRecordService() {

	int historyId;
	int recordId;
	int choice1;
	for (;;) {
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "������ѡ��ɾ��������ʷ����ɾ�����ļ�¼" << endl;
		cout << endl;
		cout << "1.ɾ��������ʷ" << endl;
		cout << "2.ɾ�����ļ�¼" << endl;
		while (1)
		{
			cout << endl;
			cout << "������ѡ��";
			choice1 = GetIntFromCin();
			break;
		}
		while (choice1 != 2 && choice1 != 1) {
			while (1)
			{
				cout << endl;
				cout << "��ֻ������1��2�����������룺";
				choice1 = GetIntFromCin();
				break;
			}
		}

		if (choice1 == 1) {
			while (1)
			{
				cout << endl;
				cout << "�����������ʷid��";
				historyId = GetIntFromCin();
				if (historyId <0) {
					cout << endl;
					cout << "�������ݸ�ʽ����" << endl;
					continue;
				}
				else
				{
					list<BorrowHistory> history = getHistoryById(historyId, 1);
					if (history.empty())
					{
						cout << endl;
						cout << "�ý�����ʷΪ�գ���ѡ������������Ƿ���" << endl;
						cout << endl;
						cout << "����1��������" << endl;
						cout << "����0����" << endl;
						int choice2;
						while (1) {

							cout << endl;
							cout << "������ѡ��";
							choice2 = GetIntFromCin();
							break;
						}

						while (choice2 != 0 && choice2 != 1) {
							while (1)
							{
								cout << endl;
								choice2 = GetIntFromCin();
								break;
							}
						}
						if (choice2 == 1) {

						}
						else {
							return;
						}
					}
					else {
						list<BorrowHistory>::iterator h = history.begin();
						deleteHistory((*h).id);
						cout << endl;
						cout << "������ʷ��ɾ����" << endl;
						return;
					}
				}
			}
		}



		else {
			while (1)
			{
				cout << endl;
				cout << "��������ļ�¼id��";
				recordId = GetIntFromCin();
				if (recordId < 0) {
					cout << endl;
					cout << "�������ݸ�ʽ����" << endl;
					continue;
				}
				else
				{
					list<BorrowRecord> record = getRecordById(recordId);
					if (record.empty())
					{
						cout << endl;
						cout << "�ý�����ʷΪ�գ���ѡ������������Ƿ���" << endl;
						cout << endl;
						cout << "����1��������" << endl;
						cout << "����0����" << endl;
						int choice2;
						while (1)
						{
							cout << endl;
							cout << "������ѡ��";
							choice2 = GetIntFromCin();
							break;
						}
						while (choice2 != 0 && choice2 != 1) {
							while (1)
							{
								cout << endl;
								cout << "��ֻ������0��1������������:";
								choice2 = GetIntFromCin();
								break;
							}
						}
						if (choice2 == 1) {

						}
						else {
							return;
						}
					}
					else {
						deleteRecord(recordId);
						cout << endl;
						cout << "���ļ�¼��ɾ����" << endl;
						list<Book> returnbook = getBookById((*record.begin()).bookId);
						((*returnbook.begin())).numberInLib++;
						modifyBook(*returnbook.begin());

						return;
					}
				}
			}
		}
	}
}


