#pragma once

/*��������ѯ������Ӧ�����Ķ��߲�չʾ���û���*/
void QueryReaderServlet();


/*����һ����ߵ�service*/
void AddReaderServlet();

/*ɾ��һ����ߵ�Servlet*/
void DeleteReaderServlet();

//����Ա�޸Ķ�����Ϣ���ܽ���
void AdminModifyReaderServlet();

//�����޸��Լ�������Ϣ����
void ReaderModifySelfServlet(int id);


//���߽���Ƿ��
void PayTheFeesServlet(int readerId);