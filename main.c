#include <iostream>
#include "func.h"

int main() {
    Book* head = readBooksFromFile("books.txt");
    if (!head) return 1;

    std::cout << "\nBooks read from file:\n";
    printTable(head);

    std::cout << "\nBooks sorted by year (already sorted by insert):\n";
    printTable(head);

    find3MinPages(head);

    float avg = calcAvgPages(head);
    std::cout << "\nAverage pages: " << avg << "\n";

    deleteLessThanAvg(&head, avg);
    std::cout << "\nBooks with pages >= average:\n";
    printTable(head);

    swap2Books(head, head->next);
    std::cout << "\nBooks after swapping the first two:\n";
    printTable(head);

    freeBookList(head);
    std::cout << "\nMemory freed successfully.\n";
    return 0;
}
