#pragma once
/*�Ѻ�����������ͷ�ļ�������к�����Ҫ����
AdminFunction�����е�����һ��ʱ��ֻ��Ҫ
�����ͷ�ļ�include�����Ϳ�����*/
#include<list>
#include<iostream>
#include "Structs.h"
/**
* ���Ĺ���Ա��Ϣ
* @param admin
* @return ���޸ĳɹ�����true�����򷵻�false��Ȼ������������
�ĺ�������������������
*/
bool modifyAdmin(Admin& admin);


/*��id�Ų��ҹ���Ա��Ϣ
����Ա��¼���õ��������
|���Ҳ����᷵��һ�����б�
*/
list<Admin> getAdminById(int id);

/*ɾ��һ������Ա����ɾ�����޸�exist���Լ���)
�������id�����ڣ���������false
���򣬼�ɾ���ɹ���������true
*/
bool deleteAdmin(int id);


/*����һ������Ա(�����״��½�һ������Ա�˺�
����Ա�˺�ֻ��һ���͹���)
����һ����¼֮���β�admin�����idֵ�ᱻ��ֵΪ�����ļ��е�id*/
bool addAdmin(Admin& admin);
