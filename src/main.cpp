#include <iostream>
#include "Book.h"

int main() {
    std::cout << "Варіант: Library Catalog" << std::endl;

    Book b("1984", "George Orwell", 1949, 328);

    std::cout << "Книга: " << b.getTitle()
              << ", автор: " << b.getAuthor()
              << ", рік: " << b.getYear()
              << ", сторінок: " << b.getPages() << std::endl;

    std::cout << "Старша за 2000 рік? "
              << (b.isOlderThan(2000) ? "так" : "ні") << std::endl;

    return 0;
}
