#include"stdafx.h"

#include"showInfo.h"
#include"Operation.h"
#include<iomanip>
#define MaxAuthorNumPerBook 10
#define MaxTypeNumPerBook 10



//����鼮��Ϣ
void showBooksInfo(list<Book> books) {
	if (books.empty())
		return;
	for (list<Book>::iterator it = books.begin(); it != books.end(); ++it) {
		cout << "Id:" << (*it).id << endl;
		cout << "ISBN: " << (*it).ISBN << endl;
		cout << "�鼮����" << (*it).name << endl;
		cout << "�����磺" << (*it).publisher << endl;
		cout << "���ߣ�";
		list<Author> aus;

		for (int i = 0; i < MaxAuthorNumPerBook; i++) {
			int id = (*it).author[i];
			if (id == 0) break;
			else {
				list<Author> a = getAuthorById(id);
				if (!a.empty()) {
					list<Author>::iterator ait = a.begin();
					aus.push_back(*ait);
				}
			}
		}

		//չʾ��ǰͼ�������������ɵ��ַ���
		showAuthorInfo(aus, false);

		cout << endl <<"ͼ���������";
		list<Type> types;
		for (int i = 0; i < MaxTypeNumPerBook; i++) {
			int id = (*it).type[i];
			if (id == 0) break;
			else {
				list<Type> t = getTypeById(id);
				if (!t.empty()) {
					list<Type>::iterator t_it = t.begin();
					types.push_back(*t_it);
				}
			}
		}

		if (types.empty()) cout << "��ͼ�鲻�����κ����" << endl;
		else showTypeInfo(types, false);
		cout << endl;

		cout << "��������" << (*it).amount << endl;
		cout << "�ݲ�������" << (*it).numberInLib << endl;
		cout << "**********************************************************" << endl;
	}
}

//���������Ϣ(���������ߵ�¼����)
void showReaderInfo(list<Reader> readers) {
	if (readers.empty())
		return;

	for (list<Reader>::iterator it = readers.begin(); it != readers.end(); it++) {
		cout << "����Id:" << (*it).id << endl;
		cout << "������" << (*it).name << endl;
		cout << "�Ա�:";
		if ((*it).sex)
			cout << "��" << endl;
		else
			cout << "Ů" << endl;

		cout << fixed << showpoint;
		cout << setprecision(2);
		cout << " Ƿ���" << (*it).fine << endl;
		cout << "**********************************************" << endl;
	}
}

//���������ʷ
//ע�⣺�ڶ���������ʾ�Ƿ�Ҫչʾ����������ʷ�Ķ�����Ϣ(��������id�Ͷ�������)
//�����ߵ�¼ʱ������չʾ���Լ��Ľ�����ʷ����Ҫչʾ������Ϣ
//���ǵ�����Ա��ѯ���������ʷ��ʱ����Ҫչʾ������Ϣ
void showBorHistoryInfo(list<BorrowHistory> his, bool showReaderInfo) {
	if (his.empty())
		return;

	for (list<BorrowHistory>::iterator it = his.begin(); it != his.end(); it++) {
		cout << "������ʷId:" << (*it).id << endl;
		list<Book> books = getBookById((*it).bookId);
		list<Book>::iterator book = books.begin();
		cout << "�����鼮��id��" << (*it).bookId << endl;
		cout << "����ͼ������" << (*book).name << endl;

		if (showReaderInfo) {
			list<Reader> readers = getReaderById((*it).readerId);
			list<Reader>::iterator reader = readers.begin();
			cout << "����id :" << (*reader).id << endl;
			cout << "����������" << (*reader).name << endl;
		}

		cout << "������ʼʱ�䣺" << getDateStr((*it).borrowTime).data() << endl;
		cout << "����ʱ�䣺" << getDateStr((*it).returnTime).data() << endl;
		cout << "**********************************************" << endl;
	}


}


//������ļ�¼
//ע�⣺�ڶ���������ʾ�Ƿ�Ҫչʾ�������ļ�¼�Ķ�����Ϣ(��������id�Ͷ�������)
//�����ߵ�¼ʱ������չʾ���Լ��Ľ��ļ�¼����Ҫչʾ������Ϣ
//���ǵ�����Ա��ѯ������ļ�¼��ʱ����Ҫչʾ������Ϣ
void showBorRecordInfo(list<BorrowRecord> records, bool showReaderInfo) {
	if (records.empty())
		return;

	for (list<BorrowRecord>::iterator it = records.begin(); it != records.end(); it++) {
		cout << "���ļ�¼Id:" << (*it).id << endl;

		cout << "�鼮Id:" << (*it).bookOnlyId << endl;
		list<Book> books = getBookById((*it).bookId);

		list<Book>::iterator book = books.begin();
		cout << "����ͼ������" << (*book).name << endl;

		if (showReaderInfo) {
			list<Reader> readers = getReaderById((*it).readerId);
			list<Reader>::iterator reader = readers.begin();
			cout << "����id :" << (*reader).id << endl;
			cout << "����������" << (*reader).name << endl;
		}

		cout << "������ʼʱ�䣺" << getDateStr((*it).startTime).data() << endl;
		cout << "��ٻ���ʱ�䣺" << getDateStr((*it).rationalTime).data() << endl;
		cout << "**********************************************" << endl;
	}

}

//���������Ϣ
//���showIdΪtrue����չʾ����Id(��ʱÿ�����ߵļ�¼��Ϣ���û��з�����)
//�����ֻչʾ��������(ֻչʾ��������ʱ������Ҫ����������һ���еطֿ���ֻ�ÿո�������ɣ����������չʾһ����Ķ��������)
void showAuthorInfo(list<Author> aus, bool showId) {
	if (aus.empty()) return;
	string  c;
	if (showId)  c = "\n";//ÿ�����ߵļ�¼��Ϣ���û��з�����
	else c = "\t";//ֻչʾ��������ʱ������Ҫ����������һ���еطֿ���ֻ�ÿո��������
	for (list<Author>::iterator it = aus.begin(); it != aus.end(); it++) {
		if (showId)
			cout << "����Id :" << (*it).id << c.data();
		cout << (*it).name << c.data();
		if (showId)
			cout << "*****************" << endl;
	}
	return;
}




//��������Ϣ
//���showIdΪtrue����չʾ���Id(��ʱÿ�����ߵļ�¼��Ϣ���û��з�����)
//�����ֻչʾ�����(ֻչʾ��������ʱ������Ҫ����������һ���еطֿ���ֻ�ÿո�������ɣ����������չʾһ����Ķ�������)
void showTypeInfo(list<Type> types, bool showId) {
	if (types.empty()) return;
	string  c;
	if (showId)  c = "\n";//ÿ�����ļ�¼��Ϣ���û��з�����
	else c = "\t";//ֻչʾ�����ʱ������Ҫ����һ���еطֿ���ֻ�ÿո��������
	for (list<Type>::iterator it = types.begin(); it != types.end(); it++) {
		if (showId)
			cout << "���Id :" << (*it).id << c.data();
		cout << (*it).name << c.data();
		if (showId)
			cout << "*****************" << endl;
	}
	return;

}












