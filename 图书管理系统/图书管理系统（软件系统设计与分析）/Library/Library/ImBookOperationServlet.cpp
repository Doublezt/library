#include"stdafx.h"
#include"BookOperationService.h"
#include<string>
#include"Operation.h"
#include"QueryBookService.h"
#include"RecordOperationService.h"
#include"DealFault.h"
using namespace std;

//(readerId�ǵ�ǰ��¼�Ķ��ߵ�id�ţ��������Ὣ���id�������service)
void BorrowBookServlet(int readerId) {
	while (1) {
		
		cout << endl << "��ӭ���������鼮���棡" << endl << endl;

		int select = 2;
		cout << "������ѡ��" << endl;
		cout << "1.����֪��Ҫ���鼮��id������£�������ֱ������һ���鼮id�Խ����鼮��" << endl;
		cout << "2.�������Ƚ����ѯ�鼮���棬��ѯ��Ҫ���ĵ��鼮��Ϣ��" << endl;
		cout << "3.�˳������鼮���档" << endl;
		select = GetIntFromCin();

		//ѡ��ͬ����
		switch (select) {
			case 2 :
			QueryBookService();
			case 1:	
			BorrowBookService(readerId); break;
			case 3:break;
			default:
				cout << "�����ѡ������" << endl;
				continue;
		}

		//�˳�����ȷ��
		while (1) {
			cout << endl << "��ȷ���˳���������������������1������������0:" << endl;
			select = GetIntFromCin();

			switch (select) {
			case 1: return;//����1���˳�����
			case 0:break;
			default:
				cout << "ֻ������0��1��" << endl;
				continue;
			}
			break;//�������1����������´μ�������������
		}

	}
}


//����ʾ��ǰ���ģ��ö�����������¼��id���л��飬�����¼��ɾ��һ����������ʷ����һ�����ݲ���������
void ReturnBookServlet(int readerId)
{
	QueryCurReaderBorRecordService(readerId);
	ReturnBookService(readerId);
}


/*�����Servlet*/
void RenewBookServlet(int readerId) {
	while (1) {
		////չʾ��ǰ�������е�ǰ�����¼��
		//��ʾ��ǰ�����鼮������ͼ�飬�����
		QueryCurReaderBorRecordService(readerId);

		RenewBookService(readerId);

		string select;
		while (1) {
			cout << endl << "�����������鼮�������������1������������0���˳�:" << endl;
			getline(cin, select);
			trimAllSpace(select);
			if (select == "1" || select == "0")
				break;
			else
				cout << "ֻ������0��1�����������룡" << endl;
		}
		if (select == "0") return;
	}

}


