
#include"stdafx.h"
#include<list>
#include"Structs.h"
#include"ReaderFunc.h"
#include"showInfo.h"
#include<string>
#include"DealFault.h"



list<Reader> QueryReaderById(int id)
{
	list<Reader> readerList = getReaderById(id);
	if (readerList.empty())
	{
		cout << "NOT FOUND!";
		readerList.clear();
		return readerList;
	}
	//����showInfo���ú���δ���
	showReaderInfo(readerList);
	return readerList;
}

//���ն����������Ҷ��ߣ�����Ϊstring�͵�name��ֱ���ں����ڵ�����ʾ������ʾ��ѯ���Ľ��
void QueryReaderByName(string name)
{
	list<Reader> readerList = getReadersByName(name);
	if (readerList.empty())
	{
		cout << "NOT FOUND!";
		return;
	}
	//����showInfo���ú���δ���
	showReaderInfo(readerList);
	return;
}

//���ն����Ա���Ҷ��ߣ�����Ϊint�͵�sex��ֱ���ں����ڵ�����ʾ������ʾ��ѯ���Ľ��
void QueryReaderBySex(int sex)
{
	list<Reader> readerList = getReadersBySex(sex);
	if (readerList.empty())
	{
		cout << "NOT FOUND!";
		return;
	}
	//����showInfo���ú���δ���
	showReaderInfo(readerList);
	return;
}

//��ȡ���ж�����Ϣ���޲�����ֱ���ں����ڵ�����ʾ������ʾ��ѯ���Ľ��
void QueryAllReader()
{
	list<Reader> readerList = getReaders();
	if (readerList.empty())
	{
		cout << "NOT FOUND!";
		return;
	}
	//����showInfo���ú���δ���
	showReaderInfo(readerList);
	return;
}



/*��������ѯ������Ӧ�����Ķ��߲�չʾ���û���*/
//��������id���������Ա����У���ѯ���ߣ��ѱ�ɾ������ɾ�����Ķ��߲��ᱻ������
void QueryReaderService() {
	while (1)
	{
		string key;//������ҵ�����
		string name;
		cout << endl << "�����������ҵ�����" << endl << "1 id" << endl << "2 ����" << endl << "3 �Ա�" << endl << "4 ��ʾ���ж�����Ϣ" << endl << "����Ϊ�˳���ѯ " << endl;
		getline(cin, key);
		if (key == "1")//����id���Ҷ���
		{
			cout << endl << "��������Ҫ���ҵĶ��ߵ�id" << endl;
			int id;//��ʱ�洢Ҫ���ҵĶ��ߵ�id
			id = GetIntFromCin();

			while (id <= 0)//id��������int���Ҵ���0�����򱨴�Ҫ����������
			{
				cout << endl << "�����������������룡" << endl;
				id = GetIntFromCin();
			}
			QueryReaderById(id);
		}
		else if (key == "2")//�����������Ҷ���
		{
			cout << endl << "��������Ҫ���ҵĶ��ߵ�����" << endl;
			string name;//��ʱ�洢Ҫ���ҵĶ��ߵ�����
			getline(cin, name);
			QueryReaderByName(name);

		}
		else if (key == "3")//�����Ա���Ҷ���
		{
			cout << endl << "������ö��ߵ��Ա�,1��ʾ���ԣ�0��ʾŮ��" << endl;
			int tempSex;//��ʱ�洢�ö��ߵ��Ա�;
			tempSex = GetIntFromCin();
			while (tempSex != 0 && tempSex != 1)//�Ա����Ϊ���Σ������������һ����֮���ֵ
			{
				cout << endl << "���벻�Ϸ��������������1��0֮����ַ�,����������" << endl;
				tempSex = GetIntFromCin();
			}
			QueryReaderBySex(tempSex);
		}
		else if (key == "4")//��ʾ���ж�����Ϣ
		{
			QueryAllReader();
		}
		else
		{
			cout << endl << "��ѯ�ѽ�����" << endl;
			return
				;
		}
	}

}


/*����һ����ߵ�service*/
//���Ӷ��ߣ���������һ��������Ϊlist<Reader>
void AddReaderService(list<Reader> readerList)
{
	if (readerList.empty())
	{
		cout << "empty rederList";
		return;
	}

	//bool status = true;//statusΪtrue��ʾ��ӹ�����û�г���Ϊfalse��ʾ����
	for (list<Reader> ::iterator it = readerList.begin(); it != readerList.end(); it++)
	{
		if (!addReader(*it))
		{
			cout << "��Ӷ���ʧ�ܣ�����idΪ" << it->id << endl;
		}
	}
	return;
}

//ɾ�����ߣ�һ��ֻɾ��һ��������ΪReader.id
void DeleteReaderService(int id)
{
	Reader aReader;
	list<Reader> readerList = getReaderById(id);
	if (readerList.empty())
	{
		cout << endl << "���޴���Ӵ~" << endl;
		return;
	}
	aReader = readerList.back();
	aReader.exist = 0;
	if (!modifyReader(aReader))
		cout << "ɾ������ʧ��" << endl;
	else
		cout << endl << "idΪ" << id << "�Ķ�����ɾ��" << endl;
	return;
}



bool ModifyReaderName(Reader &reader) {
	string name;

	cout << "�������޸ĵ�����������0ȡ���޸ģ�";
	getline(cin, name);

	if (name == "0")
		return false;
	else
		copy(reader.name, name, sizeof(Reader::name));
	return true;
}

bool ModifyReaderPassword(Reader &reader) {


	string password;

	cout << "�������޸ĵ����룬��ע�⣬����ֻ�������Ӣ���ַ������֣�����0ȡ���޸ģ�";
	getline(cin, password);

	if (password == "0")
		return false;
	else
		//���������ݴ�

		copy(reader.password, password, sizeof(Reader::password));
	return true;
}

bool ModifyReaderSex(Reader &reader) {
	int sex;

	for (;;) {
		cout << "�������޸ĵ��Ա�0.Ů��1.�У�2.ȡ���޸ģ�";
		sex = GetIntFromCin();

		if (sex == 2)
			return false;
		//�Ա�ֻ������
		else if (sex != 0 && sex != 1)
			cout << "����������������������" << endl;
		else {
			reader.sex = sex;
			break;
		}
	}
	return true;
}

bool ModifyReaderFine(Reader &reader) {
	double fine = -1;

	for (;;) {
		cout << "�������޸ĵ�Ƿ�������-1ȡ���޸ģ�";
		cin >> fine;
		//����Ƿ���ݴ�

		if (fine == -1)
			return false;
		//Ƿ�������ڵ���0
		else if (fine < 0)
			cout << "Ƿ����������0������������������������" << endl;
		else {
			reader.fine = fine;
			break;
		}
	}
	return true;
}

//����Ա�޸�����һ��������Ϣ
void AdminModifyReaderService() {
	//flag�����ж��Ƿ񾭹��޸�
	bool flag = false;
	int id;
	Reader reader;
	list<Reader> readerList;

	for (;;) {
		//ͨ��id���ҵ�����
		cout << endl;
		cout << "����������ѯ���ߵ�ID������0ȡ����ѯ��";
		id = GetIntFromCin();

		if (id == 0)
			return;
		else
			readerList = QueryReaderById(id);
		if (readerList.empty())
			return;

		reader = readerList.back();
		readerList.pop_back();

		//ʵ���޸Ķ������
		for (int i = -1; i != 0;) {
			//ѡ���޸ĵ�ѡ��
			cout << endl;
			cout << "��ѡ����Ҫ�޸ĵ���Ϣ,��ȷ���޸�������0��" << endl;
			cout << "0.ȷ�ϵ�ǰ�޸�" << endl;
			cout << "-1.ȡ���޸�" << endl;
			cout << "1.����" << endl;
			cout << "2.����" << endl;
			cout << "3.�Ա�" << endl;
			cout << "4.Ƿ����" << endl;
			i = GetIntFromCin();

			//ʵ�ֹ��ܵ�ѡ��
			switch (i) {
			case 1:
				flag = ModifyReaderName(reader);
				break;
			case 2:
				flag = ModifyReaderPassword(reader);
				break;
			case 3:
				flag = ModifyReaderSex(reader);
				break;
			case 4:
				flag = ModifyReaderFine(reader);
				break;
			case 0:
				break;
			case -1:
				return;
			default:
				cout << "����������������������" << endl;
			}
		}

		if (flag) {
			flag = false;
			cout << "ȷ���޸ģ�ȷ��������1��ȡ��������0��";
			int t = GetIntFromCin();

			if (t == 1) {
				//���ú����޸Ķ�����Ϣ
				if (modifyReader(reader)) {
					cout << "�޸Ķ�����Ϣ�ɹ���" << endl;
					//�������޸ĵĶ��ߵ���Ϣ
					readerList.clear();
					readerList.push_back(reader);
					showReaderInfo(readerList);
					return;
				}
				else
					cout << "�޸Ķ�����Ϣʧ�ܣ�" << endl;
			}
			else if (t == 0)
				cout << "�޸�ȡ����" << endl;
			else
				cout << "����������������������" << endl;
		}
	}
}

//�����޸��Լ�������Ϣ
void ReaderModifySelfService(int id) {
	//flag�����ж��Ƿ񾭹��޸�
	bool flag = false;
	Reader reader;
	list<Reader> readerList;

	for (;;) {
		readerList = QueryReaderById(id);

		reader = readerList.back();
		readerList.pop_back();

		//ʵ���޸Ķ������
		for (int i = -1; i != 0;) {
			//ѡ���޸ĵ�ѡ��
			cout << endl;
			cout << "��ѡ����Ҫ�޸ĵ���Ϣ,��ȷ���޸�������0��" << endl;
			cout << "0.ȷ�ϵ�ǰ�޸�" << endl;
			cout << "-1.ȡ���޸�" << endl;
			cout << "1.����" << endl;
			cout << "2.����" << endl;
			cout << "3.�Ա�" << endl;
			i = GetIntFromCin();

			string oriPwd;
			int okay = 1;
			int times = 5;//ÿ���������������������
			//ʵ�ֹ��ܵ�ѡ��
			switch (i) {
			case 1:
				flag = ModifyReaderName(reader);
				break;
			case 2:
				while (1) {
					if (times < 0) {
						cout << "���Ѿ������������5���ˣ����ܼ������룡" << endl;
						break;
					}
					cout << "��������ԭ�������룺";
					getline(cin, oriPwd);
					for (int j = 0; j < oriPwd.length() && j < sizeof(reader.password); j++) {
						if (oriPwd[j] != reader.password[j]) {
							okay = 0;
							break;
						}
					}
					if (okay) {
						flag = ModifyReaderPassword(reader);
						break;
					}
					else {
						cout << endl << "���������������" << endl;
						times--;
					}
				}
				break;
			case 3:
				flag = ModifyReaderSex(reader);
				break;
			case 0:
				break;
			case -1:
				return;
			default:
				cout << "����������������������" << endl;
			}
		}

		if (flag) {
			flag = false;
			cout << "ȷ���޸ģ�ȷ��������1��ȡ��������0��";
			int t = GetIntFromCin();

			if (t == 1) {
				//���ú����޸Ķ�����Ϣ
				if (modifyReader(reader)) {
					cout << "������Ϣ�޸ĳɹ���" << endl;
					//�������޸ĵĶ��ߵ���Ϣ
					readerList.clear();
					readerList.push_back(reader);
					showReaderInfo(readerList);
					return;
				}
				else
					cout << "������Ϣ�޸�ʧ�ܣ�������" << endl;
			}
			else if (t == 0)
				cout << "�޸�ȡ����" << endl;
			else
				cout << "����������������������" << endl;
		}
	}
}



//���߽���Ƿ��
void PayTheFeesService(int readerId) {

	list<Reader> reader = getReaderById(readerId);
	list<Reader>::iterator it = reader.begin();
	cout << "����Ƿ��Ϊ:" << ((*it).fine) << endl;

	if ((*it).fine == 0) {
		cout << "���������Ƿ�" << endl;
	}
	else {

		int select;
		while (1) {
			cout << endl << "1.��������Ƿ��" << endl;
			cout << "2.�˳���ǰ����" << endl;
			cout << "������ѡ�";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
				((*it).fine = 0);
				modifyReader(*it);
				cout << endl << "����Ƿ����ɳɹ�����ǰǷ��Ϊ0��" << endl;
				break;
			case 2:return;
			default:
				cout << endl << "ֻ������1��2��" << endl;
				continue;
			}

		}

	}

}

