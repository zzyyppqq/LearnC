//
// Created by 张宜鹏 on 2022/4/19.
//


#include <iostream>
#include <cstring>

using namespace std;


// 变量声明
extern int a, b;

// 声明一个结构体类型 Books，变量为 book
typedef struct Books {
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
} books;

void printBook(struct Books *book);

void printBook2(struct Books book);

int main() {
    Books Book1;        // 定义结构体类型 Books 的变量 Book1
    Books Book2;        // 定义结构体类型 Books 的变量 Book2

    // Book1 详述
    strcpy(Book1.title, "C++ 教程");
    strcpy(Book1.author, "Runoob");
    strcpy(Book1.subject, "编程语言");
    Book1.book_id = 12345;

    // Book2 详述
    strcpy(Book2.title, "CSS 教程");
    strcpy(Book2.author, "Runoob");
    strcpy(Book2.subject, "前端技术");
    Book2.book_id = 12346;

    // 输出 Book1 信息
    cout << "第一本书标题 : " << Book1.title << endl;
    cout << "第一本书作者 : " << Book1.author << endl;
    cout << "第一本书类目 : " << Book1.subject << endl;
    cout << "第一本书 ID : " << Book1.book_id << endl;

    // 输出 Book2 信息
    cout << "第二本书标题 : " << Book2.title << endl;
    cout << "第二本书作者 : " << Book2.author << endl;
    cout << "第二本书类目 : " << Book2.subject << endl;
    cout << "第二本书 ID : " << Book2.book_id << endl;

    printBook(&Book1);
    printBook(&Book2);

    printBook2(Book1);
    printBook2(Book2);

    return 0;
}

// 该函数以结构指针作为参数
void printBook(struct Books *book) {
    cout << "书标题  : " << book->title << endl;
    cout << "书作者 : " << book->author << endl;
    cout << "书类目 : " << book->subject << endl;
    cout << "书 ID : " << book->book_id << endl;
}


// 该函数以结构作为参数
void printBook2(struct Books book) {
    cout << "书标题  : " << book.title << endl;
    cout << "书作者 : " << book.author << endl;
    cout << "书类目 : " << book.subject << endl;
    cout << "书 ID : " << book.book_id << endl;
}