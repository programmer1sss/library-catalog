#pragma once

#include <cstddef>
#include <string>

class TagList {
public:
    TagList() = default;
    explicit TagList(std::size_t capacity);
    ~TagList();

    TagList(const TagList& other);                  // copy ctor (крок 3)
    TagList& operator=(TagList other);              // copy-and-swap (крок 4)

    TagList(TagList&& other) noexcept;              // ← move ctor
    TagList& operator=(TagList&& other) noexcept;   // ← move assign

    void add(const std::string& tag);
    std::size_t size() const { return size_; }
    const std::string& at(std::size_t i) const { return items_[i]; }

    // ── Лічильники (для звіту) ──
    static std::size_t copies() { return copies_; }
    static std::size_t moves()  { return moves_; }
    static void resetCounters() { copies_ = 0; moves_ = 0; }

private:
    std::string* items_ = nullptr;
    std::size_t  size_ = 0;
    std::size_t  capacity_ = 0;

    static std::size_t copies_;
    static std::size_t moves_;

    friend void swap(TagList& a, TagList& b) noexcept;
};