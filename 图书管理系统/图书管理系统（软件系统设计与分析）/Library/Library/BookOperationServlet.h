#pragma once

//(readerId�ǵ�ǰ��¼�Ķ��ߵ�id�ţ��������Ὣ���id�������service)
void BorrowBookServlet(int readerId);


//����ʾ��ǰ���ģ��ö�����������¼��id���л��飬�����¼��ɾ��һ����������ʷ����һ�����ݲ���������
void ReturnBookServlet(int readerId);

/*�����Servlet*/
void RenewBookServlet(int readerId);