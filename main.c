#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include "func.h"

using namespace std;

#define SIZE 100

int main()
{
    ifstream file("books.txt");
    if (!file) {
        cout << "Error opening file!\n";
        return 1;
    }

    Book* head = nullptr;

    char author[SIZE];
    char title[SIZE];
    int year, pages;
    float price;

    while (
        file.getline(author, SIZE) &&
        file.getline(title, SIZE) &&
        (file >> year) &&
        (file >> pages) &&
        (file >> price)
        ) {
        file.ignore();

        trim_newline(author);
        trim_newline(title);

        insertSorted(&head,
            createBook(author, title, year, pages, price));
    }

    file.close();

    cout << "\nBooks read from file:\n";
    printTable(head);

    cout << "\nBooks sorted by year (already sorted by insert):\n";
    printTable(head);

    find3MinPages(head);

    float avg = calcAvgPages(head);
    printf("\nAverage pages: %.2f\n", avg);

    deleteLessThanAvg(&head, avg);

    cout << "\nBooks with pages >= average:\n";
    printTable(head);

    if (head && head->next)
        swap2Books(head, head->next);

    cout << "\nBooks after swapping the first two:\n";
    printTable(head);

    freeBookList(head);

    cout << "\nMemory freed successfully.\n";
    return 0;
}
