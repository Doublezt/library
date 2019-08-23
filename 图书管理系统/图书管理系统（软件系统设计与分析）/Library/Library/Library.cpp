// Library.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include <map>
#include "Structs.h"
#include <string>
#include"UnsignedReaderServlet.h"
#include"LoginServlet.h"
#include"BookOperationServlet.h"
#include"QueryBookServlet.h"
#include"BookManageServlet.h"
#include"BorrowRecordManageServlet.h"
#include"ReaderManageServlet.h"
#include"QueryBookServlet.h"
#include"BookOperationServlet.h"
#include"RecordOperationServlet.h"
#include"AuthorManageServlet.h"
#include"AdminFunc.h"
using namespace std;


int main()
{
	cout << endl;
	cout << "��ӭʹ��ͼ��ݹ���ϵͳ��" << endl;
	int choose1 = 1;
	//������������ʾ��Ϣ
	while (choose1) {
		cout << endl;
		cout << "0.�˳�ϵͳ" << endl;
		cout << "1.���е�¼����" << endl;
		cout << "2.�����¶���ע�����" << endl;
		cout << "3.�οͲ���" << endl;
		cout << "����������ѡ�� ";

		choose1 = GetIntFromCin();
		map<string, int> loginInfo;
		if (choose1 < 0)            
		{
			cout << endl;
			cout << "�����д�!����������" << endl;
			choose1 = 1;
			continue;
		}
		switch (choose1)
		{
			cout << endl;
		//�˳�ϵͳ
		case 0:cout << endl <<  "��л����ʹ�ã�"; return 0;
		//�û���¼
		case 1:
			loginInfo = LoginServlet();
			if (loginInfo.size() == 0)
			{
				continue;
			}
			else
			{
				map<string, int>::iterator i;
				string userIdentity;
				cout << endl;
				cout << "���ѵ�¼�ɹ���" << endl;
				int choose2 = 1;
				i = loginInfo.begin();
				//admin��¼��Ĳ���
				if (i->first == "Admin")
				{
					while (choose2)
					{
						cout << endl;
						cout << "0.�˳���¼" << endl;
						cout << "1.�鼮�������" << endl;
						cout << "2.���߹������" << endl;
						cout << "3.���ļ�¼�������" << endl;
						cout << "4.������ʷ�������" << endl;
						cout << "5.���߹������" << endl;
						cout << "����������ѡ��" << endl;
						choose2 = GetIntFromCin();
						if (choose2 < 0)            //�����ɸ�дΪcin.fail() 
						{
							cout << "�����д�!����������" << endl;
							choose2 = 1;
							continue;
						}

						int choose3 = 1;
						switch (choose2)
						{
						//����Ա�˳���¼
						case 0:break;
						//����Ա����ͼ�����
						case 1:
							while (choose3)
							{
								cout << endl;
								cout << "�鼮������" << endl;
								cout << "0.����������" << endl;
								cout << "1.�鼮��ѯ����" << endl;
								cout << "2.�鼮���Ӳ���" << endl;
								cout << "3.�鼮�޸Ĳ���" << endl;
								cout << "4.�鼮ɾ������" << endl;
								cout << "����������ѡ��" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)           
								{
									cout << endl;
									cout << "�����д�!����������" << endl;
									choose3 = 1;
									continue;
								} 
								switch (choose3)
								{
									case 0:break;
									case 1:QueryBookServlet();break;
									case 2:AddBookServlet();break;
									case 3:ModifyBookServlet();break;
									case 4:DeleteBookServlet();break;
									default:cout <<endl<< "����ȷ����ѡ����Ϣ��" << endl; break;
								}
								if (choose3 == 0)
									break;
							}
							break;
						//����Ա���ж��߹���
						case 2:
							while (choose3)
							{
								cout << endl;
								cout << "���߹������" << endl;
								cout << "0.����������" << endl;
								cout << "1.���߲�ѯ����" << endl;
								cout << "2.�������Ӳ���" << endl;
								cout << "3.�����޸Ĳ���" << endl;
								cout << "4.����ɾ������" << endl;//�������н�����������ܱ�ɾ��
								cout << "����������ѡ��" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "�����д�!����������" << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
									case 0:break;
									case 1:QueryReaderServlet();break;
									case 2:AddReaderServlet();break;
									case 3:AdminModifyReaderServlet();break;
									case 4:DeleteReaderServlet();break;
								default:cout << endl << "����ȷ����ѡ����Ϣ��" << endl; break;;
								}
								if (choose3 == 0)
									break;
							}
							break;
						//����Ա���н��ļ�¼����
						case 3:
							while (choose3)
							{
								cout << endl;
								cout << "���ļ�¼�������" << endl;
								cout << "0.����������" << endl;
								cout << "1.���ļ�¼��ѯ����" << endl;
								cout << "2.��ѯ��ǰ����δ���鼮���ļ�¼" << endl;
								cout << "����������ѡ��" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "�����д�!����������." << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
								case 0:break;
								//		���ļ�¼��ѯ	
								case 1:QueryBorrowRecordServlet();break;
									//	��ѯ��ǰ����δ���鼮
								case 2:QueryExtendedBookServlet();break;
							
					
								default:cout << endl<< "����ȷ����ѡ����Ϣ��" << endl; break;;
								}
								if (choose3 == 0)
									break;
							}
							break;
						//����Ա���н�����ʷ����
						case 4:
							while (choose3)
							{
								cout << endl;
								cout << "���ļ�¼�������" << endl;
								cout << "0.����������" << endl;
								cout << "1.������ʷ��ѯ����" << endl;
								//cout << "2.������ʷɾ������" << endl;
								cout << "����������ѡ��" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "�����д�!����������." << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
								case 0:break;
								//		������ʷ��ѯ����
								case 1:QueryBorrowHistoryServlet(); break;
								//			������ʷɾ������	
								
								//case 2:Delete;break;

								default:cout << endl<< "����ȷ����ѡ����Ϣ��" << endl; break;
								}
								if (choose3 == 0)
									break;
							}
							break;
						//����Ա�������߹���
						case 5:
							while (choose3)
							{
								cout << endl;
								cout << "���߹������" << endl;
								cout << "0.����������" << endl;
								cout << "1.��ѯ����" << endl;
								cout << "2.�������߽����鼮��ѯ����" << endl;
								cout << "����������ѡ��" << endl;
								
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "�����д�!����������." << endl;
									choose3 = 1;
									continue;
								}

								switch (choose3)
								{
								case 0:break;
								case 1:QueryAuthorServlet();break;
								case 2:QueryBooksByAuthorServlet();break;

								default:cout << endl << "����ȷ����ѡ����Ϣ��" << endl; break;
								}
								if (choose3 == 0)
									break;

							}
							break;
						//������󣬽����ݴ�
						default:cout << endl << "����ȷ������Ϣ��" << endl; continue;
						}
						if (choose2 == 0)
						{
							break;
						}
					}

				}
				

//admin��¼��Ĳ���
			else
				{
//reader��¼��Ĳ���
					userIdentity = "Reader";
					int readerId = i->second;
					while (choose2)
					{
						cout << endl;
						cout << "0.�˳���¼" << endl;
						cout << "1.��ѯ�鼮" <<endl;
						cout << "2.�鿴��ǰ���ļ�¼" << endl;
						cout << "3.�鿴��ɾ��������ʷ" << endl;
						cout << "4.�鿴���޸ĸ�����Ϣ����" << endl;
						cout<<  "5.����" << endl;
						cout << "6.����" << endl;
						cout << "7.����" << endl;
						cout << "8.����Ƿ��" << endl;
						cout << "����������ѡ��" << endl;
						choose2 = GetIntFromCin();
						if (choose2 < 0)
						{
							cout << endl;
							cout << "�����д�!����������." << endl;
							choose2 = 1;
							continue;
						}

						int choose3 = 1;
						switch (choose2)
						{
						//�����˳���¼
						case 0:break;
						//���߲�ѯ�鼮
						case 1:QueryBookServlet();break;
						//���߲鿴��ǰ���ļ�¼
						case 2:QueryCurReaderBorRecordServlet(readerId);break;
						//���߲鿴��ɾ��������ʷ
						case 3:
							while (choose3)
							{
								cout << endl;
								cout << "0.���������� " << endl;
								cout << "1.������ʷ��ѯ" << endl;
								cout << "2.������ʷɾ��" << endl;
								cout << "����������ѡ��" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "�����д�!����������." << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
								case 0:break;
								case 1:QueryCurReaderBorHistoryServlet(readerId); break;
								case 2: DeleteCurReaderHistoryServlet(readerId); break;
								default:cout << endl; cout << "����ȷ������Ϣ��" << endl; continue;
								}
								if (choose2 == 0)
								{
									break;
								}
							}
							break;
						//�鿴���޸Ķ��߸�������
						case 4:
							while (choose3)
							{
								cout << endl;
								cout << "0.����������" << endl;
							//	cout << "1.������Ϣ�鿴" << endl;
								cout << "2.������Ϣ�޸�" << endl;
								cout << "����������ѡ��" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "�����д�!����������." << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
								case 0:break;
								//case 1:������Ϣ�鿴��break;
								//������Ϣ�޸�
								case 2:	ReaderModifySelfServlet(readerId);break;
								default:cout << "����ȷ����ѡ�" << endl; break;
								}
								if (choose3 == 0)
								{
									break;
								}

							}
							break;
						//����
						case 5:BorrowBookServlet(readerId);break; 
						//����
						case 6: ReturnBookServlet(readerId); break;
						//����
						case 7:RenewBookServlet(readerId); break;
						//����Ƿ��
						case 8:  PayTheFeesServlet(readerId); break;//����Ƿ��
						default:cout << endl<< "����ȷ����ѡ����Ϣ��" << endl; break;
						}
						if (choose2 == 0)
						{
							break;
						}
					}
				}

			}
			break;
		//����ע��
		case 2:SignUpServlet(); break;
		//�οͲ���
		case 3:UnsignedReaderServlet();break;
		default:cout << endl; cout << "����ȷ����ѡ�"; continue;
		}


	}

	return 0;
}


