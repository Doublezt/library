#include"stdafx.h"
#include"RecordOperationService.h"
#include"DealFault.h"
#include"BorrowHistoryFunc.h"
#include<string>

//(չʾ��ǰ�������е�ǰ�����¼��
//��ʾ��ǰ�����鼮������ͼ�飬�����
void QueryCurReaderBorRecordServlet(int readerId)
{
	QueryCurReaderBorRecordService(readerId);
}


//(չʾ��ǰ���ߵ����н�����ʷ)
void QueryCurReaderBorHistoryServlet(int readerId)
{
	QueryCurReaderBorHistoryService(readerId);
}


/*(һ��Ҫ��֤��¼�Ķ���ֻ��ɾ���Լ��Ľ�����ʷ��
����������һ��Ҫɾ���Ľ�����ʷ��id��Ҫȷ������������ʷ�ǵ�ǰ���ߵģ�
�ſ���ִ��ɾ������)*/

void DeleteCurReaderHistoryServlet(int readerId) {
	/**
	���û���Ҫɾ��������ʷʱ�����ǹ涨�û������û��鿴��ǰ������ʷ
	Ȼ������Ҫɾ���Ľ�����ʷ��id�Ž���ɾ��
	������Ҫ�������ݶ��ߵ�id��
	existΪ1��ʾ���ڼ�¼
	�ɹ�ɾ������true�����򷵻�false
	*/
	int HistoryId;
	string choice;
	string historyTerm;
	string historyTerm2;
	list<BorrowHistory> borrowHistory;
	list<BorrowHistory>::iterator it;

	while (1) {
		cout << endl << "����ǰ������ʷ��ϢΪ��" << endl;
		QueryCurReaderBorHistoryService(readerId);
		cout << endl << "��������Ҫɾ���Ľ�����ʷ��Ϣ��id��:" << endl;
		//cin >> historyTerm;
		getline(cin, historyTerm);
		HistoryId = atoi(historyTerm.c_str());
		historyTerm2 = "" + to_string(HistoryId);

		borrowHistory = getHistoryById(HistoryId, 1);
		it = borrowHistory.begin();

		if (historyTerm == historyTerm2 && !borrowHistory.empty() && it->readerId == readerId) {
			if (DeleteCurReadHistoryService(HistoryId)) {
				cout << endl << "ɾ���ɹ���" << endl;
				cout << "�����ڵĽ��ļ�¼Ϊ��" << endl;
				QueryCurReaderBorHistoryService(readerId);
				cout << endl << "�����Ƿ����ִ��ɾ������" << endl << endl << "1������   0���˳�" << endl;
				//cin >> choice;
				getline(cin, choice);
				if (choice == "1") {

				}
				else if (choice == "0") 
					return;
				else {
					cout << endl << "����������ݲ�����Ҫ��" << endl;
					if (DealFault() == 1) {

					}
					else
						return;
				}
			}
			else {
				cout << endl << "ɾ��ʧ��" << endl;
				return;
			}
		}
		else {
			cout << endl << "����id���Ϸ�\n" << endl;
			if (DealFault()) {
			}
			else
				return;
		}
	}


}
