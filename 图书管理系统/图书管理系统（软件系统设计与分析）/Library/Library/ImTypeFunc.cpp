#include"stdafx.h"
#include"TypeFunc.h"
#include<fstream>

/*����һ���������*/
bool addType(Type& type) {
	fstream fs;
	fs.open("type.bat", ios::out | ios::in | ios::binary);
	//��׷�ӵ���ʽ��һ���Ѿ����ڵ��ļ����ж�д����(�ļ�ָ�����ļ�ĩβ)
	if (!fs) {
		cout << " Error in open file type.bat. " << endl;
		return false;
	}
	//����type��id�������ģ��տ�ʼ��Ҫ���ļ�ָ��ָ�����һ����¼
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Type))  newId = 1;//�����ļ���һ����¼Ҳû�е����
	else {//ע������  sizeof(Type) ���޷�����������ֱ�Ӷ���ӷ���
		int typeLen = sizeof(Type);
		fs.seekg(-typeLen, ios::end); //��λ�����һ����¼�Ŀ�ʼ��

		char* buffer = new char[sizeof(Type)];
		fs.read(buffer, sizeof(Type));//��ȡ���һ��ͼ���¼

		Type* lastType = (Type*)buffer;//������������ǿ������ת��

		newId = (*lastType).id + 1;//�õ�Ҫ������type��id����ɸ�ֵ
		delete[] buffer;
	}
	type.id = newId;
	//Ȼ���ٽ��ļ�ָ�붨λ��ĩβ��дһ������ļ�¼
	fs.seekg(0, ios::end);
	fs.write((char*)&type, sizeof(Type));
	//�ر��ļ���д��
	fs.close();
	return true;
}

bool modifyType(Type& type) {
	//���ļ�type.batʱ��֤�ļ����ݲ���ɾ��
	fstream fs("type.bat", ios::out | ios::in | ios::ate | ios::binary);
	//�жϴ��ļ�type.bat�Ƿ�ɹ������޷��������������Ϣ������false
	if (!fs) {
		cout << "Error: Can not open file 'type.bat'!" << endl;
		return false;
	}
	//ͨ��id�����ļ�ָ��ƫ�����Զ�ȡָ������
	long pos = sizeof(Type) * (type.id - 1);
	//�жϲ��ҵ�λ���Ƿ���ȷ,��С��0�򳬳��ļ����������������Ϣ������false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input type ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//��ȡָ��λ�õ�����
	Type* rType;
	char* buffer = new char[sizeof(Type)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(Type));
	rType = (Type*)buffer;
	//�Ƚ��ļ��ڲ��ҵ���rType.id������Ҫ�޸ĵ�type.id�Ƿ���ͬ
	//��ͬ������ļ������޸ģ�����ͬ�����������Ϣ������false
	if (rType->id == type.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&type, sizeof(Type));
		fs.close();
		delete[] buffer;
		return true;
		//cout << "Modify Type success!" << endl;
	}
	else {
		cout << "Error: Modify Type ID mismatch!" << endl;
		fs.close();
		delete[] buffer;
		return false;
	}
}

list<Type> getTypeById(int id) {
	list<Type> typelist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("Type.bat", ios::out | ios::binary | ios::in | ios::ate);
	//��һ���Ѵ��ڵ��ļ���,�����ļ�ָ��ָ�����

	if (!fs) {
		cout << " Error in open file Type.bat. " << endl;
		return typelist;
	}

	/*ͨ��type��id���������ļ�ָ��ƫ����
	�������õ���ƫ���������ļ��ֽڳ��Ȼ���С��0��ֱ�ӷ��ؿ�list
	*/
	long pos = sizeof(Type) * (id - 1);
	if (pos < 0 || pos > fs.tellg()) { 
		fs.close();
		return typelist;
	}

	fs.seekg(pos, ios::beg);
	char* buffer = new char[sizeof(Type)];
	fs.read(buffer, sizeof(Type));//������¼
	Type type = *((Type*)buffer);
	typelist.push_back(type);//����¼��ӵ�listĩβ

	fs.close();
	delete[] buffer;

	return typelist;

}

/*����������ҵ���Ӧ�����(ģ����ѯ)*/
list<Type> getTypeByName(string name) {
	list<Type> Typelist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("type.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		cout << " Error in open file type.bat " << endl;
		return Typelist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//��ȡ�ļ�����
							   //��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Type)];//������ȡһ����¼�Ļ�����
	Type type;
	string s = "";//������ŵ�ǰ�����ļ�¼��name�ֶ�
				  /*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Type));//������¼
		type = *((Type*)buffer);
		s = type.name;
		trimAllSpace(name);//��������ַ���ȥ�����пո�

		if (s.find(name) != string::npos)
			Typelist.push_back(type);//ƥ�������list
	}
	fs.close();
	delete[] buffer;
	return Typelist;
}



/*�������������ɵ�list*/
list<Type> getAllTypes() {
	list<Type> Typelist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("type.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		cout << " Error in open file type.bat " << endl;
		return Typelist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//��ȡ�ļ�����
							   //��λ���ļ���ͷ

	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Type)];//������ȡһ����¼�Ļ�����
	

	while (fs.tellg() < len) {
		Type type;
		fs.read(buffer, sizeof(Type));//������¼
		type = *((Type*)buffer);
		Typelist.push_back(type);//����list
	}

	fs.close();
	delete[] buffer;
	return Typelist;
}


/*
int main() {
	Type t;
	setTypeName(t,"nihao");
	addType(t);
	list<Type> b = getTypeById(1);
	for (list<Type>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}

	
	b.clear();
	b = getTypeById(1);

	for (list<Type>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}


	b.clear();

	b = getTypeByName("ni");
	for (list<Type>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}
	int i;
	cin >> i;
	return 1;




}*/