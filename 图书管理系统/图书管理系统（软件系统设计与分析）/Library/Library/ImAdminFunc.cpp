#include"stdafx.h"
#include"AdminFunc.h"
#include<fstream>
/**
* ���Ĺ���Ա��Ϣ
* @param admin
* @return ���޸ĳɹ�����true�����򷵻�false��Ȼ�������������ĺ�������������������
*/
bool modifyAdmin(Admin& admin) {
	//���ļ�admin.batʱ��֤�ļ����ݲ���ɾ��
	fstream fs("admin.bat", ios::out | ios::in | ios::ate | ios::binary);
	//�жϴ��ļ�admin.bat�Ƿ�ɹ������޷��������������Ϣ������false
	if (!fs) {
		cout << "Error: Can not open file 'admin.bat'!" << endl;
		fs.close();
		return false;
	}
	//ͨ��id�����ļ�ָ��ƫ�����Զ�ȡָ������
	long pos = sizeof(Admin) * (admin.id - 1);
	//�жϲ��ҵ�λ���Ƿ���ȷ,��С��0�򳬳��ļ����������������Ϣ������false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input Admin ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//��ȡָ��λ�õ�����
	Admin* rAdmin;
	char* buffer = new char[sizeof(Admin)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(Admin));
	rAdmin = (Admin*)buffer;
	//�Ƚ��ļ��ڲ��ҵ���rAdmin.id������Ҫ�޸ĵ�admin.id�Ƿ���ͬ����ͬ������ļ������޸ģ�����ͬ�����������Ϣ������false
	if (rAdmin->id == admin.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&admin, sizeof(Admin));
		//cout << "Modify Admin success!" << endl;
		delete[] buffer;
		fs.close();
		return true;
	}
	else {
		cout << "Error: Modify Admin ID mismatch!" << endl;
		delete[] buffer;
		fs.close();
		return false;
	}
}


/*��id�Ų��ҹ���Ա��Ϣ
����Ա��¼���õ��������
|���Ҳ����᷵��һ�����б�
*/
list<Admin> getAdminById(int id) {
	list<Admin> adminList;//����list��
	fstream fs;
	fs.open("admin.bat", ios::out | ios::in | ios::binary | ios::ate);//���ļ�������in�������룬out���������ate��ʾ���ļ�ָ��ָ�����
	if (!fs)//����ļ������ڣ����error
	{
		cout << "open file admin.bat error" << endl;
	}
	else
	{
		long pos = sizeof(Admin)*(id - 1);//ͨ��id�ż���ָ��ƫ����
		if (pos<0 || pos>fs.tellg()) {
			cout << "id error" << endl;//���ƫ����С������ߴ����ļ����ȣ����error,���ؿ�list
		}
		else
		{
			fs.seekg(pos, ios::beg);//ָ����ת���ļ�ͷ
			char * buffer = new char[sizeof(Admin)];//����adamin���ȵ�buffer����
			fs.read(buffer, sizeof(Admin));//���ļ�
			Admin adminById = *((Admin*)buffer);//��bufferǿ��ת��Ϊadmin���ͣ�����ֵ��adminById
			if (adminById.exist == 1)//���δ��ɾ��������¼��ӵ�Listĩβ
			{
				adminList.push_back(adminById);
			}
			delete[] buffer;
		}
	}
	fs.close();
	return adminList;
}

/*ɾ��һ������Ա����ɾ�����޸�exist���Լ���)
������id�����ڣ���������false
�����ɾ���ɹ��󣬷���true
*/
bool deleteAdmin(int id) {
	list<Admin> adminList = getAdminById(id);
	if (adminList.empty()) return false;
	list<Admin>::iterator it = adminList.begin();

	if ((*it).exist == 0) return true;
	(*it).exist = 0;
	return modifyAdmin(*it);
}

/*����һ������Ա(�����״��½�һ������Ա�˺�
����Ա�˺�ֻ��һ���͹���)*/
bool addAdmin(Admin& admin) {
	fstream fs;
	fs.open("admin.bat", ios::out | ios::in | ios::binary);
	//��׷�ӵ���ʽ��һ���Ѿ����ڵ��ļ����ж�д����(�ļ�ָ�����ļ�ĩβ)
	if (!fs) {
		cout << " Error in open file admin.bat. " << endl;
		return false;
	}
	//���ڹ���Ա��id�������ģ��տ�ʼ��Ҫ���ļ�ָ��ָ��
	//���һ����¼��Ȼ�������һ�����id,��1�͵õ������id
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Admin))  newId = 1;//�����ļ���һ����¼Ҳû�е����
	else {//ע������  sizeof(Admin) ���޷�����������ֱ�Ӷ���ӷ���
		int adminLen = sizeof(Admin);
		fs.seekg(-adminLen, ios::end); //��λ�����һ����¼�Ŀ�ʼ��

		char* buffer = new char[sizeof(Admin)];
		fs.read(buffer, sizeof(Admin));//��ȡ���һ��ͼ���¼

		Admin* lastAdmin = (Admin*)buffer;//������������ǿ������ת��

		newId = (*lastAdmin).id + 1;//�õ�Ҫ���������id����ɸ�ֵ
		delete[] buffer;
	}
	admin.id = newId;
	//Ȼ���ٽ��ļ�ָ�붨λ��ĩβ��дһ������ļ�¼
	fs.seekg(0, ios::end);
	fs.write((char*)&admin, sizeof(Admin));
	//�ر��ļ���д��
	fs.close();

	return true;

}


/*
using namespace std;

int main()

{
Admin a;
a.exist = 1;
setAdminPd(a,"123");
addAdmin(a);
cout << a.password << endl;
list<Admin> l = getAdminById(1);
for (list<Admin>::iterator it = l.begin(); it != l.end(); ++it) {
cout << (*it).id <<" " << (*it).password << endl;
}

int i;
cin >> i;



return 0;
}*/
