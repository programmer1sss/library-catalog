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

// --- Гетери ---
const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }
const std::string& Book::getIsbn() const { return isbn_; }
int Book::getYear() const { return year_; }
int Book::getTotalCopies() const { return totalCopies_; }
int Book::getAvailableCopies() const { return available_; }

// --- Обчислювальні методи ---
int Book::lentOut() const {
    return totalCopies_ - available_;
}

bool Book::isAvailable() const {
    return available_ > 0;
}

bool Book::isOlderThan(int year) const {
    return year_ < year;
}

// --- Операції предметної області ---
bool Book::lend() {
    if (available_ <= 0) {
        return false;
    }
    --available_;
    return true;
}

bool Book::returnCopy() {
    if (available_ >= totalCopies_) {
        return false;
    }
    ++available_;
    return true;
}

bool Book::addCopies(int n) {
    if (n <= 0) {
        return false;
    }
    totalCopies_ += n;
    available_ += n;
    return true;
}

// --- Інваріант ---
bool Book::checkInvariant() const {
    return !title_.empty() &&
           year_ >= 1450 && year_ <= 2026 &&
           (isbn_.empty() || isValidIsbn(isbn_)) &&
           totalCopies_ >= 0 &&
           available_ >= 0 && available_ <= totalCopies_;
}

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
