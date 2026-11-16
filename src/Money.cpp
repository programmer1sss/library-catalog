#include "Money.h"

// Ініціалізуємо cents_, перетворюючи гривні в копійки та додаючи копійки
Money::Money(long long hryvnias, int kopecks)
    : cents_(hryvnias * 100 + kopecks)
{
}

// Повертає цілу частину в гривнях
long long Money::hryvnias() const {
    return cents_ / 100;
}

// Повертає залишок у копійках (0..99)
int Money::kopecks() const {
    return static_cast<int>(cents_ % 100);
}

// Повертає загальну суму в копійках
long long Money::totalCents() const {
    return cents_;
}