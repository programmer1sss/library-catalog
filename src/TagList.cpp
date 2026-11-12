#include "TagList.h"

#include <stdexcept>
#include <utility>   // std::swap, std::move

// ── Ініціалізація статичних лічильників ──
std::size_t TagList::copies_ = 0;
std::size_t TagList::moves_  = 0;

// ── Конструктор з виділенням пам'яті ──
TagList::TagList(std::size_t capacity)
    : items_(capacity > 0 ? new std::string[capacity] : nullptr),
      size_(0),
      capacity_(capacity)
{
}

// ── Деструктор (Крок 2) ──
// Звільняє сирий масив. Без нього ASan повідомляв про витік.
TagList::~TagList() {
    delete[] items_;
}

// ── Конструктор копіювання (Крок 3) ──
// Глибока копія: виділяємо свій блок і копіюємо size_ елементів.
TagList::TagList(const TagList& other)
    : items_(other.capacity_ > 0 ? new std::string[other.capacity_] : nullptr),
      size_(other.size_),
      capacity_(other.capacity_)
{
    for (std::size_t i = 0; i < size_; ++i) {
        items_[i] = other.items_[i];
    }
    ++copies_;  // збільшуємо лічильник копій
}

// ── Оператор присвоєння копіюванням (Крок 4) ──
// Використовує ідіому copy-and-swap (але з явним виділенням і копіюванням).
TagList& TagList::operator=(const TagList& other) {
    if (this == &other) return *this;  // самоприсвоєння (a = a)

    // 1. Виділяємо новий блок (strong exception guarantee)
    std::string* newItems = (other.capacity_ > 0)
                            ? new std::string[other.capacity_]
                            : nullptr;

    // 2. Копіюємо елементи
    for (std::size_t i = 0; i < other.size_; ++i) {
        newItems[i] = other.items_[i];
    }

    // 3. Звільняємо старий блок і забираємо новий
    delete[] items_;
    items_    = newItems;
    size_     = other.size_;
    capacity_ = other.capacity_;

    ++copies_;  // збільшуємо лічильник копій
    return *this;
}

// ── Конструктор переміщення (Крок 5) ──
// Забирає ресурси джерела і обнуляє його поля.
TagList::TagList(TagList&& other) noexcept
    : items_(other.items_),
      size_(other.size_),
      capacity_(other.capacity_)
{
    other.items_    = nullptr;
    other.size_     = 0;
    other.capacity_ = 0;
    ++moves_;  // збільшуємо лічильник переміщень
}

// ── Оператор присвоєння переміщенням (Крок 5) ──
// Звільняє власний блок, забирає блок джерела, обнуляє джерело.
TagList& TagList::operator=(TagList&& other) noexcept {
    if (this != &other) {
        delete[] items_;  // звільняємо свій старий блок
        items_    = other.items_;
        size_     = other.size_;
        capacity_ = other.capacity_;

        other.items_    = nullptr;
        other.size_     = 0;
        other.capacity_ = 0;

        ++moves_;  // збільшуємо лічильник переміщень
    }
    return *this;
}

// ── Вільна функція swap ──
// Дозволяє ефективно міняти вміст двох об'єктів (використовується в std::swap).
void swap(TagList& a, TagList& b) noexcept {
    using std::swap;
    swap(a.items_,    b.items_);
    swap(a.size_,     b.size_);
    swap(a.capacity_, b.capacity_);
}

// ── Додавання елемента ──
void TagList::add(const std::string& tag) {
    if (size_ >= capacity_)
        throw std::out_of_range("TagList: capacity exceeded");
    items_[size_] = tag;
    ++size_;
}
