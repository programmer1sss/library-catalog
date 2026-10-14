#pragma once

#include <string>

class Book
{
private:
    std::string title;
    std::string author;
    int year;
    int pages;

public:
    Book(const std::string &title,
         const std::string &author,
         int year,
         int pages);

    const std::string &getTitle() const;
    const std::string &getAuthor() const;
    int getYear() const;
    int getPages() const;

    bool isOlderThan(int year) const;
};
