#include <iostream>
#include <vector>
#include <cassert>
#include "TagList.h"

void printTags(TagList copy) {
    std::cout << "printTags: size = " << copy.size() << '\n';
}

int main() {
    std::cout << "TagList demo (кроки 1-4)\n\n";

    {
        std::cout << "--- Сценарій 1: a = b (звичайне) ---\n";
        TagList a(4), b(4);
        a.add("alpha");
        b.add("beta");
        b.add("gamma");
        std::cout << "до:   a.size=" << a.size() << "  b.size=" << b.size() << '\n';
        a = b;
        std::cout << "після: a.size=" << a.size() << "  b.size=" << b.size() << '\n';
        assert(a.size() == 2);
        assert(a.at(0) == "beta");
        assert(b.size() == 2);
        std::cout << '\n';
    }

    {
        std::cout << "--- Сценарій 2: empty = full ---\n";
        TagList empty;
        TagList full(4);
        full.add("one");
        full.add("two");
        std::cout << "до:   empty.size=" << empty.size() << "  full.size=" << full.size() << '\n';
        empty = full;
        std::cout << "після: empty.size=" << empty.size() << "  full.size=" << full.size() << '\n';
        assert(empty.size() == 2);
        assert(empty.at(0) == "one");
        std::cout << '\n';
    }

    {
        std::cout << "--- Сценарій 3: a = a (самоприсвоєння) ---\n";
        TagList a(4);
        a.add("x");
        a.add("y");
        a.add("z");
        const std::size_t before = a.size();
        std::cout << "до:   a.size=" << before << '\n';
        
        TagList& alias = a; 
        a = alias;
        
        std::cout << "після: a.size=" << a.size() << '\n';
        assert(a.size() == before);
        assert(a.at(0) == "x");
        std::cout << '\n';
    }

    std::cout << "Готово: ASan має мовчати.\n";
    return 0;
}