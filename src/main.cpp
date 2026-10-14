#include <iostream>
#include <vector>
#include "book.h"

// Функція приймає книгу за константним посиланням.
// Якщо якийсь гетер не позначено const — компілятор видасть помилку тут.
void print(const Book& b) {
    std::cout << "Назва: " << b.getTitle()
              << " | Автор: " << b.getAuthor()
              << " | ISBN: " << b.getIsbn()
              << " | Рік: " << b.getYear()
              << " | Усього: " << b.getTotalCopies()
              << " | Доступно: " << b.getAvailableCopies()
              << " | Видано: " << b.lentOut()
              << " | Є в наявності? "
              << (b.isAvailable() ? "так" : "ні")
              << " | Старша за 2000? "
              << (b.isOlderThan(2000) ? "так" : "ні")
              << std::endl;
}

int main() {
    std::cout << "Каталог книг" << std::endl;
    std::cout << "------------" << std::endl;

    std::vector<Book> catalog = {
        Book("1984", "George Orwell", "9780451524935", 1949, 3),
        Book("The Hobbit", "J.R.R. Tolkien", "9780547928227", 1937, 2),
        Book("Clean Code", "Robert C. Martin", "9780132350884", 2008, 1),
        Book("The Pragmatic Programmer", "Andrew Hunt", "9780201616224", 1999, 4)
    };

    // Виклик функції з const-посиланням
    for (const auto& book : catalog) {
        print(book);
    }

    return 0;
}
