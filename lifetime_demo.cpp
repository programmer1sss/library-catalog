#include <iostream>
#include <memory>
#include <vector>
#include "book.h"

// Статичний об'єкт: ctor — до main, dtor — після main.
static Book gStatic{"Статичний", 1900};

int main() {
    std::clog << "--- початок main ---\n";

    Book onStack{"Автоматичний", 2020};   // ctor тут, dtor — в кінці main (LIFO з onStack)

    {
        Book inner{"Вкладений", 2021};    // ctor тут, dtor — на закритті }
    }

    Book* leaked = new Book{"Забутий", 2022};   // ctor є, dtor — НЕ буде (витік)
    (void)leaked;                                // щоб -Wunused-variable не сварився

    auto owned = std::make_unique<Book>("Керований", 2023);   // ctor, dtor — в кінці main

    std::vector<Book> shelf;
    shelf.reserve(2);
    shelf.emplace_back("У векторі", 2024);     // ctor у сховищі vector, dtor — при знищенні shelf

    std::clog << "--- кінець main ---\n";
    return 0;
}