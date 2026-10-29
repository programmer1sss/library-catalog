#include <iostream>
#include "book.h"

int main() {
    std::cout << "== useful output ==\n";
    {
        Book b{"Test"};
        std::cout << "title: " << b.getTitle() << '\n';
    }
    std::cout << "== done ==\n";
}