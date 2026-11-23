#pragma once

#include <string>
#include <iostream>

// Читач — НЕ одиниця фонду. Не входить в ієрархію LibraryItem.
// Це самостійна сутність, яка бере участь у видачах (через Loan).
class Reader {
public:
    Reader() = default;
    Reader(std::string cardNumber, std::string fullName);

    const std::string& getCardNumber() const { return cardNumber_; }
    const std::string& getFullName() const   { return fullName_; }

private:
    std::string cardNumber_;
    std::string fullName_;
};

std::ostream& operator<<(std::ostream& os, const Reader& r);
std::istream& operator>>(std::istream& is, Reader& r);