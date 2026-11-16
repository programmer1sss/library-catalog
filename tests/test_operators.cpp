#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Money.h"
#include "book.h"

// ────────────────────────────────────────────────────────────
// 1. Комутативність додавання сум
// ────────────────────────────────────────────────────────────
TEST(MoneyOperators, AdditionIsCommutative) {
    Money a(10, 50);
    Money b(25, 25);
    EXPECT_EQ(a + b, b + a);
}

// ────────────────────────────────────────────────────────────
// 2. Узгодженість + і +=
// ────────────────────────────────────────────────────────────
TEST(MoneyOperators, PlusEqualsMatchesPlus) {
    Money a(10, 50);
    Money b(25, 25);
    
    Money sum1 = a + b;
    
    Money sum2 = a;
    sum2 += b;
    
    EXPECT_EQ(sum1, sum2);
}

// ────────────────────────────────────────────────────────────
// 3. Рефлексивність та симетричність ==
// ────────────────────────────────────────────────────────────
TEST(MoneyOperators, EqualityIsReflexiveAndSymmetric) {
    Money a(10, 50);
    Money b(10, 50);
    Money c(20, 0);
    
    // Рефлексивність
    EXPECT_TRUE(a == a);
    
    // Симетричність
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
    
    // Нерівність
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(c != a);
}

// ────────────────────────────────────────────────────────────
// 4. Антисиметричність < (якщо a < b, то !(b < a))
// ────────────────────────────────────────────────────────────
TEST(MoneyOperators, LessThanIsAntisymmetric) {
    Money a(10, 0);
    Money b(20, 0);
    
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(a < a); // строгий порядок
}

// ────────────────────────────────────────────────────────────
// 5. Коректність сортування вектора
// ────────────────────────────────────────────────────────────
TEST(BookOperators, SortingVector) {
    std::vector<Book> books;
    books.emplace_back("B Title", "B Author", "9780000000001", 2000, 1);
    books.emplace_back("A Title", "A Author", "9780000000002", 1990, 1);
    books.emplace_back("C Title", "C Author", "9780000000003", 2010, 1);

    std::sort(books.begin(), books.end());

    EXPECT_EQ(books[0].getAuthor(), "A Author");
    EXPECT_EQ(books[1].getAuthor(), "B Author");
    EXPECT_EQ(books[2].getAuthor(), "C Author");
}

// ────────────────────────────────────────────────────────────
// 6. Збіг результату operator<< з очікуваним рядком
// ────────────────────────────────────────────────────────────
TEST(StreamOperators, BookOutputMatchesExpected) {
    Book b("1984", "George Orwell", "9780451524935", 1949, 3);
    b.lend(); // доступно 2/3

    std::ostringstream os;
    os << b;
    EXPECT_EQ(os.str(), "George Orwell \"1984\" 1949 2/3");
}

TEST(StreamOperators, MoneyOutputMatchesExpected) {
    Money m(12, 50);
    std::ostringstream os;
    os << m;
    EXPECT_EQ(os.str(), "12.50");
}

// ────────────────────────────────────────────────────────────
// 7. Успішне читання коректного рядка
// ────────────────────────────────────────────────────────────
TEST(StreamOperators, ReadValidBook) {
    std::istringstream in("George Orwell \"1984\" 1949 2/3");
    Book b;
    EXPECT_TRUE(static_cast<bool>(in >> b));
    EXPECT_EQ(b.getAuthor(), "George Orwell");
    EXPECT_EQ(b.getTitle(), "1984");
    EXPECT_EQ(b.getYear(), 1949);
    EXPECT_EQ(b.getAvailableCopies(), 2);
    EXPECT_EQ(b.getTotalCopies(), 3);
}

TEST(StreamOperators, ReadValidMoney) {
    std::istringstream in("12.50");
    Money m;
    EXPECT_TRUE(static_cast<bool>(in >> m));
    EXPECT_EQ(m, Money(12, 50));
}

// ────────────────────────────────────────────────────────────
// 8. Виставлення failbit на зіпсованому рядку
// ────────────────────────────────────────────────────────────
TEST(StreamOperators, ReadInvalidBookSetsFailbit) {
    std::istringstream in("George Orwell \"1984\" nineteenth 2/3");
    Book b;
    EXPECT_FALSE(static_cast<bool>(in >> b));
    EXPECT_TRUE(in.fail());
}

TEST(StreamOperators, ReadInvalidMoneySetsFailbit) {
    std::istringstream in("12.abc");
    Money m;
    EXPECT_FALSE(static_cast<bool>(in >> m));
    EXPECT_TRUE(in.fail());
}