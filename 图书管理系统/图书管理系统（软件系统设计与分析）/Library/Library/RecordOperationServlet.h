#pragma once

//(չʾ��ǰ�������е�ǰ�����¼��
//��ʾ��ǰ�����鼮������ͼ�飬�����
void QueryCurReaderBorRecordServlet(int readerId);


//(չʾ��ǰ���ߵ����н�����ʷ)
void QueryCurReaderBorHistoryServlet(int readerId);


/*(һ��Ҫ��֤��¼�Ķ���ֻ��ɾ���Լ��Ľ�����ʷ��
����������һ��Ҫɾ���Ľ�����ʷ��id��Ҫȷ������������ʷ�ǵ�ǰ���ߵģ�
�ſ���ִ��ɾ������)*/
void DeleteCurReaderHistoryServlet(int readerId);
