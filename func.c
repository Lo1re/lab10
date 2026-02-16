#include "func.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Book* createBook(const std::string& author,
    const std::string& title,
    int year, int pages, float price)
{
    Book* b = new Book;
    b->author = author;
    b->title = title;
    b->year = year;
    b->pages = pages;
    b->price = price;
    b->next = nullptr;
    return b;
}

void insertSorted(Book*& head, Book* b)
{
    if (!head || head->year <= b->year) {
        b->next = head;
        head = b;
        return;
    }

    Book* cur = head;
    while (cur->next && cur->next->year > b->year)
        cur = cur->next;

    b->next = cur->next;
    cur->next = b;
}

void addBook(Book*& head)
{
    std::string author, title;
    int year, pages;
    float price;

    std::cout << "Author: ";
    std::getline(std::cin, author);

    std::cout << "Title: ";
    std::getline(std::cin, title);

    std::cout << "Year: ";
    std::cin >> year;

    std::cout << "Pages: ";
    std::cin >> pages;

    std::cout << "Price: ";
    std::cin >> price;
    std::cin.ignore();

    insertSorted(head,
        createBook(author, title, year, pages, price));
}

void printTable(const Book* head)
{
    std::cout << "\n"
        << std::left
        << std::setw(25) << "Author"
        << std::setw(30) << "Title"
        << std::setw(6) << "Year"
        << std::setw(8) << "Pages"
        << std::setw(10) << "Price"
        << "\n";

    std::cout << std::string(80, '-') << "\n";

    int count = 0;
    while (head) {
        std::cout << std::setw(25) << head->author
            << std::setw(30) << head->title
            << std::setw(6) << head->year
            << std::setw(8) << head->pages
            << std::setw(10) << std::fixed << std::setprecision(2)
            << head->price << "\n";

        head = head->next;
        count++;
    }

    std::cout << "\nCount of records: " << count << "\n";
}

void printTitleStartsWithA(const Book* head)
{
    while (head) {
        if (!head->title.empty() &&
            (head->title[0] == 'A' || head->title[0] == 'a'))
        {
            std::cout << head->title << "\n";
        }
        head = head->next;
    }
}

float calcAvgPages(const Book* head)
{
    int sum = 0;
    int count = 0;

    while (head) {
        sum += head->pages;
        count++;
        head = head->next;
    }

    return (count == 0) ? 0 : (float)sum / count;
}

void deleteLessThanAvg(Book*& head, float avg)
{
    while (head && head->pages < avg) {
        Book* tmp = head;
        head = head->next;
        delete tmp;
    }

    Book* cur = head;
    while (cur && cur->next) {
        if (cur->next->pages < avg) {
            Book* tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
        }
        else {
            cur = cur->next;
        }
    }
}

void writeToFile(const Book* head, const std::string& filename)
{
    std::ofstream fout(filename);

    while (head) {
        fout << head->author << "\n"
            << head->title << "\n"
            << head->year << " "
            << head->pages << " "
            << head->price << "\n";

        head = head->next;
    }
}

void freeBookList(Book*& head)
{
    while (head) {
        Book* next = head->next;
        delete head;
        head = next;
    }
}
