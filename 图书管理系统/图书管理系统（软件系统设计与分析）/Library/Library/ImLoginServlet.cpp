#include "stdafx.h"
#include "LoginServlet.h"
#include"LoginService.h"

/**
*Ҫ���������д���2����Ϣ��һ�����û���ݣ�һ����id��
����Ҳ��ü�ֵ�Ե���ʽ����һ����String���ͱ�ʾ�û����
�ڶ�����int���ͣ���ʾ�û�id�ţ�����û�ѡ����ݳ��ִ���
��ô�����map����Ϊ�գ�ѡ����ȷ�Ļ�����һ����Ҫ�ж�id���Ƿ�
Ϊ0��������Ϊ0��ʾ��ȷ��
*�ж�map�����Ƿ�Ϊ���ǵ���empty()�������շ���1��
*��ȡmap�ж���ļ�ֵ�Եķ����ǣ�����һ��map����ĵ�����iter��Ȼ��
��iter = ������.begin(),����ȡMap����ĵ�һ��Ԫ�أ���ʵ����Ԫ��Ҳ��ֻ��һ����
Ȼ��iter->first,iter->second�����ɻ�ȡmap�еļ�ֵ��
*map�������Ԫ�صķ�ʽֱ���ǣ�������[key] = value���������ֵΪkey
�ļ�ֵ�Դ��ڣ����޸�����valueΪvalue����������������ֵ�ԡ�
*/
map<string, int> LoginServlet() {
	string identity;
	string choice;
	map<string, int> identityMap;
	cout << endl << "��ѡ���������" << endl;
	cout << endl << "1������Ա		2������" << endl;
	//cin >> identity;
	getline(cin, identity);
	while (identity != "1" && identity != "2") {
		//�ݴ���
		if (DealFault() == 1) {
			cout << endl << "��ѡ���������" << endl;
			cout << endl << "1������Ա		2������" << endl;
			//cin >> identity;
			getline(cin, identity);
		}
		else {
			return identityMap;
		}
	}
	if (identity == "1") {
		int adminId = AdminLoginService();
		if (adminId) {
			identityMap["Admin"] = adminId;
		}
	}
	else if (identity == "2") {
		int readerId = ReaderLoginService();
		if (readerId) {
			identityMap["Reader"] = readerId;
		}
	}

	return identityMap;
}




/**
*����ע�Ṧ�ܵ�servlt��ͨ����Service���洫��reader���������Ӧ����
Reader��id��fine��exist��ϵͳ���ɣ�name��password��sex���û�����
ע��ɹ�����true����֪�û���id�ţ�ʧ���򷵻�false
*����password��name������string���ͣ�Ȼ�����strcpy()����ת����char����
strcpy(array,str.c_str)��ͨ��str.length()�����ж��û�����ĳ����Ƿ����Ҫ��
ʹ��getline(cin,str)������пո���ַ���
*������ֱ��ʹ��setReaderName()�����Ϳ����޸�name���ԣ�passwordҲ��һ����
*/
bool SignUpServlet() {
	Reader reader;
	string name;
	string nameTerm;
	string password;
	string passwordTerm;
	string x;//�ж��û��Ƿ�Ҫ������������˳�ע��
	string sex;
	int exist = 1;
	double fine = 0;
	reader.exist = exist;
	reader.fine = fine;

	cout << endl << "��ӭ����ע��ҳ��" << endl;
	while (1) {
		cout << endl << "��������������(���ó���19���ַ�,����û���ַ�������ȫΪ�ո�)��";
		getline(cin, name);//������Դ��ո���ַ���
		nameTerm = name;
		trimAllSpace(nameTerm);
		if (nameTerm.length() == 0 || name.length()<1 || name.length() > 19) {
			cout << endl << "��������ַ���������Ҫ��������������˳�ע��" << endl;
			cout << endl << "1����������		0���˳�ע��" << endl;
			//cin >> x;
			getline(cin, x);
			if (x == "1") {
			}
			else if (x == "0") {
				cout << endl << "ע��ʧ��" << endl;
				return false;
			}
			else {
				if (DealFault()) {

				}
				else {
					cout << endl << "ע��ʧ��" << endl;
					return false;
				}
			}

		}
		else {
			cout << endl << "��������Ϊ��" << name << ",��ȷ���Ƿ���ȷ" << endl;
			cout << endl << "1����ȷ   0������" << endl;
			getline(cin, x);
			if (x == "1") {
				setReaderName(reader, name);
				break;
			}
			else if (x == "0") {

			}
			else {
				if (DealFault()) {

				}
				else {
					cout << endl << "ע��ʧ��" << endl;
					return false;
				}
			}

		}
	}

	while (1) {
		cout << endl << "��������������(Ҫ��5-10���ַ�,���ܺ��пո񣬲���Ϊ���ֵ�ȫ���ַ�)��";
		getline(cin, password);
		passwordTerm = password;
		trimAllSpace(passwordTerm);//��ȥ�ո�

		if (IsDoubleChar(password) || (passwordTerm.length() != password.length()) || password.length()<5 || password.length()>10) {
			cout << endl << "��������ַ���������Ҫ��������������˳�ע��" << endl;
			cout << "1����������		0���˳�ע��" << endl;
			//cin >> x;
			getline(cin, x);

			if (x == "1") {
			}
			else if (x == "0") {
				cout << "ע��ʧ��" << endl;
				return false;
			}
			else {
				if (DealFault()) {

				}
				else {
					cout << "ע��ʧ��" << endl;
					return false;
				}
			}

		}
		else {
			cout << endl << "��������Ϊ��" << password << ",��ȷ���Ƿ���ȷ" << endl;
			cout << endl << "1����ȷ   0������" << endl;
			getline(cin, x);
			if (x == "1") {
				setReaderPw(reader, password);
				break;
			}
			else if (x == "0") {

			}
			else {
				if (DealFault()) {

				}
				else {
					cout << endl << "ע��ʧ��" << endl;
					return false;
				}
			}

		}
	}

	while (1) {
		cout << endl << "�����������Ա�1������  0��Ů�ԣ�" << endl;
		getline(cin, sex);
		if (sex != "1" && sex != "0") {
			cout << endl << "�������벻����Ҫ����ѡ����������˳�" << endl;
			cout << endl << "1������       0���˳�" << endl;
			getline(cin, x);
			if (x == "1") {

			}
			else if (x == "0") {
				cout << endl << "ע��ʧ��" << endl;
				return false;
			}
			else {
				if (DealFault()) {

				}
				else {
					return false;
				}
			}
		}
		else {
			reader.sex = atoi(sex.c_str());
			break;
		}
	}

	reader.id = SignUpService(reader);

	if (reader.id) {
		cout << endl << "ע��ɹ�������id����" << reader.id << endl;
		return true;
	}
	else {
		cout << endl << "ע��ʧ��" << endl;
		return false;
	}

}