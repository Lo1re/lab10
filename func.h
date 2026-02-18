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

// Створення та додавання
Book* createBook(const std::string& author, const std::string& title, int year, int pages, float price);
void insertSorted(Book** head, Book* newBook);

// Вивід
void printTable(const Book* head);

// Файловий ввід/вивід
Book* readBooksFromFile(const std::string& filename);
void writeBooksToFile(const std::string& filename, Book* head);

// Логіка пошуку та видалення
void findBooksStartingWithA(const Book* head);
void find3MinPages(const Book* head);
float calcAvgPages(Book* head);
void deleteLessThanAvg(Book** head, float avg);

// Допоміжне
void swap2Books(Book* a, Book* b);
void freeBookList(Book* head);

#endif
