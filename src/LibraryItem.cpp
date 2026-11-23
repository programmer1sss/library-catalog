#include "LibraryItem.h"
#include <iostream>
#include <stdexcept>
#include <utility>

LibraryItem::LibraryItem(std::string inventoryId, std::string title, int year)
    : inventoryId_(std::move(inventoryId)),
      title_(std::move(title)),
      year_(year)
{
    std::cout << "LibraryItem ctor\n";     // ← ТИМЧАСОВО

    if (inventoryId_.empty())
        throw std::invalid_argument("LibraryItem: empty inventory id");
    if (title_.empty())
        throw std::invalid_argument("LibraryItem: empty title");
    if (year_ < 1450 || year_ > 2026)
        throw std::out_of_range("LibraryItem: year out of range [1450, 2026]");
}