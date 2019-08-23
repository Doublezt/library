#include "stdafx.h"
#include "BorrowHistoryFunc.h"
#include"showInfo.h"
#include"BorrowRecordFunc.h"
#include"RecordOperationService.h"
#include<string>
#include"DealFault.h"

using namespace std;


//(չʾ��ǰ�������е�ǰ�����¼��
//��ʾ��ǰ�����鼮������ͼ�飬�����
void QueryCurReaderBorRecordService(int readerId) {
	cout << endl;
	list<BorrowRecord> borowRecordList = getRecordsByReaderId(readerId);
	if (borowRecordList.size() == 0) {
		cout << endl << "����ǰû�н����¼" << endl;
		list<Reader> reader = getReaderById(readerId);
		if (reader.begin()->fine>0)
			cout << "���Ƿ�" << reader.begin()->fine << endl;
		return;
	}
	cout << endl << "���ĵ�ǰ������Ϣ������ʾ��" << endl;
	//����߱��˲���Ҫչʾ�������Ϣ
	showBorRecordInfo(borowRecordList, false);
	list<Reader> reader = getReaderById(readerId);
	if (reader.begin()->fine>0)
		cout << "���Ƿ�" << reader.begin()->fine << endl;
}



//(չʾ��ǰ���ߵ����н�����ʷ)
void QueryCurReaderBorHistoryService(int readerId)
{

	list<BorrowHistory> borrowHistoryList = getHistoryByReaderId(readerId, 1);
	if (borrowHistoryList.size() == 0) {
		cout << endl << "����ǰû�н�����ʷ��¼" << endl;
		return;
	}
	cout << endl;
	cout << "���Ľ�����ʷ������ʾ��" << endl;
	showBorHistoryInfo(borrowHistoryList, false);
}

/*(һ��Ҫ��֤��¼�Ķ���ֻ��ɾ���Լ��Ľ�����ʷ��
����������һ��Ҫɾ���Ľ�����ʷ��id��Ҫȷ������������ʷ�ǵ�ǰ���ߵģ�
�ſ���ִ��ɾ������)*/
bool DeleteCurReadHistoryService(int id) {
	return deleteHistory(id);
}


