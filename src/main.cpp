#include <iostream>
#include <vector>
#include "book.h"

int main() {
    std::cout << "Каталог книг" << std::endl;
    std::cout << "------------" << std::endl;

    std::vector<Book> catalog = {
        Book("1984", "George Orwell", "9780451524935", 1949, 3),
        Book("The Hobbit", "J.R.R. Tolkien", "9780547928227", 1937, 2),
        Book("Clean Code", "Robert C. Martin", "9780132350884", 2008, 1),
        Book("The Pragmatic Programmer", "Andrew Hunt", "9780201616224", 1999, 4)
    };

    for (const auto& book : catalog) {
        std::cout << "Назва: " << book.getTitle()
                  << " | Автор: " << book.getAuthor()
                  << " | ISBN: " << book.getIsbn()
                  << " | Рік: " << book.getYear()
                  << " | Усього: " << book.getTotalCopies()
                  << " | Доступно: " << book.getAvailableCopies()
                  << " | Видано: " << book.lentOut()
                  << " | Старша за 2000? "
                  << (book.isOlderThan(2000) ? "так" : "ні")
                  << std::endl;
    }

    return 0;
}
