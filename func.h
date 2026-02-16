#ifndef FUNC_H
#define FUNC_H

#include <string>

struct Book {
    std::string author;
    std::string title;
    int year;
    int pages;
    float price;
    Book* next;
};

Book* createBook(const std::string& author,
    const std::string& title,
    int year, int pages, float price);

void insertSorted(Book*& head, Book* b);
void addBook(Book*& head);

void printTable(const Book* head);
void printTitleStartsWithA(const Book* head);

float calcAvgPages(const Book* head);
void deleteLessThanAvg(Book*& head, float avg);

void writeToFile(const Book* head, const std::string& filename);
void freeBookList(Book*& head);

#endif
