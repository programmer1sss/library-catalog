#pragma once

#include <string>
#include <tuple>
#include <iostream> // Для std::ostream
#include "TagList.h"

class Book {
public:
    // ... (ваші конструктори та методи без змін) ...
    Book();
    Book(std::string title, std::string author, std::string isbn, int year, int totalCopies);
    Book(std::string title, int year);
    ~Book();

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    const std::string& getIsbn() const;
    int getYear() const;
    int getTotalCopies() const;
    int getAvailableCopies() const;

    const TagList& getTags() const { return tags_; }
    void addTag(const std::string& tag) { tags_.add(tag); }

    int lentOut() const;
    bool isAvailable() const;
    bool isOlderThan(int year) const;
    bool lend();
    bool returnCopy();
    bool addCopies(int n);
    bool checkInvariant() const;

private:
    std::string title_ = "(untitled)";
    std::string author_;
    std::string isbn_;
    int year_ = 1450;
    int totalCopies_ = 0;
    int available_ = 0;
    TagList tags_{4};

    static bool isValidIsbn(const std::string& isbn);
};

// ── Порівняння Book ──
inline bool operator==(const Book& lhs, const Book& rhs) {
    return lhs.getIsbn() == rhs.getIsbn();
}
inline bool operator!=(const Book& lhs, const Book& rhs) { return !(lhs == rhs); }
inline bool operator<(const Book& lhs, const Book& rhs) {
    return std::make_tuple(lhs.getAuthor(), lhs.getTitle(), lhs.getYear())
         < std::make_tuple(rhs.getAuthor(), rhs.getTitle(), rhs.getYear());
}
inline bool operator>(const Book& lhs, const Book& rhs)  { return rhs < lhs; }
inline bool operator<=(const Book& lhs, const Book& rhs) { return !(rhs < lhs); }
inline bool operator>=(const Book& lhs, const Book& rhs) { return !(lhs < rhs); }

// ── Виведення Book ──
std::ostream& operator<<(std::ostream& os, const Book& b);