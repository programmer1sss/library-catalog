#pragma once

#include <string>

class LibraryItem {
public:
    virtual ~LibraryItem() = default;   // ← обов'язково virtual (для експерименту тимчасово прибирали)

    const std::string& getInventoryId() const { return inventoryId_; }
    const std::string& getTitle() const       { return title_; }
    int getYear() const                       { return year_; }

protected:
    LibraryItem(std::string inventoryId, std::string title, int year);

private:
    std::string inventoryId_;
    std::string title_;
    int year_ = 0;
};