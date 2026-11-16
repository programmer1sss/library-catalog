#pragma once

#include <cstddef>

// Клас для представлення грошової суми.
// Зберігає суму в найменших одиницях (копійках) у полі cents_.
class Money {
public:
    // Конструктор за замовчуванням (0 грн 0 коп)
    Money() = default;

    // Конструктор від гривень і копійок.
    // Наприклад: Money(12, 50) означає 12 грн 50 коп.
    Money(long long hryvnias, int kopecks);

    // Константні геттери
    long long hryvnias() const;
    int kopecks() const;
    long long totalCents() const;

private:
    long long cents_ = 0; // Сума в копійках
};