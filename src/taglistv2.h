#pragma once

#include <string>
#include <utility>
#include <vector>

// Клас-власник на основі std::vector.
// Демонструє Rule of Zero: жодного спеціального члена не оголошено.
// Компілятор сам згенерує коректні копіювання, переміщення та деструктор.
class TagListV2 {
public:
    void add(std::string tag) { items_.push_back(std::move(tag)); }
    std::size_t size() const { return items_.size(); }
    const std::string& at(std::size_t i) const { return items_[i]; }

private:
    std::vector<std::string> items_;  // власник всередині
};