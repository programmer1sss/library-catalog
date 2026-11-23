#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "LibraryItem.h"

class Library {
public:
    Library() = default;

    void addItem(std::unique_ptr<LibraryItem> item) {
        items_.push_back(std::move(item));
    }

    std::size_t size() const { return items_.size(); }
    LibraryItem&       at(std::size_t i)       { return *items_.at(i); }
    const LibraryItem& at(std::size_t i) const { return *items_.at(i); }

    const std::vector<std::unique_ptr<LibraryItem>>& items() const { return items_; }

    void save(std::ostream& os) const;
    void load(std::istream& is);

private:
    std::vector<std::unique_ptr<LibraryItem>> items_;
};