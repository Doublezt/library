#pragma once

#include"Structs.h"
#include<list>
void QueryBookById(list<Book> &bookList);

void QueryBookByName(list<Book> &bookList);

void QueryBookByISBN(list<Book> &bookList);

void QueryBookByAuthor(list<Book> &bookList);

void QueryBookByType(list<Book> &bookList);

void QueryBookByPublisher(list<Book> &bookList);

/*�������漸��������ɲ��鹦��*/
void QueryBookService();