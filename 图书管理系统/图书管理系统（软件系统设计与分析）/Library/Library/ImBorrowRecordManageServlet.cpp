#include"stdafx.h"
#include<iostream>
#include<string>
#include"BorrowRecordManageService.h"
#include"QueryBookService.h"
#include"ReaderManageService.h"

using namespace std;

//���ļ�¼�ͽ�����ʷ����

void QueryBorrowHistoryServlet() {
	cout << endl << "��ӭ������ѯ������ʷ����" << endl;
	cout << "������ͨ�������鼮id���߶���id��ѯ��ؽ�����ʷ��¼��" << endl;

	string choice1;
	string choice2;

	cout << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	cout << "��ѡ��:" << endl;
	cout << endl;
	cout << "0.ֱ�������鼮id���߶���id��ѯ��ؽ�����ʷ��¼" << endl;
	cout << "1.��ѯ�鼮��Ϣ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.��ѯ���н�����ʷ" << endl;
	cout << "4.�˳�" << endl;
	cout << endl;
	cout << "������ѡ��";

	while (1) {
		getline(cin, choice1);
		if (choice1 == "0") {
			break;
		}
		else if (choice1 == "1") {
			QueryBookService(); //��ѯ�鼮��Ϣ
		}
		else if (choice1 == "2") {
			QueryReaderService();//��ѯ������Ϣ
		}
		else if (choice1 == "4")
			return;
		else if (choice1 == "3")
			QueryBorrowHistoryService();
		else {
			cout << endl;
			cout << "�������ݲ��Ϲ������������룺";
			continue;
		}
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "0.ֱ�������鼮id���߶���id��ѯ��ؽ�����ʷ��¼" << endl;
		cout << "1.��ѯ�鼮��Ϣ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.��ѯ���н�����ʷ" << endl;
		cout << "4.�˳�" << endl;
		cout << "������ѡ��";
	}

	for (int t = 1; t != 0;) {
		QueryBorrowHistoryService();//����Service�ļ��еĺ������в�ѯ������ʷ
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "��Ҫ�˳���ѯ��ʷ��¼������" << endl;
		cout << endl;
		cout << "0.������ҳ" << endl;
		cout << "1.������ѯ" << endl;
		while (1) {
			cout << endl;
			cout << "������ѡ�";
			getline(cin, choice2);
			if (choice2 == "0") {
				t = 0;
				break;
			}
			else if (choice2 == "1") {
				t = 1;
				break;
			}
			else {
				cout << endl;
				cout << "�������ݲ��Ϲ���!ֻ������1��0.";
				continue;
			}
		}
	}
	return;
}

/*������id��ͼ��id�鿴���������Ľ��ļ�¼*/
void QueryBorrowRecordServlet() {
	cout << endl << "��ӭ������ѯ���ļ�¼����" << endl;
	cout << "������ͨ�������鼮id���߶���id��ѯ��ǰ���ļ�¼��" << endl;

	string choice1;
	string choice2;

	cout << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	cout << "��ѡ��:" << endl;
	cout << endl;
	cout << "0.ֱ�������鼮id���߶���idѯ��ǰ���ļ�¼" << endl;
	cout << "1.��ѯ�鼮��Ϣ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.��ѯ���н����¼" << endl;
	cout << "4.�˳�" << endl;
	cout << endl;
	cout << "������ѡ��";

	while (1) {
		getline(cin, choice1);
		if (choice1 == "0") {
			break;
		}
		else if (choice1 == "1") {
			QueryBookService(); //��ѯ�鼮��Ϣ
		}
		else if (choice1 == "2") {
			QueryReaderService();//��ѯ������Ϣ
		}
		else if (choice1 == "3")
			QueryBorrowRecordService();
		else if (choice1 == "4")
			return;
		else {
			cout << endl;
			cout << "�������ݲ��Ϲ������������룺";
			continue;
		}
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "0.ֱ�������鼮id���߶���id��ѯѯ��ǰ���ļ�¼" << endl;
		cout << "1.��ѯ�鼮��Ϣ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.��ѯ���н����¼" << endl;

		cout << "4.�˳�" << endl;
		cout << "������ѡ��";
	}

	for (int t = 1; t != 0;) {
		QueryBorrowRecordService();//����Service�ļ��еĺ������в�ѯ������ʷ
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "��Ҫ�˳���ѯ��ǰ���ļ�¼��" << endl;
		cout << endl;
		cout << "0.������ҳ" << endl;
		cout << "1.������ѯ" << endl;
		while (1) {
			cout << endl;
			cout << "������ѡ�";
			getline(cin, choice2);
			if (choice2 == "0") {
				t = 0;
				break;
			}
			else if (choice2 == "1") {
				t = 1;
				break;
			}
			else {
				cout << endl;
				cout << "�������ݲ��Ϲ���!ֻ������1��0.";
				continue;
			}
		}
	}
	return;
}


/*���ݹ���Ա�����id�������Աչʾ����Щ�飬����Щ����*/

void QueryExtendedBookServlet()
{
	cout << endl << "��ӭ������ѯ���ڽ��ļ�¼����" << endl;
	cout << "������ͨ�������鼮id���߶���id��ѯ���ڽ��ļ�¼��" << endl;

	string choice1;
	string choice2;

	cout << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	cout << "��ѡ��:" << endl;
	cout << endl;
	cout << "0.ֱ�������鼮id���߶���id��ѯ���ڽ��ļ�¼" << endl;
	cout << "1.��ѯ�鼮��Ϣ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.�˳�" << endl;
	cout << endl;
	cout << "������ѡ��";

	while (1) {
		getline(cin, choice1);
		if (choice1 == "0") {
			break;
		}
		else if (choice1 == "1") {
			QueryBookService(); //��ѯ�鼮��Ϣ
		}
		else if (choice1 == "2") {
			QueryReaderService();//��ѯ������Ϣ

		}
		else if (choice1 == "3")
			return;
		else {
			cout << endl;
			cout << "�������ݲ��Ϲ������������룺";
			continue;
		}
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "0.ֱ�������鼮id���߶���id��ѯ���ڽ��ļ�¼" << endl;
		cout << "1.��ѯ�鼮��Ϣ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.�˳�" << endl;
		cout << "������ѡ��";
	}

	for (int t = 1; t != 0;) {
		QueryExtendedBookService();//����Service�ļ��еĺ������в�ѯ������ʷ
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "��Ҫ�˳���ѯ���ڽ��ļ�¼��" << endl;
		cout << endl;
		cout << "0.������ҳ" << endl;
		cout << "1.������ѯ" << endl;
		while (1) {
			cout << endl;
			cout << "������ѡ�";
			getline(cin, choice2);
			if (choice2 == "0") {
				t = 0;
				break;
			}
			else if (choice2 == "1") {
				t = 1;
				break;
			}
			else {
				cout << endl;
				cout << "�������ݲ��Ϲ���!ֻ������1��0.";
				continue;
			}
		}
	}
	return;
}


/*
����Ա���ܣ��ܹ�ɾ��������ʷ�Լ����ļ�¼
*/
void DeleteBorrowRecordServlet() {

	string choice1;
	string choice2;

	cout << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	cout << "��ѡ���Ƿ��ѯ�鼮���ǲ�ѯ������Ϣ����" << endl;
	cout << endl;
	cout << "����1��ѯ�鼮��Ϣ" << endl;
	cout << "����2��ѯ������Ϣ" << endl;
	cout << "����0����" << endl;
	cout << endl;
	cout << "������ѡ��";
	while (1) {
		getline(cin, choice1);
		if (choice1 == "0") {
			break;
		}
		else if (choice1 == "1") {
			QueryBookService(); //��ѯ�鼮��Ϣ
		}
		else if (choice1 == "2") {
			QueryReaderService();//��ѯ������Ϣ
		}
		else {
			cout << endl;
			cout << "�������ݲ��Ϲ������������룺";
			continue;
		}
	}

	for (int t = 1; t != 0;) {
		DeleteBorrowRecordService();//����Service�ļ��еĺ������в�ѯ������ʷ
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "��ѡ�����ɾ�����������˳��˹���" << endl;
		cout << endl;
		cout << "����1����ɾ��" << endl;
		cout << "����0������ҳ" << endl;
		while (1) {
			cout << endl;
			cout << "�Ƿ������ѯ��";
			getline(cin, choice2);
			if (choice2 == "0") {
				t = 0;
				break;
			}
			else if (choice2 == "1") {
				t = 1;
				break;
			}
			else {
				cout << endl;
				cout << "�������ݲ��Ϲ������������룺";
				continue;
			}
			cout << endl;
			cout << "**********************************************" << endl;
			cout << endl;
			cout << "����1������ѯ�鼮��Ϣ" << endl;
			cout << "����2������ѯ������Ϣ" << endl;
			cout << "����0����" << endl;
			cout << "������ѡ��";
		}
	}
	return;
}


