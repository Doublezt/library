#pragma once
#include<string>
#include<iostream>
using namespace std;

int DealFault();

/*�ӱ�׼�������л��һ������������
��������һ���ַ�����ȫ�����֣��ͷ����������
ֻҪ���ַ����֣���������ͻ᷵��-1*/
int GetIntFromCin();

/*�ж�һ���ַ�����ʾ���Ƿ���һ��ISBN*/
bool IsISBN(string isbn);


/*�ж�������������Ƿ���ȫ���ַ������еĻ�����true�����򷵻�false*/
bool IsDoubleChar(string str);