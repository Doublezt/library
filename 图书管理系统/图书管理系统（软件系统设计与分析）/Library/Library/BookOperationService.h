#pragma once

//(readerId�ǵ�ǰ��¼�Ķ��ߵ�id�ţ��������Ὣ���id�������service)
void BorrowBookService(int readerId); 


//����ʾ��ǰ���ģ��ö�����������¼��id���л��飬�����¼��ɾ��һ����������ʷ����һ�����ݲ���������
void ReturnBookService(int readerId);

/*�����Service*/
void RenewBookService(int readerId);