#include "Money.h"
#include <iomanip> // Для std::setw, std::setfill

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

// ── Виведення в потік ──
std::ostream& operator<<(std::ostream& os, const Money& m) {
    // 1. Зберігаємо поточні прапорці потоку
    const auto saved = os.flags();
    
    // 2. Виводимо у форматі 123.45
    // Примітка: обробка від'ємних сум (наприклад, -12.50) вимагає уваги.
    // Якщо сума від'ємна, hryvnias() поверне -12, kopecks() поверне -50.
    // Стандартний вивід буде -12.-50, що некоректно.
    // Тому беремо абсолютне значення для копійок і додаємо мінус вручну.
    
    if (m.totalCents() < 0) {
        os << '-';
    }
    
    long long absCents = m.totalCents();
    if (absCents < 0) absCents = -absCents;
    
    long long hryv = absCents / 100;
    int kop = static_cast<int>(absCents % 100);

    os << hryv << '.' << std::setw(2) << std::setfill('0') << kop;
    
    // 3. Відновлюємо прапорці потоку
    os.flags(saved);
    
    return os;
}