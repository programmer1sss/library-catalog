#include "book.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
int gLive = 0;
}

Book::Book()
    : Book("(untitled)", "", "", 1450, 0) {}

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

    ++gLive;
    std::clog << "ctor  " << title_ << "  live=" << gLive << '\n';
}

Book::Book(std::string title, int year)
    : Book(std::move(title), std::string{}, std::string{}, year, 0) {}

// Раніше тут були Book(Book&&) та operator=(Book&&).
// Для Rule of Zero ми їх видалили, щоб компілятор сам
// згенерував копіювання та переміщення.

Book::~Book() {
    --gLive;
    std::clog << "dtor  " << title_ << "  live=" << gLive << '\n';
}

const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }
const std::string& Book::getIsbn() const { return isbn_; }
int Book::getYear() const { return year_; }
int Book::getTotalCopies() const { return totalCopies_; }
int Book::getAvailableCopies() const { return available_; }

int Book::lentOut() const { return totalCopies_ - available_; }
bool Book::isAvailable() const { return available_ > 0; }
bool Book::isOlderThan(int y) const { return year_ < y; }

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