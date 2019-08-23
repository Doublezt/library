#pragma once
#include<list>
#include"Structs.h"



list<Reader> QueryReaderById(int id);
void QueryReaderByName(string name);
void QueryReaderBySex(int sex);
void QueryAllReader();

/*��������ѯ������Ӧ�����Ķ��߲�չʾ���û���*/
void QueryReaderService();


/*����һ����ߵ�service*/
void AddReaderService(list<Reader> readerList);

/*ɾ��һ����ߵ�service*/
void DeleteReaderService(int id);


//����Ա�޸�����һ��������Ϣ
void AdminModifyReaderService();

//�����޸��Լ�������Ϣ
void ReaderModifySelfService(int id);

//���߽���Ƿ��
void PayTheFeesService(int readerId);