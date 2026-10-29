#include "book.h"

#include <stdexcept>
#include <string>
#include <utility>   // std::move

Book::Book(std::string title,
           std::string author,
           std::string isbn,
           int year,
           int totalCopies)
    : title_(std::move(title)),
      author_(std::move(author)),
      isbn_(std::move(isbn)),
      year_(year),
      totalCopies_(totalCopies),
      available_(totalCopies)
{
    if (title_.empty()) {
        throw std::invalid_argument("Book: empty title");
    }
    if (year_ < 1450 || year_ > 2026) {
        throw std::out_of_range("Book: year out of range [1450, 2026]");
    }
    if (!isbn_.empty() && !isValidIsbn(isbn_)) {
        throw std::invalid_argument("Book: invalid ISBN (expected 13 digits)");
    }
    if (totalCopies_ < 0) {
        throw std::invalid_argument("Book: totalCopies must be >= 0");
    }
}

// --- Гетери ---
const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }
const std::string& Book::getIsbn() const { return isbn_; }
int Book::getYear() const { return year_; }
int Book::getTotalCopies() const { return totalCopies_; }
int Book::getAvailableCopies() const { return available_; }

// --- Обчислювальні методи ---
int Book::lentOut() const { return totalCopies_ - available_; }
bool Book::isAvailable() const { return available_ > 0; }
bool Book::isOlderThan(int year) const { return year_ < year; }

// --- Операції ---
bool Book::lend() {
    if (available_ <= 0) return false;
    --available_;
    return true;
}

bool Book::returnCopy() {
    if (available_ >= totalCopies_) return false;
    ++available_;
    return true;
}

bool Book::addCopies(int n) {
    if (n <= 0) return false;
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
    if (isbn.size() != 13) return false;
    for (char c : isbn) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}