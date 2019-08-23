#include"stdafx.h"
#include"AuthorFunc.h"
#include<fstream>

/*ͨ������id���������Ϣ
���������߱��У�����������¼��id�Ų�һ������
(�����deleteAuthor)
��˲���ͨ������ƫ�����ķ�����λһ������
�����id�����߲������򷵻�һ����list*/
list<Author> getAuthorById(int id) {
	list<Author> authorList;//����list��
	fstream fs;
	fs.open("author.bat", ios::out | ios::in | ios::binary | ios::ate);//���ļ�������in�������룬out���������ate��ʾ���ļ�ָ��ָ�����
	if (!fs)//����ļ������ڣ����error
	{
		cout << "open file author.bat error" << endl;
	}
	else
	{
			fs.seekg(0, ios::end);//ָ����ת���ļ�β
			streamoff len = fs.tellg();//��ȡ�ļ��ֽڳ���
			fs.seekg(0, ios::beg);
			char * buffer = new char[sizeof(Author)];//����author���ȵ�buffer
			while (fs.tellg() <len) {
				fs.read(buffer, sizeof(Author));//���ļ�
				if (((Author*)buffer)->id == id) {//�ҵ�id����λ��
					Author authorById = *((Author*)buffer);//��bufferǿ��ת��Ϊauthor���ͣ�����ֵ��authorbyid
					authorList.push_back(authorById);//����¼��ӵ�Listĩβ
					break;
				}
			}
			delete[] buffer;
	}
	fs.close();
	return authorList;


}

/*ͨ��������������������Ϣ
�������������Ϊname�����߷���һ����list
����Ĳ�ѯΪģ����ѯ
*/
list<Author> getAuthorByName(string name) {
	list<Author> authorList;//����list��
	fstream fs;
	string s = "";//�����ַ������ڴ������
	fs.open("author.bat", ios::binary | ios::in);//�Զ��ķ�ʽ���ļ�
	if (!fs)//����ļ������ڣ����error
	{
		cout << "open file author.bat error" << endl;
	}
	else
	{
		fs.seekg(0, ios::end);
		streamoff len = fs.tellg();//��ȡ�ļ�����
		fs.seekg(0, ios::beg);//ָ��ָ���ļ�ͷ
		char*buffer = new char[sizeof(Author)];//����author���ȵ�buffer����
		Author a;
		while (fs.tellg() < len)//���ļ�û����ʱ�������ļ�
		{
			fs.read(buffer, sizeof(Author));//���ļ�
			a = *((Author*)buffer);//ǿ��ת��
			s = a.name;
			if (s.find(name) != string::npos)//����ģ����ѯ
			{
				authorList.push_back(a);
			}
		}
		delete[] buffer;
	}
	fs.close();
	return authorList;
}


/*����һ�����߼�¼���������ӵ�ͼ��Ķ��ߴ�δ��
���߱�����ֹ�ʱ��*/
bool addAuthor(Author& author) {
	fstream fs;
	fs.open("author.bat", ios::out | ios::in | ios::binary);
	//��׷�ӵ���ʽ��һ���Ѿ����ڵ��ļ����ж�д����(�ļ�ָ�����ļ�ĩβ)
	if (!fs) {
		cout << " Error in open file author.bat. " << endl;
		return false;
	}
	//�������ߵ�id�������ģ��տ�ʼ��Ҫ���ļ�ָ��ָ�����һ����¼
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Author))  newId = 1;//�����ļ���һ����¼Ҳû�е����
	else {//ע������  sizeof(Author) ���޷�����������ֱ�Ӷ���ӷ���
		int authorLen = sizeof(Author);
		fs.seekg(-authorLen, ios::end); //��λ�����һ����¼�Ŀ�ʼ��

		char* buffer = new char[sizeof(Author)];
		fs.read(buffer, sizeof(Author));//��ȡ���һ��ͼ���¼

		Author* lastAuthor = (Author*)buffer;//������������ǿ������ת��

		newId = (*lastAuthor).id + 1;//�õ�Ҫ���������id����ɸ�ֵ

		delete[] buffer;
	}
	author.id = newId;
	//Ȼ���ٽ��ļ�ָ�붨λ��ĩβ��дһ������ļ�¼
	fs.seekg(0, ios::end);
	fs.write((char*)&author, sizeof(Author));
	//�ر��ļ���д��
	fs.close();
	return true;
}

/*ע�⣬���������ɾ��������ֵɾ����Ч����
�������ߵ�id���䣬���ڼ�¼��id�ſ��ܲ�����������Ȼ��
��˲���ͨ��idֱ�Ӷ�λ���ߣ�����Ҫ�������߱�һ��һ������*/
bool deleteAuthor(int id) {
	fstream fs;
	/*һ��Ҫע����ļ�ʱ�������ļ��ķ�ʽ : ios::in �� ios::app
	���û����������ʽ���Ѵ��ڵ��ļ��ᱻɾ����Ȼ���½�һ��ͬ���ļ�
	*/
	fs.open("author.bat", ios::out | ios::binary | ios::in);
	
	if (!fs) {
		cout << " Error in open file author.bat. " << endl;
		return false;
	}
	int count = sizeof(Author);//����һ����¼���ֽ���
	
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//��¼�ļ����ֽ���

	/*list�����洢ɾ���������������ɵļ���*/
	list<Author> authorList;
	fs.seekg(0, ios::beg);

	char* buffer = new char[count];

	while (fs.tellg() < len) {//����δ�����ļ�ĩβʱ��������
		fs.read(buffer, count);//��һ���ļ�¼����buffer
		if (((Author*)buffer)->id == id) continue;//�����Ҫɾ�������ߣ��Ͳ�����list
		authorList.push_back(*(Author*)buffer);//Ҫ��˳��ÿ�ζ�����¼��ӵ�list��ĩβ
	}

	delete[] buffer;//�ڴ���գ�����
	fs.close();
	/*������Ҫɾ��ԭ�����ļ�(ios::out)
	�½�һ���ļ�����list�������ȫ��д��*/
	fs.open("author.bat", ios::out | ios::binary);
	if (!fs) {
		cout << "Open file failure in author.bat" << endl;
		return false;
	}

	for (list<Author>::iterator it = authorList.begin(); it != authorList.end(); ++it) {
		fs.write((char*)&(*it), sizeof(Author));//дһ����¼
	}
	fs.close();
	return true;

}
/*
int main() {
	Author a;
	setAuthorName(a, "���");
	addAuthor(a);
	setAuthorName(a, "nishishie");
	addAuthor(a);
	setAuthorName(a, "asshasuni");
	addAuthor(a);
	list<Author> b = getAuthorById(1);
	for (list<Author>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}
	
	deleteAuthor(1);
	
	b.clear();
	b = getAuthorById(1);

	if (b.empty()) cout << "�Ѿ�ɾ��" << endl;
	b.clear();
	b = getAuthorById(2);
	for (list<Author>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}
	
	
	b.clear();

	b = getAuthorByName("ni");
	for (list<Author>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}
	int i;
	cin >> i;
	return 1;



}*/