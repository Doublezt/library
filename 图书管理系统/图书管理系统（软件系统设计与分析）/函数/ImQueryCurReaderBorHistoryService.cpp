
#include "stdafx.h"
#include "QueryCurReaderBorHistoryService.h"
using namespace std;
void QueryCurReaderBorHistoryService(int readerId)
{
	cout << endl;
	list<BorrowHistory> borrowHistoryList = getHistoryByReaderId(readerId, 1);
	if(borrowHistoryList.size()==0)
	{
		cout << "��ǰ�û�û���ڽ���鼮" << endl;
	}
	else 
		showBorrowHistoryInfo(borrowHistoryList);
}