#include"stdafx.h"
#include"BookManageService.h"
#include<string>
#include"Operation.h"
#include"TypeFunc.h"
#include"AuthorFunc.h"
#include"QueryBookService.h"
#include"BookFunc.h"
#include"DealFault.h"
using namespace std;

/*����һ���鼮��servlet*/

void AddBookServlet() {
	while (1) {

		cout << endl << "��ӭ���������鼮���棡" << endl << endl;
		AddBookService();

		int select;
		while (1) {
			cout << endl << "��ȷ���˳�����鼮������" << endl;
			cout << "ȷ��������1,����������0��";

			select = GetIntFromCin();

			switch (select) {
			case 1:return;
			case 0:break;
			default:
				cout << endl << "ֻ������1��0��" << endl;
				continue;
			}

			break;//case 0����ת�����Ȼ�������һ�������鼮����
		}
		
	}
}

/*ɾ��һ���鼮��Servlet*/
void DeleteBookServlet() {
	while (1) {
		cout <<endl << "��ӭ����ɾ���鼮���棡" << endl <<endl;
		cout << "������ѡ��" << endl;
		cout << "1.����֪���鼮��id������£�������ֱ������һ���鼮id��ɾ���鼮��" << endl;
		cout << "2.�������Ƚ����ѯ�鼮���棬��ѯ��Ҫɾ���鼮��id�š�" << endl;
		cout << "3.�˳�ɾ���鼮����" << endl;
		string select;

		while (1) {
			cout << endl << "������ѡ�";
			getline(cin, select);
			trimAllSpace(select);
			if (select == "1" || select == "2" || select == "3")
				break;
			else
				cout << "ֻ������1��2��3�����������룡" << endl;
		}

		
		if (select == "2")
			QueryBookService();
		if (select == "2" || select == "1") 
			DeleteBookService();

		while (1) {
			cout << endl << "��Ҫȷ���˳�ɾ���鼮�����������������1������������0:" << endl;
			getline(cin, select);
			trimAllSpace(select);
			if (select == "1" || select == "0")
				break;
			else
				cout << "ֻ������0��1��" << endl;
		}
		if (select == "1") return;
		else continue;


	}

}



/*�޸�һ���鼮��Ϣ*/
void ModifyBookServlet() {

	for (;;) {
		cout << "�Ƿ�֪����Ҫ�޸��鼮��ISBN�ţ�" << endl;
		for (;;) {
			cout << "֪��������1������������0�����鼮���Ҳ�����";
			int t = GetIntFromCin();
			//֪��ISBN
			if (t == 1)
				break;
			//��֪��ISBN
			else if (t == 0) {
				QueryBookService();
				break;
			}
			else
				cout << "����������������������" << endl;
		}

		ModifyBookService();

		for (;;) {
			cout << "�Ƿ���������鼮��Ϣ�޸ģ�����������1��������ҳ������0��";
			int t = GetIntFromCin();

			if (t == 1)
				break;
			else if (t == 0)
				return;
			else
				cout << "����������������������" << endl;
		}
	}
}



