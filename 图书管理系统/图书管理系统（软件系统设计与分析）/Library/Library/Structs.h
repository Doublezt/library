#pragma once

#include<time.h>
#define  maxBorrowDay 30//����������(ÿ����һ�Σ���ٹ黹���Ⱦ�����maxBorrowDay��)
#define maxBorrowNum 10//����������
#define finePerday  1//����ÿ��ķ���
#define maxRenewTime  3//�������ͼ�����
#include<iostream>
#include"Operation.h"
using namespace std;

typedef struct {
	int id;
	char password[22];//����Ҫ��5-10λ��������������
	int exist;
}Admin;

/*����admin������Ϊpd*/
bool setAdminPd(Admin& admin,string pd);


/************************************************************************/

typedef struct {
	int id;
	char name[40];//һ���ַ��������ֽڣ�����������������Դ洢20���ַ�����������
}Author;



/*��name�ֶ�����ֵ
���name ���ȹ������������������ã�ֱ�ӷ���false
*/
bool setAuthorName(Author& author, string name);



/************************************************************************/
typedef struct {
	int id;
	char name[20];//һ���ַ��������ֽڣ�����������������Դ洢10���ַ��������
}Type;

bool setTypeName(Type& type,string name);

/************************************************************************/
typedef struct {
	int id;
	char name[40];//һ��unicode�ַ������������ֽڣ���������������20���ַ�
	int author[10];//�洢һ�����author��id�ţ���һ�����������ʾ
				   //����10���ĺ��油0 �ڰ����ߺŲ�ѯ������Ϣʱ�������������
				   //������Ԫ��Ϊ0 ��ֹͣ��Ȼ��ȥ��ѯ������Ϣ����



	char publisher[40];//����������
	int numberInLib;//�ݲ�����
	int amount;//����ͼ������
	int type[10];//����������һ��ͼ�飬����������洢��ͼ����������id��ɵ�����
				 //ͬ��������10�������ں��油0 ��ѯ����ͬ����id

	int exist;//��������Ϊ������ɾ���õ�
	char ISBN[14];//ISBN���,�������һλ�Ǵ洢�ַ���������
}Book;


/*��name�ֶ�����ֵ
���name ���ȹ������������������ã�ֱ�ӷ���false
*/
bool setBookName(Book& book,string name);

/*����������id��ɵ��������飬���au��������������false
len ��au����ĳ��� 
����int a[5]; ���Ⱦ���5*/
bool setBookAuthors(Book& book,int* au,unsigned len);

bool setBookPublisher(Book& book,string pub);

/*ͬauthor����ĸ���
len �ǲ���type����ĳ���*/
bool setBookTypes(Book& book,int* type, unsigned len);


bool setBookISBN(Book& book,string ISBN);




/************************************************************************/
typedef struct {
	int id;//����id
	char name[40];//��������  !!!!!
	char password[22];//����5-10λ��Ч��������������������
	int sex;//sex��0��1��ʾ�ȽϷ���  1��ʾ���ԣ�0��ʾŮ��
	int exist;//�û��Ƿ���Ч ��1��0��ʾ
	double fine;//Ƿ����
}Reader;

/*��name�ֶ�����ֵ
���name ���ȹ������������������ã�ֱ�ӷ���false
*/
bool setReaderName(Reader& reader,string name);

bool setReaderPw(Reader& reader,string pw);


/************************************************************************/

typedef struct {
	int id;
	char bookOnlyId[17];//�����bookOnlyId�ǿ���Ψһ��ʶһ�����id��
				//�����ŵ�ǰ5λ�����������ţ������12λ���Ȿ�鱻��ʱ��
	int readerId;
	int bookId;
	time_t startTime;//������ʼʱ��
	time_t rationalTime;//ͼ����ٹ黹ʱ��
						//�����������ͨ��������ʼʱ�����ٹ黹ʱ��������
						//����ǰҪ�ж�����������ܴ�������������

}BorrowRecord;


//record.rationalTime = time(NULL); �������õ�ǰʱ��

/*����һ��ʱ���ַ���(��ʽ��YYYY-MM-DD HH:MM   24Сʱ��)
���ڹ��ܽ��桢�������е�չʾ
*/
string getDateStr(time_t& time);

/*�������������bookKindId��ĳ��ʱ��(һ���ǵ�ǰʱ��)Ϊ�����ߵ��Ȿ������һ��Ψһ��id
�ú�����ֱ�ӽ����Ψһ��id��ֵ��b�� bookOnlyId�ֶ�
���һὫbookKindId��ֵ��bookId�ֶ�
*/
bool setRecordBookId(BorrowRecord& b,int bookKindId,time_t& t);


/*��ͼ����ٹ黹ʱ����� maxBorrowDay ��
�������ͨ���жϣ���ǰ��������Ѿ���������������
��rationaltime����仯�������᷵��false
(����ǰҪ��֤ startTime���rationalTime���ŵ�����Чʱ�䣬����᷵��false)
������Ե����������
*/
bool increaseRationalTimeByConst(BorrowRecord& record);

/************************************************************************/


typedef struct {
	int id; //������ʷ��¼id��
	int bookId; //����ͼ��id��(�����Ȿ���������id��)
	int readerId;//����id��

				 /*time_t�Ǳ�ʾUTCʱ��ģ�Ҳ����һ������ֵ
				 �洢 ��00:00 hours, Jan 1, 1970 UTC
				 ��ĳһʱ��㾭��������

				 size_t�����ݿ���ͨ������mktimeת���ɱ�ʾ ������ʱ���� �Ľṹ������tm
				 �Ӷ���ȡʱ����Ϣ
				 */
	time_t borrowTime;//������ʼʱ��,���ļ��д洢�������ֵ�Ϳ���
	time_t returnTime;//ͼ��黹ʱ�䣬���ļ��д洢�������ֵ�Ϳ���
	int exist;//������������ɾ�������ԣ�ȡֵΪ0���1��0���������¼��ɾ����1����ü�¼����
}BorrowHistory;

/*ע����getDataStr�����Ϳ��Եõ�����time_t�������ַ�����ʾ*/
/*Ӧ�� generateBookId��������bookId*/
/*BorrowHistory�ṹ����û���������ͣ����ֱ�Ӹ�ֵ���������Խ������
�����ڸ�ֵ֮ǰ��Ҫ�������
*/


