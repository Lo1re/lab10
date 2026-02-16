#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

#define SIZE 100

int main() {
    FILE* file = fopen("books.txt", "r");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    Book* head = NULL;
    char author[SIZE], title[SIZE];
    int year, pages;
    float price;

    while (
        fgets(author, SIZE, file) &&
        fgets(title, SIZE, file) &&
        fscanf(file, "%d", &year) == 1 &&
        fscanf(file, "%d", &pages) == 1 &&
        fscanf(file, "%f", &price) == 1
        ) {
        fgetc(file); // пропуск \n
        trim_newline(author);
        trim_newline(title);

        insertSorted(&head, createBook(author, title, year, pages, price));
    }

    fclose(file);

    printf("\nBooks read from file:\n");
    printTable(head);

    printf("\nBooks sorted by year (already sorted by insert):\n");
    printTable(head);

    find3MinPages(head);

    float avg = calcAvgPages(head);
    printf("\nAverage pages: %.2f\n", avg);

    deleteLessThanAvg(&head, avg);

    printf("\nBooks with pages >= average:\n");
    printTable(head);

        if (head && head->next)
            swap2Books(head, head->next);
    

    printf("\nBooks after swapping the first two:\n");
    printTable(head);
    if (head != NULL) {
        freeBookList(head);
    }

    printf("\nMemory freed successfully.\n");
    return 0;
}
