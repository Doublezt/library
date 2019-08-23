#include"stdafx.h"
#include"ReaderFunc.h"
#include<fstream>

/**
* ����Ψһ��Id���Ҷ���
* �Ҳ�������һ����list
* @param id
* @return
*/
list<Reader> getReaderById(int id) {
	list<Reader> readerList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("reader.bat", ios::out | ios::binary | ios::in | ios::ate);
	//��һ���Ѵ��ڵ��ļ���,�����ļ�ָ��ָ�����

	if (!fs) {
		cout << "In function getReaderById ..." << endl;
		cout << " Error in open file reader.bat. " << endl;
		return readerList;
	}

	/*ͨ�����ߵ�id���������ļ�ָ��ƫ����
	�������õ���ƫ���������ļ��ֽڳ��Ȼ���С��0��ֱ�ӷ��ؿ�list
	*/
	long pos = sizeof(Reader) * (id - 1);
	if (pos < 0 || pos > fs.tellg()) {
		fs.close();
		return readerList; }

	fs.seekg(pos, ios::beg);
	char* buffer = new char[sizeof(Reader)];
	fs.read(buffer, sizeof(Reader));//������¼
	Reader aReader = *((Reader*)buffer);

	if (aReader.exist == 1)//��������������������������������ֻ����û�б�ɾ���Ķ���
		readerList.push_back(aReader);//����¼��ӵ�listĩβ
	fs.close();
	delete[] buffer;
	return readerList;
}

/**
* �����Ա���Ҷ���
* @param sex sexȡ1�������ԣ�0����Ů��
* ����ඨ����sex������һ�µ�
* �Ҳ�������һ����list
* @return
*/
list<Reader> getReadersBySex(int sex) {
	list<Reader> readerList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("reader.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		//cout << "In function getReaderBySex ..." << endl;
		cout << " Error in open file reader.bat " << endl;
		return readerList;
	}

	//��ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();
	fs.seekg(0, ios::beg);

	char* buffer = new char[sizeof(Reader)];//������ȡһ����¼�Ļ�����
	Reader aReader;
	int tempSex;//������ŵ�ǰ�����ļ�¼��sex�ֶ�

				/*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Reader));//������¼
		aReader = *((Reader*)buffer);
		if (aReader.exist == 0) continue;//�����ǰ���߲����ڣ�ֱ������һ����¼!!!!!!!!
		tempSex = aReader.sex;

		if (tempSex == sex)//������
			readerList.push_back(aReader);//ƥ�������list
	}
	fs.close();
	delete[] buffer;
	return readerList;
}

/**
* �������ֲ��Ҷ���(ģ����ѯ)
* @param name
* @return
*/
list<Reader> getReadersByName(string name) {
	list<Reader> readerList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("reader.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		//cout << "In function getReaderByName ..." << endl;
		cout << " Error in open file reader.bat " << endl;
		return readerList;
	}

	//��ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();
	fs.seekg(0, ios::beg);

	char* buffer = new char[sizeof(Reader)];//������ȡһ����¼�Ļ�����
	Reader aReader;
	string s = "";//������ŵ�ǰ�����ļ�¼��name�ֶ�
				  /*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Reader));//������¼
		aReader = *((Reader*)buffer);
		if (aReader.exist == 0) continue;//�����ǰ����߲����ڣ�ֱ������һ����¼!!!!!!!!
		s = aReader.name;
		//trimAllSpace(name);//��������ַ���ȥ�����пո�

		if (s.find(name) != string::npos)//������
			readerList.push_back(aReader);//ƥ�������list
	}
	fs.close();
	delete[] buffer;
	return readerList;
}

/**
* ������ж��ߵ���Ϣ
* @return
*/
list<Reader> getReaders() {
	//�������ж��߼�¼
	list<Reader> readerList;
	char* buffer = new char[sizeof(Reader)];//buffer��Ϊ����ָ��
	ifstream infile("reader.bat", ios::binary);
	if (!infile)
	{
		//cout << "In function getReaders ..." << endl;
		cout << " Error in open file Reader.bat. " << endl;
		return readerList;
	}

	//��ȡ�ļ�����
	infile.seekg(0, ios::end);
	streamoff len = infile.tellg();
	infile.seekg(0, ios::beg);

	Reader aReader;
	while (infile.tellg() < len)
	{
		infile.read(buffer, sizeof(Reader));
		aReader = *((Reader*)buffer);
		//Reader aReader = *((Reader*)buffer);
		if (aReader.exist == 1)
			readerList.push_back(aReader);
	}
	infile.close();
	delete[] buffer;
	return readerList;
	/*�����ã����Խ���ɹ�
	for (it = readerList.begin(); it != readerList.end(); it++)
	{
	cout << it->name << endl;
	}
	*/
}


/**
* /��Ӷ���
* ����Ҳ��ֻ��������߱������һ�����߼�¼
* ��������Ϣ�Ĺ�����һ�������
* ��������������󣬲���reader��id�ᱻ��Ϊ�����ļ��е�id��
* @param reader
* @return
*/
bool addReader(Reader& reader) {
	fstream fs;
	fs.open("reader.bat", ios::out | ios::in | ios::binary);
	//��׷�ӵ���ʽ��һ���Ѿ����ڵ��ļ����ж�д����(�ļ�ָ�����ļ�ĩβ)
	if (!fs) {
		cout << " Error in open file reader.bat. " << endl;
		return false;
	}
	//���ڶ��ߵ�id�������ģ��տ�ʼ��Ҫ���ļ�ָ��ָ�����һ����¼
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Reader))  newId = 1;//�����ļ���һ����¼Ҳû�е����
	else {//ע������  sizeof(Reader) ���޷�����������ֱ�Ӷ���ӷ���
		int readerLen = sizeof(Reader);
		fs.seekg(-readerLen, ios::end); //��λ�����һ����¼�Ŀ�ʼ��

		char* buffer = new char[sizeof(Reader)];
		fs.read(buffer, sizeof(Reader));//��ȡ���һ��ͼ���¼

		Reader* lastReader = (Reader*)buffer;//������������ǿ������ת��

		newId = (*lastReader).id + 1;//�õ�Ҫ���������id����ɸ�ֵ
		delete[] buffer;
	}
	reader.id = newId;
	//Ȼ���ٽ��ļ�ָ�붨λ��ĩβ��дһ������ļ�¼
	fs.seekg(0, ios::end);
	fs.write((char*)&reader, sizeof(Reader));
	//�ر��ļ���д��
	fs.close();
	return true;

}

/**
* ���Ķ�����Ϣ
* @param reader
* @return
*/

bool modifyReader(Reader& reader) {
	//���ļ�reader.batʱ��֤�ļ����ݲ���ɾ��
	fstream fs("reader.bat", ios::out | ios::in | ios::ate | ios::binary);
	//�жϴ��ļ�reader.bat�Ƿ�ɹ������޷��������������Ϣ������false
	if (!fs) {
		cout << "Error: Can not open file 'reader.bat'!" << endl;
		fs.close();
		return false;
	}
	//ͨ��id�����ļ�ָ��ƫ�����Զ�ȡָ������
	long pos = sizeof(Reader) * (reader.id - 1);
	//�жϲ��ҵ�λ���Ƿ���ȷ,��С��0�򳬳��ļ����������������Ϣ������false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input Reader ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//��ȡָ��λ�õ�����
	Reader* rReader;
	char* buffer = new char[sizeof(Reader)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(Reader));
	rReader = (Reader*)buffer;
	//�Ƚ��ļ��ڲ��ҵ���rReader.id������Ҫ�޸ĵ�reader.id�Ƿ���ͬ����ͬ������ļ������޸ģ�����ͬ�����������Ϣ������false
	if (rReader->id == reader.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&reader, sizeof(Reader));
		//cout << "Modify Reader success!" << endl;
		fs.close();
		delete[] buffer;
		return true;
	}
	else {
		cout << "Error: Modify Reader ID mismatch!" << endl;
		fs.close();
		delete[] buffer;
		return false;
	}
	
}

/*ɾ��һ������(��ɾ�����޸�exist���Լ���)
�������id�����ڣ���������false
���򣬼�ɾ���ɹ���������true
*/
bool deleteReader(int id) {
	list<Reader> readerList = getReaderById(id);
	if (readerList.empty()) return false;
	list<Reader>::iterator it = readerList.begin();

	if ((*it).exist == 0) return true;
	(*it).exist = 0;
	return modifyReader(*it);
}