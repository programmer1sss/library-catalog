#include "library.h"
#include "book.h"
#include "Periodical.h"
#include "Newspaper.h"
#include <iomanip>  

void Library::save(std::ostream& os) const {
    for (const auto& p : items_) {
        if (auto* b = dynamic_cast<Book*>(p.get())) {
            os << "BOOK " << *b << '\n';
        } else if (auto* m = dynamic_cast<Periodical*>(p.get())) {
            os << "PERIODICAL " << *m << '\n';
        } else if (auto* n = dynamic_cast<Newspaper*>(p.get())) {
            os << "NEWSPAPER " << *n << '\n';
        }
    }
}

void Library::load(std::istream& is) {
    items_.clear();
    std::string kind;
    while (is >> kind) {
        if (kind == "BOOK") {
            Book b;
            if (is >> b) items_.push_back(std::make_unique<Book>(std::move(b)));
        } else if (kind == "PERIODICAL") {
            std::string id, title, freq;
            int year = 0, issue = 0;
            if (!(is >> id)) break;
            if (!(is >> std::quoted(title))) break;
            if (!(is >> year)) break;
            if (!(is >> issue)) break;
            if (!(is >> std::quoted(freq))) break;
            try {
                items_.push_back(std::make_unique<Periodical>(id, title, year, issue, freq));
            } catch (...) {
                is.setstate(std::ios::failbit);
                break;
            }
        } else if (kind == "NEWSPAPER") {
            std::string id, title, date;
            int year = 0, pages = 0;
            if (!(is >> id)) break;
            if (!(is >> std::quoted(title))) break;
            if (!(is >> year)) break;
            if (!(is >> std::quoted(date))) break;
            if (!(is >> pages)) break;
            try {
                items_.push_back(std::make_unique<Newspaper>(id, title, year, date, pages));
            } catch (...) {
                is.setstate(std::ios::failbit);
                break;
            }
        } else {
            is.setstate(std::ios::failbit);
            break;
        }
    }
}