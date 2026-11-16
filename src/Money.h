#pragma once

#include <cstddef>
#include <iostream> // Для std::ostream

class Money {
public:
    Money() = default;
    Money(long long hryvnias, int kopecks);

    long long hryvnias() const;
    int kopecks() const;
    long long totalCents() const;

    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);
    Money& operator*=(int factor);
    Money operator-() const;

private:
    long long cents_ = 0;
};

// ── Арифметика ──
Money operator+(Money lhs, const Money& rhs);
Money operator-(Money lhs, const Money& rhs);
Money operator*(Money lhs, int factor);
Money operator*(int factor, Money rhs);

// ── Порівняння ──
bool operator==(const Money& lhs, const Money& rhs);
bool operator<(const Money& lhs, const Money& rhs);

inline bool operator!=(const Money& lhs, const Money& rhs) { return !(lhs == rhs); }
inline bool operator>(const Money& lhs, const Money& rhs)  { return rhs < lhs; }
inline bool operator<=(const Money& lhs, const Money& rhs) { return !(rhs < lhs); }
inline bool operator>=(const Money& lhs, const Money& rhs) { return !(lhs < rhs); }

// ── Виведення в потік ──
std::ostream& operator<<(std::ostream& os, const Money& m);