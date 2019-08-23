#include"stdafx.h"
#include"Structs.h"
#include"ReaderManageService.h"
#include<list>
#include<iostream>
#include<string>
#include"ReaderFunc.h"
#include"ReaderManageService.h"
#include"DealFault.h"
using namespace std;



/*��������ѯ������Ӧ�����Ķ��߲�չʾ���û���*/
//��������id���������Ա����У���ѯ���ߣ��ѱ�ɾ������ɾ�����Ķ��߲��ᱻ������
void QueryReaderServlet() {
	QueryReaderService();
}


//���Ӷ��ߣ�������һ����Ҳ������һ����
void AddReaderServlet() {
	while (1)
	{
		cout << endl << "��Ҫ����һ�������𣿰�1ȷ�����������˳�����:" << endl;
		string key;//����ѡ�����
		getline(cin, key);
		if (key == "1")//keyΪ1��ʱ�����Ҫ��������
		{
			Reader tempReader;//��ʱ����һ�����߽ṹ��
			list<Reader> readerList;//ÿ����һ����ʱ�Ķ��߽ṹ�壬�ͽ��䴫��readerList�У����ͽ����󣬵���AddReaderService


									//��������				
			while (1) {
				cout << endl << "������ö��ߵ�����(������������20���ַ�):" << endl;
				string tempPwd;//��ʱ�����ַ���
				getline(cin, tempPwd);

				trimAllSpace(tempPwd);

				if (tempPwd == "" || !setReaderPw(tempReader, tempPwd))
				{
					cout << endl << "�������볤�ȷǷ�������������!" << endl;
					continue;
				}

				string confirm;
				while (1) {
					cout << endl << "������Ķ�������Ϊ��";
					cout << tempReader.password << endl;
					cout << endl << "������ȷ�����룡��ȷ������1������������0��������������!" << endl;
					getline(cin, confirm);
					if (confirm == "0" || confirm == "1")
						break;
					else {
						cout << "��ֻ������0��1�����������룡" << endl;
					}
				}
				if (confirm == "1") break;
				else continue;//����0���������������룡


			}

			//��������
			while (1) {
				cout << endl << "��������ߵ�����" << endl;
				string tempName;//��ʱ�Ķ�������
				getline(cin, tempName);

				if (!setReaderName(tempReader, tempName))
				{
					cout << endl << "�����������ȷǷ�������������" << endl;
					continue;
				}


				string confirm;
				while (1) {
					cout << endl << "������Ķ�������Ϊ:" << tempReader.name << endl;
					cout << endl << "������ȷ�϶�����������ȷ������1������������0�����������������!" << endl;
					getline(cin, confirm);
					if (confirm == "0" || confirm == "1")
						break;
					else {
						cout << "��ֻ������0��1�����������룡" << endl;
					}
				}

				if (confirm == "1") break;
				else continue;//����0���������������������

			}



			//�����Ա𣬸÷�����Ľ�
			while (1) {
				cout << endl << "������ö��ߵ��Ա�,1��ʾ���ԣ�0��ʾŮ��" << endl;
				int tempSex;//��ʱ�洢�ö��ߵ��Ա�;
				tempSex = GetIntFromCin();
				while (tempSex != 0 && tempSex != 1)//�Ա����Ϊ���Σ������������һ����֮���ֵ
				{
					cout << endl << "���벻�Ϸ��������������1��0֮����ַ�,����������" << endl;
					tempSex = GetIntFromCin();
				}
				tempReader.sex = tempSex;
				string confirm;
				while (1) {

					cout << endl << "������Ķ����Ա�Ϊ��";
					if (tempReader.sex) cout << "��" << endl;
					else cout << "Ů" << endl;

					cout << endl << "������ȷ�϶����Ա���ȷ������1������������0��������������Ա�!" << endl;
					getline(cin, confirm);
					if (confirm == "0" || confirm == "1")
						break;
					else {
						cout << endl << "��ֻ������0��1�����������룡" << endl;
					}
				}
				if (confirm == "1") break;
				else
					continue;//����0����������������Ա�

			}

			//��������Ч���Լ�Ƿ������ΪĬ��ֵ
			tempReader.exist = 1;
			tempReader.fine = 0;

			//������ʱ���߽ṹ�����list�У����ڲ�ȷ��list�д����tempReader��ָ�뻹����������
			//ÿ����һ��tempReader�ͽ��䱣����ṹ���в������ļ���
			readerList.push_back(tempReader);
			AddReaderService(readerList);

			//��������ɹ�����ʾ��Ϣ
			cout << endl << "�¶����Ѵ���" << endl;
		}
		else//����ֵ�����˳�����
		{
			cout << endl << "��������ģ�����˳�" << endl;
			return;
		}
	}

}



void DeleteReaderServlet() {
	while (1)
	{
		cout << endl << "��Ҫɾ��һ�������𣿰�1ȷ�����������˳�" << endl;
		string key;
		getline(cin, key);
		if (key == "1")//1�������ɾ������
		{
			cout << endl << "���Ƿ�֪��Ҫɾ���Ķ��ߵ�id��" << endl << "����֪�����밴1����ɾ���������밴���������Ҹ��û���id" << endl;
			getline(cin, key);
			if (key == "1")//1�������ɾ������
			{
				cout << endl << "��������Ҫɾ���Ķ��ߵ�id" << endl;
				int tempId;//��ʱ���Ҫɾ���Ķ��ߵ�id
				tempId = GetIntFromCin();
				while (tempId == -1)
				{
					cout << endl << "���벻�Ϸ�����ֻ���������֣����������룡";
					tempId = GetIntFromCin();
				}
				DeleteReaderService(tempId);
			}
			else//�����������û������Ҫɾ���Ķ��ߵ�id����Ҫ�Ƚ��в��Ҳ���
			{
				QueryReaderService();//���Ҷ���

									 //����ɾ������if�н��еĲ�����ͬ
				cout << endl << "��������Ҫɾ���Ķ��ߵ�id" << endl;
				int tempId;//��ʱ���Ҫɾ���Ķ��ߵ�id
				tempId = GetIntFromCin();
				while (tempId == -1)
				{
					cout << endl << "���벻�Ϸ�����ֻ���������֣����������룡";
					tempId = GetIntFromCin();
				}
				DeleteReaderService(tempId);
				//cout << endl << "idΪ" << tempId << "�Ķ�����ɾ��" << endl;
			}
		}
		else//���������˳���servlet
		{
			cout << endl << "ɾ�����߳������˳���" << endl;
			return;
		}
	}

}


//����Ա�޸Ķ�����Ϣ���ܽ���
void AdminModifyReaderServlet() {

	for (;;) {
		cout << endl;
		cout << "���Ƿ�֪����Ҫ�޸ĵĶ���ID�ţ�" << endl;
		for (;;) {
			cout << "֪��������1������������0������߲�ѯ������";
			int t = GetIntFromCin();

			if (t == 1)
				break;
			else if (t == 0) {
				QueryReaderService();
				break;
			}
			else
				cout << "����������������������" << endl;
		}

		AdminModifyReaderService();

		for (;;) {
			cout << "�Ƿ�������ж�����Ϣ�޸ģ�����������1��������ҳ������0��";
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

//�����޸��Լ�������Ϣ����
void ReaderModifySelfServlet(int id) {

	for (;;) {

		ReaderModifySelfService(id);

		for (;;) {
			cout << "�Ƿ��������������Ϣ�޸ģ�����������1��������ҳ������0��";
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

//���߽���Ƿ��
void PayTheFeesServlet(int readerId) {
	PayTheFeesService(readerId);
}




