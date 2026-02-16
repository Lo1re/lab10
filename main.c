#include <iostream>
#include <fstream>
#include "func.h"

int main()
{
    Book* head = nullptr;

    std::ifstream fin("books.txt");

    if (fin) {
        std::string author, title;
        int year, pages;
        float price;

        while (std::getline(fin, author) &&
            std::getline(fin, title) &&
            fin >> year >> pages >> price)
        {
            fin.ignore();
            insertSorted(head,
                createBook(author, title, year, pages, price));
        }
    }

    std::cout << "\nBooks read from file:\n";
    printTable(head);

    int n;
    std::cout << "\nHow many books to add? ";
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; ++i)
        addBook(head);

    std::cout << "\nBooks after adding:\n";
    printTable(head);

    std::cout << "\nBooks starting with A:\n";
    printTitleStartsWithA(head);

    float avg = calcAvgPages(head);
    std::cout << "\nAverage pages: " << avg << "\n";

    deleteLessThanAvg(head, avg);

    std::cout << "\nBooks with pages >= average:\n";
    printTable(head);

    writeToFile(head, "result.txt");

    freeBookList(head);

    return 0;
}
