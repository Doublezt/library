#pragma once
#include <list>
#include "Structs.h"

/**
* ��ӽ��ļ�¼
* @param borrowHistory
* @return
*/
bool addHistory(BorrowHistory& borrowHistory);

/**
* ���ݽ��ļ�¼idɾ�����ļ�¼����ɾ����
* @param borrowHistoryId
* @return
* ���id�����ڣ���������false
* ���򣬼�ɾ���ɹ��󷵻�true
*/

bool deleteHistory(int id);


/**
* ͨ������id��ѯ���ļ�¼
*/
list<BorrowHistory> getHistoryByReaderId(int readerId, int exist);

/**
* ͨ���鼮id(�����ͼ��id��һ��ͼ��Ĺ�ͬid)��ѯ���ļ�¼
* @return
*/
list<BorrowHistory> getHistoryByBooksId(int bookId, int exist);

/**
* �������еĽ��ļ�¼
* @return
*/
list<BorrowHistory> getAllHistory(int exist);

/*ͨ����ʷ��¼��id���Ҽ�¼
existΪ1 ������ҵ���δ��ɾ������ʷ��¼�в���
existΪ0����������ʷ��¼�в���*/
list<BorrowHistory> getHistoryById(int id, int exist);