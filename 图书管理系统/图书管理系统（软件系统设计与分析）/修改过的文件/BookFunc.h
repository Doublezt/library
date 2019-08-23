#pragma once
#include"Structs.h"
#include<list>
/*�Ѻ�����������ͷ�ļ�������к�����Ҫ����
BooksFunction�����е�����һ��ʱ��ֻ��Ҫ
�����ͷ�ļ�include�����Ϳ�����*/


/*ͨ��ͼ��Ψһ��id�Ų�ѯ�Ȿ�����Ϣ������
��ѯ��ʱ��Ҫע��exist ������ҪΪ1(����δ��ɾ��)
�Ҳ����ͷ��ؿ�list*/
list<Book> getBookById(int id);

/**
* ����ISBN���ѯ�鼮
exist����Ϊ1��0�����Ϊ1����ֻ����existΪ1����
���Ϊ0������������鼮
��������Ƚ����⣬����Ϊ�����һ����Ҫ���һ��������飬����������
��ISBN�Ѿ�������ͼ����У�ֻ�Ǳ���ɾ���ˡ���ʱ����Ҫ�õ�����ɾ����
�����飬Ȼ���޸���exist���Ժ��������ɣ�����Ҫ������һ����¼
* �Ҳ����ͷ��ؿ�list
* @param ISBN
* @return
*/
list<Book> getBookByISBN(string ISBN,int exist);

/*ͨ�������ҵ����������������ͼ�鲢����
��ѯ��ʱ��Ҫע��exist ������ҪΪ1(����δ��ɾ��)
���û���ҵ��򷵻ؿ�list
*/
list<Book> getBooksByType(int typeId, int exist);

/*�������ߺ��ҵ��������д����������
��ѯ��ʱ��Ҫע��exist ������ҪΪ1(����δ��ɾ��)
�Ҳ����ͷ��ؿ�list*/
list<Book> getBooksByAuthor(int authorId);

/*�ɳ�����������ҵ�������ͼ��
��ѯ��ʱ��Ҫע��exist ������ҪΪ1(����δ��ɾ��)
�Ҳ����ͷ��ؿ�list*/
list<Book> getBooksByPublisher(string publisher);

//������string ������Ϊ�˲�Խ������ַ�����
//�������������char*,�����޷�׼ȷ֪�����������ַ������ж೤

/*ͨ��ͼ������ѯͼ�� ����������ģ����ѯ(�������ַ���)
��ѯ��ʱ��Ҫע��exist ������ҪΪ1(����δ��ɾ��)
�Ҳ����ͷ��ؿ�list*/
list<Book> getBooksByName(string name);


/**
* �����鼮��Ϣ
* @param books
* @return
*/
bool modifyBook(Book& book);

/**
* ɾ���鼮��Ϣ����ɾ����
* ����ٶ�id����һ�����ڣ��������ɾ��(�жϸ����Ƿ��������һ�����Ĺ���)
* @param books
* @return
*/
bool deleteBook(int id);

/**
* �����������鼮
* �ú���ֻ����book(һ������)�ӽ�ͼ���
* ���Ȿ�����ݵļ�鹤������һ�����
* (��һ����Ҫ���Ҫ���ӵ��Ȿ���ISBN�Ƿ��Ѿ����ڼ�¼��
* �����Ȿ��ĸ�����Ϣ��ʽ�Ƿ���ȷ
)
* @param book
* @return
*/
bool addBook(Book& book);

