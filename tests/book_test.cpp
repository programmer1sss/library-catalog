#include <gtest/gtest.h>
#include "book.h"

// ─────────────────────────────────────────────────────────────
// 1. Успішна зміна поля
//    addCopies(3) додає 3 примірники — обидва лічильники ростуть
// ─────────────────────────────────────────────────────────────
TEST(BookTest, SuccessfulAddCopies) {
  Book b("Кобзар", "Тарас Шевченко", "9789660335809", 1840, 2);

  EXPECT_TRUE(b.addCopies(3));
  EXPECT_EQ(b.getTotalCopies(), 5);
  EXPECT_EQ(b.getAvailableCopies(), 5);
  EXPECT_EQ(b.lentOut(), 0);
}

// ─────────────────────────────────────────────────────────────
// 2. Відхилення некоректного значення
//    addCopies(0) і addCopies(-5) мають повернути false
// ─────────────────────────────────────────────────────────────
TEST(BookTest, RejectsInvalidAddCopies) {
  Book b("Кобзар", "Тарас Шевченко", "9789660335809", 1840, 2);

  EXPECT_FALSE(b.addCopies(0));
  EXPECT_FALSE(b.addCopies(-5));
}

// ─────────────────────────────────────────────────────────────
// 3. Незмінність стану після відхилення
//    Після невдалого addCopies(-1) стан не змінюється
// ─────────────────────────────────────────────────────────────
TEST(BookTest, RejectedOperationKeepsState) {
  Book b("Кобзар", "Тарас Шевченко", "9789660335809", 1840, 2);

  int totalBefore    = b.getTotalCopies();
  int availableBefore = b.getAvailableCopies();

  EXPECT_FALSE(b.addCopies(-1));
  EXPECT_EQ(b.getTotalCopies(), totalBefore);
  EXPECT_EQ(b.getAvailableCopies(), availableBefore);

  // Те саме для lend() на порожньому available_
  Book empty("Порожня", "Автор", "9789660335809", 2000, 1);
  EXPECT_TRUE(empty.lend());              // видалили єдиний
  EXPECT_FALSE(empty.lend());             // немає що видавати
  EXPECT_EQ(empty.getAvailableCopies(), 0);
}

// ─────────────────────────────────────────────────────────────
// 4. Видача останнього примірника
//    lend() на книзі з 1 примірником → true, available стає 0
// ─────────────────────────────────────────────────────────────
TEST(BookTest, LendLastCopy) {
  Book b("Кобзар", "Тарас Шевченко", "9789660335809", 1840, 1);

  EXPECT_TRUE(b.lend());
  EXPECT_EQ(b.getAvailableCopies(), 0);
  EXPECT_EQ(b.lentOut(), 1);
  EXPECT_FALSE(b.isAvailable());
}

// ─────────────────────────────────────────────────────────────
// 5. Спроба видати книжку, якої немає
//    lend() при available_ == 0 → false, стан не змінюється
// ─────────────────────────────────────────────────────────────
TEST(BookTest, LendUnavailableBook) {
  Book b("Кобзар", "Тарас Шевченко", "9789660335809", 1840, 1);

  EXPECT_TRUE(b.lend());            // видалили єдиний примірник
  EXPECT_FALSE(b.lend());           // немає що видавати
  EXPECT_EQ(b.getAvailableCopies(), 0);
  EXPECT_EQ(b.lentOut(), 1);
}

// ─────────────────────────────────────────────────────────────
// 6. Повернення понад наявну кількість
//    returnCopy() при available_ == totalCopies_ → false
// ─────────────────────────────────────────────────────────────
TEST(BookTest, ReturnMoreThanPossible) {
  Book b("Кобзар", "Тарас Шевченко", "9789660335809", 1840, 3);

  EXPECT_TRUE(b.lend());            // available: 3 → 2
  EXPECT_TRUE(b.returnCopy());      // available: 2 → 3
  EXPECT_FALSE(b.returnCopy());     // available вже == totalCopies_ → відмова
  EXPECT_EQ(b.getAvailableCopies(), 3);
  EXPECT_EQ(b.getTotalCopies(), 3);
}

// ─────────────────────────────────────────────────────────────
// 7. Перевірка обчислювальних методів
//    lentOut() та isAvailable() обчислюються з полів
// ─────────────────────────────────────────────────────────────
TEST(BookTest, ComputedMethods) {
  Book b("Кобзар", "Тарас Шевченко", "9789660335809", 1840, 3);

  EXPECT_EQ(b.lentOut(), 0);
  EXPECT_TRUE(b.isAvailable());

  b.lend();
  b.lend();
  EXPECT_EQ(b.lentOut(), 2);
  EXPECT_EQ(b.getAvailableCopies(), 1);
  EXPECT_TRUE(b.isAvailable());

  b.lend();
  EXPECT_EQ(b.lentOut(), 3);
  EXPECT_FALSE(b.isAvailable());
}

// ─────────────────────────────────────────────────────────────
// 8. Інваріант зберігається після будь-якої послідовності операцій
// ─────────────────────────────────────────────────────────────
TEST(BookTest, InvariantHoldsAfterOperations) {
  Book b("Кобзар", "Тарас Шевченко", "9789660335809", 1840, 2);

  b.lend();
  b.returnCopy();
  b.addCopies(1);
  b.lend();
  b.lend();
  b.lend();          // третій lend() має бути відхилений
  b.addCopies(0);    // відхилено
  b.addCopies(-5);   // відхилено

  EXPECT_TRUE(b.checkInvariant());
}
