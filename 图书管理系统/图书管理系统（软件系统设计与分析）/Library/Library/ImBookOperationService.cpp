#include "stdafx.h"
#include"Structs.h"
#include<string>
#include"BookFunc.h"
#include"showInfo.h"
#include <array>
#include <unordered_set>
#include"Operation.h"
#include"BorrowRecordFunc.h"
#include"BorrowHistoryFunc.h"
#include"DealFault.h"
#include<sstream>
#define MaxTypeAmount 10//ÿ���������10�����
#define MaxAuthorAmount 10//ÿ��������¼ʮ����Ҫ����
#define MaxFine 20 //���Ƿ���������ߵ�Ƿ��������Ŀ���Ͳ��ܼ���������
using namespace std;



//(readerId�ǵ�ǰ��¼�Ķ��ߵ�id�ţ��������Ὣ���id�������service)
/*�����Service*/
void BorrowBookService(int readerId) {

	//�ȵõ���ǰ���ߵ������ڽ��鼮���ж��Ƿ��������鼮
	//����У���ֹ��ǰ���߽���
	list<BorrowRecord> r = getRecordsByReaderId(readerId);
	for (list<BorrowRecord>::iterator it = r.begin(); it != r.end(); it++) {
		//�����鼮�ı�־�ǣ�Ӧ����ʱ��С�ڵ�ǰʱ��
		if ((*it).rationalTime < time(NULL)) {//���е�����
											  //����Ȿ������1.2�������ĵ��ģ���Ӧ�黹ʱ����2.2�����ĵ�֮ǰ��������2.2�������
											  //ʱ���ǿ��Խ���ġ�������������Ӧ����ÿ��0��00��Ϊ�������е��ڼ�¼����Ӧ�黹ʱ��
											  //���ǰ���ǰһ��˼·��
			cout << endl <<"�����������鼮δ�黹�����ܽ���!��黹�鼮��������顣��������˳���" << endl;
			return;
		}
	}

	if (r.size() >= maxBorrowNum) {
		cout << endl << "���Ѿ�����" << r.size() << "���鼮���ﵽ�������ޣ���������˳���" << endl;
		return;
	}
	r.clear();//�ͷŴ洢�ռ�

	//Ƿ��ﵽĳ����ֵҲ���ܼ�������
	list<Reader> reader = getReaderById(readerId);
	list<Reader>::iterator it = reader.begin();
	if ((*it).fine > MaxFine) {
		cout << endl <<"����Ƿ�����ѳ���20Ԫ�������Ƿ����������!��������˳���" << endl;
		return;
	}



	 //�������ö�������Ҫ����鼮���id

	int id;
	list<Book> book;

	cout << endl << "��������ѡ��" << endl;
	string select;
	cout << endl << "1.��ʼ����" << endl;
	cout << "2.�˳��������" << endl;
	cout << "������ѡ�";
	getline(cin, select);
	trimAllSpace(select);

	while (select != "1" && select != "2") {
		cout << "ֻ������ѡ��1��2��" << endl;

		cout << endl << "1.��ʼ����" << endl;
		cout << "2.�˳��������" << endl;
		cout << "������ѡ�";
		getline(cin, select);
		trimAllSpace(select);
	}

	if (select == "2") return;

		cout << endl << "��������Ҫ����鼮���id:" << endl;
		id = GetIntFromCin();
		if (id <= 0) {
			cout << "��������鼮id�Ÿ�ʽ����" << endl;
			return;
		}

		book = getBookById(id);
		if (book.empty()) {//������鼮�����ڣ�Ҫ����������
			cout << endl << "��������鼮id�����ڣ�" << endl;
			return;
		}
		else {//����鼮���ڣ��жϸ��鼮�ݲ������Ƿ����1
			  //�����Ƿ���Խ��飬Ҫ���û�չʾ����鼮��Ϣ
			cout << endl << "���鼮��Ϣ������ʾ��" << endl;
			showBooksInfo(book);

			list<Book>::iterator b = book.begin();
			if ((*b).numberInLib <= 1) {
				cout << endl << "���鼮�ݲ���������,�������Խ��ĸ��飡" << endl;
				return;//�ö�����������һ���鼮id
			}
			else {//�ݲ������㹻������£��ö���ȷ�Ϻ��ٽ��н������

				string bor;
				while (1) {
					cout << endl << "��ȷ��Ҫ�����Ȿ������������1����������0��" << endl;
					getline(cin, bor);
					trimAllSpace(bor);
					if (bor != "1" && bor != "0")
						cout << endl << "��ֻ������1��0�����������룺" << endl;
					else break;
				}

				if (bor == "1") {
					//ֻ��ȷ��Ҫ���飬�����鼮�ɽ裬�����Ż���е�����
					//������Ҫ����һ�������¼

					BorrowRecord record;
					time_t now = time(NULL);
					if (!setRecordBookId(record, id, now)) {
						cout << "�����¼���������˳�������棡" << endl;
						return;
					}

					record.readerId = readerId;
					record.startTime = now;
					record.rationalTime = now;
					increaseRationalTimeByConst(record);//���ú���黹ʱ��Ϊ����ǰʱ�� + MaxBorrowDay

					if (!addRecord(record)) {
						cout << endl << "�����¼���������˳�������棡" << endl;
						return;
					}
					//����˵�������¼���ɳɹ�
					//������Ӧ������Ӧͼ����������1


					list<Book>::iterator b = book.begin();
					(*b).numberInLib--;
					if (!modifyBook(*b)) {
						//�����Ϊĳ��ԭ����δ�ܳɹ��޸��鼮�Ĺݲ�����
						//�Ǿ�Ӧ��ɾ��֮ǰ���ɵĽ����¼
						deleteRecord(record.id);
						cout << endl << "�����¼���������˳�������棡" << endl;
						return;
					}

					//����ͼ��Ĺݲ���������1�ɹ��޸���

					cout << endl << "����ɹ���" << endl;
					cout << "���ĸ��������¼������ʾ��" << endl;
					showBorRecordInfo(getRecordById(record.id), false);
					return;
				}
				//����ȷ��Ҫ������������������鼮id�����ѭ����,�����ļ�����
				else
					return;//����ͷ���

			}

		}

}


//����ʾ��ǰ���ģ��ö�����������¼��id���л��飬�����¼��ɾ��һ����������ʷ����һ�����ݲ���������
void ReturnBookService(int readerId)
{
	int choose = 1;
	list<BorrowRecord> borRecordList = getRecordsByReaderId(readerId);
	list<BorrowRecord>::iterator i;
	string str2;
	while (choose)
	{

		cout << endl;
		cout << "����0�˳����鹦�� ����1���л������:" << endl;
		cout << "����������ѡ��" << endl;

		choose = GetIntFromCin();
		if (choose == -1)
		{
			cout << endl;
			cout << "��ֻ������0��1������������" << endl;
			choose = 1;
			continue;
		}
		bool hasDeleted = false;
		int choose2 = 1;
		string bookOnlyId;
		char bookOId[17];
		int choice = 1;
		switch (choose)
		{
		case 0:return;
		case 1:
			if (0)//borRecordList.size() == 0
			{
				cout << endl;
				cout << endl << "��û��Ҫ�����鼮��" << endl;
				return;
			}

			//ͨ�������鼮��Ψһid������
			cout << endl;
			cout << endl << "������Ҫ���鼮��Ψһid�ţ�";
			while (1)
			{
				choice = 1;
				getline(cin, bookOnlyId);
				if (bookOnlyId.size() != 12) {
					cout << endl << "�������id��ʽ�����ϣ�����������:";
					continue;
				}
				strcpy_s(bookOId, bookOnlyId.c_str());
				for (int k = 0; k < 12; k++) {
					if (bookOId[k]<'0' || bookOId[k]>'9') {
						cout << endl << "�������id��ʽ�����ϣ�����������:";
						choice = 0;
						continue;
					}
				}
				if (!choice)
					continue;
				break;
			}
			cout << endl << "������ȷ���鼮��Ψһid:" << bookOnlyId << endl;
			while (1) {
				cout << endl << "ȷ�ϻ���������1������������0��" << endl;
				choose2 = GetIntFromCin();
				if (choose2 != 0 && choose2 != 1)
				{
					cout << endl;
					cout << "��ֻ������0����1������������" << endl;
					continue;
				}
				break;
			}
			if (choose2 == 0) {
				cout << endl;
				cout << "���ѳɹ�ȡ���������" << endl;
				choose2 = 1;
				continue;
			}
			//������뻹�飬���»ص�������ͷ
			//�����������Ļ������

			//������߼������ҵ���Ӧ�Ľ����¼��ɾ�����������¼
			//����Ȿ�������ڹ黹����ô����Ҫ���������׷�ӷ���
			//Ȼ������һ��������ʷ
			//���һ���Ҫ������鼮�Ĺݲ�������һ
			cout << "bookOnlyId" << bookOnlyId << endl;
			for (i = borRecordList.begin(); i != borRecordList.end(); i++)
			{
				if (bookOnlyId._Equal(i->bookOnlyId))
				{
					time_t now = time(NULL);
					list<Reader> rList = getReaderById(i->readerId);
					list<Reader>::iterator j;
					if (now > i->rationalTime)
					{
						cout << endl;
						cout << endl << "�����ѳ��ڣ������з���" << endl;
						j = rList.begin();
						j->fine += (now - i->rationalTime) / (24 * 3600);
					}

					//���ɽ�����ʷ
					BorrowHistory b;
					b.bookId = i->bookId;
					b.readerId = i->readerId;
					b.borrowTime = i->startTime;
					b.returnTime = now;
					addHistory(b);

					//ɾ�����ļ�¼
					deleteRecord(i->id);

					//�����鼮����
					list<Book> book = getBookById(i->bookId);
					list<Book>::iterator bo = book.begin();
					(*bo).numberInLib++;
					modifyBook(*bo);

					hasDeleted = true;
					break;
				}
			}
			bookOnlyId.clear();
			if (!hasDeleted)
			{
				cout << endl;
				cout << endl << "���ļ�¼��û�ж�ӦID���鼮��,����ʧ��" << endl;
			}
			else
				cout << endl << "����ɹ���" << endl;

			break;

		default:cout << endl << "����ȷ����ѡ��" << endl;
			break;
		}

	}

}

/*�����Service*/
void RenewBookService(int readerId) {

	//�ȵõ���ǰ���ߵ������ڽ��鼮���ж��Ƿ��������鼮
	//����У���ֹ��ǰ���������鼮
	list<BorrowRecord> r = getRecordsByReaderId(readerId);
	for (list<BorrowRecord>::iterator it = r.begin(); it != r.end(); it++) {
		//�����鼮�ı�־�ǣ�Ӧ����ʱ��С�ڵ�ǰʱ��
		if ((*it).rationalTime < time(NULL)) {
			cout << endl << "�����������鼮δ�黹�����������鼮!��������˳���" << endl;
			return;
		}
	}
	//Ƿ��ﵽĳ����ֵҲ���ܼ�������
	list<Reader> reader = getReaderById(readerId);
	list<Reader>::iterator it = reader.begin();
	if ((*it).fine > MaxFine) {
		cout << endl << "����Ƿ�����ѳ���20Ԫ�������Ƿ����������!��������˳���" << endl;
		return;
	}



	r.clear();//�ͷŴ洢�ռ�

	while (1) {
		cout << endl << "��������Ҫ����Ľ����¼id(��Ҳ��������0���˳��������)��" << endl;
		int id;
		cin >> id;
		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "�������id��ʽ�������������룡" << endl;
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');//��ȡ����id��Ļ��з�

		if (id == 0) return;

		//�����û�����Ľ����¼���һ�������¼
		list<BorrowRecord> record = getRecordById(id);
		if (record.empty()) {
			cout << endl << "��������ȷ�Ľ����¼id!" << endl;
			continue;
		}

		//��Ҫ���Ҫ�޸ĵĽ����¼�Ƿ��ǵ�ǰ���ߵ�
		list<BorrowRecord>::iterator it = record.begin();
		if ((*it).readerId != readerId) {
			cout << endl << "��������ȷ�Ľ����¼id!" << endl;
			continue;
		}

		int recordId = (*it).id;

		cout << endl << "���Ľ�����Ϣ���£�" << endl;
		showBorRecordInfo(record, false);

		string select;
		while (1) {
			cout << endl << "��ȷ��Ҫ������ȷ��������1������������0��" << endl;
			getline(cin, select);
			if (select == "1" || select == "0")
				break;
			else
				cout << endl << "��ֻ������0��1�����������룡" << endl;
		}

		if (select == "0") continue;//����0�������û���������һ�������¼id

									//����Ӧ���жϸ��������¼�Ƿ񻹿������裬������ԵĻ�����ɹ�
		if (!increaseRationalTimeByConst(*it)) {
			cout << endl << "���Ѿ��ﵽ�����������������������Ȿ���ˣ�" << endl;
			continue;
		}

		if (!modifyRecord(*it)) {
			cout << endl << "����ʧ�ܣ�" << endl;
			return;
		}
		else {
			cout << endl << "����ɹ���" << endl;
			cout << endl << "���ĸ���������Ϣ������ʾ��" << endl;
			list<BorrowRecord> re = getRecordById(recordId);
			showBorRecordInfo(re, false);
			return;
		}

	}

}