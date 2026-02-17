#include <iostream>
#include <cstring>
#include "func.h"

using namespace std;

Book* createBook(const char* author, const char* title,
    int year, int pages, float price)
{
    Book* newBook = new Book;

    strncpy(newBook->author, author, sizeof(newBook->author));
    newBook->author[sizeof(newBook->author) - 1] = '\0';

    strncpy(newBook->title, title, sizeof(newBook->title));
    newBook->title[sizeof(newBook->title) - 1] = '\0';

    newBook->year = year;
    newBook->pages = pages;
    newBook->price = price;
    newBook->next = nullptr;

    return newBook;
}

void insertSorted(Book** head, Book* newBook)
{
    if (!newBook) return;

    if (*head == nullptr || (*head)->year >= newBook->year) {
        newBook->next = *head;
        *head = newBook;
        return;
    }

    Book* current = *head;

    while (current->next &&
        current->next->year < newBook->year)
    {
        current = current->next;
    }

    newBook->next = current->next;
    current->next = newBook;
}

void trim_newline(char* s)
{
    if (!s) return;
    s[strcspn(s, "\r\n")] = '\0';
}

void printTable(const Book* head)
{
    const int authorW = 25;
    const int titleW = 30;
    const int yearW = 5;
    const int pagesW = 7;
    const int priceW = 10;

    cout << "\n";
    printf("%-*s %-*s %*s %*s %*s\n",
        authorW, "Author",
        titleW, "Title",
        yearW, "Year",
        pagesW, "Pages",
        priceW, "Price");

    int width = authorW + titleW + yearW + pagesW + priceW + 4;
    for (int i = 0; i < width; i++) cout << '-';
    cout << '\n';

    int count = 0;

    while (head) {
        printf("%-*s %-*s %*d %*d %*.2f\n",
            authorW, head->author,
            titleW, head->title,
            yearW, head->year,
            pagesW, head->pages,
            priceW, head->price);

        head = head->next;
        count++;
    }

    cout << "\ncount of records: " << count << "\n";
}

void find3MinPages(Book* head)
{
    Book* min1 = nullptr, * min2 = nullptr, * min3 = nullptr;

    while (head) {
        if (!min1 || head->pages < min1->pages) {
            min3 = min2;
            min2 = min1;
            min1 = head;
        }
        else if (!min2 || head->pages < min2->pages) {
            min3 = min2;
            min2 = head;
        }
        else if (!min3 || head->pages < min3->pages) {
            min3 = head;
        }

        head = head->next;
    }

    cout << "\nBooks with the three minimum page counts:\n";
    if (min1) cout << "1. " << min1->title << " (" << min1->pages << " pages)\n";
    if (min2) cout << "2. " << min2->title << " (" << min2->pages << " pages)\n";
    if (min3) cout << "3. " << min3->title << " (" << min3->pages << " pages)\n";
}

float calcAvgPages(Book* head)
{
    int sum = 0, count = 0;

    while (head) {
        sum += head->pages;
        count++;
        head = head->next;
    }

    return (count == 0) ? 0.0f : (float)sum / count;
}

void deleteLessThanAvg(Book** head, float avg)
{
    while (*head && (*head)->pages < avg) {
        Book* temp = *head;
        *head = (*head)->next;
        delete temp;
    }

    Book* current = *head;

    while (current && current->next) {
        if (current->next->pages < avg) {
            Book* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else {
            current = current->next;
        }
    }
}

void freeBookList(Book* head)
{
    while (head) {
        Book* next = head->next;
        delete head;
        head = next;
    }
}

void swap2Books(Book* a, Book* b)
{
    if (!a || !b) return;

    Book tempData = *a;

    strcpy(a->author, b->author);
    strcpy(a->title, b->title);
    a->year = b->year;
    a->pages = b->pages;
    a->price = b->price;

    strcpy(b->author, tempData.author);
    strcpy(b->title, tempData.title);
    b->year = tempData.year;
    b->pages = tempData.pages;
    b->price = tempData.price;
}
