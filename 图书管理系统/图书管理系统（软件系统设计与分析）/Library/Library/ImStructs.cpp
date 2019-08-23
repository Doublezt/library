#include"stdafx.h"
#include"Structs.h"
#include<sstream>
#include<string>


//Admin
/************************************************************************/
bool setAdminPd(Admin& admin,string pd) {
	return copy(admin.password, pd, sizeof(admin.password));
}


//Author

/************************************************************************/
bool setAuthorName(Author& author, string name) {
	return copy(author.name, name, sizeof(author.name));
}



//Type
/************************************************************************/

bool setTypeName(Type& type, string name) {
	return copy(type.name, name, sizeof(type.name));
}




//Book
/************************************************************************/
/*��name�ֶ�����ֵ
���name ���ȹ������������������ã�ֱ�ӷ���false
*/
bool setBookName(Book& book, string name) {
	return copy(book.name, name, sizeof(book.name));
}

/*����������id��ɵ��������飬���au��������������false
len ��au����ĳ���*/
bool setBookAuthors(Book& book, int* au,unsigned len) {
	return copy(book.author, au, sizeof(book.author) / sizeof(int), len);
}

bool setBookPublisher(Book& book, string pub) {
	return copy(book.publisher, pub, sizeof(book.publisher));
}

/*ͬauthor����ĸ���*/
bool setBookTypes(Book& book, int* type, unsigned len) {
	return copy(book.type, type, sizeof(book.type) / sizeof(int), len);
}



/*���ڲ�ȥ�ж�ISBN�����Ƿ���ϸ�ʽ�ˣ�ֻҪISBN������13���ַ��Ϳ���*/
bool setBookISBN(Book& book, string ISBN) {
	return copy(book.ISBN, ISBN, sizeof(book.ISBN));
}



//Reader
/************************************************************************/
bool setReaderName(Reader& reader, string name) {
	return copy(reader.name, name, sizeof(reader.name));
}

bool setReaderPw(Reader& reader, string pw) {
	return copy(reader.password, pw, sizeof(reader.password));
}


//BorrowRecord
/************************************************************************/
bool increaseRationalTimeByConst(BorrowRecord& record) {

	//double difftime(time_t end, time_t beginning); ������������֮�������
	double seconds = difftime(record.rationalTime, record.startTime);
	//������������֮�������
	int day = seconds / (24 * 3600) + 1;

	//��������������maxRenewTime (����������)������false
	if (day >= maxBorrowDay * maxRenewTime)
		return false;

	//����ͼ�����黹ʱ������maxBorrowDay��
	tm time;
	int err = localtime_s(&time, &(record.rationalTime));
	if (err) return false; //���ת������ֱ�ӷ���false
	time.tm_mday += maxBorrowDay;

	//Ȼ���ٽ���tm�ṹ��ת����time_t���ͼ���

	record.rationalTime = mktime(&time);
	return true;
}

/*��һ�� time_t ���͵�ʱ��ת���� YYYY-MM-DD HH:MM ��ʽ���ַ���
��һ���ַ���������Ե����ַ�����data����
*/
string getDateStr(time_t& t) {
	/*�������֣�ʹ��gtime_s(&tm,&time_t) ��time_tת����tm�õ�����0ʱ����ʱ��
	������localtime�õ��Ĳ��Ǳ���ʱ��*/
	tm time;
	int err = localtime_s(&time, &t);
	if (err) return "";//���ת����������һ�����ַ���
					   //ת���ɹ����򽫽ṹ��time�е���Ϣƴ�ӳ�һ���ַ���

					   /*size_t strftime (char* ptr, size_t maxsize, const char* format,
					   const struct tm* timeptr ); �ú����������ǣ���timeptr��ָ�ṹ����
					   ʱ�����Ϣ����format��ʽ�ַ�����֯���������Ƶ�ptr��ַ��ȥ
					   ��ิ��maxsize���ַ�������ֵ�����Ƶ�ptr�е��ַ�����
					   */
					   //%F	Short YYYY-MM-DD date, equivalent to %Y-%m-%d
					   //%R	24-hour HH:MM time, equivalent to %H:%M

	char str[30];
	int len = strftime(str, 30, "%F %R", &time);
	if (len == 0) return "";
	else return str;
}



/*�������������bookKindId��ĳ��ʱ��(һ���ǵ�ǰʱ��)Ϊ�����ߵ��Ȿ������һ��Ψһ��id
(bookKindId������Ӧ���Ѿ�������⣬��һ�����id��)
�ú�����ֱ�ӽ����Ψһ��id��ֵ��b�� bookOnlyId�ֶ�
���һὫbookKindId��ֵ��bookId�ֶ�
*/
bool setRecordBookId(BorrowRecord& b, int bookKindId, time_t& t) {
	string temp;
	stringstream ss;
	ss << bookKindId;
	ss >> temp;
	int n = temp.length();
	int j = 0;
	/*һ�����Ψһ���ǰ4λ�����������id*/
	for (int i = 0; i < 4; i++) {
		if (i < 4 - n) b.bookOnlyId[i] = '0';
		else b.bookOnlyId[i] = temp[j++];
	}
	/*��12λ��ʱ��t*/
	tm time;
	int err = localtime_s(&time, &t);
	if (err) false;
	/*�����ǣ�������ʱ����*/
	char temp2[13];
	int len = strftime(temp2,13, "%C%m%d%H%M%S", &time);
	if (len == 0) return false;
	for (int i = 4; i < 17; i++)
		b.bookOnlyId[i] = temp2[i];

	b.bookId = bookKindId;
	return true;

}


/*
int main() {
	
	

	BorrowRecord record;
	record.id = 1;
	record.bookId = 1;
	record.startTime = time(NULL);
	record.rationalTime = time(NULL);
	setRecordBookId(record, 1, record.startTime);
	cout << getDateStr(record.startTime).data()<<endl;
	cout << getDateStr(record.rationalTime).data() << endl;

	int j;
	cin >> j;
	return 1;

}*/
