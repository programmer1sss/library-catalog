#include "book.h"

// Конструктор: поля ініціалізуються у списку ініціалізації
Book::Book(const std::string& title,
           const std::string& author,
           const std::string& isbn,
           int year,
           int totalCopies)
    : title_(title),
      author_(author),
      isbn_(isbn),
      year_(year),
      totalCopies_(totalCopies),
      available_(totalCopies)   // на старті всі примірники доступні
{
}

const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }
const std::string& Book::getIsbn() const { return isbn_; }
int Book::getYear() const { return year_; }
int Book::getTotalCopies() const { return totalCopies_; }
int Book::getAvailableCopies() const { return available_; }

// Похідні величини — обчислюються з полів, не зберігаються
int Book::lentOut() const {
    return totalCopies_ - available_;
}

bool Book::isAvailable() const {
    return available_ > 0;
}

bool Book::isOlderThan(int year) const {
    return year_ < year;
}

// Методи обліку
void Book::lend() {
    if (available_ > 0) {
        --available_;
    }
}

void Book::returnCopy() {
    if (available_ < totalCopies_) {
        ++available_;
    }
}
