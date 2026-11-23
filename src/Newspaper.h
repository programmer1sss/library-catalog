#pragma once

#include <string>
#include <iostream>
#include "LibraryItem.h"

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

    bool isThick() const { return pageCount_ >= 20; }

private:
    std::string issueDate_;
    int pageCount_ = 0;
};

std::ostream& operator<<(std::ostream& os, const Newspaper& n);
std::istream& operator>>(std::istream& is, Newspaper& n);