#pragma once

#include <string>
#include <memory>
#include <iostream>
#include "LibraryItem.h"
#include "Reader.h"

// Видача — НЕ одиниця фонду. Правильне рішення — КОМПОЗИЦІЯ:
// Loan МАЄ У СКЛАДІ:
//   - ідентифікатор читача (за карткою),
//   - вказівник на одиницю фонду (не володіє нею — unique_ptr тут не потрібен,
//     бо фонд належить Library; Loan лише спостерігає),
//   - дату видачі та дату повернення.
//
// Успадкування Loan : LibraryItem було б хибним, бо «видача Є одиницею фонду»
// — нонсенс. Видача — це подія/транзакція, яка ВІДНОСИТЬСЯ до одиниці фонду.
class Loan {
public:
    Loan() = default;

    // item НЕ owned — Loan лише зберігає спостережувач (raw pointer).
    Loan(std::string readerCard,
         const LibraryItem* item,
         std::string issueDate,
         std::string returnDate);

    const std::string& getReaderCard() const  { return readerCard_; }
    const LibraryItem* getItem() const        { return item_; }
    const std::string& getIssueDate() const   { return issueDate_; }
    const std::string& getReturnDate() const  { return returnDate_; }

    void setReturnDate(std::string d) { returnDate_ = std::move(d); }

    bool isReturned() const { return !returnDate_.empty(); }

private:
    std::string readerCard_;
    const LibraryItem* item_ = nullptr;
    std::string issueDate_;
    std::string returnDate_;
};

std::ostream& operator<<(std::ostream& os, const Loan& l);