#include "TagList.h"

#include <stdexcept>
#include <utility>   // std::swap, std::move

// ── Визначення статичних лічильників ──
std::size_t TagList::copies_ = 0;
std::size_t TagList::moves_  = 0;

TagList::TagList(std::size_t capacity)
    : items_(capacity > 0 ? new std::string[capacity] : nullptr),
      size_(0),
      capacity_(capacity)
{
}

TagList::TagList(const TagList& other)
    : items_(other.capacity_ > 0 ? new std::string[other.capacity_] : nullptr),
      size_(other.size_),
      capacity_(other.capacity_)
{
    for (std::size_t i = 0; i < size_; ++i) {
        items_[i] = other.items_[i];
    }
    ++copies_;                                     // ← лічильник копій
}

TagList::TagList(TagList&& other) noexcept
    : items_(other.items_),
      size_(other.size_),
      capacity_(other.capacity_)
{
    other.items_    = nullptr;                     // ← обнуляємо джерело
    other.size_     = 0;
    other.capacity_ = 0;
    ++moves_;                                      // ← лічильник переміщень
}

TagList& TagList::operator=(TagList other) {       // copy-and-swap (крок 4)
    swap(*this, other);
    return *this;
}

TagList& TagList::operator=(TagList&& other) noexcept {
    if (this != &other) {
        delete[] items_;                           // звільняємо СВІЙ блок
        items_    = other.items_;                  // забираємо блок джерела
        size_     = other.size_;
        capacity_ = other.capacity_;

        other.items_    = nullptr;                 // ← обнуляємо джерело
        other.size_     = 0;
        other.capacity_ = 0;
        ++moves_;                                  // ← лічильник переміщень
    }
    return *this;
}

TagList::~TagList() {
    delete[] items_;
}

void swap(TagList& a, TagList& b) noexcept {
    using std::swap;
    swap(a.items_,    b.items_);
    swap(a.size_,     b.size_);
    swap(a.capacity_, b.capacity_);
}

void TagList::add(const std::string& tag) {
    if (size_ >= capacity_)
        throw std::out_of_range("TagList: capacity exceeded");
    items_[size_] = tag;
    ++size_;
}