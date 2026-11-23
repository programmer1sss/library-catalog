#pragma once

#include <string>
#include <iostream>

class LibraryItem {
public:
    virtual ~LibraryItem() = default;

    const std::string& getInventoryId() const { return inventoryId_; }
    const std::string& getTitle() const       { return title_; }
    int getYear() const                       { return year_; }

    // ── Дві перевантажені версії describe ──
    void describe() const {
        std::cout << "Одиниця фонду: " << title_
                  << " (ID: " << inventoryId_
                  << ", рік: " << year_ << ")\n";
    }

    void describe(int width) const {
        std::cout << "Одиниця фонду (ширина " << width << "): "
                  << title_ << " [" << inventoryId_ << "]\n";
    }

protected:
    LibraryItem(std::string inventoryId, std::string title, int year);

private:
    std::string inventoryId_;
    std::string title_;
    int year_ = 0;
};