#pragma once

#include <cstddef>
#include <string>

// Клас-власник сирого масиву std::string*.
// Демонструє Rule of Five (правило п'яти) та copy-and-swap / copy-and-move.
class TagList {
public:
    // ── Конструктори та деструктор ──
    TagList() = default;
    explicit TagList(std::size_t capacity);
    ~TagList();

    // ── Копіювання (Rule of Three) ──
    // Крок 3: глибока копія.
    TagList(const TagList& other);
    // Крок 4 (адаптовано): явне присвоєння копіюванням.
    // ВАЖЛИВО: раніше тут було operator=(TagList other) (copy-and-swap).
    // Але компілятор не може однозначно вибрати між by-value та move-версією
    // при виклику b = std::move(a). Тому ми розділили їх на const& та &&.
    TagList& operator=(const TagList& other);

    // ── Переміщення (Rule of Five, Крок 5) ──
    // Обидва методи позначені noexcept, щоб std::vector при реаллокації
    // використовував переміщення, а не копіювання.
    TagList(TagList&& other) noexcept;
    TagList& operator=(TagList&& other) noexcept;

    // ── Основні операції ──
    void add(const std::string& tag);
    std::size_t size() const { return size_; }
    const std::string& at(std::size_t i) const { return items_[i]; }

    // ── Лічильники для Кроку 5 ──
    // Дозволяють перевірити, скільки разів вектор робив копію, а скільки — переміщення.
    static std::size_t copies() { return copies_; }
    static std::size_t moves()  { return moves_; }
    static void resetCounters() { copies_ = 0; moves_ = 0; }

private:
    std::string* items_ = nullptr;  // сирий вказівник на масив (власність)
    std::size_t  size_ = 0;         // скільки елементів заповнено
    std::size_t  capacity_ = 0;     // скільки всього виділено

    // Статичні лічильники (визначені в .cpp)
    static std::size_t copies_;
    static std::size_t moves_;

    // Дружня функція для обміну (використовується для std::swap / ADL)
    friend void swap(TagList& a, TagList& b) noexcept;
};
