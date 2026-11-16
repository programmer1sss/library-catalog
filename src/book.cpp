#include "book.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <utility>

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
}

Book::Book(std::string title, int year)
    : Book(std::move(title), std::string{}, std::string{}, year, 0) {}

Book::~Book() = default;

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

std::ostream& operator<<(std::ostream& os, const Book& b) {
    const auto saved = os.flags();
    os << b.getAuthor() << ' '
       << std::quoted(b.getTitle()) << ' '
       << b.getYear() << ' '
       << b.getAvailableCopies() << '/' << b.getTotalCopies();
    os.flags(saved);
    return os;
}

// ── ВИПРАВЛЕНИЙ оператор введення ──
std::istream& operator>>(std::istream& is, Book& b) {
    // 1. Пропускаємо провідні пробіли
    is >> std::ws;
    if (!is) return is;

    // 2. Читаємо автора до першої лапки (автор може містити пробіли)
    std::string author;
    char ch;
    while (is.get(ch)) {
        if (ch == '"') {
            is.unget();        // повертаємо лапку назад — її прочитає std::quoted
            break;
        }
        author += ch;
    }
    // Прибираємо пробіл перед лапкою
    while (!author.empty() && author.back() == ' ') {
        author.pop_back();
    }

    if (author.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    // 3. Читаємо назву в лапках
    std::string title;
    if (!(is >> std::quoted(title))) return is;

    // 4. Рік
    int year = 0;
    if (!(is >> year)) return is;

    // 5. available/total
    int available = 0, total = 0;
    char slash = '\0';
    if (!(is >> available >> slash >> total)) return is;
    if (slash != '/') {
        is.setstate(std::ios::failbit);
        return is;
    }

    // 6. Перевірки
    if (title.empty() || year < 1450 || year > 2026
        || total < 0 || available < 0 || available > total) {
        is.setstate(std::ios::failbit);
        return is;
    }

    // 7. Лише тепер змінюємо об'єкт
    b = Book(title, author, "", year, total);
    int toLend = total - available;
    for (int i = 0; i < toLend; ++i) {
        b.lend();
    }
    return is;
}