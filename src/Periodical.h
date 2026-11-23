#pragma once

#include <string>
#include <iostream>
#include "LibraryItem.h"

// Журнал / періодичне видання. Спадкоємець LibraryItem.
// Додає власні поля: номер випуску та періодичність.
class Periodical final : public LibraryItem {
public:
    Periodical(std::string inventoryId,
               std::string title,
               int year,
               int issueNumber,
               std::string frequency);
    ~Periodical() override = default;

    // Специфічні геттери
    int getIssueNumber() const { return issueNumber_; }
    const std::string& getFrequency() const { return frequency_; }

    // Специфічний метод
    bool isMonthly() const { return frequency_ == "щомісячно"; }

private:
    int issueNumber_ = 0;
    std::string frequency_;   // напр. "щомісячно", "щотижня", "щокварталу"
};

// ── Виведення / введення ──
std::ostream& operator<<(std::ostream& os, const Periodical& p);
std::istream& operator>>(std::istream& is, Periodical& p);