#include "TagList.h"

#include <stdexcept>
#include <utility>

TagList::TagList(std::size_t capacity)
    : items_(capacity > 0 ? new std::string[capacity] : nullptr),
    size_(0),
    capacity_(capacity)
{
}

TagList::~TagList() {          
    delete[] items_;
}

void TagList::add(const std::string &tag)
{
    if (size_ >= capacity_)
    {
        throw std::out_of_range("TagList: capacity exceeded");
    }
    items_[size_] = tag;
    ++size_;
}