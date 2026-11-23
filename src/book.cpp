#include "book.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <utility>

// ── Конструктори ──
Book::Book()
    : LibraryItem("(no-id)", "(untitled)", 1450),
      author_(""),
      isbn_(""),
      totalCopies_(0),
      available_(0)
{
    std::cout << "Book ctor (default)\n";
}

Book::Book(std::string inventoryId,
           std::string title,
           std::string author,
           std::string isbn,
           int year,
           int totalCopies)
    : LibraryItem(std::move(inventoryId), std::move(title), year),
      author_(std::move(author)),
      isbn_(std::move(isbn)),
      totalCopies_(totalCopies),
      available_(totalCopies)
{
    std::cout << "Book ctor\n";

    if (!isbn_.empty() && !isValidIsbn(isbn_)) {
        throw std::invalid_argument("Book: invalid ISBN (expected 13 digits)");
    }
    if (totalCopies_ < 0) {
        throw std::invalid_argument("Book: totalCopies must be >= 0");
    }
}

Book::Book(std::string inventoryId, std::string title, int year)
    : Book(std::move(inventoryId), std::move(title), std::string{}, std::string{}, year, 0)
{
}

Book::~Book() {
    std::cout << "Book dtor\n";
}

// ── Гетери ──
const std::string& Book::getAuthor() const { return author_; }
const std::string& Book::getIsbn() const { return isbn_; }
int Book::getTotalCopies() const { return totalCopies_; }
int Book::getAvailableCopies() const { return available_; }

int Book::lentOut() const { return totalCopies_ - available_; }
bool Book::isAvailable() const { return available_ > 0; }
bool Book::isOlderThan(int y) const { return getYear() < y; }

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
    return !getTitle().empty() &&
           getYear() >= 1450 && getYear() <= 2026 &&
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

// ── Виведення / введення Book (без змін у логіці) ──
std::ostream& operator<<(std::ostream& os, const Book& b) {
    const auto saved = os.flags();
    os << b.getAuthor() << ' '
       << std::quoted(b.getTitle()) << ' '
       << b.getYear() << ' '
       << b.getAvailableCopies() << '/' << b.getTotalCopies();
    os.flags(saved);
    return os;
}

std::istream& operator>>(std::istream& is, Book& b) {
    is >> std::ws;
    if (!is) return is;

    std::string author;
    char ch;
    while (is.get(ch)) {
        if (ch == '"') {
            is.unget();
            break;
        }
        author += ch;
    }
    while (!author.empty() && author.back() == ' ') author.pop_back();

    if (author.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::string title;
    if (!(is >> std::quoted(title))) return is;

    int year = 0;
    if (!(is >> year)) return is;

    int available = 0, total = 0;
    char slash = '\0';
    if (!(is >> available >> slash >> total)) return is;

    if (slash != '/') {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (title.empty() || year < 1450 || year > 2026
        || total < 0 || available < 0 || available > total) {
        is.setstate(std::ios::failbit);
        return is;
    }

    // Тут створюємо Book з новим inventoryId — оскільки з потоку його немає,
    // використаємо щось унікальне. Для прикладу можна взяти ISBN як id.
    b = Book("id-" + title, title, author, "", year, total);

    int toLend = total - available;
    for (int i = 0; i < toLend; ++i) b.lend();
    return is;
}