#pragma once
#include"stdafx.h"
#include "Structs.h"
#include "ReaderFunc.h"
#include <iostream>
#include <string>
#include "DealFault.h"
using namespace std;/*��������ע��͵�½�ĺ�����ͷ�ļ�*/

/*����Ա��¼������½�ɹ����ع���Աid�ţ����򷵻�0*/
int AdminLoginService();

/***
���ߵ�¼����
***/
int ReaderLoginService();


/**
����һ������
*/
int SignUpService(Reader reader);