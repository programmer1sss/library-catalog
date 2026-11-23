#pragma once

#include <string>
#include <tuple>
#include <iostream>
#include "LibraryItem.h"
#include "TagList.h"

class Book final : public LibraryItem {
public:
    Book();
    Book(std::string inventoryId,
         std::string title,
         std::string author,
         std::string isbn,
         int year,
         int totalCopies);
    Book(std::string inventoryId, std::string title, int year);

    // Сумісний конструктор без inventoryId (для тестів ЛР5).
    // inventoryId генерується як "id-" + title.
    Book(std::string title,
         std::string author,
         std::string isbn,
         int year,
         int totalCopies)
        : Book("id-" + title, std::move(title), std::move(author),
               std::move(isbn), year, totalCopies) {}

    ~Book() override = default;

    // ── Власний describe() у Book ──
    void describe() const {
        std::cout << "Книга: " << getTitle()
                  << " (автор: " << author_
                  << ", ISBN: " << isbn_ << ")\n";
    }

    // ✅ РЯТУЄ ВІД ПРИХОВУВАННЯ: тепер обидві версії LibraryItem::describe
    //    і Book::describe доступні через Book.
    using LibraryItem::describe;

    const std::string& getAuthor() const;
    const std::string& getIsbn() const;
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
    std::string author_;
    std::string isbn_;
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

// ── Виведення / введення Book ──
std::ostream& operator<<(std::ostream& os, const Book& b);
std::istream& operator>>(std::istream& is, Book& b);