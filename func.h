#ifndef FUNC_H
#define FUNC_H

typedef struct Book {
    char author[50];
    char title[50];
    int year;
    int pages;
    float price;
    struct Book* next;
} Book;

Book* createBook(const char* author, const char* title, int year, int pages, float price);
void insertSorted(Book** head, Book* newBook);

void printBook(const Book* b);
void printTable(const Book* head);

void trim_newline(char* s);
void find3MinPages(Book* head);
float calcAvgPages(Book* head);
void deleteLessThanAvg(Book** head, float avg);
void freeBookList(Book* head);
void swap2Books(Book* a, Book* b);

#endif
