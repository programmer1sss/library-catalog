#include "library.h"

void Library::save(std::ostream& os) const {
    for (const auto& b : books_) {
        os << b << '\n';
    }
}

void Library::load(std::istream& is) {
    books_.clear();
    Book temp;
    while (is >> temp) {
        books_.push_back(temp);
    }
}