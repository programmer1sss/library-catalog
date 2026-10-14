#include "book.h"

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
      available_(totalCopies)
{
}

const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }
const std::string& Book::getIsbn() const { return isbn_; }
int Book::getYear() const { return year_; }
int Book::getTotalCopies() const { return totalCopies_; }
int Book::getAvailableCopies() const { return available_; }

int Book::lentOut() const {
    return totalCopies_ - available_;
}

bool Book::isAvailable() const {
    return available_ > 0;
}

bool Book::isOlderThan(int year) const {
    return year_ < year;
}

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

// Перевірка інваріанта — буквально повторює 5 пунктів із коментаря над класом,
// по одній умові на пункт, у тому самому порядку.
bool Book::checkInvariant() const {
    return !title_.empty() &&                                        // 1
           year_ >= 1450 && year_ <= 2026 &&                         // 2
           (isbn_.empty() || isValidIsbn(isbn_)) &&                  // 3
           totalCopies_ >= 0 &&                                      // 4
           available_ >= 0 && available_ <= totalCopies_;            // 5
}

// Допоміжний метод: ISBN або порожній, або містить рівно 13 цифр
bool Book::isValidIsbn(const std::string& isbn) {
    if (isbn.size() != 13) {
        return false;
    }
    for (char c : isbn) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}
