#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
//створити книгу
Book* createBook(const char* author, const char* title, int year, int pages, float price) {
    Book* b = malloc(sizeof(Book));
    if (!b) return NULL;
    strncpy_s(b->author, sizeof(b->author), author, _TRUNCATE);
    strncpy_s(b->title, sizeof(b->title), title, _TRUNCATE);
    b->year = year;
    b->pages = pages;
    b->price = price;
    b->next = NULL;

    return b;
}
//сортування встаавкою
void insertSorted(Book** head, Book* b) {
    if (*head == NULL || (*head)->year >= b->year) {
        b->next = *head;
        *head = b;
        return;
    }

    Book* cur = *head;
    while (cur->next && cur->next->year < b->year)
        cur = cur->next;

    b->next = cur->next;
    cur->next = b;
}

void trim_newline(char* s) {
    if (!s) return;
    s[strcspn(s, "\r\n")] = '\0';
}

void printTable(const Book* head) {
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

        count++;
        head = head->next;
    }
    printf("\ncount of records: %d\n", count);
}

void find3MinPages(Book* head) {
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

float calcAvgPages(Book* head) {
    int sum = 0, count = 0;

    while (head) {
        sum += head->pages;
        count++;
        head = head->next;
    }
    return (count == 0) ? 0 : (float)sum / count;
}

void deleteLessThanAvg(Book** head, float avg) {
    while (*head && (*head)->pages < avg) {
        Book* tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }

    Book* cur = *head;
    while (cur && cur->next) {
        if (cur->next->pages < avg) {
            Book* tmp = cur->next;
            cur->next = cur->next->next;
            free(tmp);
        }
        else {
            cur = cur->next;
        }
    }
}

void freeBookList(Book* head) {
    while (head) {
        Book* next = head->next;
        free(head);
        head = next;
    }
}
void swap2Books(Book* a, Book* b) {
    Book temp = *a;
    *a = *b;
    *b = temp;
    Book* tempNext = a->next;
    a->next = b->next;
    b->next = tempNext;
}