

#include"Structs.h"
#include<list>

//�����鼮�����ͣ����Ǿ�Ĭ��һ��ʼ�ӽ�ȥ���鼮����ںܳ�ʱ���ڶ�����ȷ��
//��˲���дɾ�����͵ĺ���

/*

���������������Ĵ���
while (1) {
cout << "������һ���������" << endl;
string kind;
getline(cin, kind);
trimAllSpace(kind);

if (kind == "#") return 1;

Type t;
setTypeName(t, kind);

if (addType(t)) {
cout << "��ӳɹ���" << endl;
}

*/

/*����һ���������*/
bool addType(Type& type);

bool modifyType(Type& type);


list<Type> getTypeById(int id);

/*����������ҵ���Ӧ�����(ģ����ѯ)*/
list<Type> getTypeByName(string name);

/*�������������ɵ�list*/
list<Type> getAllTypes();


