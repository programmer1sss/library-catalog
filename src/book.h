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
  Book(const std::string& title,
       const std::string& author,
       const std::string& isbn,
       int year,
       int totalCopies);

  // --- Константні методи доступу ---
  // Рядки повертаємо як const std::string& (без копіювання)
  const std::string& getTitle() const;
  const std::string& getAuthor() const;
  const std::string& getIsbn() const;

  // Числа повертаємо за значенням (дешево копіювати)
  int getYear() const;
  int getTotalCopies() const;
  int getAvailableCopies() const;

  // --- Обчислювальні методи (нічого не зберігають) ---
  int lentOut() const;            // totalCopies_ - available_
  bool isAvailable() const;       // available_ > 0
  bool isOlderThan(int year) const; // year_ < year

  // --- Методи, що змінюють стан ---
  void lend();
  void returnCopy();

  // Перевірка інваріанта
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
