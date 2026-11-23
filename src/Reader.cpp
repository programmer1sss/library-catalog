#include "Reader.h"
#include <iomanip>
#include <stdexcept>
#include <utility>

Reader::Reader(std::string cardNumber, std::string fullName)
    : cardNumber_(std::move(cardNumber)),
      fullName_(std::move(fullName))
{
    if (cardNumber_.empty())
        throw std::invalid_argument("Reader: empty card number");
    if (fullName_.empty())
        throw std::invalid_argument("Reader: empty full name");
}

std::ostream& operator<<(std::ostream& os, const Reader& r) {
    const auto saved = os.flags();
    os << r.getCardNumber() << ' ' << std::quoted(r.getFullName());
    os.flags(saved);
    return os;
}

std::istream& operator>>(std::istream& is, Reader& r) {
    std::string card, name;
    if (!(is >> card)) return is;
    if (!(is >> std::quoted(name))) return is;
    if (card.empty() || name.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }
    r = Reader(card, name);
    return is;
}