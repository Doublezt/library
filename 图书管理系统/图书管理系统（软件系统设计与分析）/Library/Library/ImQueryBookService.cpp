#include "stdafx.h"
#include"Structs.h"
#include<list>
#include<string>
#include"BookFunc.h"
#include"AuthorFunc.h"
#include"TypeFunc.h"
#include"DealFault.h"
#include"showInfo.h"


void QueryBookById(list<Book> &bookList) {
	int id;

	for (;;) {
		cout << endl;
		cout << "����������ѯ�鼮��ID������0ȡ����ѯ��";
		id = GetIntFromCin();

		if (id == 0) {
			bookList.clear();
			return;
		}
		else {
			bookList = getBookById(id);
			if (bookList.empty())
				cout << "��Ǹ����ѯ��������鼮,����������" << endl;
			else
				break;
		}
	}
}

void QueryBookByName(list<Book> &bookList) {
	string name;

	for (;;) {
		cout << endl;
		cout << "����������ѯ�鼮�����ƣ�����0ȡ����ѯ��";
		getline(cin, name);

		if (name == "0") {
			bookList.clear();
			return;
		}
		else {
			bookList = getBooksByName(name);
			if (bookList.empty())
				cout << "��Ǹ����ѯ��������鼮,����������" << endl;
			else
				break;
		}
	}
}

void QueryBookByISBN(list<Book> &bookList) {
	string ISBN;

	for (;;) {
		cout << endl;
		cout << "����������ѯ�鼮��ISBN��(9λ��13λ)������0ȡ����ѯ��";
		getline(cin, ISBN);

		if (ISBN == "0") {
			bookList.clear();
			return;
		}
		else if (!IsISBN(ISBN))
			cout << "���������ʽ��������������" << endl;
		else {
			bookList = getBookByISBN(ISBN, 1);
			if (bookList.empty())
				cout << "��Ǹ����ѯ��������鼮,����������" << endl;
			else
				break;
		}
	}
}

void QueryBookByAuthor(list<Book> &bookList) {
	string authorName;
	Author author;
	list<Book> tempBookList;
	list<Author> authorList;

	for (;;) {
		cout << endl;
		cout << "����������ѯ�鼮�����ߵ����֣�����0ȡ����ѯ��";
		getline(cin, authorName);

		if (authorName == "0") {
			bookList.clear();
			return;
		}
		else {
			authorList = getAuthorByName(authorName);
			while (!authorList.empty()) {
				author = authorList.back();
				authorList.pop_back();
				//��tempBookList�ݴ���ҵ�������
				tempBookList = getBooksByAuthor(author.id);
				//�ϲ�����list����Ϣ
				bookList.splice(bookList.end(), tempBookList);
			}
			if (bookList.empty())
				cout << "��Ǹ����ѯ��������鼮,����������" << endl;
			else
				break;
		}
	}
}

void QueryBookByType(list<Book> &bookList) {
	int typeId;

	for (;;) {
		cout << endl;
		cout << "�ɲ�ѯ���鼮�������£�" << endl;
		showTypeInfo(getAllTypes(), true);

		cout << "����������ѯ�鼮�������ID������0ȡ����ѯ��";
		typeId = GetIntFromCin();

		if (typeId == 0) {
			bookList.clear();
			return;
		}
		else {
			bookList = getBooksByType(typeId, 1);
			if (bookList.empty())
				cout << "��Ǹ����ѯ��������鼮,����������" << endl;
			else
				break;
		}
	}
}

void QueryBookByPublisher(list<Book> &bookList) {
	string publisher;

	for (;;) {
		cout << endl;
		cout << "����������ѯ�鼮�ĳ����磬����0ȡ����ѯ��";
		getline(cin, publisher);

		if (publisher == "0") {
			bookList.clear();
			return;
		}
		else {
			bookList = getBooksByPublisher(publisher);
			if (bookList.empty())
				cout << "��Ǹ����ѯ��������鼮,����������" << endl;
			else
				break;
		}
	}
}


void QueryAllBook() {

	int select;
	while (1) {
		cout << "����Ҫ�鿴�����鼮���ǰ��շ�ҳ�鿴�鼮?" << endl;
		cout << "1.�鿴�����鼮" << endl;
		cout << "2.���շ�ҳ�鿴�鼮" << endl;
		cout << "������ѡ�";
		select = GetIntFromCin();
		switch (select)
		{
		case 1:break;
		case 2:break;
		default:
			cout << "ֻ������1��2��" << endl;
			continue;
		}
		break;
	}

	int i = 1;
	int start = 1;
	list<Book> booklist;
	switch (select)
	{
	case 1:
		booklist = getBooks(1);
		showBooksInfo(booklist);
		break;
	case 2:
		while (1) {
			booklist.clear();
			booklist = getBooks(start, 5);//ÿҳչʾ5����
			if (booklist.empty()) {
				cout << "�Ѿ������鼮ĩβҳ��" << endl;
				break;
			}

			cout << endl << endl <<  "��" << i <<"ҳ�鼮��Ϣ������ʾ��" << endl;
			showBooksInfo(booklist);
			start = start + 5;
			i++;
			while (1) {
				cout << endl << "���Ƿ�Ҫ�鿴�����鼮����������1����������0" << endl;

				cout << "������ѡ�";
				select = GetIntFromCin();
				switch (select)
				{
				case 1:break;
				case 2:break;
				default:
					cout << "ֻ������1��2��" << endl;
					continue;
				}
				break;
			}
			switch (select)
			{
			case 1:continue;//����չʾ�鼮��Ϣ
			case 2:break;
			}
			break;
		}
		break;
	}
	
}


//��������id��ISBN�����������ߣ���𣬳����磩��ѯ��
void QueryBookService() {
	list<Book> bookList;
	list<Author> authorList;
	list<Type> typeList;

	//ʵ�ֶ�β�ѯ
	for (int i = 0;;) {
		//ѡ���ѯ��ѡ��
		cout << endl;
		cout << "��ѯ�鼮����" << endl;
		cout << "1.���鼮ID�Ų����鼮" << endl;
		cout << "2.���鼮���Ʋ����鼮" << endl;
		cout << "3.���鼮ISBN�Ų����鼮" << endl;
		cout << "4.�����߲����鼮" << endl;
		cout << "5.����������鼮" << endl;
		cout << "6.������������鼮" << endl;
		cout << "7.��ʾ�����鼮" << endl;
		cout << "0.ȡ����������ҳ" << endl;
		cout << "��ѡ���ѯ�ķ�ʽ��" << endl;
		i = GetIntFromCin();

		//ʵ�ֹ��ܵ�ѡ��
		switch (i) {
		case 1:
			QueryBookById(bookList);
			break;
		case 2:
			QueryBookByName(bookList);
			break;
		case 3:
			QueryBookByISBN(bookList);
			break;
		case 4:
			QueryBookByAuthor(bookList);
			break;
		case 5:
			QueryBookByType(bookList);
			break;
		case 6:
			QueryBookByPublisher(bookList);
			break;
		case 7:
			QueryAllBook();
			break;
		case 0:
			return;
		default:
			cout << "����������������������" << endl;
		}

		if (!bookList.empty()) {
			cout << endl;
			cout << "����ѯ���鼮��Ϣ���£�" << endl;
			showBooksInfo(bookList);
		}

		for (;;) {
			cout << endl;
			cout << "������ѯ����ѯ������1���˳�������0��";
			int t = GetIntFromCin();
			if (t == 1)
				break;
			else if (t == 0)
				return;
			else
				cout << "����������������������" << endl;
		}

		//���list
		bookList.clear();
	}
}
