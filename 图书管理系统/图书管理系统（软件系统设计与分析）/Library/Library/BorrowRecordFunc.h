#pragma once
#include <list>
#include "Structs.h"

/**
* ��Ӽ�¼���������
* @param borrowRecord
* @return
*/
bool addRecord(BorrowRecord& borrowRecord);

/**
* ɾ����¼����ɾ����ʱ�����ֻ��id�ż��ɣ�
* @param borrowRecord
* @return
*/
bool deleteRecord(int id);

/**
* ͨ������id��ѯ�������Ϣ
* @return
*/
list<BorrowRecord> getRecordsByReaderId(int readerId);

/**
* �����鼮id��ѯ�������Ϣ
* �����id��һ���鹲ͬ��id
* @return
*/
list<BorrowRecord> getRecordByBookId(int bookId);



list<BorrowRecord> getRecords(int start, int amount = -1);

/**
* ���Ľ�����еĽ����¼
* ������蹦�ܵ�ʱ����õ�
* @param borrowRecord
* @return
*/
bool modifyRecord(BorrowRecord& borrowRecord);

/*
ͨ����¼��id�Ų�ѯ�õ���¼��Ϣ*/
list<BorrowRecord> getRecordById(int id);
