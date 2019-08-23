#include"stdafx.h"
#include"BorrowRecordFunc.h"
#include<fstream>
#include"showInfo.h"
#include"BookOperationServlet.h"



/**
* ��Ӽ�¼���������
* ��¼��id�������ģ���Ҫ���ļ�ָ�붨Ϊ��ĩβ��ȡ���һ����¼��id
* @param borrowRecord
* @return
*/
bool addRecord(BorrowRecord& borrowRecord) {
	fstream fs;
	fs.open("borrowRecord.bat", ios::out | ios::in | ios::binary);
	//��׷�ӵ���ʽ��һ���Ѿ����ڵ��ļ����ж�д����(�ļ�ָ�����ļ�ĩβ)
	if (!fs) {
		cout << " Error in open file borrowRecord.bat. " << endl;
		return false;
	}
	
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(BorrowRecord))  newId = 1;//�����ļ���һ����¼Ҳû�е����
	else {//ע������  sizeof(BorrowRecord) ���޷�����������ֱ�Ӷ���ӷ���
		int recordLen = sizeof(BorrowRecord);
		fs.seekg(-recordLen, ios::end); //��λ�����һ����¼�Ŀ�ʼ��

		char* buffer = new char[sizeof(BorrowRecord)];
		fs.read(buffer, sizeof(BorrowRecord));//��ȡ���һ����¼

		BorrowRecord* lastRecord = (BorrowRecord*)buffer;//������������ǿ������ת��

		newId = (*lastRecord).id + 1;//�õ�Ҫ�����ļ�¼��id����ɸ�ֵ
	}
	borrowRecord.id = newId;
	//Ȼ���ٽ��ļ�ָ�붨λ��ĩβ��дһ���¼�¼
	fs.seekg(0, ios::end);
	fs.write((char*)&borrowRecord, sizeof(BorrowRecord));

	//�ر��ļ���д��
	fs.close();
	return true;

}
/*���Գɹ�*/
/**
* ɾ����¼����ɾ����ʱ�����ֻ��id�ż��ɣ�
*�����뷨�ǽ���ɾ����¼֮��֮���ÿ����¼��id����1
*Ȼ����ǰ�ƶ�
*�����ļ����нضϼ���
*���Ǻ�������windows�� c++û�нض��ļ�����
����Ϊ����ɾ����ֻ����дһ���ļ���
* @param borrowRecord
* @return
*/
bool deleteRecord(int id) {
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowRecord.bat", ios::out | ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���,�����ļ�ָ��ָ�����

	if (!fs) {
		cout << " Error in open file borrowRecord.bat. " << endl;
		return false;
	}
	int count = sizeof(BorrowRecord);
	/*����Ҫ�����㱻ɾ���ļ�¼����λ��*/
	streamoff pos = count * (id - 1);
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();
	if (pos < 0 || pos > len) {
		fs.close();
		return false; 
	}//���Ҫɾ����¼��id����Ч������false


	/*����ʣ�µļ�¼��д��list*/
	list<BorrowRecord> recordList;
	fs.seekg(0, ios::beg);

	char* buffer = new char[count];
	streamoff l = fs.tellg();
	/*ע������δ�����ļ�ĩβ���ж����
	��һ�ε��Է��� len�����ļ��д�ŵ���ʵ�ֽ��������Ǳ���ʵ�ֽ���Ҫ��
	������������û�г�����������������˹���*/
	/*������ж����������� while(!fs.eof()) ��Ϊ�������ļ����һ���ֽ�ʱ,fs.eof()����
	true��ֻ����׼����ȡ�ֽڵ�ʱ��fs.eof()�Ż���false
	�����������fs.eof()��Ϊ�������ͻᵼ�¼�¼��һ��...C++���������Ƶ�����...*/
	while (l < len) {//����δ�����ļ�ĩβʱ��������
		if (fs.tellg() == pos) { 
			fs.seekg(count, ios::cur);
			l = fs.tellg();//!!!!!!!!!!!
			continue;
		}//����Ҫɾ���ļ�¼
		fs.read(buffer, count);//��һ���ļ�¼����buffer
		BorrowRecord record = *((BorrowRecord*)buffer);
		if(fs.tellg() > pos){
			record.id--;//��ɾ����¼֮��ļ�¼id�Ŷ����1
		}
		recordList.push_back(record);//Ҫ��˳��ÿ�ζ�����¼��ӵ�list��ĩβ
		l = fs.tellg();
	}

	delete [] buffer;//�ڴ���գ�����
	fs.close();

	/*������Ҫɾ��ԭ�����ļ�(ios::out)
	�½�һ���ļ�����list�������ȫ��д��*/
	fs.open("borrowRecord.bat", ios::out | ios::binary);
	if (!fs) {
		cout << "Open file failure in borrowRecord.bat" << endl;
		return false;
	}

	if (!recordList.empty()) {
		for (list<BorrowRecord>::iterator it = recordList.begin(); it != recordList.end(); ++it) {
			fs.write((char*)&(*it), sizeof(BorrowRecord));//дһ����¼
		}
	}

	fs.close();
	return true;
}




/**
* ͨ������id��ѯ�������Ϣ
* @return
*/
list<BorrowRecord> getRecordsByReaderId(int readerId) {
	list<BorrowRecord> borrowRecordList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowRecord.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		cout << " Error in open file borrowRecord.bat " << endl;
		return borrowRecordList;
	}
	//��ָ���Ƶ��ļ�ĩβ�Ի�ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��ȡ�ļ�����
	//��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowRecord)];//������ȡһ����¼�Ļ�����
	BorrowRecord borrowRecord;
	int rId; //���������ȡ��BookId
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowRecord));//������¼
		borrowRecord = *((BorrowRecord*)buffer);
		rId = borrowRecord.readerId;
		if (rId == readerId)
			borrowRecordList.push_back(borrowRecord);//ƥ�������list
	}
	delete[](buffer);
	fs.close();
	return borrowRecordList;
}

/**
* �����鼮id��ѯ�������Ϣ
* @return
*/
list<BorrowRecord> getRecordByBookId(int bookId) {
	list<BorrowRecord> borrowRecordList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowRecord.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		cout << " Error in open file borrowRecord.bat " << endl;
		return borrowRecordList;
	}
	//��ָ���Ƶ��ļ�ĩβ�Ի�ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��ȡ�ļ�����
						  //��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowRecord)];//������ȡһ����¼�Ļ�����
	BorrowRecord borrowRecord;
	int bId; //���������ȡ��BookId
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowRecord));//������¼
		borrowRecord = *((BorrowRecord*)buffer);
		bId = borrowRecord.bookId;
		if (bId  == bookId)
			borrowRecordList.push_back(borrowRecord);//ƥ�������list
	}
	delete[](buffer);
	fs.close();
	return	borrowRecordList;
}


//�ӵڼ�����¼���ѯ������ͼ���¼������
//amount = -1�����ش�start��ʼ������ͼ���¼
list<BorrowRecord> getRecords(int start, int amount) {
	list<BorrowRecord> BorrowRecordlist;
	if (amount <= 0 && amount != -1) return BorrowRecordlist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowRecord.bat", ios::out | ios::binary | ios::in | ios::ate);
	//��һ���Ѵ��ڵ��ļ���,�����ļ�ָ��ָ�����

	if (!fs) {
		//cout << "In function getBorrowRecordById ..." << endl;
		cout << " Error in open file BorrowRecord.bat. " << endl;
		return BorrowRecordlist;
	}

	/*ͨ��ͼ���id���������ļ�ָ��ƫ����
	�������õ���ƫ���������ļ��ֽڳ��Ȼ���С��0��ֱ�ӷ��ؿ�list
	*/
	long pos = sizeof(BorrowRecord) * (start - 1);
	if (pos < 0 || pos > fs.tellg()) {
		fs.close();
		return BorrowRecordlist;
	}
	fs.seekg(0, ios::end);
	streamoff fileLen = fs.tellg();
	streamoff endPos;

	if (amount == -1) endPos = fileLen;
	else endPos = pos + sizeof(BorrowRecord) *  amount;
	endPos = (endPos > fileLen) ? fileLen : endPos;

	fs.seekg(pos, ios::beg);
	char* buffer = new char[sizeof(BorrowRecord)];

	while (fs.tellg() < endPos) {
		fs.read(buffer, sizeof(BorrowRecord));//������¼-
		BorrowRecord borrowRecord = *((BorrowRecord*)buffer);

			BorrowRecordlist.push_back(borrowRecord);//����¼��ӵ�listĩβ
	}
	fs.close();
	delete[] buffer;
	return BorrowRecordlist;
}
/**
* ���Ľ�����еĽ����¼
* ������蹦�ܵ�ʱ����õ�
* @param borrowRecord
* @return
*/
bool modifyRecord(BorrowRecord& borrowRecord) {
	//���ļ�borrowRecord.batʱ��֤�ļ����ݲ���ɾ��
	fstream fs("borrowRecord.bat", ios::out | ios::in | ios::ate | ios::binary);
	//�жϴ��ļ�borrowRecord.bat�Ƿ�ɹ������޷��������������Ϣ������false
	if (!fs) {
		cout << "Error: Can not open file 'borrowRecord.bat'!" << endl;
		fs.close();
		return false;
	}
	//ͨ��id�����ļ�ָ��ƫ�����Զ�ȡָ������
	long pos = sizeof(BorrowRecord) * (borrowRecord.id - 1);
	//�жϲ��ҵ�λ���Ƿ���ȷ,��С��0�򳬳��ļ����������������Ϣ������false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input BorrowRecord ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//��ȡָ��λ�õ�����
	BorrowRecord* rBorrowRecord;
	char* buffer = new char[sizeof(BorrowRecord)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(BorrowRecord));
	rBorrowRecord = (BorrowRecord*)buffer;
	//�Ƚ��ļ��ڲ��ҵ���rBorrowRecord.id������Ҫ�޸ĵ�borrowRecord.id�Ƿ���ͬ����ͬ������ļ������޸ģ�����ͬ�����������Ϣ������false
	if (rBorrowRecord->id == borrowRecord.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&borrowRecord, sizeof(BorrowRecord));
		//cout << "Modify BorrowRecord success!" << endl;
		fs.close();
		delete[] buffer;
		return true;
	}
	else {
		cout << "Error: Modify BorrowRecord ID mismatch!" << endl;
		fs.close();
		delete[] buffer;
		return false;
	}
	
}



/*
ͨ����¼��id�Ų�ѯ�õ���¼��Ϣ*/
list<BorrowRecord> getRecordById(int id) {
	list<BorrowRecord> borrowRecordList;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("borrowRecord.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		cout << " Error in open file borrowRecord.bat " << endl;
		return borrowRecordList;
	}
	//��ָ���Ƶ��ļ�ĩβ�Ի�ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��ȡ�ļ�����
						  //��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowRecord)];//������ȡһ����¼�Ļ�����
	BorrowRecord borrowRecord;
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowRecord));//������¼
		borrowRecord = *((BorrowRecord*)buffer);
		if (borrowRecord.id == id){
			borrowRecordList.push_back(borrowRecord);//ƥ�������list
			break;
		}
	}
	delete[](buffer);
	fs.close();
	return borrowRecordList;

}





//�ú����Ĺ����ǣ�����һ��time_t�ͱ���
//���ʾ����time+day���ʱ��
//day�Ǵ���0ʱ��������time֮���ʱ��
//С��0������time֮ǰ��ʱ��
//����ú�����ֱ�ӷ���time
time_t addDayToTime(time_t time, int day) {
	if (day == 0) return time;
	else {
		//�Ƚ�time_t�ͱ���ת��Ϊtm�ṹ��������������ڼ�day��
		tm t;
		int err = localtime_s(&t, &time);
		if (err) return time; //���ת������ֱ�ӷ���time
		t.tm_mday += day;

		//Ȼ���ٽ�����ṹ��ת����time_t���������ؾͿ�����
		return mktime(&t);
	}

}


//����������һ�����ڼ�¼�ĺ���(���ڲ���),overDay�����õ���������,�������Ҫ����0
//���С��0��ȡ�����ֵ
void addExtendRecord(int readerId, int bookId,int overdueDay) {

	//�������id���鼮id������һ�����Ϸ����ú�����ֱ�ӷ���
	list<Book> book = getBookById(bookId);
	if (book.empty()) {
		cout << "��ǰ�鼮�����ڣ��޷��������ڼ�¼�������˳���" << endl;
		return; }
	list<Book>::iterator it1 = book.begin();
	if ((*it1).numberInLib <= 1) {
		cout << "��ǰ�鼮��������㣬�����������ڼ�¼�������˳�!" << endl;
		return;
	}
	//�����ǰ�鼮������С��1�����ܽ�ñ���

	//�����ǰ���߲����ڣ�ֱ�ӷ���
	list<Reader> reader = getReaderById(readerId);
	if (reader.empty()) { 
		cout << "��ǰ���߲����ڣ��޷��������ڼ�¼�������˳���" << endl;
		return; 
	}

	//�����ǰ���߽����ĸ�����������������Ͳ�������һ�����ڼ�¼
	list<BorrowRecord> r = getRecordsByReaderId(readerId);
	if (r.size() >= maxBorrowNum)
	{
		cout << "��ǰ���߽���鼮�����ﵽ�����������������ܼ����������ڼ�¼�������˳���" << endl;
		return;
	}


	//���൱���� ����һ�����ڼ�¼���ٽ���Ӧ�鼮�Ĺݲ�������1

	BorrowRecord record;
	record.bookId = bookId;
	time_t now = time(NULL);

	int day = overdueDay >= 0 ? -overdueDay : overdueDay;

	time_t RationalTime = addDayToTime(now, day);
	time_t startTime = addDayToTime(RationalTime, -maxBorrowDay);
	record.startTime = startTime;
	record.rationalTime = RationalTime;
	setRecordBookId(record, bookId, startTime);
	record.readerId = readerId;

	addRecord(record);
	
	list<Book>::iterator it = book.begin();
	Book b = (*it);
	b.numberInLib--;

	modifyBook(b);

	cout << "���ڼ�¼�ѳɹ����ɣ�չʾ���£�" << endl;

	list<BorrowRecord> re = getRecordById(record.id);
	showBorRecordInfo(re,true);

	cout << "�����˳���" << endl;
	return;

}



/*
int main() {
	
	/*
	BorrowRecord br;
	br.readerId = 1;
	br.startTime = time(NULL);
	br.rationalTime = time(NULL);
	setRecordBookId(br, 1, br.startTime);
	addRecord(br);
	*/

	/*
	list<BorrowRecord> records;
	records = getRecordById(1);
	showBorRecordInfo(records,true);

	if (deleteRecord(1)) cout << "delete success!" << endl;
	
	list<BorrowRecord> record;
	record = getRecordById(1);
	showBorRecordInfo(record, true);
	*/
/*
	addExtendRecord(1, 2,21);

	int i;
	cin >> i;
	
	cout << endl;


	
	
	
	
	return 1;

}*/

/*
int main() {

	//BorrowBookServlet(1);
	
	
	while (1) {
		int i; 
		cout << "id:";
		cin >> i;

		list<BorrowRecord> records = getAllRecords();
		showBorRecordInfo(records, 1);

		cout << endl << "ɾ����" << endl;
		deleteRecord(i);
		records.clear();
		records = getAllRecords();
		showBorRecordInfo(records, 1);

	}
	

	int i;
	cin >> i;
	return 1;
}*/