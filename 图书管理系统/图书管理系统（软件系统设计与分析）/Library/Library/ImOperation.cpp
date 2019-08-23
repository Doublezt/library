#include"stdafx.h"
#include"Operation.h"
#include<time.h>
#include<iostream>
using namespace std;

//ȥ���ַ���s��β�Ŀո�
void trimFLSpace(string& s) {
	if (!s.empty()) {
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}
}


//find ��������ֵ��The position of the first character of the first match.
//If no matches were found, the function returns string::npos.
// �ڶ��������� Position of the first character in the string to be considered in the search.
//ȥ���ַ���s�е����пո�
void trimAllSpace(string& s) {
	int index = 0;
	if (!s.empty()) {//�ú����Ĺ����ǣ�ÿ�ҵ�һ���ո񣬾ͽ���Ĩȥ��Ȼ�����Ѱ����һ���ո����ڵ�λ��ֱ������
		while ((index = s.find(' ', index)) != string::npos) {
			s.erase(index, 1);// erase(offset,count) ��offsetλ�ÿ�ʼĨȥcount���ַ�
		}
	}
}


/*��s2���ַ������Ƶ�s1��ȥ��n��ʾs1����Ч����
���s2���ַ����ȴ��ڵ���n�����������ƣ�ֱ�ӷ���false
����s2���Ƶ�s1��s1ʣ�����Ч�洢�ռ䶼��'\0'���
*/
bool copy(char* s1, string s2, unsigned n) {
	unsigned n2 = s2.length();
	if (n2 >= n) return false;// n2 >= n ��Ϊ�˱�֤s1һ��������һ���ַ��������� '\0'
	const char* c2 = s2.data();
	for (unsigned i = 0; i < n; i++)
	{
		if (i < n2)
			s1[i] = c2[i];
		else
			s1[i] = '\0';
	}
	return true;
}






/*
void test(int* a) {
cout << "test:" << sizeof(a) << endl;
}

�������Ժ��֣�
int a[5];
cout << sizeof(a);
test(a);
���������ֵ�ֱ���20��4  
Ҳ����˵�ڽ�����ָ����Ϊ��������ʱ��������Ϣ���ᱻ��������
*/
/*��b������������θ��Ƶ�a������ȥ
n1��a����ĳ��� n2��b����ĳ���
���b����ĳ��ȴ���n1
���������ƣ�ֱ�ӷ���false
*/
bool copy(int* a, int* b, unsigned n1, unsigned n2) {
	if (n2 > n1) return false;
	for (unsigned i = 0; i < n1; i++) {
		if (i < n2) a[i] = b[i];
		else a[i] = 0;
	}
	return true;
}








/*����ʹ��
int main() {
int i;
string s = "   kkkkllll    ";
cout << s.data() <<"end"<< endl;
trimFLSpace(s);
cout << s.data() << "end"<<endl;
cin >> i;
return 0;
}
*/