#pragma once

#include <string>

// Інваріант Book:
//  1. title_ не порожній;
//  2. рік у діапазоні [1450, 2026];
//  3. isbn_ порожній або містить рівно 13 цифр;
//  4. totalCopies_ >= 0;
//  5. 0 <= available_ <= totalCopies_.
class Book {
 public:
  Book(const std::string title,
       const std::string author,
       const std::string isbn,
       int year,
       int totalCopies);

  // --- Константні гетери ---
  const std::string& getTitle() const;
  const std::string& getAuthor() const;
  const std::string& getIsbn() const;
  int getYear() const;
  int getTotalCopies() const;
  int getAvailableCopies() const;

  // --- Обчислювальні методи ---
  int lentOut() const;
  bool isAvailable() const;
  bool isOlderThan(int year) const;

  // --- Операції предметної області (замість сетерів) ---
  // Кожна повертає true, якщо операція виконана, і false, якщо її відхилено.
  bool lend();               // видати один примірник
  bool returnCopy();         // повернути один примірник
  bool addCopies(int n);     // додати n примірників

  // --- Перевірка інваріанта ---
  bool checkInvariant() const;

 private:
  std::string title_;
  std::string author_;
  std::string isbn_;
  int year_ = 1450;
  int totalCopies_ = 0;
  int available_ = 0;

  static bool isValidIsbn(const std::string& isbn);
};
