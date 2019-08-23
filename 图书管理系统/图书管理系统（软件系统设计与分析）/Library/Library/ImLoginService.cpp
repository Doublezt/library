

#include"stdafx.h"
#include"AdminFunc.h"
#include<list>
#include<string>
#include"DealFault.h"
#include"ReaderFunc.h"

/*��������ע��͵�½�ĺ�����ͷ�ļ�*/


/**
�ɹ���Ա�����Լ���id��password������getAdminById(id)�����ҵ����id��
��Ӧ��һ����¼��Ȼ����һ��������admin����Ϊֻ����һ��Ԫ�أ�����ֱ��
���ø÷�����begin()�������У�Ȼ��Աȷ��ض����password���û��������
��һ�£��ܷ��ϵĻ��ͷ��ظ��û���id�ţ����򷵻�0
*/
int AdminLoginService() {
	int id;
	list<Admin> adminList;
	string idTerm;//���ڴ洢�û������id
	string idTerm2;//���ڰ�idת�����ַ������õ���ʱ����
	string password;

	cout << endl << "����������id�ţ�";
	//cin >> id;
	getline(cin, idTerm);
	cout << endl << "���������룺";
	//cin >> password;
	getline(cin, password);

	id = atoi(idTerm.c_str());
	idTerm2 = "" + to_string(id);
	list<Admin> ::iterator admin;

	while (1) {
		adminList = getAdminById(id);
		admin = adminList.begin();
		if (idTerm == idTerm2 && !adminList.empty()) {
			if (admin->password == password) {
				cout << endl << "��¼�ɹ�����ӭ" << admin->id << "ʹ�ñ�ϵͳ" << endl;
				return id;
				break;
			}
			else {
				cout << endl << "������id����" << endl;
				if (DealFault() == 1) {
					cout << endl << "����������id�ţ�";
					//cin >> id;
					getline(cin, idTerm);
					cout << endl << "���������룺";
					//cin >> password;
					getline(cin, password);
					id = atoi(idTerm.c_str());
					idTerm2 = "" + to_string(id);
				}
				else {
					return 0;
				}

			}
		}
		else {
			cout << endl << "������id����" << endl;
			if (DealFault() == 1) {
				cout << endl << "����������id�ţ�";
				//cin >> id;
				getline(cin, idTerm);
				cout << endl << "���������룺";
				//cin >> password;
				getline(cin, idTerm2);
				id = atoi(idTerm.c_str());
				idTerm2 = "" + to_string(id);
			}
			else {
				return 0;
			}
		}
	}

}


/***
�ɶ��������Լ���id��password������getReaderById(id)�����ҵ����id��
��Ӧ��һ����¼��Ȼ����һ��������reader����Ϊֻ����һ��Ԫ�أ�����ֱ��
���ø÷�����begin()�������У�Ȼ��Աȷ��ض����password���û��������
��һ�£��ܷ��ϵĻ��ͷ��ظ��û���id�ţ����򷵻�0
***/
int ReaderLoginService() {
	int id;
	string idTerm;//�����û��������id���ݴ���
	string idTerm2;
	string password;
	list<Reader> readerList;

	cout << endl << "����������id�ţ�";
	//cin >> id;
	getline(cin, idTerm);
	cout << endl << "���������룺";
	//cin >> password;
	getline(cin, password);
	id = atoi(idTerm.c_str());
	idTerm2 = "" + to_string(id);

	while (1) {
		readerList = getReaderById(id);
		list<Reader> ::iterator reader = readerList.begin();
		if (idTerm == idTerm2 && !readerList.empty()) {
			if (reader->password == password) {
				cout << endl << "��¼�ɹ�����ӭ" << reader->name << "ʹ�ñ�ϵͳ" << endl;
				return id;
				break;
			}
			else {
				cout << endl << "������id����" << endl;
				if (DealFault() == 1) {
					cout << endl << "����������id�ţ�";
					//cin >> id;
					getline(cin, idTerm);
					cout << endl << "���������룺";
					//cin >> password;
					getline(cin, password);
					id = atoi(idTerm.c_str());
					idTerm2 = "" + to_string(id);
				}
				else {
					return 0;
				}

			}
		}
		else {
			cout << endl << "������id����" << endl;
			if (DealFault() == 1) {
				cout << "����������id�ţ�";
				//cin >> id;
				getline(cin, idTerm);
				cout << "���������룺";
				//cin >> password;
				getline(cin, password);
				id = atoi(idTerm.c_str());
				idTerm2 = "" + to_string(id);
			}
			else {
				return 0;
			}
		}
	}
}


/**
����addReader()�����������ӳɹ��ͷ�������id�ţ����򷵻�0
servelt����Ը��������صĽ���ж��Ƿ���ӳɹ����Լ���ȡ��ӵ�id��
*/
int SignUpService(Reader reader) {
	if (addReader(reader)) {
		return reader.id;
	}
	else {
		return 0;
	}
}