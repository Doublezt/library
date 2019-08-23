

#include "stdafx.h"
#include"Structs.h"
#include"BookFunc.h"
#include"showInfo.h"
#include"Operation.h"
#include"BorrowRecordFunc.h"
#include <array>
#include<string>
#include <unordered_set>
#include"DealFault.h"
#include"QueryBookService.h"
#define MaxTypeAmount 10//ÿ���������10�����
#define MaxAuthorAmount 10//ÿ��������¼ʮ����Ҫ����
using namespace std;





/*���һ���鼮��service*/
void AddBookService(){
	Book book;

	int out;//�����˳���ǰ�����鼮����
	//����������������鼮��ÿһ��֮��ѯ��һ���Ƿ�Ҫ�˳������鼮���ܣ�����
	//������Щ�鷳�����ֻ���ڸտ�ʼ��������ʱ���ѯ��һ���Ƿ�Ҫ�˳�(�п��������������)

	//ÿ���ͼ���ĳһ����Ϣ֮�󶼻�ѯ���Ƿ��˳�����鼮����
	while (1) {
		cout << "�����Խ������²�����" << endl;
		cout << "1.��ʼ���ͼ��" << endl;
		cout << "2.�˳������鼮����" << endl;
		cout << "������ѡ��1��2��";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "ֻ������1��2��" << endl;
			continue;
		}
		break;//case 1�����
	}

	//���Ȼ�ȡ����ͼ���ISBN���
	string isbn;
	while (1) {
		cout << endl << "����������ͼ���ISBN���:" << endl;
		getline(cin, isbn);
		trimFLSpace(isbn);//ȥ����β�ո�

		//��������ISBN����Ƿ�����ISBNУ�鷽ʽ
		bool  isISBN = IsISBN(isbn);

		//���������ISBN��ʽҪ��ѯ��Ҫ��������ISBN��Ż����˳������鼮
		if (!isISBN) {
			cout << endl << "�������ISBN��Ÿ�ʽ����!" << endl;
			while (1) {
				cout << endl << "����Ҫ��������ISBN���������1�Լ���������0�˳������鼮����:";
				out = GetIntFromCin();

				switch (out)
				{
				case 1:break;
				case 0:return;
				default:
					cout << endl << "ֻ������1��0��" << endl;
					continue;
				}
				break;//case 1�����
			}
			continue;
		}

		//�������У�鷽ʽ�����������鼮��ISBN
		setBookISBN(book, isbn);

		//�õ���ʽ��ȷ��ISBN��ź����û�ȷ��һ��ISBN
		int select;
		cout << endl << "����ȷ��ISBN:" << isbn.data() << endl;
		while (1) {
			cout << endl;
			cout << "1.ȷ��ISBN���" << endl;
			cout << "2.��������ISBN���" << endl;
			cout << endl << "������ѡ��1��2��";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
			case 2:break;
			default:
				cout << endl << "ֻ������1��2��" << endl;
				continue;
			}

			break;//1.ȷ�ϵ�ǰ��ISBN���
				// 2.��������ISBN���
		}
		switch (select)
		{
		case 1:break;//1.ȷ�ϵ�ǰ��ISBN��ţ���������ĺ���
		case 2:continue;//2.��������ISBN���
		}

		//�õ���ʽ��ȷ��ISBN�����ȷ�Ϻ�Ҫ���ݸñ�Ų�ѯ���鼮�Ƿ����
		//������ڣ���Ϊ���������
		//1.�鼮�����ұ���ɾ���ˣ�Ӧչʾͼ����Ϣ�����û�ȷ������Ƿ����Ҫ���ӵ�
		//�鼮������ǵĻ��������û������������������޸��鼮��Ϣ
		//2.�鼮������δ��ɾ������ʱ��ֹ���Ӹñ��鼮

		list<Book> b = getBookByISBN(isbn, 0);
		if (!b.empty()) {
			list<Book>::iterator it = b.begin();
			if ((*it).exist == 0) {//���1
				cout << endl << "��Ҫ��ӵ��鼮��Ϣ�Ѿ������ڹ��У�������ʾ:" << endl;
				showBooksInfo(b);

				while (1) {
					cout << endl << "������Ҫ��ӵ��鼮��Ϣ��" << endl;
					cout << "1.�ǵ�" << endl;
					cout << "2.���ǡ�(ͨ��ѡ��2��������������ISBN���)" << endl;
					cout << "������ѡ��1��2��" << endl;
					select = GetIntFromCin();

					int amount;
					switch (select) {
					case 1:
						cout << endl << "��������鼮����Ŀ��" << endl;
						amount = GetIntFromCin();
						//������鼮��������С�ڵ���0(�������û�����һ���������ֵ��ַ���Ҳ�ᵼ��amount < 0)
						while (amount <= 0) {
							cout << "����������ݸ�ʽ�������������룡" << endl;
							cout << endl << "��������鼮����Ŀ��";
							amount = GetIntFromCin();
						}
						//����������������ԭ�ȼ�ɾ�������鼮��Ϣ��д
						(*it).amount = amount;
						(*it).numberInLib = amount;
						(*it).exist = 1;
						modifyBook(*it);
						cout << "�����鼮�ɹ�!�鼮��Ϣ������ʾ��" << endl;
						showBooksInfo(getBookByISBN(isbn, 1));
						return;
					case 2:
						break;
					default:
						cout << endl << "ֻ������1��2��" << endl;
						continue;
					}
					break;
				}
			}
			else {//�����ISBN��ŵ��鼮�Ѿ������Ҹ�ͼ��δ��ɾ�������ֹ���Ӹñ��鼮
				cout << endl << "��ISBN��ŵ��鼮�Ѵ��ڣ�" << endl;
				continue;
			}
		}
		else break;//�����ISBN��������ͼ����У���������鼮
	}


	//ÿ���ͼ���ĳһ����Ϣ֮�󶼻�ѯ���Ƿ��˳�����鼮����
	while (1) {
		cout << "�����Խ������²�����" << endl;
		cout << endl;
		cout << "1.�������뵱ǰͼ����Ϣ" << endl;
		cout << "2.�˳������鼮����" << endl;
		cout << "������ѡ��1��2��";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "ֻ������1��2��" << endl;
			continue;
		}
		break;//case 1�����
	}


	//������Ҫ������������Ӧ�ñ�֤����������һ�пո�
	//�����п����пո�,����������β�����пո�
	string name;
	while (1) {
		cout << endl << "�����������鼮��������" << endl;
		getline(cin, name);
		trimFLSpace(name);

		if (!setBookName(book, name)) {
			cout << endl <<"��������������������!" << endl;
			continue;
		}
		else {
			if (name == "") {//��֤����������һ�пո�
				cout << endl << "��������Ϊ�գ����������룡" << endl;
			}
			else {
				
				//������Ҫ�ٴ�ȷ��
				int select;
				cout << endl << "�����ٴ�ȷ������:" << "<<" <<  name.data()  << ">>"<< endl;
				while (1) {
					cout << endl;
					cout << "1.ȷ������" << endl;
					cout << "2.������������" << endl;
					cout << endl << "������ѡ��1��2��";
					select = GetIntFromCin();
					switch (select)
					{
					case 1:
					case 2:break;
					default:
						cout << endl << "ֻ������1��2��" << endl;
						continue;
					}

					break;//1.ȷ��
						  // 2.��������
				}
				switch (select)
				{
				case 1:break;//1.ȷ�ϣ���������ĺ���
				case 2:continue;//2.��������
				}
				break;//ȷ������
			}
		}
	}

	//ÿ���ͼ���ĳһ����Ϣ֮�󶼻�ѯ���Ƿ��˳�����鼮����
	while (1) {
		cout << endl <<"�����Խ������²�����" << endl;
		cout << "1.�������뵱ǰͼ����Ϣ" << endl;
		cout << "2.�˳������鼮����" << endl;
		cout << "������ѡ��1��2��";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "ֻ������1��2��" << endl;
			continue;
		}
		break;//case 1�����
	}


	//������Ҫ�������������
	//Ӧ�ñ�֤��������������һ�пո�
	//���������п����пո񣬵�����β�Ŀո��ַ��ᱻ���е�
	string publisher;
	while (1) {

		cout << endl << "�����������鼮�ĳ���������" << endl;
		getline(cin, publisher);
		trimFLSpace(publisher);

		if (!setBookPublisher(book, publisher)) {
			cout << endl << "������������������������!" << endl;
			continue;
		}
		else {
			if (publisher == "") {//��֤����������һ�пո�
				cout << endl << "������������Ϊ�գ����������룡" << endl;
			}
			else {//����ȷ��һ���������
				cout << endl << "�����ٴ�ȷ�ϳ�������:" << publisher.data() << endl;

				//������Ҫ�ٴ�ȷ��
				int select;
				while (1) {
					cout << endl << "1.ȷ�ϳ�������" << endl;
					cout << "2.���������������" << endl;
					cout << endl << "������ѡ��1��2��";
					select = GetIntFromCin();
					switch (select)
					{
					case 1:
					case 2:break;
					default:
						cout << endl << "ֻ������1��2��" << endl;
						continue;
					}

					break;//1.ȷ��
						  // 2.��������
				}
				switch (select)
				{
				case 1:break;//1.ȷ�ϣ���������ĺ���
				case 2:continue;//2.��������
				}
				break;//ȷ��

			}
		}
	}

	//ÿ���ͼ���ĳһ����Ϣ֮�󶼻�ѯ���Ƿ��˳�����鼮����
	while (1) {
		cout << endl << "�����Խ������²�����" << endl;
		cout << "1.�������뵱ǰͼ����Ϣ" << endl;
		cout << "2.�˳������鼮����" << endl;
		cout << "������ѡ��1��2��";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "ֻ������1��2��" << endl;
			continue;
		}
		break;//case 1�����
	}

	//���������û�ѡ��ͼ�����������Ϊ��
	//��һ��set�������洢�û�������������id��Ϊ�˱�֤�������ظ���id
	unordered_set<int> typeIdSet;	

	//չʾ����������Ϣ�����û�����ñ��鼮�������id,һ���鼮��������10����ͬ�����
	//ÿ���û�����һ�����id(Ҫ��֤�����ÿ��id����ͬ)���������û�����ȷ��һ��������Ϣ�������ȷ�Ļ��͸��Ƹ�types�����е�Ԫ��
	//�ȵ��û����������id��չʾ���и�����������������û�ȷ��һ�Σ������ȷ�Ļ������types���Ե����

	list<Type> T = getAllTypes();
	cout << endl << "����������Ϣ������ʾ��" << endl;
	showTypeInfo(T, true);
	list<Type> curType;//�����洢��ǰ�鼮�������������
	//�����洢������id
	int maxTypeId = T.size();

	cout << endl << "��������Ϊһ����ѡ��" << MaxTypeAmount << "�����" << endl;
	while (1) {
		if (typeIdSet.size() >= MaxTypeAmount) {
			cout << endl << "�Ѿ�������" << MaxTypeAmount << "����𣬲��ܼ�����������!" << endl;
			break;
		}

		cout << endl << "������ñ��鼮��������id��(����������0����������������):";

		int id;
		id = GetIntFromCin();

		//����Ҫ��֤�����id���������id�ķ�Χ�ڶ������ݸ�ʽҪ��ȷ
		if (id < 0 || id > maxTypeId)
		{
			cout << endl << "����������id����" << endl;
			continue;
		}

		if (id == 0) break;//����0�Խ����������

		//��������id�����ظ������ᱻ�ظ���ӵ�������ȥ
		//Ӧ�����û�ȷ��һ�¸�������Ϣ�����ȷ����ȷ�Ž�id��ӵ�set��ȥ
		 //����û�����ˣ�ȡ����ǰ���id������
		list<Type> t = getTypeById(id);
		cout << endl << "����ȷ�������Ϣ:" << endl;
		showTypeInfo(t, true);

		int select;
		while (1) {
			cout << endl << "1.ȷ�����" << endl;
			cout << "2.��������һ�����" << endl;
			cout << endl << "������ѡ��1��2��";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
			case 2:break;
			default:
				cout << endl << "ֻ������1��2��" << endl;
				continue;
			}
			break;//1.ȷ��
				  // 2.��������
		}
		switch (select)
		{
		case 1:break;//1.ȷ�ϣ���������ĺ���
		case 2:continue;//2.��������
		}
		//ȷ������
		//����1����ȷ��������id
	
		pair<unordered_set<int>::iterator,bool> p = typeIdSet.insert(id);
		if (p.second) {
			list<Type>::iterator it = t.begin();
			curType.push_back(*it);
		}
	}

	T.clear();//�ͷſռ�
			  //�õ�����Щ���id��Ӧ�ö�book��types���Ը�ֵ��
	int types[MaxTypeAmount];

	int i = 0;
	for (int id : typeIdSet)
		types[i++] = id;
	
	setBookTypes(book, types, typeIdSet.size());
	typeIdSet.clear();//�ͷſռ�
					  //ÿ���ͼ���ĳһ����Ϣ֮�󶼻�ѯ���Ƿ��˳�����鼮����
	
	while (1) {
		cout << endl << "�����Խ������²�����" << endl;
		cout << "1.�������뵱ǰͼ����Ϣ" << endl;
		cout << "2.�˳������鼮����" << endl;
		cout << "������ѡ��1��2��";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "ֻ������1��2��" << endl;
			continue;
		}
		break;//case 1�����
	}


					  //���������û�������������
					  //��������ȱ�ݵġ���Ϊ����������ͬ�����ߣ��������Ϊ������ͬһ���ˡ�
					  //���û��������ɸ����������ü������洢��Щ������������֤ÿ��Ԫ��ֵ��Ψһ��
					  //������ͬ������������û�б�Ҫ���û�����
					  //Ĭ��ÿ��������������ͬ���������������пո�ᱻ�Զ��ü���
					  //һ����Ķ�����Ϣ����Ϊ�գ�������Ҫ��һ������
					  //�������п��Ժ��пո񣬵���������β�Ŀո�ᱻ����
	unordered_set<string> authorNames;

	cout << endl << "������ñ��鼮����Ҫ���ߡ�һ������������" << MaxAuthorAmount << "�����ߡ�" << endl;

	while (1) {

		if (authorNames.size() == MaxAuthorAmount)
		{
			cout << endl << "���Ѿ�������" << MaxAuthorAmount << "����Ҫ���ߣ����ܼ�������������!������һ����" << endl;
			break;
		}

		cout << endl << "������һ����������,��������������0������������������������:" << endl;
		cout << endl;
		string aName;
		getline(cin, aName);
		trimFLSpace(aName);//�ü��ո��ַ�

		//if (aName == "2") return;

		if (aName == "0") {
			if (authorNames.size() == 0) {//
				cout << endl << "��������Ҫ����һ��������Ϣ!" << endl;
				continue;
			}
			else //�û���Ҫ������������������ʱ
				  //�Ƿ������������Ӧ�ý�Set�����ÿգ���������������������
				break;//�˳������������룬�������߱������
		}

		
		Author a;
		//�ȱ�֤����������ȫ�ǿո��Ҳ����Թ���

		if (aName == "" || !setAuthorName(a, aName)) {
			//���aNameȫΪ�ո��ַ�����Ϊ�ջ��߹���(��������������ַ�����)
			//��ʾ��������һ����������
			cout << "��������������Ϊ�գ���ʽ����!" << endl;
			continue;
		}

		//��ʽ��ȷ�Ļ���ȷ��һ����������
		int select;
		cout << endl << "��ȷ������������" << aName.data() << endl;

		while (1) {
			cout << endl;
			cout << "1.ȷ������" << endl;
			cout << "2.������������" << endl;
			cout << endl << "������ѡ��1��2��";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
			case 2:break;
			default:
				cout << endl << "ֻ������1��2��" << endl;
				continue;
			}

			break;//1.ȷ��
				  // 2.��������
		}
		switch (select)
		{
		case 1:break;//1.ȷ�ϣ���������ĺ���
		case 2:continue;//2.��������
		}
		//��ȷ�ϳɹ�������������������뵽������ȥ
		authorNames.insert(aName);
	}

	//ÿ���ͼ���ĳһ����Ϣ֮�󶼻�ѯ���Ƿ��˳�����鼮����
	while (1) {
		cout << endl << "�����Խ������²�����" << endl;
		cout << "1.�������뵱ǰͼ����Ϣ" << endl;
		cout << "2.�˳������鼮����" << endl;
		cout << "������ѡ��1��2��";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "ֻ������1��2��" << endl;
			continue;
		}
		break;//case 1�����
	}

	//���������û�����ͼ������
	int amount;
	while (1) {
		cout << endl << "����������鼮��������";
		amount = GetIntFromCin();

		if (amount <= 0) {
			cout << endl << "�鼮���������ʽ����" << endl;
			continue;
		}
		else {

			int select;
			cout << endl << "�����ٴ�ȷ���鼮����:" << amount << endl;

			while (1) {
				cout << endl;
				cout << "1.ȷ��" << endl;
				cout << "2.ȡ�������������鼮����" << endl;
				cout << endl << "������ѡ��1��2��";
				select = GetIntFromCin();

				switch (select)
				{
				case 1:
				case 2:break;
				default:
					cout << endl <<"ֻ������1��2��" << endl;
					continue;
				}
				break;//1.ȷ��
					  // 2.��������
			}

			switch (select)
			{
			case 1:break;//1.ȷ�ϣ���������ĺ���
			case 2:continue;//2.��������
			}
			
			//����鼮�����ĸ�ֵ
			book.amount = amount;
			book.numberInLib = amount;
			break;
		}
	}

	cout << endl << "�鼮��Ϣ�Ѿ�������ϡ���ǰ������鼮��Ϣ������ʾ��" << endl;
	cout << endl;
	cout << "ISBN��ţ�" << isbn.data() << endl;
	cout << "������" << name.data() << endl;
	cout << "�����磺" << publisher.data() << endl;
	cout << "���";
	showTypeInfo(curType, false);
	cout <<endl << "���ߣ�";
	for (string s:authorNames) {
		cout << s.data() << "  ";
	}
	cout << endl << "������" << amount << endl;

	while (1) {
		cout << endl << "���Ƿ�ȷ��Ҫ����ñ��鼮��" << endl;
		cout << "1.ȷ������ñ��鼮��" << endl;
		cout << "2.ȡ�������˳������鼮���档" << endl;
		cout << "������ѡ��1��2��";

		out = GetIntFromCin();
		int index = 0;
		int authorId[MaxAuthorAmount];
		switch (out) {
		case 1:
			book.exist = 1;
			//�ȵ��û�ȷ��Ҫ��Ӹñ��鼮��Ż��������
			//�������������ߵ��������
			//���������������������������ļ��в�����һ�����߼�¼

			for (string s : authorNames) {
				list<Author> a = getAuthorByName(s, true);
				if (a.empty()) {//���������������������������ļ��в�����һ�����߼�¼
					Author au;
					setAuthorName(au, s);
					addAuthor(au);
					authorId[index++] = au.id;
				}
				else {
					list<Author>::iterator it = a.begin();
					authorId[index++] = (*it).id;
				}
			}

			//�������id����ĸ�ֵ
			setBookAuthors(book, authorId, authorNames.size());

			//����鼮�ɹ���չʾ�鼮��Ϣ���˳�����
			if (addBook(book)) {
				list<Book> bookList = getBookById(book.id);
				cout << endl << "�鼮��ӳɹ����鼮��Ϣ������ʾ��" << endl;
				showBooksInfo(bookList);
			}
			else {
				cout << "����AddBook����false,����鼮ʧ�ܣ�" << endl;
			}
		case 2: return;//����2�˳������鼮����
		default:
			cout << endl <<  "ֻ������1��2��" << endl;
			continue;
		}
	
	}
}


/*ɾ��һ���鼮���߼����鼮��service*/
void DeleteBookService() {

	//Ҫ������ɾ���鼮��id
	int bookId;
	
		//�������֮�����û�ѡ���Ƿ��˳�(�п�����ѡ�����Ž��뵱ǰ�����)
		
		cout << endl << "��������Ҫɾ��ͼ���id:" << endl;
		bookId = GetIntFromCin();
		if (bookId <= 0) {
			cout << endl << "�������ͼ��id��ʽ����ȷ��" << endl;
			return;//��������һ��ͼ��id
		}

		list<Book> book = getBookById(bookId);
		if (book.empty()) {
			cout << endl << "��������鼮id�����ڣ�" << endl;
			return;
		}

		//����鼮���ڣ����Ƚ��Ȿ�����Ϣ������û�
		cout << endl << "��Ҫɾ�����鼮��Ϣ������ʾ��" << endl;
		showBooksInfo(book);

		
		cout << "�����Խ������²�����" << endl;
		cout << endl << "1.ɾ�������鼮.(�����鼮����Ϣ�ᱻ���)" << endl;
		cout << "2.���ٸ����鼮������." << endl;
		cout << "3.�˳�ɾ���鼮����." << endl;

		cout << endl << "������ѡ��:";
		string select;
		while (1) {
			getline(cin, select);
			trimAllSpace(select);
			if (select == "1" || select == "2" || select == "3")
				break;
			else {
				cout << endl << "��ֻ������1,2,3�����������룺" << endl;
				cout << endl << "������ѡ��:";
			}
		}

		//����������3����֧��1.ɾ�������鼮��2.���ٸ����鼮��������3.�˳�ɾ���鼮����

		list<Book>::iterator b = book.begin();
		if (select == "1") {//����ɾ��һ���鼮�ķ�֧
			if ((*b).numberInLib != (*b).amount) {//���Ҫɾ�����鼮���ڽ�ģ���ֹɾ��
				cout << endl << "�����鼮���ڽ������������ɾ����" << endl;
				return;//��������һ���鼮id
			}
			else {//�������ɾ���������û���ȷ��һ�º���ȥ�޸�ͼ����Ϣ
				string select2;
				while (1) {
					cout << endl << "��ȷ��Ҫɾ�������鼮��ȷ��������1��ȡ��������0��" << endl;
					getline(cin, select2);
					trimAllSpace(select2);
					if (select2 == "1" || select2 == "0")
						break;
					else
						cout << endl << "��ֻ������1��0�����������룺" << endl;
				}
				if (select2 == "0") return;//��������һ��ͼ��id
											
				//����1����ȷ��ɾ���鼮
				(*b).exist = 0;
				(*b).amount = 0;
				(*b).numberInLib = 0;
				if (modifyBook(*b)) {//����޸ĳɹ��������ʾ��Ϣ
					cout << endl << "�鼮ɾ���ɹ���" << endl;
					return;
				}
				else {//������ĳ��ԭ���޸�ʧ�ܣ������ʾ��Ϣ���˳�ɾ���鼮����(���ڵ���)
					cout << endl << "�鼮ɾ��ʧ�ܣ�" << endl;
					return;
				}

			}


		}
		else if (select == "2") {//2.���ٸ����鼮������

			int deleteNum;
			
			while (1) {
				//�õ���ʽ��ȷ���鼮ɾ������
				cout << endl << "������Ҫ���ٵĸ����鼮��������" << endl;
				deleteNum = GetIntFromCin();

				if (deleteNum <= 0) {
					cout << endl << "�������������ʽ��Ч��" << endl;
					continue;
				}
				else if (deleteNum >= (*b).numberInLib) {//Ҫ��֤������һ��������
					cout << endl << "��ɾ�������鼮���������ܴ�����ݲ�����!" << endl;
					continue;
				}
				else {
					//���û�ȷ��һ��ɾ���鼮������
					string confirm;
					cout << endl << "��ȷ��Ҫɾ��" << deleteNum << "�������鼮��" << endl;
					cout << "1.ȷ��ɾ��" << endl;
					cout << "2.ȡ��ɾ��" << endl;
					while (1) {
						cout << endl << "����������ѡ�" << endl;
						getline(cin, confirm);
						trimAllSpace(confirm);
						if (confirm == "1" || confirm == "2")
							break;
						else
							cout << endl << "��ֻ������1,2��" << endl;
					}
					if (confirm == "2") return;
					else {
						(*b).amount -= deleteNum;
						(*b).numberInLib -= deleteNum;
						if (modifyBook(*b)) {
							cout << "ɾ���鼮�ɹ���" << endl;
							return;
						}
						else {
							cout << "ɾ���鼮ʧ�ܣ�" << endl;
							return;
						}

					}

				}
			}
			
				
			}
		//��ǰ������鼮id�����û���Ҫɾ�����鼮idʱ��Ӧ�ü�����һ���鼮id������
		else return;

	

}


bool ModifyBookName(Book &book) {
	string name;

	cout << endl;
	cout << "��������Ҫ�޸ĵ�����������0ȡ���޸ģ�";
	getline(cin, name);

	if (name == "0")
		return false;
	else
		copy(book.name, name, sizeof(Book::name));
	return true;
}

bool ModifyBookISBN(Book &book) {
	string ISBN;

	for (;;) {
		cout << endl;
		cout << "�������޸ĵ�ISBN�ţ�9λ��13λ��������0ȡ���޸ģ�";
		getline(cin, ISBN);

		if (ISBN == "0")
			return false;
		else
			if (IsISBN(ISBN)) {
				copy(book.ISBN, ISBN, sizeof(Book::ISBN));
				return true;
			}
			else
				cout << "���������ʽ��������������" << endl;
	}
}

bool ModifyBookAuthor(Book &book) {

	cout << endl << "�������޸ĺ�ǰ�鼮��ȫ�����ߣ�" << endl;
	//���������û�������������
	//��������ȱ�ݵġ���Ϊ����������ͬ�����ߣ��������Ϊ������ͬһ���ˡ�
	//���û��������ɸ����������ü������洢��Щ������������֤ÿ��Ԫ��ֵ��Ψһ��
	//������ͬ������������û�б�Ҫ���û�����
	//Ĭ��ÿ��������������ͬ���������������пո�ᱻ�Զ��ü���
	//һ����Ķ�����Ϣ����Ϊ�գ�������Ҫ��һ������
	//�������п��Ժ��пո񣬵���������β�Ŀո�ᱻ����
	unordered_set<string> authorNames;

	cout << endl << "������ñ��鼮����Ҫ���ߡ�һ������������" << MaxAuthorAmount << "�����ߡ�" << endl;

	while (1) {

		if (authorNames.size() == MaxAuthorAmount)
		{
			cout << endl << "���Ѿ�������" << MaxAuthorAmount << "����Ҫ���ߣ����ܼ�������������!������һ����" << endl;
			break;
		}

		cout << endl << "������һ����������,��������������0������������������������:" << endl;
		cout << endl;
		string aName;
		getline(cin, aName);
		trimFLSpace(aName);//�ü��ո��ַ�

						   //if (aName == "2") return;

		if (aName == "0") {
			if (authorNames.size() == 0) {//
				cout << endl << "��������Ҫ����һ��������Ϣ!" << endl;

				while (1) {
					cout << "���Ƿ�Ҫ�˳��޸ĵ�ǰͼ�����߹��ܣ���������1����������0: " << endl;
					int select;
					select = GetIntFromCin();
					switch (select) {
					case 1:return false;
					case 0:break;
					default:cout << endl << "ֻ������0��1��" << endl;
						continue;
					}
					break;
				}
				continue;
			}
			else //�û���Ҫ������������������ʱ
				 //�Ƿ������������Ӧ�ý�Set�����ÿգ���������������������
				break;//�˳������������룬�������߱������
		}


		Author a;
		//�ȱ�֤����������ȫ�ǿո��Ҳ����Թ���

		if (aName == "" || !setAuthorName(a, aName)) {
			//���aNameȫΪ�ո��ַ�����Ϊ�ջ��߹���(��������������ַ�����)
			//��ʾ��������һ����������
			cout << "��������������Ϊ�գ���ʽ����!" << endl;
			continue;
		}

		//��ʽ��ȷ�Ļ���ȷ��һ����������
		int select;
		cout << endl << "��ȷ������������" << aName.data() << endl;

		while (1) {
			cout << endl;
			cout << "1.ȷ������" << endl;
			cout << "2.������������" << endl;
			cout << endl << "������ѡ��1��2��";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
			case 2:break;
			default:
				cout << endl << "ֻ������1��2��" << endl;
				continue;
			}

			break;//1.ȷ��
				  // 2.��������
		}
		switch (select)
		{
		case 1:break;//1.ȷ�ϣ���������ĺ���
		case 2:continue;//2.��������
		}
		//��ȷ�ϳɹ�������������������뵽������ȥ
		authorNames.insert(aName);
	}

	int index = 0;
	int authorId[MaxAuthorAmount];

	for (string s : authorNames) {
		list<Author> a = getAuthorByName(s, true);
		if (a.empty()) {//���������������������������ļ��в�����һ�����߼�¼
			Author au;
			setAuthorName(au, s);
			addAuthor(au);
			authorId[index++] = au.id;
		}
		else {
			list<Author>::iterator it = a.begin();
			authorId[index++] = (*it).id;
		}
	}

	//�������id����ĸ�ֵ
	setBookAuthors(book, authorId, authorNames.size());
	return true;


	/*
	string authorName[10];
	string tempAuthorName[10];
	list<Author> authorList;

	//��Ϊ���߿����ж�������������洢����id������temp�洢����ʵ��ȡ���޸�
	cout << endl;
	cout << "�������鼮���ߵ����������10��" << endl;
	cout << "����0����������-1��������,����-2ȡ���޸ģ�" << endl;
	for (int i = 0; i < 10; i++) {
		for (;;) {
			cout << i + 1 << ".";
			getline(cin, authorName[i]);

			getAuthorByName(authorName[i], t)

			//ȡ���޸�ֱ���˳�����������book��author�����κ��޸�
			if (authorName[i] == -2)
				return false;
			//֮ǰ���������󣬿�����-1ѡ���������룬ʹfor����ѭ��
			else if (authorName[i] == -1) {
				i = -1;
				break;
			}
			else if (authorId[i] == 0) {
				//�û��������������������Ԫ����0�����˳�forѭ��
				for (int k = i; k < 10; k++)
					tempAuthorId[i] = 0;
				i = 10;
				break;
			}
			else {
				authorList = getAuthorById(authorId[i]);
				if (!authorList.empty()) {
					tempAuthorId[i] = authorId[i];
					break;
				}
				else
					//�Ҳ������ߣ����û���������
					cout << "������������ID��ƥ������ߣ�����������" << endl;
			}
		}
	}

	//�޸���ɣ���temp����book��author
	for (int i = 0; i < 10; i++)
		book.author[i] = tempAuthorId[i];
	return true;
	*/
}

bool ModifyBookType(Book &book) {

	cout << endl << "�������޸ĺ�ǰ�鼮��ȫ�����" << endl;
	int typeId[10];
	int tempTypeId[10];
	list<Type> typeList;

	cout << endl;
	cout << "���޸ĵ��鼮�������£�" << endl;
	showTypeInfo(getAllTypes(), true);

	//�鼮����ͬ����һ�����ж������˲�����ͬ
	cout << endl;
	cout << "�������޸ĵ��鼮�����ID�ţ����10��" << endl;
	cout << "����0���������� - 1��������, ���� - 2ȡ���޸ģ�" << endl;
	for (int i = 0; i < 10; i++) {
		for (;;) {
			cout << i + 1 << ".";
			typeId[i] = GetIntFromCin();

			if (typeId[i] == -2)
				return false;
			else if (typeId[i] == -1) {
				i = -1;
				break;
			}
			else if (typeId[i] == 0) {
				for (int k = i; k < 10; k++)
					tempTypeId[k] = 0;
				i = 10;
				break;
			}
			else {
				typeList = getTypeById(typeId[i]);
				if (!typeList.empty()) {
					tempTypeId[i] = typeId[i];
					break;
				}
				else
					cout << "������������ID��ƥ����鼮���࣬����������" << endl;
			}
		}
	}

	for (int i = 0; i < 10; i++)
		book.type[i] = tempTypeId[i];
	return true;
}

bool ModifyBookPublisher(Book &book) {
	string publisher;

	cout << endl;
	cout << "�������޸ĵĳ��������ƣ�����0ȡ���޸ģ�";
	getline(cin, publisher);

	if (publisher == "0")
		return false;
	else
		copy(book.publisher, publisher, sizeof(Book::publisher));
	return true;
}

bool ModifyBookAmount(Book &book) {
	int amount;

	for (;;) {
		cout << endl;
		cout << "�������޸ĵ�����������-1ȡ���޸�:";
		amount = GetIntFromCin();

		if (amount == -1)
			return false;
		//�޸ĵ�����������ڵ���0
		else if (amount < 0)
			cout << "����������������������" << endl;
		else if (amount < book.numberInLib)
			cout << "�������������С�ڸ���Ĺݴ���������������" << endl;
		else {
			book.amount = amount;
			break;
		}
	}
	return true;
}

bool ModifyBookNumInLib(Book &book) {
	int numberInLib;

	for (;;) {
		cout << endl;
		cout << "�������޸ĵĹݴ���������-1ȡ���޸�:";
		numberInLib = GetIntFromCin();

		if (numberInLib == -1)
			return false;
		//�޸ĵĹݴ������ڵ���0
		else if (numberInLib < 0)
			cout << "����������������������" << endl;
		else if (numberInLib > book.amount)
			cout << "����Ĺݴ������ɴ�������������������" << endl;
		else {
			book.numberInLib = numberInLib;
			break;
		}
	}
	return true;
}

void ModifyBookService() {
	//flag�����ж��Ƿ񾭹��޸�
	bool flag = false;
	Book book;
	list<Book> bookList;
	list<Author> authorList;
	list<Type> typeList;

	for (;;) {
		//ͨ��ISBN���ҵ���Ҫ�޸ĵ��鼮
		QueryBookByISBN(bookList);
		//������ֵΪ�գ����˳��ú���
		if (bookList.empty())
			return;
		else
			//������ҵ����鼮����Ϣ�������û�������Ҫ�޸ĵ���Ϣ
			showBooksInfo(bookList);

		book = bookList.back();
		bookList.pop_back();

		//ʵ���޸Ķ������
		for (int i = -1; i != 0;) {
			//ѡ���޸ĵ�ѡ��
			cout << endl;
			cout << "��ѡ����Ҫ�޸ĵ���Ϣ��ȷ���޸�������0��" << endl;
			cout << "0.ȷ�ϵ�ǰ�޸�" << endl;
			cout << "-1.ȡ���޸�" << endl;
			cout << "1.����" << endl;
			cout << "2.ISBN" << endl;
			cout << "3.����" << endl;
			cout << "4.����" << endl;
			cout << "5.������" << endl;
			cout << "6.����" << endl;
			cout << "7.�ݴ���" << endl;
			i = GetIntFromCin();

			//ʵ�ֹ��ܵ�ѡ��
			switch (i) {
			case 1:
				flag = ModifyBookName(book);
				break;
			case 2:
				flag = ModifyBookISBN(book);
				break;
			case 3:
				flag = ModifyBookAuthor(book);
				break;
			case 4:
				flag = ModifyBookType(book);
				break;
			case 5:
				flag = ModifyBookPublisher(book);
				break;
			case 6:
				flag = ModifyBookAmount(book);
				break;
			case 7:
				flag = ModifyBookNumInLib(book);
				break;
			case 0:
				break;
			case -1:
				return;
			default:
				cout << "����������������������" << endl;
			}
		}

		//�����й��޸ģ�������޸ĺ���
		if (flag) {
			flag = false;
			cout << "ȷ���޸ģ�ȷ��������1��ȡ��������0��";
			int t = GetIntFromCin();

			if (t == 1) {
				//���ú����޸��鼮��Ϣ
				if (modifyBook(book)) {
					cout << "�鼮��Ϣ�޸ĳɹ���" << endl;
					bookList.clear();
					bookList.push_back(book);
					//������ҵ����鼮����Ϣ
					showBooksInfo(bookList);
					return;
				}
				else
					cout << "�鼮��Ϣ�޸�ʧ�ܣ�" << endl;
			}
			else if (t == 0)
				cout << "�޸�ȡ����" << endl;
			else
				cout << "����������������������" << endl;
		}
	}
}


