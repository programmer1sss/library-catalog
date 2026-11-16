#include "Money.h"

// Конструктор
Money::Money(long long hryvnias, int kopecks)
    : cents_(hryvnias * 100 + kopecks)
{
}

// Геттери
long long Money::hryvnias() const {
    return cents_ / 100;
}

int Money::kopecks() const {
    return static_cast<int>(cents_ % 100);
}

long long Money::totalCents() const {
    return cents_;
}

// ── Складені присвоєння (містять усю логіку) ──
Money& Money::operator+=(const Money& other) {
    cents_ += other.cents_;
    return *this;
}

Money& Money::operator-=(const Money& other) {
    cents_ -= other.cents_;
    return *this;
}

Money& Money::operator*=(int factor) {
    cents_ *= factor;
    return *this;
}

// ── Унарний мінус ──
Money Money::operator-() const {
    // Створюємо копію, змінюємо знак через *= -1
    Money result = *this;
    result *= -1;
    return result;
}

// ── Вільні оператори (канонічна пара: копія -> += -> return) ──
Money operator+(Money lhs, const Money& rhs) {
    lhs += rhs;
    return lhs;
}

Money operator-(Money lhs, const Money& rhs) {
    lhs -= rhs;
    return lhs;
}

Money operator*(Money lhs, int factor) {
    lhs *= factor;
    return lhs;
}

Money operator*(int factor, Money rhs) {
    rhs *= factor;
    return rhs;
}