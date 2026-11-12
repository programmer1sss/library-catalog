#pragma once

#include <cstddef>
#include <string>

class TagList
{
public:
    TagList() = default;
    explicit TagList(std::size_t capacity);
    ~TagList();  

    void add(const std::string &tag);

    std::size_t size() const { return size_; }

private:
    std::string *items_ = nullptr; // власний блок пам'яті
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};