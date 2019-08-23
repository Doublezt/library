#pragma once
#include"AuthorFunc.h"
#include"BookFunc.h"
#include"TypeFunc.h"
#include"ReaderFunc.h"
#define MaxAuthorNumPerBook 10
#define MaxTypeNumPerBook 10



//����鼮��Ϣ
void showBooksInfo(list<Book> books);

//���������Ϣ(���������ߵ�¼����)
void showReaderInfo(list<Reader> readers);

//���������ʷ
//ע�⣺�ڶ���������ʾ�Ƿ�Ҫչʾ����������ʷ�Ķ�����Ϣ(��������id�Ͷ�������)
//�����ߵ�¼ʱ������չʾ���Լ��Ľ�����ʷ����Ҫչʾ������Ϣ
//���ǵ�����Ա��ѯ���������ʷ��ʱ����Ҫչʾ������Ϣ
void showBorHistoryInfo(list<BorrowHistory> his, bool showReaderInfo);


//������ļ�¼
//ע�⣺�ڶ���������ʾ�Ƿ�Ҫչʾ�������ļ�¼�Ķ�����Ϣ(��������id�Ͷ�������)
//�����ߵ�¼ʱ������չʾ���Լ��Ľ��ļ�¼����Ҫչʾ������Ϣ
//���ǵ�����Ա��ѯ������ļ�¼��ʱ����Ҫչʾ������Ϣ
void showBorRecordInfo(list<BorrowRecord> records, bool showReaderInfo);

//���������Ϣ
//���showIdΪtrue����չʾ����Id(��ʱÿ�����ߵļ�¼��Ϣ���û��з�����)
//�����ֻչʾ��������(ֻչʾ��������ʱ������Ҫ����������һ���еطֿ���ֻ�ÿո�������ɣ����������չʾһ����Ķ��������)
void showAuthorInfo(list<Author> aus, bool showId);




//��������Ϣ
//���showIdΪtrue����չʾ���Id(��ʱÿ�����ߵļ�¼��Ϣ���û��з�����)
//�����ֻչʾ�����(ֻչʾ��������ʱ������Ҫ����������һ���еطֿ���ֻ�ÿո�������ɣ����������չʾһ����Ķ�������)
void showTypeInfo(list<Type> types, bool showId);