#include "stdafx.h"
#include "UnsignedReaderServlet.h"


void UnsignedReaderServlet() {
	string choice;
	cout << endl << "������δ��¼�����ֻ��ʹ�ò��鹦��" << endl;

	while (1) {
		QueryBookService();
		cout << endl << "�Ƿ���Ҫ��������" << endl;
		cout << endl << "1������   0���˳�" << endl;
		getline(cin, choice);
		if (choice == "1") {

		}
		else if (choice == "0") {
			break;
		}
		else {
			if (DealFault()) {

			}
			else {
				break;
			}
		}
	}
	cout << endl << "���˳�" << endl;
}