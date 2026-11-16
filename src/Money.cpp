#include "Money.h"
#include <iomanip>
#include <string>

Money::Money(long long hryvnias, int kopecks)
    : cents_(hryvnias * 100 + kopecks) {}

long long Money::hryvnias() const { return cents_ / 100; }
int Money::kopecks() const { return static_cast<int>(cents_ % 100); }
long long Money::totalCents() const { return cents_; }

Money& Money::operator+=(const Money& other) { cents_ += other.cents_; return *this; }
Money& Money::operator-=(const Money& other) { cents_ -= other.cents_; return *this; }
Money& Money::operator*=(int factor) { cents_ *= factor; return *this; }

Money Money::operator-() const {
    Money result = *this;
    result *= -1;
    return result;
}

Money operator+(Money lhs, const Money& rhs) { lhs += rhs; return lhs; }
Money operator-(Money lhs, const Money& rhs) { lhs -= rhs; return lhs; }
Money operator*(Money lhs, int factor) { lhs *= factor; return lhs; }
Money operator*(int factor, Money rhs) { rhs *= factor; return rhs; }

bool operator==(const Money& lhs, const Money& rhs) {
    return lhs.totalCents() == rhs.totalCents();
}

bool operator<(const Money& lhs, const Money& rhs) {
    return lhs.totalCents() < rhs.totalCents();
}

std::ostream& operator<<(std::ostream& os, const Money& m) {
    const auto saved = os.flags();
    
    if (m.totalCents() < 0) {
        os << '-';
    }
    
    long long absCents = m.totalCents();
    if (absCents < 0) absCents = -absCents;
    
    long long hryv = absCents / 100;
    int kop = static_cast<int>(absCents % 100);

    os << hryv << '.' << std::setw(2) << std::setfill('0') << kop;
    
    os.flags(saved);
    return os;
}

std::istream& operator>>(std::istream& is, Money& m) {
    std::string s;
    if (!(is >> s)) {
        return is;
    }

    bool negative = false;
    std::size_t pos = 0;
    if (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) {
        negative = (s[pos] == '-');
        ++pos;
    }

    std::size_t dotPos = s.find('.', pos);
    std::string hryvPart;
    std::string kopPart;

    if (dotPos == std::string::npos) {
        hryvPart = s.substr(pos);
        kopPart  = "0";
    } else {
        hryvPart = s.substr(pos, dotPos - pos);
        kopPart  = s.substr(dotPos + 1);
    }

    auto allDigits = [](const std::string& str) {
        if (str.empty()) return false;
        for (char c : str) {
            if (c < '0' || c > '9') return false;
        }
        return true;
    };

    if (!allDigits(hryvPart) || (dotPos != std::string::npos && !allDigits(kopPart))) {
        is.setstate(std::ios::failbit);
        return is;
    }

    long long hryv = 0;
    for (char c : hryvPart) hryv = hryv * 10 + (c - '0');

    int kop = 0;
    if (dotPos != std::string::npos) {
        if (kopPart.size() > 2) {
            is.setstate(std::ios::failbit);
            return is;
        }
        while (kopPart.size() < 2) kopPart += '0';
        kop = (kopPart[0] - '0') * 10 + (kopPart[1] - '0');
    }

    long long total = hryv * 100 + kop;
    if (negative) total = -total;

    m = Money(total / 100, static_cast<int>(total % 100));
    return is;
}