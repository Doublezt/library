#pragma once

//(չʾ��ǰ�������е�ǰ�����¼��
//��ʾ��ǰ�����鼮������ͼ�飬�����
void QueryCurReaderBorRecordService(int readerId); 


//(չʾ��ǰ���ߵ����н�����ʷ)
void QueryCurReaderBorHistoryService(int readerId); 


/*(һ��Ҫ��֤��¼�Ķ���ֻ��ɾ���Լ��Ľ�����ʷ��
����������һ��Ҫɾ���Ľ�����ʷ��id��Ҫȷ������������ʷ�ǵ�ǰ���ߵģ�
�ſ���ִ��ɾ������) ����id��ɾ����Ӧ��ʷ��¼�����Ǳ����Ǹö��߱���*/
bool DeleteCurReadHistoryService(int id);
