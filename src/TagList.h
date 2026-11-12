#pragma once

#include <cstddef>
#include <string>

class TagList
{
public:
    TagList() = default;
    explicit TagList(std::size_t capacity);
    ~TagList();  

    TagList(const TagList& other);            
    TagList& operator=(const TagList&) = delete;  

    void add(const std::string &tag);
    std::size_t size() const { return size_; }

    const std::string& at(std::size_t i) const { return items_[i]; }


private:
    std::string *items_ = nullptr; // власний блок пам'яті
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};