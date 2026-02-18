#include "func.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

// Створення книги
Book* createBook(const std::string& author, const std::string& title, int year, int pages, float price) {
    Book* newBook = new Book{ author, title, year, pages, price, nullptr };
    return newBook;
}

// Додавання у список у порядку спадання року
void insertSorted(Book** head, Book* newBook) {
    if (!*head || newBook->year > (*head)->year) {
        newBook->next = *head;
        *head = newBook;
        return;
    }
    Book* current = *head;
    while (current->next && current->next->year >= newBook->year)
        current = current->next;
    newBook->next = current->next;
    current->next = newBook;
}

// Вивід таблиці
void printTable(const Book* head) {
    std::cout << "\n" << std::left
        << std::setw(25) << "Author"
        << std::setw(30) << "Title"
        << std::setw(6) << "Year"
        << std::setw(7) << "Pages"
        << std::setw(10) << "Price" << "\n";
    std::cout << std::string(78, '-') << "\n";

    int count = 0;
    while (head) {
        std::cout << std::left
            << std::setw(25) << head->author
            << std::setw(30) << head->title
            << std::setw(6) << head->year
            << std::setw(7) << head->pages
            << std::fixed << std::setprecision(2)
            << std::setw(10) << head->price << "\n";
        head = head->next;
        count++;
    }
    std::cout << "Total records: " << count << "\n";
}

// Читання з файлу
Book* readBooksFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: cannot open file " << filename << "\n";
        return nullptr;
    }

    Book* head = nullptr;
    std::string author, title;
    int year, pages;
    float price;

    while (std::getline(file, author)) {
        if (!std::getline(file, title)) break;
        if (!(file >> year >> pages >> price)) {
            std::cerr << "Warning: invalid record skipped.\n";
            file.clear();
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // пропуск кінця рядка
        insertSorted(&head, createBook(author, title, year, pages, price));
    }

    return head;
}

// Запис у файл
void writeBooksToFile(const std::string& filename, Book* head) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: cannot write to file " << filename << "\n";
        return;
    }
    while (head) {
        file << head->author << "\n"
            << head->title << "\n"
            << head->year << " " << head->pages << " " << head->price << "\n";
        head = head->next;
    }
}

// Пошук книг, що починаються на "А"
void findBooksStartingWithA(const Book* head) {
    std::cout << "\nBooks starting with 'A':\n";
    while (head) {
        if (!head->title.empty() && (head->title[0] == 'A' || head->title[0] == 'А')) {
            std::cout << head->title << " (" << head->year << ")\n";
        }
        head = head->next;
    }
}

// Пошук трьох книг з мінімальною кількістю сторінок
void find3MinPages(const Book* head) {
    const Book* min1 = nullptr, * min2 = nullptr, * min3 = nullptr;
    while (head) {
        if (!min1 || head->pages < min1->pages) {
            min3 = min2; min2 = min1; min1 = head;
        }
        else if (!min2 || head->pages < min2->pages) {
            min3 = min2; min2 = head;
        }
        else if (!min3 || head->pages < min3->pages) {
            min3 = head;
        }
        head = head->next;
    }

    std::cout << "\nBooks with three minimum page counts:\n";
    if (min1) std::cout << "1. " << min1->title << " (" << min1->pages << " pages)\n";
    if (min2) std::cout << "2. " << min2->title << " (" << min2->pages << " pages)\n";
    if (min3) std::cout << "3. " << min3->title << " (" << min3->pages << " pages)\n";
}

// Середня кількість сторінок
float calcAvgPages(Book* head) {
    int sum = 0, count = 0;
    while (head) { sum += head->pages; count++; head = head->next; }
    return count ? static_cast<float>(sum) / count : 0.0f;
}

// Видалення книг з менше середньої сторінок
void deleteLessThanAvg(Book** head, float avg) {
    while (*head && (*head)->pages < avg) {
        Book* tmp = *head;
        *head = (*head)->next;
        delete tmp;
    }
    Book* current = *head;
    while (current && current->next) {
        if (current->next->pages < avg) {
            Book* tmp = current->next;
            current->next = tmp->next;
            delete tmp;
        }
        else {
            current = current->next;
        }
    }
}

// Swap перших двох книг
void swap2Books(Book* a, Book* b) {
    if (!a || !b) return;
    std::swap(*a, *b);
    std::swap(a->next, b->next);
}

// Звільнення пам'яті
void freeBookList(Book* head) {
    while (head) {
        Book* tmp = head;
        head = head->next;
        delete tmp;
    }
}
