#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include "Loan.h"
#include "Reader.h"
#include "book.h"

TEST(ReaderTest, NotInLibraryItemHierarchy) {
    Reader r("R-001", "Шевченко Тарас");
    // Наступний рядок НЕ скомпілюється (і це правильно):
    // LibraryItem* p = &r;   // ❌ Reader не є LibraryItem
    EXPECT_EQ(r.getCardNumber(), "R-001");
    EXPECT_EQ(r.getFullName(), "Шевченко Тарас");
}

TEST(LoanTest, ComposesLibraryItem) {
    Book book("INV-B1", "1984", "George Orwell", "9780451524935", 1949, 3);
    Loan loan("R-001", &book, "2024-05-01", "");

    EXPECT_EQ(loan.getReaderCard(), "R-001");
    ASSERT_NE(loan.getItem(), nullptr);
    EXPECT_EQ(loan.getItem()->getInventoryId(), "INV-B1");
    EXPECT_FALSE(loan.isReturned());
}

TEST(LoanTest, DoesNotOwnItem) {
    auto book = std::make_unique<Book>(
        "INV-B2", "The Hobbit", "Tolkien", "", 1937, 2);
    Loan loan("R-002", book.get(), "2024-05-02", "");
    EXPECT_EQ(loan.getItem()->getTitle(), "The Hobbit");
}

TEST(LoanTest, MarkReturned) {
    Book book("INV-B3", "Clean Code", "Martin", "", 2008, 1);
    Loan loan("R-003", &book, "2024-05-03", "");
    EXPECT_FALSE(loan.isReturned());
    loan.setReturnDate("2024-05-20");
    EXPECT_TRUE(loan.isReturned());
    EXPECT_EQ(loan.getReturnDate(), "2024-05-20");
}

TEST(ReaderTest, EqualityByFields) {
    Reader a("R-001", "Шевченко Тарас");
    Reader b("R-001", "Шевченко Тарас");
    Reader c("R-002", "Франко Іван");
    EXPECT_EQ(a.getCardNumber(), b.getCardNumber());
    EXPECT_EQ(a.getFullName(), b.getFullName());
    EXPECT_NE(a.getCardNumber(), c.getCardNumber());
}