#include <iostream>
#include "book.h"

int main() {
    {
        Book b("INV-001", "1984", "George Orwell", "9780451524935", 1949, 3);
        (void)b;
    } // ← тут b знищується

    std::cout << "--- кінець області ---\n";
    return 0;
}