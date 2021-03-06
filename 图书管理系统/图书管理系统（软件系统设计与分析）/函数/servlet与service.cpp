#include"stdafx.h"
#include<fstream>
#include <string>
#include"AuthorFunc.h"
#include"BookFunc.h"
#include"TypeFunc.h"
#include"BorrowRecordFunc.h"
#include"showInfo.h"
#include"ReaderFunc.h"
using namespace std;
void QueryAuthorServiceById(int id)//通过作者id查找作者的service 
{
	list<Author> authorList = getAuthorById(id);//调用通过作者id查找函数 
	bool a = true;
	if (authorList.empty())//如果数据为空，输出提示信息 
	{
		cout << "找不到此作者"<<endl;
	}
	else
	{
		showAuthorInfo(authorList,a);//否则显示所查作者信息 
	}
}
void QueryAuthorServiceByName(string name)//通过作者姓名查找作者的service 
{
	list<Author> authorList = getAuthorByName(name);//调用通过作者姓名查找函数 
	bool a = true;
	if (authorList.empty())//如果数据为空，输出提示信息 
	{
		cout << "找不到此作者"<<endl;
	}
	else
	{
		showAuthorInfo(authorList,a);//否则显示所查作者信息 
	}
}
void QueryAuthorServlet()//查找作者servlet 
{
	int id;
	string name, x = "1", i;
	while (x == "1")//用于多次调用 
	{
		//cin.ignore();
		cout << "请问您要通过什么方式查找？1--id,2--name,0--退出" << endl;//通过输入i来决定下一步干什么 
		getline(cin, i);
		if (i == "1")//通过id查找 
		{
			while (1)
			{
				cout << "请输入要查找作者的id:" << endl;
				cin >> id;
				if (cin.fail())//查错处理 
				{
					cout << "输出有误，请重新输入！" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else break;
			}
			QueryAuthorServiceById(id);
			cout << "是否继续？是--1，否--0？" << endl;
			cin.ignore();//忽略换行符（容错处理,如果不加就会跳过getline(cin,x)这行语句
			getline(cin, x);
		}
		else if (i == "2")//通过书名查找 
		{
			cout << "请输入要查找作者的名字:" << endl;
			getline(cin, name);
			QueryAuthorServiceByName(name);
			cout << "是否继续？是--1，否--0？" << endl;
			getline(cin, x);
		}
		else break;
	}
}
void QueryBooksByAuthorById(int id)//通过作者id查找书的service 
{
	list<Book> bookList = getBooksByAuthor(id);//调用通过作者id查找书的函数 
	if (bookList.empty())//如果数据为空，输出提示信息 
	{
		cout << "找不到此书籍";
	}
	else
	{
		showBooksInfo(bookList);//否则显示所查书的信息 
	}
}
void QueryBooksByAuthorByName(string name)//通过作者姓名查找书的service 
{
	int n = 0;//用n来记录经过模糊查询得到的作者id与书的不匹配次数 
	list<Author> authorList = getAuthorByName(name);//调用函数查得所查书的所有信息（模糊查询） 
	if (authorList.empty())//如果数据为空，输出提示信息 
	{
		cout << "找不到此书籍" << endl;
	}
	else
	{
		bool a = true;
		showAuthorInfo(authorList,a);//首先输出模糊查询后的作者表 
		for (list<Author>::iterator i = authorList.begin();i != authorList.end();++i)//通过list迭代器遍历作者表 
		{
			list<Book> bookList = getBooksByAuthor((*i).id);//通过每次所遍历的作者表中的作者id号查找相应的书的信息 
			if (bookList.empty())//每当数据为空一次，n++ 
			{
				n++;
			}
			else
			{
				showBooksInfo(bookList);//否则显示书的信息 
			}
		}
		if (n == authorList.size())//如果所有的作者id号都没有匹配的书，输出提示信息 
		{
			cout << "找不到此书籍" << endl;
		}
	}
}
void QueryBooksByAuthorServlet()//通过作者查找书的servlet 
{
	int id;
	string name, i, x ;
	while (1)
	{
		cout << "请问您要通过什么方式查找？1--id,2--name,0--退出" << endl;//通过输入整数i来确定接下来的步骤 
		getline(cin, i);
		if (i == "1")//通过id查找 
		{
			while (1)
			{
				cout << "请输入要查找书的作者id:" << endl;
				cin >> id;
				if (cin.fail())//查错处理 
				{
					cout << "输出有误，请重新输入！" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else break;
			}
			QueryBooksByAuthorById(id);
			cout << "是否继续？是--1，否--0？" << endl;
			cin.ignore();//忽略换行符（容错处理,如果不加就会跳过getline(cin,x)这行语句
			getline(cin, x);
			if (x == "1")continue;
			else break;
		}
		else if (i == "2")//通过姓名查找 
		{
			cout << "请输入要查找书的作者名字:" << endl;
			getline(cin, name);
			QueryBooksByAuthorByName(name);
			cout << "是否继续？是--1，否--0？" << endl;
			getline(cin, x);
			if (x == "1")continue;
			else break;
		}
		else break;
	}
}
void QueryBorrowRecordServiceByBook(int id)//管理员通过书的id查找借阅记录的service 
{
	bool a = true;//a这个参数表示接下来调用显示借阅记录信息函数时，可以显示读者的数据 
	list<BorrowRecord> recordList = getRecordByBookId(id);//调用通过书的id查找借阅记录的函数 
	if (recordList.empty())//如果为空，输出提示信息 
	{
		cout << "找不到此借阅记录"<<endl;
	}
	else//否则输出借阅记录 
	{
		showBorRecordInfo(recordList, a);
	}
}
void QueryBorrowRecordServiceByReader(int id)//管理员通过读者的id查找借阅记录的service 
{
	bool a = true;//a这个参数表示接下来调用显示借阅记录信息函数时，可以显示读者的数据 
	list<BorrowRecord> recordList = getRecordByBookId(id);//调用通过读者的id查找借阅记录的函数 
	if (recordList.empty())//如果为空，输出提示信息 
	{
		cout << "找不到此借阅记录"<<endl;
	}
	else//否则输出借阅记录 
	{
		showBorRecordInfo(recordList, a);
	}
}
void QueryBorrowRecordServlet()//管理员查找借阅记录的servlet 
{
	int bookId, readerId;
	string x, y, z,n = "1",m;
	while (n == "1")
	{
		cout << "是否需要查看书籍相关信息？是--1，否--0" << endl;//询问管理员是否查看书籍的相关信息 
		getline(cin, x);
		while (x == "1")//加一个循环方便多次查找 
		{
			//QueryBookServlet();//调用查书的servlet 
			cout << "是否继续？是--1，否--0？" << endl;
			getline(cin, x);
		}
		cout << "是否需要查看读者相关信息？是--1，否--0" << endl;//询问管理员是否查看读者的相关信息 
		getline(cin, y);
		while (y == "1")//加一个循环方便多次查找 
		{
			//QueryReaderServlet();//调用查读者的servlet 
			cout << "是否继续？是--1，否--0？" << endl;
			getline(cin, y);
		}
		while (1)
		{
			cout << "你要通过什么方式查找借阅记录？书的id--1,读者的id--2,退出--0?" << endl;//询问管理员通过什么方式查找借阅信息 
			getline(cin, z);
			if (z == "1")//通过书的id查借阅记录 
			{
				while (1)
				{
					cout << "请输入要查找书的id:" << endl;
					cin >> bookId;
					if (cin.fail())//查错处理 
					{
						cout << "输出有误，请重新输入！" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else break;
				}
				QueryBorrowRecordServiceByBook(bookId);
				cout << "是否继续？是--1，否--0" << endl;
				cin.ignore();//忽略换行符（容错处理,如果不加就会跳过getline(cin,x)这行语句
				getline(cin, m);
				if (m == "1")continue;
				else break;
			}
			else if (z == "2")//通过读者id查借阅记录 
			{
				while (1)
				{
					cout << "请输入要查找的读者id:" << endl;
					cin >> readerId;
					if (cin.fail())//查错处理 
					{
						cout << "输出有误，请重新输入！" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else break;
				}
				QueryBorrowRecordServiceByReader(readerId);
				cout << "是否继续？是--1，否--0" << endl;
				cin.ignore();//忽略换行符（容错处理,如果不加就会跳过getline(cin,x)这行语句
				getline(cin,m);
				if (m == "1")continue;
				else break;
			}
			else break;
		}
		cout << "是否继续？是--1，否--0" << endl;
		getline(cin, n);
	}
}

//测试主程序
//int main()
//{
    /*
	Author a;
	setAuthorName(a, "余华");
	addAuthor(a);
	setAuthorName(a, "孙皓晖");
	addAuthor(a);
	setAuthorName(a, "李海涛");
	addAuthor(a);
	setAuthorName(a, "李华");
	addAuthor(a);
	Type t;
	setTypeName(t, "文学类");
	addType(t);
	setTypeName(t, "历史类");
	addType(t);
	setTypeName(t, "理工类");
	addType(t);
	Reader r;
	r.exist = 1;
	r.sex = 1;
	r.fine = 0;
	setReaderName(r, "张三");
	setReaderPw(r, "2323");
	addReader(r);
	setReaderName(r, "李四");
	setReaderPw(r, "2323");
	addReader(r);
	setReaderName(r, "王五");
	setReaderPw(r, "2323");
	addReader(r);
	Book b;
	b.amount = 4;
	b.exist = 1;
	b.numberInLib = 3;
	setBookISBN(b, "9787302227984");
	setBookName(b, "活着");
	setBookPublisher(b, "人民邮电出版社");
	int x[1] = { 1 };
	setBookAuthors(b, x, 1);
	setBookTypes(b, x, 1);
	addBook(b);
	setBookISBN(b, "9787302227923");
	setBookName(b, "大秦帝国");
	setBookPublisher(b, "中华书局");
	int y[1] = { 2 };
	int z[2] = { 1,2 };
	setBookAuthors(b, y, 1);
	setBookTypes(b, z, 2);
	addBook(b);
	setBookISBN(b, "9787302227941");
	setBookName(b, "c语言程序设计");
	setBookPublisher(b, "清华大学出版社");
	int m[2] = { 3,4 };
	int n[1] = { 3 };
	setBookAuthors(b, m, 2);
	setBookTypes(b, n, 1);
	addBook(b);
	BorrowRecord record;
	record.readerId = 3;
	record.bookId = 4;
	record.startTime = time(NULL);
	record.rationalTime = time(NULL);
	setRecordBookId(record, 4, record.startTime);
	addRecord(record);
	record.readerId = 3;
	record.bookId = 5;
	record.startTime = time(NULL);
	record.rationalTime = time(NULL);
	setRecordBookId(record, 5, record.startTime);
	addRecord(record);
	*/
     //QueryAuthorServlet();
	//QueryBooksByAuthorServlet();
	//QueryBorrowRecordServlet();
		//return 0;
//}
