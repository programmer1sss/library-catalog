#pragma once

#include <string>
#include <iostream>
#include "LibraryItem.h"

// Газета — ще один спадкоємець LibraryItem.
// Додає власні поля: дата випуску (рядок) та кількість сторінок.
class Newspaper final : public LibraryItem {
public:
    Newspaper(std::string inventoryId,
              std::string title,
              int year,
              std::string issueDate,
              int pageCount);
    ~Newspaper() override = default;

    const std::string& getIssueDate() const { return issueDate_; }
    int getPageCount() const { return pageCount_; }

    // Специфічний метод
    bool isThick() const { return pageCount_ >= 20; }

private:
    std::string issueDate_;   // напр. "2024-05-15"
    int pageCount_ = 0;
};

std::ostream& operator<<(std::ostream& os, const Newspaper& n);
std::istream& operator>>(std::istream& is, Newspaper& n);