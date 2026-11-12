#include <iostream>
#include <cassert>
#include "library.h"

int main() {
    std::cout << "Library demo (крок 6: Rule of Zero з TagList у Book)\n\n";

    Library original;
    {
        Book b1("1984", "George Orwell", "9780451524935", 1949, 3);
        b1.addTag("dystopia");
        b1.addTag("classic");
        original.addBook(std::move(b1));

        Book b2("The Hobbit", "J.R.R. Tolkien", "9780547928227", 1937, 2);
        b2.addTag("fantasy");
        original.addBook(std::move(b2));

        Book b3("Clean Code", "Robert C. Martin", "9780132350884", 2008, 1);
        b3.addTag("programming");
        original.addBook(std::move(b3));
    }
    std::cout << "original.size = " << original.size() << '\n';

    Library copy = original;
    std::cout << "copy.size     = " << copy.size()     << '\n';

    assert(copy.size() == original.size());
    assert(copy.at(0).getTags().size() == 2);
    assert(copy.at(0).getTags().at(0) == "dystopia");
    assert(copy.at(0).getTags().at(1) == "classic");

    original.at(0).addTag("new-tag-for-original");

    std::cout << "\nПісля original.at(0).addTag(...):\n";
    std::cout << "  original[0].tags.size = " << original.at(0).getTags().size() << '\n';
    std::cout << "  copy[0].tags.size     = " << copy.at(0).getTags().size()     << '\n';

    assert(original.at(0).getTags().size() == 3);
    assert(copy.at(0).getTags().size()     == 2);
    assert(copy.at(0).getTags().at(0) == "dystopia");

    std::cout << "\nКопія незалежна від оригіналу. ASan має мовчати.\n";
    return 0;
}