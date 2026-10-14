#pragma once

#include <string>

class Book {
 public:
  // Конструктор приймає всі значущі поля
  Book(const std::string& title,
       const std::string& author,
       const std::string& isbn,
       int year,
       int totalCopies);

  // Константні гетери — використовують приватні поля
  const std::string& getTitle() const;
  const std::string& getAuthor() const;
  const std::string& getIsbn() const;
  int getYear() const;
  int getTotalCopies() const;
  int getAvailableCopies() const;

  // Похідні величини — обчислюються, не зберігаються
  int lentOut() const;
  bool isAvailable() const;
  bool isOlderThan(int year) const;

  // Методи обліку — змінюють стан
  void lend();
  void returnCopy();

 private:
  std::string title_;
  std::string author_;
  std::string isbn_;
  int year_ = 1450;
  int totalCopies_ = 0;
  int available_ = 0;
};
