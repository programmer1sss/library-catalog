#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "book.h"

class Library {
public:
    Library() = default;

    void addBook(Book b) { books_.push_back(std::move(b)); }

    std::size_t size() const { return books_.size(); }
    Book&       at(std::size_t i)       { return books_.at(i); }
    const Book& at(std::size_t i) const { return books_.at(i); }

    const std::vector<Book>& books() const { return books_; }

    // ── Методи для Кроку 6 ──
    void save(std::ostream& os) const;
    void load(std::istream& is);

private:
    std::vector<Book> books_;
};