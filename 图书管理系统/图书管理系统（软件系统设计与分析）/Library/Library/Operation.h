#pragma once
#include<iostream>
using namespace std;





/*��s2�ַ������Ƶ� s1ָ����ַ�������ȥ�����Ƴ���Ϊn�����s2��ռ�ֽ�������n����������false*/
bool copy(char* s1, string s2, unsigned n);

/*��b������������θ��Ƶ�a������ȥ
n1��a����ĳ��� n2��b����ĳ���
���b����ĳ��ȴ���n1
���������ƣ�ֱ�ӷ���false

������и��ƣ�a�в�������0���
*/
bool copy(int* a,int* b,unsigned n1,unsigned n2);




//ȥ���ַ���s��β�Ŀո�
void trimFLSpace(string& s);

//ȥ���ַ���s�е����пո�
void trimAllSpace(string& s);




