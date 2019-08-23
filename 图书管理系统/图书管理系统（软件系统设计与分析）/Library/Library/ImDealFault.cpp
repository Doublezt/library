#include "stdafx.h"
#include<string>
#include<iostream>
using namespace std;


int DealFault() {

	string choice;
	cout << endl << "��ѡ����������˳�" << endl;
	cout << endl << "1������    0���˳�" << endl;
	//cin >> choice;
	getline(cin, choice);
	while (choice != "1" && choice != "0") {
		cout << endl << "���������Ϣ������Ҫ����ѡ��������������˳�" << endl;
		cout << endl << "1������			0���˳�" << endl;
		//cin >> choice;
		getline(cin, choice);
	}
	if (choice == "1") {
		return 1;
	}
	else {
		return 0;
	}
}

//���������ݴ���
int GetIntFromCin() {

	/**/
	string str;
	string str2;
	int choice;
	getline(cin, str);
	choice = atoi(str.c_str());
	str2 = "" + to_string(choice);
	if (str != str2) {
		return -1;
	}
	return choice;
}

/*�ж�һ���ַ�����ʾ���Ƿ���һ��ISBN*/
bool IsISBN(string isbn) {

	if (isbn == "") return false;

	/*����ISBN�Ƿ�����У������
	ISBN�����֣�9λ�ĺ�13λ��
	����9λ�ģ���10-2�ֱ�ȥ��ǰ8λ�����������Σ�
	����Щ�˻�������Ϊsum Ȼ����� f = 11 - (sum%11)
	����f�Ĳ�ͬȡֵ�õ���ͬ��У��λbit��Ȼ��ȥ�������һλ�Ƿ�������bit

	����13λ�ģ���1,3,1,3...ȥ���γ���ǰ12λ��Ȼ����������õ�sum
	f = 10 - (sum%10) ��f��ȡֵȥ�ж�У��λӦ����ʲô
	*/
	unsigned i = 0;
	for (i = 0; i < isbn.length(); i++) {
		if (!(isbn[i] >= '0' && isbn[i] <= '9')) return false;
	}

	string frontStr = isbn.substr(0, isbn.length() - 1);
	string backStr = isbn.substr(isbn.length() - 1, 1);
	const char* c = backStr.data();
	if (!(frontStr.length() == 9 || frontStr.length() == 12))
		return false;
	const char* s = isbn.data();
	char rightChar;
	if (frontStr.length() == 9) {
		int sum = 0;
		int mul = 10;
		for (i = 1; i <= 9; i++) {
			sum += mul * (s[i - 1] - '0');
			mul--;
		}
		int num = 11 - (sum % 11);
		if (num == 10) rightChar = 'X';
		else if (num == 11) rightChar = '0';
		else rightChar = num + '0';

	}
	else {
		int mul;
		int sum = 0;
		for (i = 1; i <= 12; i++) {
			if (i % 2 == 1) mul = 1;
			else mul = 3;
			sum += mul * (s[i - 1] - '0');
		}
		int num = 10 - (sum % 10);
		if (num == 10) rightChar = '0';
		else rightChar = '0' + num;
	}
	if (rightChar == c[0]) return true;
	else return false;
}

/*�ж�������������Ƿ���ȫ���ַ������еĻ�����true�����򷵻�false*/
bool IsDoubleChar(string str) {
	const char* ch = str.c_str();//��һ�����ַ�ָ��ָ��һ���ַ���
	char c;//����һ���ַ��������ַ���
	while (c = *ch++) {
		if ((c & 0x80) && (*ch & 0x80)) {
			return true;
		}
	}
	return false;
}

