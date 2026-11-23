#pragma once

#include <string>

// Базовий клас для всіх одиниць фонду бібліотеки.
// Містить лише спільні поля: інвентарний ідентифікатор, назву, рік.
class LibraryItem {
public:
    virtual ~LibraryItem() = default;

    // Константні геттери (доступ для похідних і зовнішнього коду).
    const std::string& getInventoryId() const { return inventoryId_; }
    const std::string& getTitle() const       { return title_; }
    int getYear() const                       { return year_; }

protected:
    // Захищений конструктор: доступний лише похідним класам.
    LibraryItem(std::string inventoryId, std::string title, int year);

private:
    std::string inventoryId_;
    std::string title_;
    int year_ = 0;
};