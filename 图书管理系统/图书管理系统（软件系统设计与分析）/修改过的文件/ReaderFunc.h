#pragma once
#include <list>
#include "Structs.h"


/**
* ����Ψһ��Id���Ҷ���
* �Ҳ�������һ����list
* @param id
* @return
*/
list<Reader> getReaderById(int id);

/**
* �����Ա���Ҷ���
* @param sex sexȡ1�������ԣ�0����Ů��
* ����ඨ����sex������һ�µ�
* �Ҳ�������һ����list
* @return
*/
list<Reader> getReadersBySex(int sex);

/**
* �������ֲ��Ҷ���(ģ����ѯ)
* @param name
* @return
*/
list<Reader> getReadersByName(string name);

/**
* ������ж��ߵ���Ϣ
* @return
*/
list<Reader> getReaders();


/**
* /��Ӷ���
* ����Ҳ��ֻ��������߱������һ�����߼�¼
* ��������Ϣ�Ĺ�����һ�������
* @param reader
* @return
*/
bool addReader(Reader& reader);

/**
* ���Ķ�����Ϣ
* @param reader
* @return
*/

bool modifyReader(Reader& reader);

/*ɾ��һ������(��ɾ�����޸�exist���Լ���)
�������id�����ڣ���������false
���򣬼�ɾ���ɹ���������true
*/
bool deleteReader(int id);