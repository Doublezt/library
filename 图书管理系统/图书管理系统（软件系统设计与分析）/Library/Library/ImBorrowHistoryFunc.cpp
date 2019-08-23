#include"stdafx.h"
#include"BorrowHistoryFunc.h"
#include<fstream>
/**
* ��ӽ��ļ�¼
* ���ļ�¼��id��������
* @param borrowHistory
* @return
*/
bool addHistory(BorrowHistory& borrowHistory) {
	fstream fs;
	fs.open("borrowHistory.bat", ios::out | ios::in | ios::binary);
	//��׷�ӵ���ʽ��һ���Ѿ����ڵ��ļ����ж�д����(�ļ�ָ�����ļ�ĩβ)
	if (!fs) {
		//cout << "In function addHistory ..." << endl;
		cout << " Error in open file  borrowHistory .bat. " << endl;
		return false;
	}
	//���ڲ�ͬ������鼮��id�������ģ��տ�ʼ��Ҫ���ļ�ָ��ָ��
	//���һ����¼��Ȼ�������һ�����id,��1�͵õ������id
	fs.seekg(0, ios::end);
	int newId;
	streamoff len = fs.tellg();
	if (len < sizeof(BorrowHistory))  newId = 1;//�����ļ���һ����¼Ҳû�е����
	else {//ע������  sizeof(BorrowHistory) ���޷�����������ֱ�Ӷ���ӷ���
		int recordLen = sizeof(BorrowHistory);
		fs.seekg(-recordLen, ios::end); //��λ�����һ����¼�Ŀ�ʼ��

		char* buffer = new char[sizeof(BorrowHistory)];
		fs.read(buffer, sizeof(BorrowHistory));//��ȡ���һ��ͼ���¼

		BorrowHistory* lastRecord = (BorrowHistory*)buffer;//������������ǿ������ת��

		newId = (*lastRecord).id + 1;//�õ�Ҫ���������id����ɸ�ֵ
	}
	borrowHistory.id = newId;

	//Ȼ���ٽ��ļ�ָ�붨λ��ĩβ��дһ������ļ�¼
	fs.seekg(0, ios::end);
	fs.write((char*)&borrowHistory, sizeof(BorrowHistory));
	//�ر��ļ���д��
	fs.close();
	return true;

}

/**
* ���ݽ��ļ�¼idɾ�����ļ�¼����ɾ����
* @param borrowHistoryId
* @return
* ���id�����ڣ���������false
* ���򣬼�ɾ���ɹ��󷵻�true
*/
bool deleteHistory(int id) {
	/*�Ȳ��Ҹ�id�Ƿ���ڣ����������ֱ�ӷ���false*/
	list<BorrowHistory> bList = getHistoryById(id, 0);
	if (bList.empty()) return false;

	/*����id���ڣ��޸�������¼��exist���ԣ���д��ԭ����λ�ü���*/
	list<BorrowHistory>::iterator borrowHistory = bList.begin();
	if ((*borrowHistory).exist == 0) return true;

	(*borrowHistory).exist = 0;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowHistory.bat", ios::out | ios::binary | ios::in | ios::ate);
	//��һ���Ѵ��ڵ��ļ���,�����ļ�ָ��ָ�����

	if (!fs) {
		cout << " Error in open file borrowHistory.bat. " << endl;
		return false;
	}
	/*�����ļ�ָ�����ļ�ĩβ*/
	/*ͨ��record��id���������ļ�ָ��ƫ����*/
	long pos = sizeof(BorrowHistory) * ((*borrowHistory).id - 1);

	fs.seekg(pos, ios::beg);//��λ��Ҫ�޸ĵļ�¼��
	fs.write((char*)&(*borrowHistory), sizeof(BorrowHistory));//�޸ļ�¼

	fs.close();
	return true;
}


/**
* ͨ������id��ѯ���ļ�¼
* ���exist����Ϊ1����ֻ����δ��ɾ���Ľ�����ʷ�����߲��ģ�
* ���򣬲������н�����ʷ������Ա���ģ�
*/
list<BorrowHistory> getHistoryByReaderId(int readerId, int exist) {
	list<BorrowHistory> borrowHistoryList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowHistory.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		//cout << "In function getHistoryByReaderId ..." << endl;
		cout << " Error in open file borrowHistory.bat " << endl;
		return borrowHistoryList;
	}
	//��ָ���Ƶ��ļ�ĩβ�Ի�ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��ȡ�ļ�����
							   //��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowHistory)];//������ȡһ����¼�Ļ�����
	BorrowHistory borrowHistory;
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowHistory));//������¼
		borrowHistory = *((BorrowHistory*)buffer);
		if (exist == 1) {
			if (borrowHistory.exist == 0) continue;
			//ֻ����δ��ɾ���Ľ�����ʷʱ�������ǰ�鼮�����ڣ�ֱ������һ����¼!!!!!!!!
		}//��existΪ0ʱ���ҷ�Χ��ȫ��������ʷ
		if (borrowHistory.readerId == readerId)
			borrowHistoryList.push_back(borrowHistory);//��������������б�
	}
	delete[](buffer);
	fs.close();
	return borrowHistoryList;

}

/**
* ͨ���鼮id(����Ĳ���bookId��һ��ͼ��Ĺ�ͬid)��ѯ���ļ�¼
*
* ���exist����Ϊ1����ֻ����δ��ɾ���Ľ�����ʷ�����߲��ģ�
* ��0���������н�����ʷ������Ա���ģ�
* @return
*/
list<BorrowHistory> getHistoryByBooksId(int bookId, int exist) {
	list<BorrowHistory> borrowHistoryList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowHistory.bat", ios::binary | ios::in | ios::app);
	//��һ���Ѵ��ڵ��ļ���
	//��ָ���Ƶ��ļ�ĩβ�Ի�ȡ�ļ�����
	if (!fs) {
		//cout << "In function getHistoryByBookId ..." << endl;
		cout << " Error in open file borrowHistory.bat " << endl;
		return borrowHistoryList;
	}

	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��ȡ�ļ�����
							   //��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowHistory)];//������ȡһ����¼�Ļ�����
	BorrowHistory borrowHistory;
	int bId; //���������ȡ��BookId
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowHistory));//������¼
		borrowHistory = *((BorrowHistory*)buffer);
		if (exist == 1) {
			if (borrowHistory.exist == 0) continue;
			//ֻ����δ��ɾ���Ľ�����ʷʱ�������ǰ��¼����ɾ���ˣ�ֱ������һ����¼!!!!!!!!
		}
		//existΪ0ʱ����ѯ���н�����ʷ

		//����ÿ��ͼ���Ψһ����ǣ�
		//ǰ��λ�������id����2λ�ǵڼ����飬�������ͨ����bookId����100�Ϳ���
		//�õ��Ȿ�����������id

		bId = borrowHistory.bookId;
		if (bId == bookId)
			borrowHistoryList.push_back(borrowHistory);//ƥ�������list

	}
	delete[](buffer);
	fs.close();
	return borrowHistoryList;
}

/**
* �������еĽ��ļ�¼
* ���exist����Ϊ1����ֻ����δ��ɾ���Ľ�����ʷ�����߲��ģ�
* Ϊ0���������н�����ʷ������Ա���ģ�
* @return
*/
list<BorrowHistory> getAllHistory(int exist) {
	list<BorrowHistory> borrowHistoryList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowHistory.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		cout << " Error in open file borrowHistory.bat " << endl;
		return borrowHistoryList;
	}
	//��ָ���Ƶ��ļ�ĩβ�Ի�ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��ȡ�ļ�����
							   //��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowHistory)];//������ȡһ����¼�Ļ�����
	BorrowHistory borrowHistory;
	/*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowHistory));//������¼
		borrowHistory = *((BorrowHistory*)buffer);
		if (exist == 1) {
			if (borrowHistory.exist == 0) continue;
			//ֻ����δ��ɾ���Ľ�����ʷʱ�������ǰ��¼����ɾ���ˣ�ֱ������һ����¼!!!!!!!!
		}
		//existΪ0ʱ����ѯ���н�����ʷ
		borrowHistoryList.push_back(borrowHistory);
	}
	delete[](buffer);
	fs.close();
	return borrowHistoryList;
}




/*ͨ����ʷ��¼��id���Ҽ�¼
existΪ1 ������ҵ���δ��ɾ������ʷ��¼�в���
existΪ0����������ʷ��¼�в���*/
list<BorrowHistory> getHistoryById(int id, int exist) {
	list<BorrowHistory> borrowHistoryList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowHistory.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		cout << " Error in open file borrowHistory.bat " << endl;
		return borrowHistoryList;
	}
	//��ָ���Ƶ��ļ�ĩβ�Ի�ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��ȡ�ļ�����
							   //��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowHistory)];//������ȡһ����¼�Ļ�����
	BorrowHistory borrowHistory;
	/*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowHistory));//������¼
		borrowHistory = *((BorrowHistory*)buffer);
		if (exist == 1) {
			if (borrowHistory.exist == 0) continue;
			//ֻ����δ��ɾ���Ľ�����ʷʱ�������ǰ��¼����ɾ���ˣ�ֱ������һ����¼!!!!!!!!
		}
		//existΪ0ʱ����ѯ���н�����ʷ
		if (borrowHistory.id == id) {
			borrowHistoryList.push_back(borrowHistory);
			break;
		}
	}
	delete[](buffer);
	fs.close();
	return borrowHistoryList;
}

/*
int main() {
BorrowHistory h;
h.id = 1;
h.bookId = 3;
h.borrowTime = time(NULL);
h.exist = 0;
h.returnTime = time(NULL);

addHistory(h);

list<BorrowHistory> l;
l = getHistoryByBooksId(3,0);

l.clear();
l = getHistoryByBooksId(3,1);

l.clear();
l = getHistoryById(1,0);


deleteHistory(h);
l.clear();
l = getHistoryById(1, 1);
return 1;





}*/