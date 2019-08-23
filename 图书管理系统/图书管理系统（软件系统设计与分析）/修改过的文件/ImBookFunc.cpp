#include"stdafx.h"
#include"BookFunc.h"
#include"Operation.h"
#include<fstream>
using namespace std;
/*�Ѻ�����������ͷ�ļ�������к�����Ҫ����
BooksFunction�����е�����һ��ʱ��ֻ��Ҫ
�����ͷ�ļ�include�����Ϳ�����*/


/*ͨ��ͼ��Ψһ��id�Ų�ѯ�Ȿ�����Ϣ������
�Ҳ����ͷ��ؿ�list*/
list<Book> getBookById(int id) {
	list<Book> booklist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app 
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("book.bat", ios::out | ios::binary|ios::in|ios::ate);
	//��һ���Ѵ��ڵ��ļ���,�����ļ�ָ��ָ�����

	if (!fs) {
		//cout << "In function getBookById ..." << endl;
		cout << " Error in open file book.bat. " << endl;
		return booklist;
	}
	
	/*ͨ��ͼ���id���������ļ�ָ��ƫ����
	�������õ���ƫ���������ļ��ֽڳ��Ȼ���С��0��ֱ�ӷ��ؿ�list
	*/
	long pos = sizeof(Book) * (id - 1);
	if (pos < 0 || pos > fs.tellg()) { 
		fs.close();
		return booklist;
	}

	fs.seekg(pos, ios::beg);
	char* buffer = new char[sizeof(Book)];
	fs.read(buffer, sizeof(Book));//������¼-
	Book book = *((Book*)buffer);

	if(book.exist == 1)//��������������������������������ֻ����û�б�ɾ�����鼮
	booklist.push_back(book);//����¼��ӵ�listĩβ
	fs.close();
	delete[] buffer;
	return booklist;

}

/**
* ����ISBN���ѯ�鼮
* exist����Ϊ1ʱֻ��δ��ɾ�������в���
* Ϊ0ʱ�����е����в���
* �Ҳ����ͷ��ؿ�list
* @param ISBN
* @return
*/
list<Book> getBookByISBN(string ISBN,int exist) {
	list<Book> booklist;
	//if (!isISBN(ISBN)) return booklist;//���ISBN��ʽ����ȷ��ֱ�ӷ��ؿ�list
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("book.bat", ios::out | ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���,�����ļ�ָ��ָ�����

	if (!fs) {
		//cout << "In function getBookByISDN ..." << endl;
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//��ȡ�ļ�����
	fs.seekg(0, ios::beg);
	string isbn = "";
	char* buffer = new char[sizeof(Book)];//������ȡһ����¼�Ļ�����
	Book book;
	/*��û�в��ҵ���Ӧ��ISBN���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len && isbn != ISBN) {
		fs.read(buffer, sizeof(Book));//������¼
		book = *((Book*)buffer);
		isbn = book.ISBN;
	}
	if (isbn == ISBN) {
		if (exist == 1) {//ֻ����δ��ɾ�����鼮
			if (book.exist == 0) return booklist;//���鵽���鼮�Ѿ���ɾ�������ؿ�list!!!!!!!!!
		}
		booklist.push_back(book);//�ҵ��ͽ���¼��ӵ�listĩβ
	}
	fs.close();
	delete[] buffer;
	return booklist;

}

/*ͨ�������ҵ����������������ͼ�鲢����
* ע����ҵõ������exist���Զ���ҪΪ1
���û���ҵ��򷵻ؿ�list
*/
list<Book> getBooksByType(int typeId,int exist) {
	list<Book> booklist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("book.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		//cout << "In function getBookByType ..." << endl;
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}
	//��ָ���Ƶ��ļ�ĩβ�Ի�ȡ�ļ�����
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��ȡ�ļ�����
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Book)];//������ȡһ����¼�Ļ�����
	Book book;
	/*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Book));//������¼
		book = *((Book*)buffer);
		if (book.exist != exist) continue;//�����ǰ�鼮�����ڣ�ֱ������һ����¼!!!!!!!
		for (int i = 0; i < (sizeof(book.type) / sizeof(int)); i++) {
			if (book.type[i] == typeId) {
				booklist.push_back(book);
				break;//����ǰ�鼮������һ�࣬�Ͱ�������booklist��Ȼ�����һ�м�¼
			}
		}
	}
	//ɾ��ָ�룬�����ڴ�
	delete[](buffer);
	fs.close();
	return booklist;
}

/*�������ߺ��ҵ��������д����������
�Ҳ����ͷ��ؿ�list*/
list<Book> getBooksByAuthor(int authorId) {
	list<Book> booklist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("book.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		//cout << "In function getBookByAuthor ..." << endl;
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//��ȡ�ļ�����
	//��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Book)];//������ȡһ����¼�Ļ�����
	Book book;
	/*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Book));//������¼
		book = *((Book*)buffer);
		if (book.exist == 0) continue;//�����ǰ�鼮�����ڣ�ֱ������һ����¼!!!!!!!!
		for (int i = 0; i < (sizeof(book.author) / sizeof(int)); i++) {
			if (book.author[i] == authorId) {
					booklist.push_back(book);
				break;//����ǰ�鼮������һ�࣬�Ͱ�������booklist��Ȼ�����һ�м�¼
			}
		}
	}
	fs.close();
	delete[] buffer;
	return booklist;
}

/*�ɳ�����������ҵ�������ͼ��
�����������ֲ���Ҳ��ģ����ѯ
�Ҳ����ͷ��ؿ�list*/
list<Book> getBooksByPublisher(string publisher) {
	list<Book> booklist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("book.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		//cout << "In function getBookByPublisher ..." << endl;
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//��ȡ�ļ�����
	//��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Book)];//������ȡһ����¼�Ļ�����
	Book book;
	string s = "";//������ŵ�ǰ�����ļ�¼��publisher�ֶ�
	/*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Book));//������¼
		book = *((Book*)buffer);
		if (book.exist == 0) continue;//�����ǰ�鼮�����ڣ�ֱ������һ����¼!!!!!!!!
		s = book.publisher;
		trimAllSpace(publisher);//��������ַ���ȥ�����пո�

		if (s.find(publisher) != string::npos)
			booklist.push_back(book);//ƥ�������list
	}
	fs.close();
	delete[] buffer;
	return booklist;

}

//������string ������Ϊ�˲�Խ������ַ�����
//�������������char*,�����޷�׼ȷ֪�����������ַ������ж೤

/*ͨ��ͼ������ѯͼ�� ����������ģ����ѯ(�������ַ���)
����Ĳ���name�����пո�
�Ҳ����ͷ��ؿ�list*/
list<Book> getBooksByName(string name) {
	list<Book> booklist;
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("book.bat", ios::binary | ios::in);
	//��һ���Ѵ��ڵ��ļ���

	if (!fs) {
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//��ȡ�ļ�����
							//��λ���ļ���ͷ
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Book)];//������ȡһ����¼�Ļ�����
	Book book;
	string s = "";//������ŵ�ǰ�����ļ�¼��name�ֶ�
				  /*���ļ���δ����ʱ�����������ļ�*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Book));//������¼
		book = *((Book*)buffer);
		if (book.exist == 0) continue;//�����ǰ�鼮�����ڣ�ֱ������һ����¼!!!!!!!!
		s = book.name;
		trimAllSpace(name);//��������ַ���ȥ�����пո�

		if (s.find(name) != string::npos)
			booklist.push_back(book);//ƥ�������list
	}
	fs.close();
	delete[] buffer;
	return booklist;

}


/**
* �����鼮��Ϣ
* �������Ѿ��޸Ĺ����鼮����Ϣ
* �ú���ͨ���鼮��id�ż������¼����λ��
* Ȼ���޸��鼮��Ϣ
* @param books
* @return
*/
bool modifyBook(Book& book) {
	//���ļ�book.batʱ��֤�ļ����ݲ���ɾ��
	fstream fs("book.bat", ios::out | ios::in | ios::ate | ios::binary);
	//�жϴ��ļ�book.bat�Ƿ�ɹ������޷��������������Ϣ������false
	if (!fs) {
		cout << "Error: Can not open file 'book.bat'!" << endl;
		fs.close();
		return false;
	}
	//ͨ��id�����ļ�ָ��ƫ�����Զ�ȡָ������
	long pos = sizeof(Book) * (book.id - 1);
	//�жϲ��ҵ�λ���Ƿ���ȷ,��С��0�򳬳��ļ����������������Ϣ������false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input Book ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//��ȡָ��λ�õ�����
	Book* rBook;
	char* buffer = new char[sizeof(Book)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(Book));
	rBook = (Book*)buffer;
	//�Ƚ��ļ��ڲ��ҵ���rBook.id������Ҫ�޸ĵ�Book.id�Ƿ���ͬ����ͬ������ļ������޸ģ�����ͬ�����������Ϣ������false
	if (rBook->id == book.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&book, sizeof(Book));
		fs.close();
		delete[] buffer;
		return true;
		//cout << "Modify Book success!" << endl;
	}
	else {
		cout << "Error: Modify Book ID mismatch!" << endl;
		fs.close();
		delete[] buffer;
		return false;
	}
	
}

/*ɾ��һ���鼮����ɾ�����޸�exist���Լ���)
������id�����ڣ���������false
�����ɾ���ɹ��󣬷���true
*/
bool deleteBook(int id) {
	list<Book> bookList = getBookById(id);
	if (bookList.empty()) return false;
	list<Book>::iterator it = bookList.begin();

	if ((*it).exist == 0) return true;
	(*it).exist = 0;
	return modifyBook(*it);
}

/**
* �����������鼮
* �ú���ֻ����һ���µ�book(һ������)�ӽ�ͼ��ݣ���
* ���Ȿ�����ݵļ�鹤������һ�����
* (��һ����Ҫ���Ҫ���ӵ��Ȿ���ISBN�Ƿ��Ѿ����ڼ�¼��
* ���Ҫ��ӵ��鼮��ISBN�Ѿ����ڣ����ù���Ա����Ҫ��ӵ���Ŀ
* Ȼ�����modify�����޸Ĺݲ�������������)
* ��Ҫ����Ȿ��ĸ�����Ϣ��ʽ�Ƿ���ȷ
* @param book
* @return
*/
bool addBook(Book& book) {
	fstream fs;
	fs.open("book.bat", ios::out |ios::in| ios::binary);
	//��׷�ӵ���ʽ��һ���Ѿ����ڵ��ļ����ж�д����(�ļ�ָ�����ļ�ĩβ)
	if (!fs) {
		cout << " Error in open file book.bat. " << endl;
		return false;
	}
	//���ڲ�ͬ������鼮��id�������ģ��տ�ʼ��Ҫ���ļ�ָ��ָ��
	//���һ����¼��Ȼ�������һ�����id,��1�͵õ������id
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Book))  newId = 1;//�����ļ���һ����¼Ҳû�е����
	else {//ע������  sizeof(Book) ���޷�����������ֱ�Ӷ���ӷ���
		int bookLen = sizeof(Book);
		fs.seekg(-bookLen, ios::end); //��λ�����һ����¼�Ŀ�ʼ��

		char* buffer = new char[sizeof(Book)];
		fs.read(buffer, sizeof(Book));//��ȡ���һ��ͼ���¼

		Book* lastBook = (Book*)buffer;//������������ǿ������ת��

		newId = (*lastBook).id + 1;//�õ�Ҫ���������id����ɸ�ֵ
		delete[] buffer;
	}
	book.id = newId;
	//Ȼ���ٽ��ļ�ָ�붨λ��ĩβ��дһ������ļ�¼
	fs.seekg(0, ios::end);
	fs.write((char*)&book, sizeof(book));
	//�ر��ļ���д��
	fs.close();
	return true;
}

/*
int main() {
	
	Book book;
	
	book.amount = 4;
	book.exist = 1;
	book.numberInLib = 4;
	setBookISBN(book, "9787302227984");
	setBookName(book,"c++�������");
	setBookPublisher(book, "�廪��ѧ������");
	int a[4] = { 1,2,3,4 };
	setBookAuthors(book, a, 4);
	setBookTypes(book, a, 4);

	cout << book.ISBN << endl;
	cout << book.name << endl;
	cout << book.author[0] << endl;
	
	//if (addBook(book)) {
		
	list<Book> booklist = getBookById(1);
		for (list<Book>::iterator it = booklist.begin(); it != booklist.end(); ++it) {
			cout << (*it).id << endl;
			cout << (*it).ISBN << endl;
			cout << (*it).name << endl;
			cout << (*it).author[0] << endl;
		}

		booklist.clear();
		booklist = getBookByISBN("9787302227984",1);
		for (list<Book>::iterator it = booklist.begin(); it != booklist.end(); ++it) {
			cout << (*it).id << endl;
			cout << (*it).ISBN << endl;
			cout << (*it).name << endl;
			cout << (*it).author[0] << endl;
			book = *it;
		}
		book.exist = 0;
		modifyBook(book);

		booklist.clear();
		booklist = getBookByISBN("9787302227984", 1);
		for (list<Book>::iterator it = booklist.begin(); it != booklist.end(); ++it) {
			cout << (*it).id << endl;
			cout << (*it).ISBN << endl;
			cout << (*it).name << endl;
			cout << (*it).author[0] << endl;
			book = *it;
		}

		
	//}
	
	
	list<Book> booklist = getBookById(1);
	for (list<Book>::iterator it = booklist.begin(); it != booklist.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).ISBN << endl;
		cout << (*it).name << endl;
		cout << (*it).author[0] << endl;
		book = *it;
	}
	
	setBookName(book, "����");
	modifyBook(book);
	list<Book> b = getBookById(1);
	for (list<Book>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).ISBN << endl;
		cout << (*it).name << endl;
		cout << (*it).author[0] << endl;
	}
	int i;
	std::cin >> i;
	return 0;
}*/
