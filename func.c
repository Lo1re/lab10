#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

Book* createBook(const char* author, const char* title,
    int year, int pages, float price)
{
    Book* newBook = (Book*)malloc(sizeof(Book));
    if (!newBook) return NULL;

    strncpy_s(newBook->author, sizeof(newBook->author), author, _TRUNCATE);
    strncpy_s(newBook->title, sizeof(newBook->title), title, _TRUNCATE);

    newBook->year = year;
    newBook->pages = pages;
    newBook->price = price;
    newBook->next = NULL;

    return newBook;
}

void insertSorted(Book** head, Book* newBook)
{
    if (!newBook) return;

    if (*head == NULL || (*head)->year >= newBook->year) {
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

    printf("\n%-*s %-*s %*s %*s %*s\n",
        authorW, "Author",
        titleW, "Title",
        yearW, "Year",
        pagesW, "Pages",
        priceW, "Price");

    int width = authorW + titleW + yearW + pagesW + priceW + 4;
    for (int i = 0; i < width; i++) putchar('-');
    putchar('\n');

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

    printf("\ncount of records: %d\n", count);
}

void find3MinPages(Book* head)
{
    Book* min1 = NULL, * min2 = NULL, * min3 = NULL;

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

    printf("\nBooks with the three minimum page counts:\n");
    if (min1) printf("1. %s (%d pages)\n", min1->title, min1->pages);
    if (min2) printf("2. %s (%d pages)\n", min2->title, min2->pages);
    if (min3) printf("3. %s (%d pages)\n", min3->title, min3->pages);
}

float calcAvgPages(Book* head)
{
    int sum = 0, count = 0;

    while (head) {
        sum += head->pages;
        count++;
        head = head->next;
    }

    return (count == 0) ? 0 : (float)sum / count;
}

void deleteLessThanAvg(Book** head, float avg)
{
    while (*head && (*head)->pages < avg) {
        Book* temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    Book* current = *head;

    while (current && current->next) {
        if (current->next->pages < avg) {
            Book* temp = current->next;
            current->next = current->next->next;
            free(temp);
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
        free(head);
        head = next;
    }
}

/* Безпечний swap — міняємо тільки дані */
void swap2Books(Book* a, Book* b)
{
    if (!a || !b) return;

    char author[50];
    char title[50];
    int year;
    int pages;
    float price;

    strcpy_s(author, sizeof(author), a->author);
    strcpy_s(title, sizeof(title), a->title);
    year = a->year;
    pages = a->pages;
    price = a->price;

    strcpy_s(a->author, sizeof(a->author), b->author);
    strcpy_s(a->title, sizeof(a->title), b->title);
    a->year = b->year;
    a->pages = b->pages;
    a->price = b->price;

    strcpy_s(b->author, sizeof(b->author), author);
    strcpy_s(b->title, sizeof(b->title), title);
    b->year = year;
    b->pages = pages;
    b->price = price;
}
