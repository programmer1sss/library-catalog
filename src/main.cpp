#include <iostream>
#include <vector>
#include <string>
#include "Book.h"

int main() {
    std::cout << "Варіант: Library Catalog" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::vector<Book> items = {
        Book("1984",              "George Orwell",   1949, 328),
        Book("The Hobbit",        "J.R.R. Tolkien",  1937, 310),
        Book("Clean Code",        "Robert C. Martin", 2008, 464),
        Book("The Pragmatic Programmer", "Andrew Hunt", 1999, 352)
    };

    for (const auto& item : items) {
        std::cout << "Назва: "      << item.getTitle()
                  << " | Автор: "   << item.getAuthor()
                  << " | Рік: "     << item.getYear()
                  << " | Сторінок: " << item.getPages()
                  << " | Старша за 2000? "
                  << (item.isOlderThan(2000) ? "так" : "ні")
                  << std::endl;
    }

    return 0;
}
