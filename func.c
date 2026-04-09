#include "func.h"
#include <vector>
//functions for book management
bool isValidAuthor(const std::string& author) {
    if (author.empty() || author.length() > 50) return false;
    for (size_t i = 0; i < author.length(); ++i) {
        unsigned char c = author[i];
        if (!std::isalpha(c) && !std::isspace(c) && c != '-' && c != '\'')
            return false;
    }
    return true;
}
std::string trim(const std::string& s) {
    int start = 0;
    while (start < (int)s.length() && std::isspace(s[start])) start++;
    int end = (int)s.length() - 1;
    while (end >= start && std::isspace(s[end])) end--;
    if (start > end) return "";
    return s.substr(start, end - start + 1);
}
std::string replaceCommaWithDot(const std::string& s) {
    std::string result = s;
    for (char& ch : result) {
        if (ch == ',') {
            ch = '.';
        }
    }
    return result;
}

bool isValidLength(const std::string& s, size_t maxLen) {
    return !s.empty() && s.length() <= maxLen;
}

bool isValidTitle(const std::string& title) {
    if (title.empty() || title.length() > 50) return false;
    for (char ch : title) {
        unsigned char c = (unsigned char)ch;
        if (!std::isalnum(c) && ch != ' ' && ch != '-' && ch != '\'')
            return false;
    }
    return true;
}
bool parseAndValidateYear(const std::string& s, int& year) {
    std::istringstream iss(s);
    std::string extra;

    if (!(iss >> year) || (iss >> extra)) {
        return false;
    }

    return year > 0 && year <= 2026;
}
bool parseAndValidatePages(const std::string& s, int& pages) {
    std::istringstream iss(s);
    std::string extra;

    if (!(iss >> pages) || (iss >> extra)) {
        return false;
    }

    return pages > 0 && pages <= 10000;
}
bool parseAndValidatePrice(const std::string& s, float& price) {
    std::istringstream iss(s);
    std::string extra;

    if (!(iss >> price) || (iss >> extra)) {
        return false;
    }

    return price > 0 && price <= 50000;
}
bool readNonEmptyLine(std::ifstream& f, std::string& out) {
    while (std::getline(f, out)) {
        out = trim(out);
        if (!out.empty()) return true;
    }
    return false;
}
// helper
bool looksLikeAuthor(const std::string& line) {
    std::string trimmed = trim(line);
    if (trimmed.empty()) return false;
    for (char ch : trimmed) {
        unsigned char c = (unsigned char)ch;
        if (!std::isalpha(c) && !std::isspace(c) && c != '-' && c != '\'') return false;
    }
    return true;
}





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
    bool anyrecords = false;

    std::vector<std::string> lines;
    std::string line;


    while (std::getline(file, line)) {
        line = trim(line);
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    if (lines.empty()) {
        std::cout << "Notice: file is empty or contains no valid records.\n";
        return nullptr;
    }

    size_t i = 0;
    while (i < lines.size()) {
        std::string author = lines[i];

        if (!looksLikeAuthor(author)) {
            i++;
            continue;
        }

        if (i + 4 >= lines.size()) {
            std::cerr << "Warning: incomplete record skipped.\n";
            break;
        }

        std::string title = lines[i + 1];
        std::string yearLine = lines[i + 2];
        std::string pagesLine = lines[i + 3];
        std::string priceLine = replaceCommaWithDot(lines[i + 4]);

        int year, pages, tempInt;
        float price, tempFloat;
       
        if (parseAndValidateYear(title, tempInt)) {
            std::cerr << "Warning: title is missing. Record skipped.\n";
            i += 1; 
            continue;
        }

        if (!parseAndValidateYear(yearLine, tempInt) &&
            parseAndValidatePages(yearLine, tempInt) &&
            parseAndValidatePrice(replaceCommaWithDot(pagesLine), tempFloat)) {
            std::cerr << "Warning: year is missing. Record skipped.\n";
            i += 2; 
            continue;
        }

        if (parseAndValidateYear(yearLine, tempInt) &&
            !parseAndValidatePages(pagesLine, tempInt) &&
            parseAndValidatePrice(replaceCommaWithDot(pagesLine), tempFloat)) {
            std::cerr << "Warning: pages are missing. Record skipped.\n";
            i += 3; 
            continue;
        }


        if (parseAndValidateYear(yearLine, tempInt) &&
            parseAndValidatePages(pagesLine, tempInt) &&
            looksLikeAuthor(priceLine)) {
            std::cerr << "Warning: price is missing. Record skipped.\n";
            i += 4; // author + title + year + pages
            continue;
        }


        if (!isValidAuthor(author)) {
            std::cerr << "Warning: invalid author. Record skipped.\n";
            i += 1;
            continue;
        }

        if (!isValidTitle(title)) {
            std::cerr << "Warning: invalid title. Record skipped.\n";
            i += 2;
            continue;
        }

        if (!parseAndValidateYear(yearLine, year)) {
            std::cerr << "Warning: invalid year. Record skipped.\n";
            i += 3;
            continue;
        }

        if (!parseAndValidatePages(pagesLine, pages)) {
            std::cerr << "Warning: invalid pages. Record skipped.\n";
            i += 4;
            continue;
        }

        if (!parseAndValidatePrice(priceLine, price)) {
            std::cerr << "Warning: invalid price. Record skipped.\n";
            i += 5;
            continue;
        }


        insertSorted(&head, createBook(author, title, year, pages, price));
        anyrecords = true;

        i += 5;
    }

    if (!anyrecords) {
        std::cout << "Notice: file is empty or contains no valid records.\n";
    }

    return head;
}
//
void writeBooksToFile(const std::string& filename, Book* head) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: cannot write to file " << filename << "\n";
        return;
    }

    file.imbue(std::locale::classic()); 

    if (!head) {
        std::cout << "Notice: nothing to write, list is empty.\n";
        return;
    }

    while (head) {
        file << head->author << "\n"
            << head->title << "\n"
            << head->year << "\n"
            << head->pages << "\n"
            << std::fixed << std::setprecision(2) << head->price << "\n";
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
    if (!head) {
        std::cout << "\nThe list is empty.\n";
        return;
    }

    // Перевірка: чи всі книги мають однакову кількість сторінок
    int firstPages = head->pages;
    bool allSame = true;
    const Book* temp = head;

    while (temp) {
        if (temp->pages != firstPages) {
            allSame = false;
            break;
        }
        temp = temp->next;
    }

    if (allSame) {
        std::cout << "\nAll books have the same number of pages: "
            << firstPages << " pages.\n";
        return;
    }

    const Book* min1 = nullptr, * min2 = nullptr, * min3 = nullptr;

    while (head) {
        if (!min1 || head->pages < min1->pages) {
            min3 = min2;
            min2 = min1;
            min1 = head;
        }
        else if (head != min1 && (!min2 || head->pages < min2->pages)) {
            min3 = min2;
            min2 = head;
        }
        else if (head != min1 && head != min2 && (!min3 || head->pages < min3->pages)) {
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
	bool anyDeleted = false;
    while (*head && (*head)->pages < avg) {
        Book* tmp = *head;
        *head = (*head)->next;
        delete tmp;
		anyDeleted = true;
    }
    Book* current = *head;
    while (current && current->next) {
        if (current->next->pages < avg) {
            Book* tmp = current->next;
            current->next = tmp->next;
            delete tmp;
			anyDeleted = true;
        }
        else {
            current = current->next;
        }
    }
    if (!anyDeleted) {
        std::cout << "\nNo books were deleted, all have pages >= average (" << avg << " pages).\n";
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
